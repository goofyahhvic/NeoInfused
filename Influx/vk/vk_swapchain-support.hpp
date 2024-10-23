#if !defined(VK_SWAPCHAIN_SUPPORT_HPP)
#define VK_SWAPCHAIN_SUPPORT_HPP

namespace vk {
    class swapchain_support_t {
    public:
        swapchain_support_t(VkPhysicalDevice device, VkSurfaceKHR surface);
        ~swapchain_support_t(void) = default;

        inline operator bool(void) const { return m_Supported; }
    public:
        VkSurfaceCapabilitiesKHR capabilities;
        neo::array_list_t<VkSurfaceFormatKHR> formats;
        neo::array_list_t<VkPresentModeKHR> present_modes;
    private:
        bool m_Supported = false;
    };
    using swap_chain_support_t = swapchain_support_t;
}

#endif // VK_SWAPCHAIN_SUPPORT_HPP