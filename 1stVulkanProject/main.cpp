#include <iostream>
#include <vulkan/vulkan.hpp>

int main()
{
	VkResult result;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pNext = nullptr;

	VkInstance m_instance;

	std::vector<VkPhysicalDevice> m_physicalDevices;

	result = vkCreateInstance(&createInfo, nullptr, &m_instance);

	if (result == VK_SUCCESS)
	{
		uint32_t physicalDeviceCount = 0;
		result = vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr);

		if (result == VK_SUCCESS)
		{
			m_physicalDevices.resize(physicalDeviceCount);
			result = vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, &m_physicalDevices[0]);

			if (result == VK_SUCCESS)
			{
				VkPhysicalDeviceProperties properties;
				// device features

				for (VkPhysicalDevice physicalDevice : m_physicalDevices)
				{
					vkGetPhysicalDeviceProperties(physicalDevice, &properties);
					// device features

					// print properties & features
					std::cout << properties.deviceName << std::endl;
				}
			}
		}
	}

	return 0;
}