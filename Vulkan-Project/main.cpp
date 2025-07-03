#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	void initWindow() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // because is not OpenGL
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // later will work on resizable windows

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void initVulkan() {
		createInstance();
	}

	void createInstance() {
		// VK APP INFO
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// VK INSTANCE CREATE INFO
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		// REQUIRED EXTENSIONS
		std::vector<const char*> requiredExtensions;

		// get extensions required by glfw
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount); 

		for (int i = 0; i < glfwExtensionCount; ++i) {
			requiredExtensions.emplace_back(glfwExtensions[i]);
		}

		// for MacOS development is necessary this extension
		// since 1.3.216 Vulkan SDK VK_KHR_PORTABILITY_subset is mandatory
		requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

		std::cout << "Required Extensions: \n";
		for (const auto& extension : requiredExtensions) {
			std::cout << '\t' << extension << '\n';
		}
		std::cout << std::endl;

		createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
		createInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
		createInfo.ppEnabledExtensionNames = requiredExtensions.data();

		createInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create vkInstance");
		}

		// EXTENSIONS SUPPORT / AVAILABLE EXTENSIONS
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

		std::cout << "Available Extensions:\n";
		for (const auto& extension : availableExtensions) {
			std::cout << '\t' << extension.extensionName << '\n';
		}
		std::cout << std::endl;

		// check the required extensions are available
		bool areRequiredExtensionsAvailable = true;
		for (const auto& requiredExtension : requiredExtensions) {
			bool isAvailable = false;
			for (const auto& availableExtension : availableExtensions) {
				if (std::strcmp(requiredExtension, availableExtension.extensionName)) {
					isAvailable = true;
					break;
				}
			}
			
			if (!isAvailable) {
				areRequiredExtensionsAvailable = false;
				break;
			}
		}

		if (areRequiredExtensionsAvailable) {
			std::cout << "All Required Extensions are Available!";
			std::cout << std::endl;

		}
		else {
			throw std::runtime_error("Some Required Extension is not Available");
		}
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	void cleanup() {
		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window);

		glfwTerminate();
	}

	GLFWwindow* window;

	VkInstance instance;
};

int main() {
	HelloTriangleApplication app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}