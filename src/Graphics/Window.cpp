#include "Window.h"
#include "../util/Debug.h"

GLFW_window::GLFW_window(vec2ui dimentions, const char* name)
    : m_Window(nullptr)
{
    if (!glfwInit()) { Debug::Log("GFLW initialization failiure"); ASSERT(false); }

    m_Window = glfwCreateWindow(dimentions.v0, dimentions.v1, name, nullptr, nullptr);
    if (!m_Window) { Debug::Log("GFLW window creation failiure"); ASSERT(false); }
}
GLFW_window::GLFW_window(const char* name)
    : m_Window(nullptr)
{
    if (!glfwInit()) { Debug::Log("GFLW initialization failiure"); ASSERT(false); }
    
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    if (!primaryMonitor) { glfwTerminate(); Debug::Log("GFLW failed to detect screen dimentions"); ASSERT(false); }

    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    if (!videoMode) { glfwTerminate(); Debug::Log("GFLW failed to get video mode for primary monitor"); ASSERT(false); }

    GLFWwindow* window = glfwCreateWindow(
        videoMode->width, videoMode->height,
        name,
        primaryMonitor,
        nullptr
    );
    if (!m_Window) { Debug::Log("GFLW window creation failiure"); ASSERT(false); }
}

GLFW_window::~GLFW_window() 
{
	glfwDestroyWindow(m_Window);
    glfwTerminate();
    Debug::Log("Released window", Debug::INFO);
}

GLFWwindow* GLFW_window::ptr() 
{
	return m_Window;
}