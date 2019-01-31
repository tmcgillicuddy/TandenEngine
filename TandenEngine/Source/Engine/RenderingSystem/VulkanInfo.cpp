//
// Created by thomas.mcgillicuddy on 1/19/2019.
//
#define NOMINMAX
#include "VulkanInfo.h"

namespace TandenEngine {




    void VulkanInfo::InitVulkan()
    {
        InitVKInstance();
        InitWindowSurface();
        SelectPhysicalDevice();
        InitLogicalDevice();
    }


    void VulkanInfo::InitVulkanPipeline() {
        CreateSwapChain();
        CreateImageViews();
        CreateRenderPass();
        CreateGraphicsPipeline();
        CreateFramebuffers();
        CreateCommandPool();
        CreateCommandBuffers();
        CreateSemaphores();
    }

    void VulkanInfo::InitVKInstance()
    {
        //create instance
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

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &VulkanInstance);

        if (vkCreateInstance(&createInfo, nullptr, &VulkanInstance) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
    }

    void VulkanInfo::SelectPhysicalDevice()
    {
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
    }

    void VulkanInfo::InitLogicalDevice()
    {
        QueueFamilyIndices indices = FindQueueFamilies(physicalDevice);

        //look for queue family with capacity for graphics
        //VkDeviceQueueCreateInfo queueCreateInfo = {};
        //queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        //queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        //queueCreateInfo.queueCount = 1;
        //queueCreateInfo.pQueuePriorities = &queuePriority;

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};


