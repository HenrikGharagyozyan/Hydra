#include "hdpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/gl.h>

#include <Hydra/Core.h>

namespace Hydra
{

	OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HD_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HD_CORE_ASSERT(status, "Failed to initialize Glad!");

		HD_CORE_INFO("OpenGL Info:");
		HD_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		HD_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		HD_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
