//
// Created by rosser.martinez on 2/17/2019.
//

#include "Buffer.h"

namespace TandenEngine {

    void Buffer::destroy() {
        if (mBuffer) {
            vkDestroyBuffer(mDevice, mBuffer, nullptr);
        }

        if (mMemory) {
            vkFreeMemory(mDevice, mMemory, nullptr);
        }
    }

    VkResult Buffer::flush(VkDeviceSize size, VkDeviceSize offset) {
        VkMappedMemoryRange mappedRange = {};
        mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedRange.memory = mMemory;
        mappedRange.offset = offset;
        mappedRange.size = size;
        return vkFlushMappedMemoryRanges(mDevice, 1, &mappedRange);
    }
}  // namespace TandenEngine