        //set priorities for queues, value between 0 and 1 to have priority when queueing events, necessary even if we are only using one queue for event execution
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }


        //check for special device features, like different shader types but right now, again, we dont give a shit
        VkPhysicalDeviceFeatures deviceFeatures = {};

        //create empty info for the new logical device
        VkDeviceCreateInfo newDeviceInfo = {};
        newDeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        //info queue
        newDeviceInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        newDeviceInfo.pQueueCreateInfos = queueCreateInfos.data();

        //give it the empty features object we created
        newDeviceInfo.pEnabledFeatures = &deviceFeatures;

        newDeviceInfo.enabledExtensionCount = static_cast<uint32_t>(DeviceExtensions.size());
        newDeviceInfo.ppEnabledExtensionNames = DeviceExtensions.data();

        //create the actual device and set it to our instance of logical device
        if (vkCreateDevice(physicalDevice, &newDeviceInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        //get one queue from queue family of logical device and set it to the graphics queue
        vkGetDeviceQueue(logicalDevice, indices.graphicsFamily.value(), 0, &gfxQueue);
        vkGetDeviceQueue(logicalDevice, indices.presentFamily.value(), 0, &presentationQueue);
    }

    QueueFamilyIndices VulkanInfo::FindQueueFamilies(VkPhysicalDevice targetDevice)
    {
        QueueFamilyIndices indices;

        //get queue families supported by target device
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(targetDevice, &queueFamilyCount, nullptr);

        //load found queue families into a vector
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(targetDevice, &queueFamilyCount, queueFamilies.data());

        //iterate through queue family vec until we find a queue family on the graphcis card that can support VK_QUEUE_GRAPHICS_BIT
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

    bool VulkanInfo::CheckDeviceExtSupport(VkPhysicalDevice targetDevice)
    {
        //find number of supported extensions
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(targetDevice, nullptr, &extensionCount, nullptr);

        //create list of extensions based on how many are supported for that device
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(targetDevice, nullptr, &extensionCount, availableExtensions.data());

        //convert renderingsystem requirements into a set of strings
        std::set<std::string> requiredExtensions(DeviceExtensions.begin(), DeviceExtensions.end());

        //iterate through both lists to see if the device has the requirements
        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        //return if all the requirements were covered or not
        return requiredExtensions.empty();
    }

    SwapChainSupportDetails VulkanInfo::PollSwapChainSupport(VkPhysicalDevice targetDevice)
    {
        SwapChainSupportDetails details;


        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(targetDevice, WindowSurface, &details.capabilities);


        //get devices supported window surface formats
        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(targetDevice, WindowSurface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(targetDevice, WindowSurface, &formatCount, details.formats.data());
        }

        //get devices supported presentation modes
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(targetDevice, WindowSurface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(targetDevice, WindowSurface, &presentModeCount, details.presentModes.data());
        }
        //TODO finish swapchain bru go to bed lmao





        return details;
    }

    VkSurfaceFormatKHR VulkanInfo::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
            return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
        }

        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    VkPresentModeKHR VulkanInfo::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
    {
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

    VkExtent2D VulkanInfo::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
    {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        } else {
            VkExtent2D actualExtent = {windowWidth, windowHeight};

            actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
            actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

            return actualExtent;
        }
    }

    void VulkanInfo::CreateSwapChain() {
        SwapChainSupportDetails swapChainSupport = PollSwapChainSupport(physicalDevice);

        VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);


        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
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
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

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

    void VulkanInfo::CreateImageViews()
    {
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

            if (vkCreateImageView(logicalDevice, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create image views!");
            }
        }
    }

    std::vector<char> VulkanInfo::ReadFile(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            //throw std::runtime_error("failed to open file!");
            std::cout << "failed to open file!" << filename << std::endl;
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;

    }

    void VulkanInfo::CreateGraphicsPipeline() {
        //read files
        auto vsCode = ReadFile("./ContentFiles/Shaders/vert.spv"); //can also read directly from the TriangleShader.frag
        auto fsCode = ReadFile("./ContentFiles/Shaders/frag.spv");

        //make shader modules
        VkShaderModule vsModule = CreateShaderModule(vsCode);
        VkShaderModule fsModule = CreateShaderModule(fsCode);

        //make stages from shader modules
        //vertex
        VkPipelineShaderStageCreateInfo vsStageInfo = {};
        vsStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vsStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vsStageInfo.module = vsModule;
        vsStageInfo.pName = "main";

        //fragment
        VkPipelineShaderStageCreateInfo fsStageInfo = {};
        fsStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fsStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fsStageInfo.module = fsModule;
        fsStageInfo.pName = "main";


        //create stage info for combined shader
        VkPipelineShaderStageCreateInfo shaderStages[] = {vsStageInfo, fsStageInfo};

        //vertex input stage info
        VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        auto bindingDescription = MeshVertex::GetBindingDescription();
        auto attributeDescriptions = MeshVertex::GetAttributeDescriptions();

        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

        //specify geometry type
        VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        //create base viewport
        VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float) swapChainExtent.width;
        viewport.height = (float) swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        //scizzors
        VkRect2D scissor = {};
        scissor.offset = {0, 0};
        scissor.extent = swapChainExtent;

        //combine viewport and scizzor
        VkPipelineViewportStateCreateInfo viewportState = {};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

        //rasterizer
        VkPipelineRasterizationStateCreateInfo rasterizer = {};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;                     //toggle discarding fragments beyond planes
        rasterizer.rasterizerDiscardEnable = VK_FALSE;              //enables rasterization
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;              //fill type, other options are LINE or POINT
        rasterizer.lineWidth = 1.0f;                                //line thickness between verts
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;                //face culling
        rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;             //face culling direction
        rasterizer.depthBiasEnable = VK_FALSE;                      //toggle depth bias


        //multisampling, for anti aliasing
        VkPipelineMultisampleStateCreateInfo multisampling = {};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;                   //disable for now
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        multisampling.minSampleShading = 1.0f;
        multisampling.pSampleMask = nullptr;
        multisampling.alphaToCoverageEnable = VK_FALSE;
        multisampling.alphaToOneEnable = VK_FALSE;

        //color blending attachment, mixing frag returned color with color in framebuffer for new color
        VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;
        //colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
        //colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
        //colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
        //colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
        //colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
        //colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

        //color blending, blend constants and other relevant information
        VkPipelineColorBlendStateCreateInfo colorBlending = {};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f; // Optional
        colorBlending.blendConstants[1] = 0.0f; // Optional
        colorBlending.blendConstants[2] = 0.0f; // Optional
        colorBlending.blendConstants[3] = 0.0f; // Optional

        //things that are changeable without recreating the entire pipeline, need to be specified on draw
        VkDynamicState dynamicStates[] = {
                VK_DYNAMIC_STATE_VIEWPORT,
                VK_DYNAMIC_STATE_LINE_WIDTH
        };

        VkPipelineDynamicStateCreateInfo dynamicState = {};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.dynamicStateCount = 2;
        dynamicState.pDynamicStates = dynamicStates;


        //pipeline layout for uniform creation
        VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0; // Optional
        pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
        pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
        pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

        if (vkCreatePipelineLayout(logicalDevice, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }

        //create actual pipeline with above settings
        VkGraphicsPipelineCreateInfo pipelineInfo = {};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;

        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = nullptr; // Optional
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.pDynamicState = nullptr; // Optional

        //set layout for pipeline
        pipelineInfo.layout = pipelineLayout;

        //set render pass for pipeline
        pipelineInfo.renderPass = renderPass;
        pipelineInfo.subpass = 0;

        //pipeline extension, but not required here since we dont have a base pipeline
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
        pipelineInfo.basePipelineIndex = -1; // Optional

        //null check
        if (vkCreateGraphicsPipelines(logicalDevice, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline!");
        }

        //local cleanup
        vkDestroyShaderModule(logicalDevice, fsModule, nullptr);
        vkDestroyShaderModule(logicalDevice, vsModule, nullptr);
    }

    void VulkanInfo::CreateFramebuffers()
    {
        swapChainFramebuffers.resize(swapChainImageViews.size());

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            VkImageView attachments[] = {
                    swapChainImageViews[i]
            };

            VkFramebufferCreateInfo framebufferInfo = {};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swapChainExtent.width;
            framebufferInfo.height = swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(logicalDevice, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }

    void VulkanInfo::CreateCommandPool()
    {
        QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(physicalDevice);

        //command pool so multiple threads can draw ahead of time
        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
        poolInfo.flags = 0; // Optional

        if (vkCreateCommandPool(logicalDevice, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }

    void VulkanInfo::CreateCommandBuffers()
    {
        commandBuffers.resize(swapChainFramebuffers.size());

        //create command buffer info
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;                   //also secondary option. Primary can be sent, secondary cant be but can be called from primary
        allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

        //throw if failed allocation
        if (vkAllocateCommandBuffers(logicalDevice, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        //recording command buffer
        for (size_t i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo = {};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT; //resubmitted while pending execution
            beginInfo.pInheritanceInfo = nullptr; // Optional

            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            //configure render pass for command buffer
            VkRenderPassBeginInfo renderPassInfo = {};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = renderPass;
            renderPassInfo.framebuffer = swapChainFramebuffers[i];
            //size of render area on screen
            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = swapChainExtent;

            //clear color for render pass
            VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
            renderPassInfo.clearValueCount = 1;
            renderPassInfo.pClearValues = &clearColor;

            //begin the render pass!
            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            //bind our graphics pipeline
            vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

            //bind vertex buffers from buffer list
            VkBuffer vertexBuffers[] = {BufferManager::mBufferList[0]};
            VkDeviceSize offsets[] = {0};
            vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);

            //draw vertices
            vkCmdDraw(commandBuffers[i], static_cast<uint32_t>(BufferManager::mVertices.size()), 1, 0, 0);

            //end render pass
            vkCmdEndRenderPass(commandBuffers[i]);

            //finish recording command buffer, throw if failed
            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }
        }
    }

    void VulkanInfo::CreateSemaphores() {
        //create semaphore info
        VkSemaphoreCreateInfo semaphoreInfo = {};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        //throw if it fails to create both semaphores
        if (vkCreateSemaphore(logicalDevice, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
            vkCreateSemaphore(logicalDevice, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS) {
            throw std::runtime_error("failed to create semaphores!");
        }
    }

    void RenderingSystem::DrawWindow() {
        //get next image from swapchain and trigger avaliable semaphore
        uint32_t imageIndex;
        vkAcquireNextImageKHR(mVulkanInfo.logicalDevice, mVulkanInfo.swapChain, std::numeric_limits<uint64_t>::max(), mVulkanInfo.imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

        //info for submission to queue
        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        //determine which semaphores wait on eachother
        VkSemaphore waitSemaphores[] = {mVulkanInfo.imageAvailableSemaphore};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        //determine which command buffers to bind for the color attachment
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &mVulkanInfo.commandBuffers[imageIndex];

        //determine which semaphore will signal once command buffer finishes
        VkSemaphore signalSemaphores[] = {mVulkanInfo.renderFinishedSemaphore};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        //failed to submit
        if (vkQueueSubmit(mVulkanInfo.gfxQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        //presentation info
        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        //which semaphores to wait on for presentation
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        //specify swapchain to present images and the index of the target image
        VkSwapchainKHR swapChains[] = {mVulkanInfo.swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imageIndex;

        //not necessary with one swapchain but this checks if all swapchain presentation was successful or not
        presentInfo.pResults = nullptr; // Optional

        //present image to swapchain
        vkQueuePresentKHR(mVulkanInfo.presentationQueue, &presentInfo);
    }

    VkShaderModule VulkanInfo::CreateShaderModule(const std::vector<char>& code)
    {
        VkShaderModuleCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(logicalDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module!");
        }

        return shaderModule;
    }

    void VulkanInfo::CreateRenderPass()
    {
        //render color in one of the images of the swapchain
        //format of attachment must match format of swap chain images
        VkAttachmentDescription colorAttachment = {};
        colorAttachment.format = swapChainImageFormat;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;

        //settings ofr what to do with data before and after render
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;      //LOAD, CLEAR, DONT_CARE
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;    //STORE, DONT_CARE

        //stencil buffer settings, doesnt matter for now but here they are
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

        //layouts for pixels in memory, may change existing texture and framebuffer format
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;              //before render pass, disregard preexisting image
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;          //after, ready for presentation using swapchain post render

        //create color attachment for subpass
        VkAttachmentReference colorAttachmentRef = {};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        //create subpass
        VkSubpassDescription subpass = {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        //refer to color attachment
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        //create actual render pass with above information
        VkRenderPassCreateInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colorAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;

        if (vkCreateRenderPass(logicalDevice, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass!");
        }

        //subpass dependencies (transitions between subpasses)
        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;

        //Order of operations, which operations wait on what -- look into this more later
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        //set dependencies in render pass
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;
    }

    void VulkanInfo::InitWindowSurface() {
        if (glfwCreateWindowSurface(VulkanInstance, RenderingSystem::GetWindow()->GetWindowRef(), nullptr, &WindowSurface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    bool VulkanInfo::SuitableDevice(VkPhysicalDevice targetDevice) {
        QueueFamilyIndices indices = FindQueueFamilies(targetDevice);

        //check for required extensions
        bool extensionsSupported = CheckDeviceExtSupport(targetDevice);

        //check for swapchain support, at least one supported image format and presentation mode
        bool swapChainAdequate = false;

        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = PollSwapChainSupport(targetDevice);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return indices.isComplete() && extensionsSupported && swapChainAdequate;
    }


}