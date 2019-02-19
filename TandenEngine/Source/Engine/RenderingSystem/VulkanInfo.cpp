// Created by thomas.mcgillicuddy on 1/19/2019.
#define NOMINMAX
#include "VulkanInfo.h"
#include <Debug.h>
namespace TandenEngine {




    void VulkanInfo::InitVulkan() {
        InitVKInstance();
        SetupDebugMessenger();
        InitWindowSurface();
        SelectPhysicalDevice();
        InitLogicalDevice();
    }

    VkResult VulkanInfo::CreateDebugUtilsMessengerEXT(VkInstance instance,
            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
            const VkAllocationCallbacks* pAllocator,
            VkDebugUtilsMessengerEXT* pDebugMessenger) {
        // create debug messenger
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)
                vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void VulkanInfo::DestroyDebugUtilsMessengerEXT(VkInstance instance,
            VkDebugUtilsMessengerEXT debugMessenger,
            const VkAllocationCallbacks* pAllocator) {
        // destroy debug messenger
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
                vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }

    std::vector<const char*> VulkanInfo::GetRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    void VulkanInfo::SetupDebugMessenger() {
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = DebugCallback;

        if (CreateDebugUtilsMessengerEXT(VulkanInstance,
                &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanInfo::DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData) {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }


    void VulkanInfo::InitVulkanPipeline() {
        CreateSwapChain();
        CreateImageViews();
        CreateRenderPass();
        CreateDescriptorSetLayout();
        CreateGraphicsPipeline();
        CreateFramebuffers();
        CreateCommandPool();
        BufferManager::CreateVertexBufferForTargetModel();
        BufferManager::CreateIndexBufferForTargetModel();
        BufferManager::CreateUniformBuffers();
        CreateDescriptorPool();
        CreateDescriptorSets();

        CreateCommandBuffers();  //TODO(Rosser) use an init function, vbuffers will be made later
        CreateSyncObjects();
    }

    bool VulkanInfo::CheckValidationLayerSupport() {
        // find layer count, put into vector
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        // check if all validation layers are in list of avaliable layers
        for (const char* layerName : ValidationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        // true if we support, false if we  dont
        return true;
    }

    void VulkanInfo::InitVKInstance() {
        // enable validation layers
        if (enableValidationLayers && !CheckValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        //  create instance
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = GetRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
            createInfo.ppEnabledLayerNames = ValidationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateInstance(&createInfo, mAllocator, &VulkanInstance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }

    void VulkanInfo::SelectPhysicalDevice() {
        physicalDevice = VK_NULL_HANDLE;

        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(VulkanInstance , &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(VulkanInstance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (SuitableDevice(device)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }

        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);
    }

    void VulkanInfo::InitLogicalDevice() {
        QueueFamilyIndices indices = FindQueueFamilies(physicalDevice);

        // look for queue family with capacity for graphics
        // VkDeviceQueueCreateInfo queueCreateInfo = {};
        // queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        // queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        // queueCreateInfo.queueCount = 1;
        // queueCreateInfo.pQueuePriorities = &queuePriority;

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies =
                {indices.graphicsFamily.value(), indices.presentFamily.value()};


        // set priorities for queues, value between 0 and 1 to have priority when queueing events
        // necessary even if we are only using one queue for event execution
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }


        // check for special device features, like different shader types but right now
        VkPhysicalDeviceFeatures deviceFeatures = {};

        // create empty info for the new logical device
        VkDeviceCreateInfo newDeviceInfo = {};
        newDeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        // info queue
        newDeviceInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        newDeviceInfo.pQueueCreateInfos = queueCreateInfos.data();

        // give it the empty features object we created
        newDeviceInfo.pEnabledFeatures = &deviceFeatures;

        newDeviceInfo.enabledExtensionCount = static_cast<uint32_t>(DeviceExtensions.size());
        newDeviceInfo.ppEnabledExtensionNames = DeviceExtensions.data();

        // create the actual device and set it to our instance of logical device
        if (vkCreateDevice(physicalDevice, &newDeviceInfo,
                mAllocator, &logicalDevice) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        // get one queue from queue family of logical device and set it to the graphics queue
        vkGetDeviceQueue(logicalDevice, indices.graphicsFamily.value(), 0, &gfxQueue);
        vkGetDeviceQueue(logicalDevice, indices.presentFamily.value(), 0, &presentationQueue);
    }

    QueueFamilyIndices VulkanInfo::FindQueueFamilies(VkPhysicalDevice targetDevice) {
        QueueFamilyIndices indices;

        // get queue families supported by target device
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(targetDevice, &queueFamilyCount, nullptr);

        // load found queue families into a vector
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(
                targetDevice,
                &queueFamilyCount,
                queueFamilies.data());

        // iterate through queue family vec until we find a queue family on
        // the graphics card that can support VK_QUEUE_GRAPHICS_BIT
        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(targetDevice, i, WindowSurface, &presentSupport);

            if (queueFamily.queueCount > 0 && presentSupport) {
                indices.presentFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            ++i;
        }

        return indices;
    }

    bool VulkanInfo::CheckDeviceExtSupport(VkPhysicalDevice targetDevice) {
        // find number of supported extensions
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(targetDevice, nullptr, &extensionCount, nullptr);

        // create list of extensions based on how many are supported for that device
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(
                targetDevice,
                nullptr,
                &extensionCount,
                availableExtensions.data());

        // convert renderingsystem requirements into a set of strings
        std::set<std::string> requiredExtensions(DeviceExtensions.begin(), DeviceExtensions.end());

        // iterate through both lists to see if the device has the requirements
        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        // return if all the requirements were covered or not
        return requiredExtensions.empty();
    }

    SwapChainSupportDetails VulkanInfo::PollSwapChainSupport(VkPhysicalDevice targetDevice) {
        SwapChainSupportDetails details;


        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
                targetDevice,
                WindowSurface,
                &details.capabilities);


        // get devices supported window surface formats
        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(
                targetDevice,
                WindowSurface,
                &formatCount,
                nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(
                    targetDevice,
                    WindowSurface,
                    &formatCount,
                    details.formats.data());
        }

        // get devices supported presentation modes
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(
                targetDevice,
                WindowSurface,
                &presentModeCount,
                nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(
                    targetDevice,
                    WindowSurface,
                    &presentModeCount,
                    details.presentModes.data());
        }

        return details;
    }

    VkSurfaceFormatKHR VulkanInfo::ChooseSwapSurfaceFormat(
            const std::vector<VkSurfaceFormatKHR>& availableFormats) {
        if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
            return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
        }

        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM &&
                availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    VkPresentModeKHR VulkanInfo::ChooseSwapPresentMode(
            const std::vector<VkPresentModeKHR> availablePresentModes) {
        VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            } else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                bestMode = availablePresentMode;
            }
        }
        return bestMode;
    }

    VkExtent2D VulkanInfo::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
        // Basically just the window size for the surface
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        } else {
            VkExtent2D actualExtent = {windowWidth, windowHeight};

            actualExtent.width = std::max(capabilities.minImageExtent.width,
                    std::min(capabilities.maxImageExtent.width, actualExtent.width));
            actualExtent.height = std::max(capabilities.minImageExtent.height,
                    std::min(capabilities.maxImageExtent.height, actualExtent.height));

            return actualExtent;
        }
    }

