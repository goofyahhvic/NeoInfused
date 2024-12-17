#include "vk_pch.hpp"
#include "vk_core.hpp"

#include "vk_swapchain-support.hpp"

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData)
{
#if !defined(NEO_CONFIG_DIST)
    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
        INFVK_ERROR_LOG("{}", pCallbackData->pMessage);
    else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        INFVK_WARN_LOG("{}", pCallbackData->pMessage);
    else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
        INFVK_INFO_LOG("{}", pCallbackData->pMessage);
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
    static neo::array_list_t<const char*> extensions;
    static neo::array_list_t<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    static neo::array_list_t<const char*> requiredDeviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    static bool validationLayersSupported(void)
    {
        uint32_t layer_count;
        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

        neo::array_list_t<VkLayerProperties> available_layers(layer_count, layer_count);
        vkEnumerateInstanceLayerProperties(&layer_count, available_layers.ptr());

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

        create_info->messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

        create_info->messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

        create_info->pfnUserCallback = debugCallback;
    }

    QueueFamilyIndices Core::GetQueueFamilies(VkPhysicalDevice device)
    {
        uint32_t queue_family_count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

        neo::array_list_t<VkQueueFamilyProperties> queue_families(queue_family_count, queue_family_count);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.ptr());

        QueueFamilyIndices indices;
        for (uint32_t i = 0; i < queue_family_count; i++)
        {
            if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                indices.graphics = i;

            VkBool32 present_support = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, Core::g_InitSurface, &present_support);
            if (present_support)
                indices.present = i;

            if (indices)
                break;
        }

        return indices;
    }

    static bool areRequiredDeviceExtensionsSupported(VkPhysicalDevice device)
    {
        uint32_t available_extensions_count;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &available_extensions_count, nullptr);

        neo::array_list_t<VkExtensionProperties> available_extensions(available_extensions_count, available_extensions_count);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &available_extensions_count, available_extensions.ptr());

        neo::array_list_t<std::string> required_extensions(requiredDeviceExtensions.capacity());
        for (const char* required_extension : requiredDeviceExtensions)
        {
            required_extensions.emplace(required_extension);
            for (const VkExtensionProperties& available_extension : available_extensions)
                if (required_extensions.tail() == available_extension.extensionName)
                    required_extensions.pop();
        }

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

        if (!Core::GetQueueFamilies(device))
            return 0;

        if (!areRequiredDeviceExtensionsSupported(device))
            return 0;

        if (!swapchain_support_t(device, Core::g_InitSurface))
            return 0;

        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            deviceProperties.limits.maxImageDimension2D += 1000;

        return deviceProperties.limits.maxImageDimension2D;
    }

    void Core::InitializeGLFW(void)
    {
        glfwSetErrorCallback([](int error, const char* description)
        {
            g_ErrorCallback(INF_GLFW_ERROR, description, nullptr);
        });
        if (!glfwInit())
            g_ErrorCallback(INF_GLFW_ERROR, "Failed to initialize GLFW!", nullptr);

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    }

    void Core::CreateInstance(void)
    {
        if (VALIDATION_LAYERS_ENABLED && !validationLayersSupported())
            g_ErrorCallback(INF_ERROR_NONE, "Validation Layers requested, but not supported!", nullptr);

        VkApplicationInfo app_info{};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pEngineName = "NeoInfused";

        VkInstanceCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;

        {
            uint32_t required_extension_count = 0;
            const char** required_extensions = glfwGetRequiredInstanceExtensions(&required_extension_count);

            extensions.reallocate(required_extension_count);
            for (uint32_t i = 0; i < required_extension_count; i++)
                extensions.emplace(required_extensions[i]);
        }

        VkDebugUtilsMessengerCreateInfoEXT debug_create_info{};
        if (VALIDATION_LAYERS_ENABLED)
        {
            extensions.emplace(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            create_info.enabledLayerCount = (uint32_t)validationLayers.size();
            create_info.ppEnabledLayerNames = validationLayers.ptr();

            populateDebugMessengerCreateInfo(&debug_create_info);
            create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debug_create_info;
        } else
        {
            create_info.enabledLayerCount = 0;
        }
        
        create_info.enabledExtensionCount = (uint32_t)extensions.size();
        create_info.ppEnabledExtensionNames = extensions.ptr();

        if (vkCreateInstance(&create_info, nullptr, &g_Instance) != VK_SUCCESS)
            g_ErrorCallback(INF_ERROR_NONE, "Failed to create instance!", nullptr);
    }

    void Core::CreateDebugMessenger(void)
    {
        if (!VALIDATION_LAYERS_ENABLED)
            return;

        VkDebugUtilsMessengerCreateInfoEXT create_info{};
        populateDebugMessengerCreateInfo(&create_info);

        if (CreateDebugUtilsMessengerEXT(g_Instance, &create_info, nullptr, &g_DebugMessenger) != VK_SUCCESS)
            g_ErrorCallback(INF_ERROR_NONE, "Failed to set up debug messenger!", nullptr);
    }

    void Core::CreateInitializationSurface(void)
    {
        GLFWwindow* init_window = glfwCreateWindow(1, 1, "", nullptr, nullptr);
        if (glfwCreateWindowSurface(g_Instance, init_window, nullptr, &g_InitSurface) != VK_SUCCESS)
            g_ErrorCallback(INF_ERROR_NONE, "Failed to create Vulkan initialization surface!", nullptr);
        glfwDestroyWindow(init_window);
    }

    void Core::PickPhysicalDevice(void)
    {
        uint32_t device_count;
        vkEnumeratePhysicalDevices(g_Instance, &device_count, nullptr);
        if (!device_count)
            g_ErrorCallback(INF_ERROR_NONE, "No GPUs with Vulkan support!", nullptr);

        neo::array_list_t<VkPhysicalDevice> available_devices(device_count, device_count);
        vkEnumeratePhysicalDevices(g_Instance, &device_count, available_devices.ptr());

        int32_t high_score = 0;
        for (uint32_t i = 0; i < device_count; i++)
        {
            if (ratePhysicalDevice(available_devices[i]) > high_score)
            {
                high_score = ratePhysicalDevice(available_devices[i]);
                g_PhysicalDevice = available_devices[i];
            }
        }

        if (!high_score)
            g_ErrorCallback(INF_ERROR_NONE, "No suitable GPU found!", nullptr);
    }

    static const float priorities[] = { 1.0f };
    static VkDeviceQueueCreateInfo createQueueCreateInfo(uint32_t index, uint32_t count = 1, const float* _priorities = priorities)
    {
        VkDeviceQueueCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        create_info.queueFamilyIndex = index;
        create_info.queueCount = count;
        create_info.pQueuePriorities = _priorities;
        return create_info;
    }

    void Core::CreateLogicalDevice(void)
    {
        QueueFamilyIndices indices = GetQueueFamilies(g_PhysicalDevice);
        neo::array_list_t<VkDeviceQueueCreateInfo> queue_create_infos;
        queue_create_infos.emplace(createQueueCreateInfo(indices.graphics));
        if (indices.graphics != indices.present)
            queue_create_infos.emplace(createQueueCreateInfo(indices.present));

        VkDeviceCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        create_info.queueCreateInfoCount = (uint32_t)queue_create_infos.size();
        create_info.pQueueCreateInfos = queue_create_infos.ptr();

        VkPhysicalDeviceFeatures device_features{};
        create_info.pEnabledFeatures = &device_features;

        create_info.enabledExtensionCount = (uint32_t)requiredDeviceExtensions.size();
        create_info.ppEnabledExtensionNames = requiredDeviceExtensions.ptr();

        if (vkCreateDevice(g_PhysicalDevice, &create_info, nullptr, &g_LogicalDevice) != VK_SUCCESS)
            g_ErrorCallback(INF_ERROR_NONE, "Failed to create logical device!", nullptr);

        vkGetDeviceQueue(g_LogicalDevice, indices.graphics, 0, &g_GraphicsQueue);
        vkGetDeviceQueue(g_LogicalDevice, indices.present,  0, &g_PresentQueue);
    }

    std::filesystem::path GetExecPath(void)
    {
    #if defined(NEO_PLATFORM_LINUX)
        return std::filesystem::canonical("/proc/self/exe");
    #elif defined(NEO_PLATFORM_WINDOWS)
        char exec_path_buffer[MAX_PATH];
        GetModuleFileNameA(nullptr, exec_path_buffer, MAX_PATH);
        return exec_path_buffer;
    #endif
    }
} // namespace vk 

using namespace vk;
EXPORT_FN void SetErrorCallback(error_callback_fn error_callback)
{
    g_ErrorCallback = error_callback;
}

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
    if (Core::g_LogicalDevice)
        vkDestroyDevice(Core::g_LogicalDevice, nullptr);

    if (Core::g_InitSurface)
        vkDestroySurfaceKHR(Core::g_Instance, Core::g_InitSurface, nullptr);

    if (Core::VALIDATION_LAYERS_ENABLED)
        DestroyDebugUtilsMessengerEXT(Core::g_Instance, Core::g_DebugMessenger, nullptr);

    if (Core::g_Instance)
        vkDestroyInstance(Core::g_Instance, nullptr);

    glfwTerminate();
}
