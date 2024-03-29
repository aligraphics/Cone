#include "Core/CnPch.hpp"
#include "Utilities.hpp"

namespace Utilities
{
    void ChangeLayout(VkCommandBuffer commandBuffer, const LayoutTransitionInfo& layoutTransitionInfo)
    {
        VkImageMemoryBarrier barrier{};
        barrier.sType                           = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout                       = layoutTransitionInfo.oldLayout;
        barrier.newLayout                       = layoutTransitionInfo.newLayout;
        barrier.srcQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
        barrier.image                           = layoutTransitionInfo.image;
        barrier.subresourceRange.aspectMask     = layoutTransitionInfo.aspectFlags;
        barrier.subresourceRange.baseMipLevel   = 0;
        barrier.subresourceRange.levelCount     = layoutTransitionInfo.mipLevels;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount     = 1;

        VkPipelineStageFlags sourceStage;
        VkPipelineStageFlags destinationStage;

        if(layoutTransitionInfo.oldLayout == VK_IMAGE_LAYOUT_UNDEFINED)
        {
            barrier.srcAccessMask = 0;
            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        } else if(layoutTransitionInfo.oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
        {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        } else if(layoutTransitionInfo.oldLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)
        {
            barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            sourceStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        } else if(layoutTransitionInfo.oldLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
        {
            barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
            sourceStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        } else if(layoutTransitionInfo.oldLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
        {
            barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
            sourceStage = layoutTransitionInfo.sourceStageFlags;
        }
        else {
            throw std::invalid_argument("Error: This layout transition is unsupported!");
        }

        if(layoutTransitionInfo.newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
        {
            barrier.dstAccessMask   = VK_ACCESS_TRANSFER_WRITE_BIT;
            destinationStage        = VK_PIPELINE_STAGE_TRANSFER_BIT;
        } else if(layoutTransitionInfo.newLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
        {
            barrier.dstAccessMask   = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
            destinationStage        = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        } else if(layoutTransitionInfo.newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
        {
            barrier.dstAccessMask   = VK_ACCESS_SHADER_READ_BIT;
            destinationStage        = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        } else if(layoutTransitionInfo.newLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)
        {
            barrier.dstAccessMask   = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            destinationStage        = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        } else if(layoutTransitionInfo.newLayout == VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL)
        {
            barrier.dstAccessMask   = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
            destinationStage        = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
        }
        else {
            throw std::invalid_argument("Error: This layout transition is unsupported!");
        }

        vkCmdPipelineBarrier(
                commandBuffer,
                sourceStage, destinationStage,
                0,
                0, nullptr,
                0, nullptr,
                1, &barrier
        );
    }
}
