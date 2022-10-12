#pragma once

#include <Core/CnPch.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(const VkExtent2D extent, const std::string& windowTitle);
    ~Window();

    Window(const Window& otherWindow) = delete;
    Window& operator=(const Window& otherWindow) = delete;
public:
    inline GLFWwindow* GetGLFWWindow() const { return m_Window; }
    inline bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }
    inline void PollEvents() const { glfwPollEvents(); }
    inline int GetWidth() const { return m_Extent.width; }
    inline int GetHeight() const { return m_Extent.height; }
private:
    GLFWwindow* m_Window;
    VkExtent2D  m_Extent;
    std::string m_WindowTitle;
};
