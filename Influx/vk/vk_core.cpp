#include "vk_pch.hpp"
#include "vk_core.hpp"

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData)
{
#if !defined(NEO_CONFIG_DIST)
    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
        VK_ERROR_LOG("{}", pCallbackData->pMessage);
    else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        VK_WARN_LOG("{}", pCallbackData->pMessage);
    else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
        VK_INFO_LOG("{}", pCallbackData->pMessage);
#endif

    return VK_FALSE;
}

static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func)
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;

}
static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func)
        func(instance, debugMessenger, pAllocator);
}

namespace vk {
    static std::vector<const char*> extensions,
        validationLayers = { "VK_LAYER_KHRONOS_validation" },
        requiredDeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    static bool validationLayersSupported(void)
    {
        uint32_t layer_count;
        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

        std::vector<VkLayerProperties> available_layers(layer_count);
        vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

        for (const char* requested_layer : validationLayers)
        {
            bool found = false;

            for (const VkLayerProperties& available_layer : available_layers)
                if (!strcmp(requested_layer, available_layer.layerName))
                {
                    found = true;
                    break;
                }

            if (!found)
                return false;
        }

        return true;
    }

    static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* create_info)
    {
        create_info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        create_info->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        create_info->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        create_info->pfnUserCallback = debugCallback;
    }

    struct QueueFamilyIndices {
        uint32_t graphics = UINT32_MAX,
                 present  = UINT32_MAX;

        inline bool complete(void) const { return graphics != UINT32_MAX && present != UINT32_MAX ; }
    };
    static QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device)
    {
        uint32_t queue_family_count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

        VkQueueFamilyProperties* queue_families = new VkQueueFamilyProperties[queue_family_count];
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families);

        QueueFamilyIndices indices;
        for (uint32_t i = 0; i < queue_family_count; i++)
        {
            if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                indices.graphics = i;

            VkBool32 present_support = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, Core::m_InitSurface, &present_support);
            if (present_support)
                indices.present = i;

            if (indices.complete())
                break;
        }
        delete[] queue_families;

        return indices;
    }

    static bool areRequiredDeviceExtensionsSupported(VkPhysicalDevice device)
    {
        uint32_t available_extensions_count;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &available_extensions_count, nullptr);

        VkExtensionProperties* available_extensions = new VkExtensionProperties[available_extensions_count];
        vkEnumerateDeviceExtensionProperties(device, nullptr, &available_extensions_count, available_extensions);

        std::unordered_set<std::string> required_extensions(requiredDeviceExtensions.begin(), requiredDeviceExtensions.end());
        for (uint32_t i = 0; i < available_extensions_count; i++)
            required_extensions.erase(available_extensions[i].extensionName);

        delete[] available_extensions;
        return required_extensions.empty();
    }

    static int32_t ratePhysicalDevice(VkPhysicalDevice device)
    {
        if (!device)
            return 0;

        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        if (!deviceFeatures.geometryShader)
            return 0;

        if (!getQueueFamilies(device).complete())
            return 0;

        if (!areRequiredDeviceExtensionsSupported(device))
            return 0;

        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            deviceProperties.limits.maxImageDimension2D += 1000;

        return deviceProperties.limits.maxImageDimension2D;
    }

    void Core::InitializeGLFW(void)
    {
        glfwSetErrorCallback([](int error, const char* description)
        {
            VK_ERROR_LOG("GLFW Error#{}: {}", error, description);
            throw std::runtime_error(NEO_FORMAT("GLFW Error #{}", error));
        });
        NEO_ASSERT_FUNC(glfwInit(), "Failed to initialize glfw!");
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    }

    void Core::CreateInstance(void)
    {
        if (VALIDATION_LAYERS_ENABLED && !validationLayersSupported())
            throw std::runtime_error("Validation Layers requested, but not supported!");

        VkApplicationInfo app_info {};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pEngineName = "NeoInfused";

        VkInstanceCreateInfo create_info {};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;

        {
            uint32_t required_extension_count = 0;
            const char** required_extensions = glfwGetRequiredInstanceExtensions(&required_extension_count);
            extensions = std::vector<const char*>(required_extensions, required_extensions + required_extension_count);
        }
        VkDebugUtilsMessengerCreateInfoEXT debug_create_info{};
        if (VALIDATION_LAYERS_ENABLED)
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            create_info.enabledLayerCount = (uint32_t)validationLayers.size();
            create_info.ppEnabledLayerNames = &validationLayers[0];

            populateDebugMessengerCreateInfo(&debug_create_info);
            create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debug_create_info;
        } else
        {
            create_info.enabledLayerCount = 0;
        }
        create_info.enabledExtensionCount = (uint32_t)extensions.size();
        create_info.ppEnabledExtensionNames = &extensions[0];

        if (vkCreateInstance(&create_info, nullptr, &m_Instance) != VK_SUCCESS)
            throw std::runtime_error("failed to create instance!");
    }

    void Core::CreateDebugMessenger(void)
    {
        if (!VALIDATION_LAYERS_ENABLED)
            return;

        VkDebugUtilsMessengerCreateInfoEXT create_info{};
        populateDebugMessengerCreateInfo(&create_info);

        if (CreateDebugUtilsMessengerEXT(m_Instance, &create_info, nullptr, &m_DebugMessenger) != VK_SUCCESS)
            throw std::runtime_error("failed to set up debug messenger!");
    }

    void Core::CreateInitializationSurface(void)
    {
        GLFWwindow* init_window = glfwCreateWindow(1, 1, "", nullptr, nullptr);
        if (glfwCreateWindowSurface(m_Instance, init_window, nullptr, &m_InitSurface) != VK_SUCCESS)
            throw std::runtime_error("Failed to create Vulkan initialization surface!");
        glfwDestroyWindow(init_window);
    }

    void Core::PickPhysicalDevice(void)
    {
        uint32_t device_count;
        vkEnumeratePhysicalDevices(m_Instance, &device_count, nullptr);
        if (!device_count)
            throw std::runtime_error("No GPUs with Vulkan support!");

        VkPhysicalDevice* available_devices = new VkPhysicalDevice[device_count];
        vkEnumeratePhysicalDevices(m_Instance, &device_count, available_devices);

        int32_t high_score = 0;
        for (uint32_t i = 0; i < device_count; i++)
        {
            if (ratePhysicalDevice(available_devices[i]) > high_score)
            {
                high_score = ratePhysicalDevice(available_devices[i]);
                m_PhysicalDevice = available_devices[i];
            }
        }

        delete[] available_devices;

        if (!high_score)
            throw std::runtime_error("No suitable GPU found!");
    }

    static const float priorities[] = { 1.0f };
    static VkDeviceQueueCreateInfo createQueueCreateInfo(uint32_t index, uint32_t count = 1, const float* _priorities = priorities)
    {
        VkDeviceQueueCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        create_info.queueFamilyIndex = index;
        create_info.queueCount = count;
        create_info.pQueuePriorities = _priorities;
        return create_info;
    }

    void Core::CreateLogicalDevice(void)
    {
        QueueFamilyIndices indices = getQueueFamilies(m_PhysicalDevice);
        std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
        queue_create_infos.push_back(createQueueCreateInfo(indices.graphics));
        if (indices.graphics != indices.present)
            queue_create_infos.push_back(createQueueCreateInfo(indices.present));

        VkDeviceCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        create_info.pQueueCreateInfos = &queue_create_infos[0];
        create_info.queueCreateInfoCount = (uint32_t)queue_create_infos.size();

        VkPhysicalDeviceFeatures device_features = {};
        create_info.pEnabledFeatures = &device_features;

        create_info.enabledExtensionCount = (uint32_t)requiredDeviceExtensions.size();
        create_info.ppEnabledExtensionNames = &requiredDeviceExtensions[0];

        if (vkCreateDevice(m_PhysicalDevice, &create_info, nullptr, &m_LogicalDevice) != VK_SUCCESS)
            throw std::runtime_error("Failed to create logical device!");

        vkGetDeviceQueue(m_LogicalDevice, indices.graphics, 0, &m_GraphicsQueue);
        vkGetDeviceQueue(m_LogicalDevice, indices.present,  0, &m_PresentQueue);
    }
}
using namespace vk;

EXPORT_FN void InitAPI(void)
{
    Core::InitializeGLFW();
    Core::CreateInstance();
    Core::CreateDebugMessenger();
    Core::CreateInitializationSurface();
    Core::PickPhysicalDevice();
    Core::CreateLogicalDevice();
}

EXPORT_FN void ShutdownAPI(void)
{
    vkDestroyDevice(Core::m_LogicalDevice, nullptr);
    vkDestroySurfaceKHR(Core::m_Instance, Core::m_InitSurface, nullptr);
    if (Core::VALIDATION_LAYERS_ENABLED)
        DestroyDebugUtilsMessengerEXT(Core::m_Instance, Core::m_DebugMessenger, nullptr);
    vkDestroyInstance(Core::m_Instance, nullptr);
    glfwTerminate();
}