    void VulkanInfo::CreateSwapChain() {
        SwapChainSupportDetails swapChainSupport = PollSwapChainSupport(physicalDevice);

        VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);


        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 &&
            imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = WindowSurface;

        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = FindQueueFamilies(physicalDevice);
        uint32_t queueFamilyIndices[] =
                {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(logicalDevice, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(logicalDevice, swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(logicalDevice, swapChain, &imageCount, swapChainImages.data());

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;
    }

    void VulkanInfo::CreateImageViews() {
        swapChainImageViews.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            VkImageViewCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = swapChainImages[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = swapChainImageFormat;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;

            if (vkCreateImageView(
                    logicalDevice,
                    &createInfo,
                    nullptr,
                    &swapChainImageViews[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create image views!");
            }
        }
    }

    //TODO(Rosser) Deprecate
    std::vector<char> VulkanInfo::ReadFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            // throw std::runtime_error("failed to open file!");
            std::cout << "failed to open file!" << filename << std::endl;
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    // TODO(Rosser) return pipeline (can use to create multiple pipelines)
    // TODO(Rosser) take input file path/resource
    void VulkanInfo::CreateGraphicsPipeline() {
        // read files
        auto vsCode = ReadFile("./ContentFiles/Shaders/vert.spv");
        auto fsCode = ReadFile("./ContentFiles/Shaders/frag.spv");

        // make shader modules
        VkShaderModule vsModule = CreateShaderModule(vsCode);
        VkShaderModule fsModule = CreateShaderModule(fsCode);

        // make stages from shader modules
        // vertex
        VkPipelineShaderStageCreateInfo vsStageInfo = {};
        vsStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vsStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vsStageInfo.module = vsModule;
        vsStageInfo.pName = "main";

        // fragment
        VkPipelineShaderStageCreateInfo fsStageInfo = {};
        fsStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fsStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fsStageInfo.module = fsModule;
        fsStageInfo.pName = "main";


        // create stage info for combined shader
        VkPipelineShaderStageCreateInfo shaderStages[] = {vsStageInfo, fsStageInfo};

        // vertex input stage info
        VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        auto bindingDescription = MeshVertex::GetBindingDescription();
        auto attributeDescriptions = MeshVertex::GetAttributeDescriptions();

        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.vertexAttributeDescriptionCount =
                static_cast<uint32_t>(attributeDescriptions.size());
        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

        // specify geometry type
        VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        // create base viewport
        VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float) swapChainExtent.width;
        viewport.height = (float) swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        // scizzors
        VkRect2D scissor = {};
        scissor.offset = {0, 0};
        scissor.extent = swapChainExtent;

        // combine viewport and scizzor
        VkPipelineViewportStateCreateInfo viewportState = {};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

        // rasterizer
        VkPipelineRasterizationStateCreateInfo rasterizer = {};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;          // toggle discarding frags beyond planes
        rasterizer.rasterizerDiscardEnable = VK_FALSE;   // enables rasterization
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;   // fill type, other options: LINE or POINT
        rasterizer.lineWidth = 1.0f;                     // line thickness between verts
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;     // face culling
        rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;  // culling direction
        rasterizer.depthBiasEnable = VK_FALSE;           // toggle depth bias

        // multisampling, for anti aliasing
        VkPipelineMultisampleStateCreateInfo multisampling = {};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;                   // disable for now
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        multisampling.minSampleShading = 1.0f;
        multisampling.pSampleMask = nullptr;
        multisampling.alphaToCoverageEnable = VK_FALSE;
        multisampling.alphaToOneEnable = VK_FALSE;

        // color blending attachment, mixing returned color with color in framebuffer for new color
        VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
        colorBlendAttachment.colorWriteMask =
                VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

        colorBlendAttachment.blendEnable = VK_FALSE;
        // colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; //  Optional
        // colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; //  Optional
        // colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; //  Optional
        // colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; //  Optional
        // colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; //  Optional
        // colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; //  Optional

        // color blending, blend constants and other relevant information
        VkPipelineColorBlendStateCreateInfo colorBlending = {};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;  // Optional
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;  // Optional
        colorBlending.blendConstants[1] = 0.0f;  // Optional
        colorBlending.blendConstants[2] = 0.0f;  // Optional
        colorBlending.blendConstants[3] = 0.0f;  // Optional

        // things that are changeable without recreating the entire pipeline
        VkDynamicState dynamicStates[] = {
                VK_DYNAMIC_STATE_VIEWPORT,
                VK_DYNAMIC_STATE_LINE_WIDTH
        };

        VkPipelineDynamicStateCreateInfo dynamicState = {};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.dynamicStateCount = 2;
        dynamicState.pDynamicStates = dynamicStates;


        // pipeline layout for uniform creation
        VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 1;
        pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;

        if (vkCreatePipelineLayout(
                logicalDevice,
                &pipelineLayoutInfo,
                nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }

        // create actual pipeline with above settings
        VkGraphicsPipelineCreateInfo pipelineInfo = {};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;

        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = nullptr;  //  Optional
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.pDynamicState = nullptr;  //  Optional

        // set layout for pipeline
        pipelineInfo.layout = pipelineLayout;

        // set render pass for pipeline
        pipelineInfo.renderPass = mRenderPass;
        pipelineInfo.subpass = 0;

        // pipeline extension, but not required here since we dont have a base pipeline
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;  //  Optional
        pipelineInfo.basePipelineIndex = -1;  //  Optional

        // null check
        if (vkCreateGraphicsPipelines(
                logicalDevice,
                VK_NULL_HANDLE,
                1,
                &pipelineInfo,
                nullptr,
                &graphicsPipeline) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline!");
        }

        // local cleanup
        vkDestroyShaderModule(logicalDevice, fsModule, nullptr);
        vkDestroyShaderModule(logicalDevice, vsModule, nullptr);
    }

    void VulkanInfo::CreateFramebuffers() {
        swapChainFramebuffers.resize(swapChainImageViews.size());

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            VkImageView attachments[] = {
                    swapChainImageViews[i]
            };

            VkFramebufferCreateInfo framebufferInfo = {};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = mRenderPass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swapChainExtent.width;
            framebufferInfo.height = swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(
                    logicalDevice,
                    &framebufferInfo,
                    nullptr,
                    &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }

    void VulkanInfo::CreateCommandPool() {
        QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(physicalDevice);

        // command pool so multiple threads can draw ahead of time
        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
        poolInfo.flags = 0;  //  Optional

        if (vkCreateCommandPool(logicalDevice, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }

    // TODO(Rosser) Deprecate
    void VulkanInfo::CreateCommandBuffers() {
        commandBuffers.resize(swapChainFramebuffers.size());

        // create command buffer info
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

        // throw if failed allocation
        if (vkAllocateCommandBuffers(
                logicalDevice,
                &allocInfo,
                commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        // recording command buffer
        for (size_t i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo = {};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
            beginInfo.pInheritanceInfo = nullptr;  //  Optional

            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            // configure render pass for command buffer
            VkRenderPassBeginInfo renderPassInfo = {};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = mRenderPass;
            renderPassInfo.framebuffer = swapChainFramebuffers[i];
            // size of render area on screen
            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = swapChainExtent;

            // clear color for render pass
            VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
            renderPassInfo.clearValueCount = 1;
            renderPassInfo.pClearValues = &clearColor;

            // begin the render pass!
            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            // bind our graphics pipeline
            vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

            // bind vertex buffers from buffer list
            // TODO(Rosser) iterate through all vertex buffers
            VkBuffer vertexBuffers[] = {BufferManager::mVertexBufferList.at(0)};
            VkDeviceSize offsets[] = {0};
            vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);

            // draw indexed vertices
            vkCmdBindIndexBuffer(
                    commandBuffers[i],
                    BufferManager::mIndexBufferList.at(0),
                    0,
                    VK_INDEX_TYPE_UINT16);

            // TODO(Rosser) uncomment when matrices work
            // bind descriptor sets from uniform buffers
            // vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS,
            // pipelineLayout, 0, 1, &descriptorSets[i], 0, nullptr);

            vkCmdDrawIndexed(
                    commandBuffers[i],
                    static_cast<uint32_t>(BufferManager::modelList[0]->mIndices.size()),
                    1, 0, 0, 0);
            // draw non indexed
            // vkCmdDraw(
            // commandBuffers[i],
            // static_cast<uint32_t>(BufferManager::mVertices.size()),
            // 1, 0, 0);

            // end render pass
            vkCmdEndRenderPass(commandBuffers[i]);

            // finish recording command buffer, throw if failed
            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }
        }
    }

    void VulkanInfo::CreateSyncObjects() {
        // fill vectors for multiple
        imageAvailableSemaphores.resize(maxFramesInFlight);
        renderFinishedSemaphores.resize(maxFramesInFlight);
        inFlightFences.resize(maxFramesInFlight);

        // semaphore info
        VkSemaphoreCreateInfo semaphoreInfo = {};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        // fence info
        VkFenceCreateInfo fenceInfo = {};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < (size_t)maxFramesInFlight; i++) {
            if (vkCreateSemaphore(
                    logicalDevice,
                    &semaphoreInfo,
                    nullptr,
                    &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(
                        logicalDevice,
                        &semaphoreInfo,
                        nullptr,
                        &renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(
                        logicalDevice,
                        &fenceInfo,
                        nullptr,
                        &inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
    }

    VkShaderModule VulkanInfo::CreateShaderModule(const std::vector<char>& code) {
        VkShaderModuleCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(
                logicalDevice,
                &createInfo,
                nullptr,
                &shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module!");
        }

        return shaderModule;
    }

    void VulkanInfo::CreateRenderPass() {
        // render color in one of the images of the swapchain
        // format of attachment must match format of swap chain images
        VkAttachmentDescription colorAttachment = {};
        colorAttachment.format = swapChainImageFormat;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;

        // settings ofr what to do with data before and after render
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;      // LOAD, CLEAR, DONT_CARE
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;    // STORE, DONT_CARE

        // stencil buffer settings, doesnt matter for now but here they are
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

        // layouts for pixels in memory, may change existing texture and framebuffer format
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        // create color attachment for subpass
        VkAttachmentReference colorAttachmentRef = {};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        // create subpass
        VkSubpassDescription subpass = {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        // refer to color attachment
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        // create actual render pass with above information
        VkRenderPassCreateInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colorAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;

        if (vkCreateRenderPass(
                logicalDevice,
                &renderPassInfo,
                nullptr,
                &mRenderPass) != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass!");
        }

        // subpass dependencies (transitions between subpasses)
        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;

        // Order of operations, which operations wait on what -- look into this more later
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask =
                VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
                VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        // set dependencies in render pass
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;
    }

    void VulkanInfo::InitWindowSurface() {
        if (glfwCreateWindowSurface(
                VulkanInstance,
                RenderingSystem::GetWindow()->GetWindowRef(),
                mAllocator,
                &WindowSurface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    bool VulkanInfo::SuitableDevice(VkPhysicalDevice targetDevice) {
        QueueFamilyIndices indices = FindQueueFamilies(targetDevice);

        // check for required extensions
        bool extensionsSupported = CheckDeviceExtSupport(targetDevice);

        // check for swapchain support, at least one supported image format and presentation mode
        bool swapChainAdequate = false;

        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = PollSwapChainSupport(targetDevice);
            swapChainAdequate = !swapChainSupport.formats.empty() &&
                    !swapChainSupport.presentModes.empty();
        }

        return indices.isComplete() && extensionsSupported && swapChainAdequate;
    }

    // TODO(Rosser) Deprecate
    void VulkanInfo::RecreateSwapChain() {
        vkDeviceWaitIdle(logicalDevice);

        CreateSwapChain();
        CreateImageViews();
        CreateRenderPass();
        CreateGraphicsPipeline();
        CreateFramebuffers();
        // CreateCommandBuffers();
    }

    void VulkanInfo::CreateDescriptorSetLayout() {
        // layout for uniform buffer object
        VkDescriptorSetLayoutBinding uboLayoutBinding = {};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorCount = 1;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.pImmutableSamplers = nullptr;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutCreateInfo layoutInfo = {};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = &uboLayoutBinding;

        if (vkCreateDescriptorSetLayout(logicalDevice, &layoutInfo,
                nullptr, &descriptorSetLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
    }

    void VulkanInfo::CreateDescriptorPool() {
        // create descriptor pool
        VkDescriptorPoolSize poolSize[] = {
                { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
                { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
                { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
                { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
                { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
                { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
                { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
        };
        // poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        // poolSize.descriptorCount = static_cast<uint32_t>(swapChainImages.size());

        // info for pool
        VkDescriptorPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        poolInfo.maxSets = 1000;
        poolInfo.poolSizeCount = _countof(poolSize);
        poolInfo.pPoolSizes = poolSize;
        // poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());

        if (vkCreateDescriptorPool(logicalDevice, &poolInfo,
                mAllocator, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }

    void VulkanInfo::CreateDescriptorSets() {
        // create descriptor sets for pool
        std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(), descriptorSetLayout);
        VkDescriptorSetAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
        allocInfo.pSetLayouts = layouts.data();

        // change size based on uniform buffers
        descriptorSets.resize(swapChainImages.size());

        if (vkAllocateDescriptorSets(logicalDevice, &allocInfo,
                descriptorSets.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }

        // write sets from buffers to swapchain images
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            VkDescriptorBufferInfo bufferInfo = {};
            bufferInfo.buffer = BufferManager::mUniformBufferList[i];
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(UniformBufferObject);

            // write new sets based on
            VkWriteDescriptorSet descriptorWrite = {};
            descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite.dstSet = descriptorSets[i];
            descriptorWrite.dstBinding = 0;
            descriptorWrite.dstArrayElement = 0;
            descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrite.descriptorCount = 1;
            descriptorWrite.pBufferInfo = &bufferInfo;

            // update sets
            vkUpdateDescriptorSets(logicalDevice, 1, &descriptorWrite, 0, nullptr);
        }
    }

    void VulkanInfo::CleanupVulkan() {
        // swapchain cleanup
        for (size_t i = 0; i < swapChainFramebuffers.size(); i++) {
            vkDestroyFramebuffer(logicalDevice, swapChainFramebuffers[i], nullptr);
        }

        vkDestroyDescriptorPool(logicalDevice, descriptorPool, nullptr);


        vkDestroyDescriptorSetLayout(logicalDevice, descriptorSetLayout, nullptr);

        // free command buffers
        vkFreeCommandBuffers(
                logicalDevice,
                commandPool,
                static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            vkDestroyImageView(logicalDevice, swapChainImageViews[i], nullptr);
        }

        vkDestroySwapchainKHR(logicalDevice, swapChain, nullptr);

        // destroy sync objects
        for (size_t i = 0; i < (size_t)maxFramesInFlight; i++) {
            vkDestroySemaphore(logicalDevice, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(logicalDevice, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(logicalDevice, inFlightFences[i], nullptr);
        }

        vkDestroyCommandPool(logicalDevice, commandPool, nullptr);

        for (auto framebuffer : swapChainFramebuffers) {
            vkDestroyFramebuffer(logicalDevice, framebuffer, nullptr);
        }

        vkDestroyPipeline(logicalDevice, graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(logicalDevice, pipelineLayout, nullptr);
        vkDestroyRenderPass(logicalDevice, mRenderPass, nullptr);

        for (auto imageView : swapChainImageViews) {
            vkDestroyImageView(logicalDevice, imageView, nullptr);
        }

        vkDestroyPipelineLayout(logicalDevice, pipelineLayout, nullptr);

        vkDestroySurfaceKHR(VulkanInstance, WindowSurface, nullptr);

        vkDestroySwapchainKHR(logicalDevice, swapChain, nullptr);

        vkDestroyDevice(logicalDevice, nullptr);

        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(VulkanInstance, debugMessenger, nullptr);
        }

        vkDestroyInstance(VulkanInstance, nullptr);
    }
}  // namespace TandenEngine
