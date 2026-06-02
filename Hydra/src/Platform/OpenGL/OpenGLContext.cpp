#include "hdpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <Hydra/Core/Base.h>

namespace Hydra
{

	OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HD_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		HD_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HD_CORE_ASSERT(status, "Failed to initialize Glad!");

		HD_CORE_INFO("OpenGL Info:");
		HD_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		HD_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		HD_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		HD_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hydra requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		HD_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}
