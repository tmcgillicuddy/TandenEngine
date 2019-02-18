//
// Created by rosser.martinez on 2/17/2019.
//

#ifndef TANDENENGINE_BUFFER_H
#define TANDENENGINE_BUFFER_H

#include <vulkan/vulkan.h>

namespace TandenEngine {

    class Buffer {

    public:
        VkBuffer mBuffer = VK_NULL_HANDLE;
        VkDevice mDevice;
        VkDeviceMemory mMemory = VK_NULL_HANDLE;
        VkDeviceSize mSize;

        void* mMapped = nullptr;

        VkResult map(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0) {
            return vkMapMemory(mDevice, mMemory, offset, size, 0, &mMapped);
        }

        void unmap() {
            if (mMapped) {
                vkUnmapMemory(mDevice, mMemory);
                mMapped = nullptr;
            }
        }

        // Free memory for memory domain to use
        VkResult flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

        void destroy();  // Destroy buffer

    };

}  // namespace TandenEngine

#endif //TANDENENGINE_BUFFER_H
