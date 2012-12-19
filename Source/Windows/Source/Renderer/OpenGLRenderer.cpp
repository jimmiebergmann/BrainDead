#include <Renderer/OpenGLRenderer.hpp>
#include <OpenGL/OpenGL.hpp>

OpenGLRenderer::~OpenGLRenderer()
{
}

OpenGLRenderer::OpenGLRenderer() :
	m_pHDC(NULL)
{

}

int OpenGLRenderer::Create(Window & window)
{
	// Make sure the window is loaded before we do anything.
	if(window.IsLoaded() == false)
	{
		return 1;
	}

	// Get tje HDC from the window class, also make sure it's not null.
	if((m_pHDC = window.GetHDC()) == NULL)
	{
		return 1;
	}


	// Load the rest of the renderer.

	return 0;
}

void OpenGLRenderer::StartScene()
{
}

void OpenGLRenderer::EndScene()
{
	SwapBuffers(*m_pHDC);
}

void OpenGLRenderer::SetClearColor(const float r, const float g, const float b, const float a)
{
	glClearColor(r, g, b, a);
}

void OpenGLRenderer::SetClearDepth(float depth)
{
	glClearDepth(depth);
}

void OpenGLRenderer::SetViewport(const int lx, const int ly,const int hx, const int hy)
{
	glViewport(lx, ly, hx, hy);
}

void OpenGLRenderer::SetLineWidth(const float width)
{
	glLineWidth(width);
}

void OpenGLRenderer::ClearColor()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
void OpenGLRenderer::ClearDepth()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::EnableTexture()
{
	glEnable(GL_TEXTURE_2D);
}

void OpenGLRenderer::DisableTexture()
{
	glDisable(GL_TEXTURE_2D);
}

void OpenGLRenderer::EnableAlpha()
{
	/// We have to make this function customizable.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glAlphaFunc(GL_GREATER, 0);
	glEnable(GL_ALPHA_TEST);
}

void OpenGLRenderer::DisableAlpha()
{
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}

void OpenGLRenderer::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void OpenGLRenderer::DisableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}

void OpenGLRenderer::EnableSmoothLines()
{
	glEnable(GL_LINE_SMOOTH);
}

void OpenGLRenderer::DisableSmoothLines()
{
	glDisable(GL_LINE_SMOOTH);
}
