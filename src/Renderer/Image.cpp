#include "Core/CnPch.hpp"
#include "Image.hpp"

#include "Context.hpp"

Image::Image(Context* context, const ImageInfo& imageInfo)
    :   m_Context{context}, m_Image{}, m_ImageView{},
        m_ImageLayout{VK_IMAGE_LAYOUT_UNDEFINED}, m_ImageFormat{imageInfo.format},
        m_ImageDimension{imageInfo.dimension}, m_UsageFlags{imageInfo.usageFlags},
        m_AspectFlags{imageInfo.aspectFlags}, m_ImageMemory{}
{
    CreateImage();
    CreateImageView();
}

void Image::ChangeLayout(VkImageLayout newLayout)
{
    VkCommandBuffer commandBuffer = m_Context->BeginSingleTimeCommands(Context::CommandType::GRAPHICS);
    Utilities::ChangeLayout(commandBuffer, m_ImageLayout, newLayout, m_Image, m_AspectFlags);
    m_Context->EndSingleTimeCommands(Context::CommandType::GRAPHICS, commandBuffer);

    m_ImageLayout = newLayout;
}

void Image::CreateImage()
{
    VkImageCreateInfo imageCreateInfo{};
    imageCreateInfo.sType           = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageCreateInfo.imageType       = VK_IMAGE_TYPE_2D;
    imageCreateInfo.format          = m_ImageFormat;
    imageCreateInfo.extent.width    = m_ImageDimension.width;
    imageCreateInfo.extent.height   = m_ImageDimension.height;
    imageCreateInfo.extent.depth    = 1U;
    imageCreateInfo.mipLevels       = 1U;
    imageCreateInfo.arrayLayers     = 1U;
    imageCreateInfo.samples         = VK_SAMPLE_COUNT_1_BIT;
    imageCreateInfo.tiling          = VK_IMAGE_TILING_OPTIMAL;
    imageCreateInfo.usage           = m_UsageFlags;
    imageCreateInfo.sharingMode     = VK_SHARING_MODE_EXCLUSIVE;
    imageCreateInfo.initialLayout   = VK_IMAGE_LAYOUT_UNDEFINED;

    VK_CHECK(vkCreateImage(m_Context->GetLogicalDevice(), &imageCreateInfo, nullptr, &m_Image))
}

void Image::CreateImageView()
{
    VkImageViewCreateInfo imageViewCreateInfo{};
    imageViewCreateInfo.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.image                           = m_Image;
    imageViewCreateInfo.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
    imageViewCreateInfo.format                          = m_ImageFormat;
    imageViewCreateInfo.subresourceRange.aspectMask     = m_AspectFlags;
    imageViewCreateInfo.subresourceRange.baseMipLevel   = 0;
    imageViewCreateInfo.subresourceRange.levelCount     = 1;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
    imageViewCreateInfo.subresourceRange.layerCount     = 1;

    VK_CHECK(vkCreateImageView(m_Context->GetLogicalDevice(), &imageViewCreateInfo, nullptr, &m_ImageView))
}

Image::~Image()
{
    if(m_ImageView)
    {
        vkDestroyImageView(m_Context->GetLogicalDevice(), m_ImageView, nullptr);
    }
    if(m_Image)
    {
        vkDestroyImage(m_Context->GetLogicalDevice(), m_Image, nullptr);
    }
    if(m_ImageMemory)
    {
        vkFreeMemory(m_Context->GetLogicalDevice(), m_ImageMemory, nullptr);
    }
}
