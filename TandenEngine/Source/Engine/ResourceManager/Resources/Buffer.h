//
// Created by rosser.martinez on 2/17/2019.
//

#ifndef TANDENENGINE_BUFFER_H
#define TANDENENGINE_BUFFER_H

#include <vulkan/vulkan.h>

class Buffer {

private:
    VkBuffer mBuffer;
    VkDevice mDevice;
    VkDeviceMemory mMemory;
    VkDeviceSize mSize;

public:
    VkBuffer GetBuffer() { return mBuffer; };
    VkDevice GetDevice() { return mDevice; };
    VkDeviceMemory GetMemory() { return mMemory; };
    VkDeviceSize GetSize() {return mSize; };

    void SetBuffer(VkBuffer newBuffer){ mBuffer = newBuffer; };
    void SetDevice(VkDevice newDevice){ mDevice = newDevice; };
    void SetMemory(VkDeviceMemory newMemory){ mMemory = newMemory; };
    void SetSize(VkDeviceSize newSize){ mSize = newSize; };

};


#endif //TANDENENGINE_BUFFER_H
