#include <iostream>

#define VK_USE_PLATFORM_WIN32_KHR
// #include <win>
#include <vulkan/vulkan.hpp>
// #include <vulkan/vulkan_win32.h>

int main()
{
	VkResult result;

	// layers & extensions

	uint32_t instanceExtensionPropertyCount = 0;
	std::vector<VkExtensionProperties> instanceExtensionProperties;

	vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionPropertyCount, nullptr);

	if (instanceExtensionPropertyCount != 0)
	{
		instanceExtensionProperties.resize(instanceExtensionPropertyCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionPropertyCount, instanceExtensionProperties.data());
	}

	std::cout << "----- INSTANCE EXTENSIONS -----" << std::endl;

	for (VkExtensionProperties extension : instanceExtensionProperties)
	{
		std::cout << extension.extensionName << " " << extension.specVersion << std::endl;
	}

	std::vector<const char*> ppEnabledExtensionNames;
	ppEnabledExtensionNames.push_back("VK_KHR_surface");
	ppEnabledExtensionNames.push_back("VK_KHR_win32_surface");

	// instance

	VkInstanceCreateInfo createInfo = {
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,	// sType
		nullptr,								// pNext
		0,										// flags
		nullptr,								// pApplicationInfo
		0,										// enabledLayerCount
		nullptr,								// ppEnabledLayerNames
		ppEnabledExtensionNames.size(),			// enabledExtensionCount
		ppEnabledExtensionNames.data()			// ppEnabledExtensionNames
	};

	// createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	// createInfo.pNext = nullptr;

	VkInstance instance;
	result = vkCreateInstance(&createInfo, nullptr, &instance);

	if (result == VK_SUCCESS)
	{
		uint32_t physicalDeviceCount = 0;
		result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);

		if (result == VK_SUCCESS)
		{
			std::vector<VkPhysicalDevice> devices;
			devices.resize(physicalDeviceCount);

			result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, &devices[0]);

			if (result == VK_SUCCESS)
			{
				VkPhysicalDeviceProperties properties;
				// device features

				std::cout << "----- PHYSICAL DEVICES -----" << std::endl;

				for (VkPhysicalDevice physicalDevice : devices)
				{
					vkGetPhysicalDeviceProperties(physicalDevice, &properties);
					// device features

					// print properties & features
					std::cout << properties.deviceName << std::endl;

					// device extension properties

					uint32_t deviceExtensionPropertyCount = 0;
					std::vector<VkExtensionProperties> deviceExtensionProperties;

					vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &deviceExtensionPropertyCount, nullptr);

					if (deviceExtensionPropertyCount != 0)
					{
						deviceExtensionProperties.resize(deviceExtensionPropertyCount);
						vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &deviceExtensionPropertyCount, deviceExtensionProperties.data());
					}

					std::cout << "----- DEVICE EXTENSIONS -----" << std::endl;

					for (VkExtensionProperties extension : deviceExtensionProperties)
					{
						std::cout << extension.extensionName << " " << extension.specVersion << std::endl;
					}

					uint32_t pQueueFamilyPropertyCount = 0;
					vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &pQueueFamilyPropertyCount, nullptr);

					std::cout << "----- vkGetPhysicalDeviceWin32PresentationSupportKHR (queue/flag) -----" << std::endl;

					for (uint32_t i = 0; i < pQueueFamilyPropertyCount; i++)
					{
						VkBool32 support = vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, i);

						std::cout << i << " : " << support << std::endl;

						// create Win32 surface

						if (false)
						{
							VkWin32SurfaceCreateInfoKHR createInfo = {
								VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR,	// sType
								nullptr,											// pNext
								0,													// flags
								GetModuleHandle(nullptr),							// hinstance
								nullptr												// hwnd
							};

							VkSurfaceKHR surface;
							result = vkCreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface);
						}

					}
				}

				// logical device
			}
		}

		// shutting down cleanly

		vkDestroyInstance(instance, nullptr);
	}

	return 0;
}