#if !defined(VK_SWAPCHAIN_SUPPORT_HPP)
#define VK_SWAPCHAIN_SUPPORT_HPP

namespace vk {
    class SwapchainSupport {
    public:
        SwapchainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
        ~SwapchainSupport(void) = default;

        inline operator bool(void) const { return m_Supported; }
    public:
        VkSurfaceCapabilitiesKHR capabilities;
        neo::Arena<VkSurfaceFormatKHR> formats;
        neo::Arena<VkPresentModeKHR> present_modes;
    private:
        bool m_Supported = false;
    };
    using SwapChainSupport = SwapchainSupport;
}

#endif // VK_SWAPCHAIN_SUPPORT_HPP