#include <Renderer/OpenGLRenderer.hpp>
#include <OpenGL/OpenGL.hpp>

namespace BD
{
	OpenGLRenderer::~OpenGLRenderer()
	{
	}

	OpenGLRenderer::OpenGLRenderer() :
		m_Context(NULL),
		m_pHDC(NULL),
		m_eRenderType(RENDERERTYPE_NONE)
	{

	}

	BD_UINT32 OpenGLRenderer::Create(Window & p_window)
	{
		// Make sure the window is loaded before we do anything.
		/*if(p_window.IsLoaded() == false)
		{
			return BD_ERROR;
		}

		// Get the HDC from the window class, also make sure it's not null.
		if((m_pHDC = p_window.GetHDC()) == NULL)
		{
			return BD_ERROR;
		}
*/
		// Filling the pixel fromat structure.
		static PIXELFORMATDESCRIPTOR PFD = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			16,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			16,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		// Choose and set the pixel format
		GLuint PixelFormat;

		if((PixelFormat = ChoosePixelFormat(*m_pHDC, &PFD)) == 0)
		{
			return BD_ERROR;
		}
		if((SetPixelFormat(*m_pHDC, PixelFormat, &PFD)) == false)
		{
			return BD_ERROR;
		}

		// Create a temporary regual context.
		// We need this context to create the 3.x context.
		HGLRC TemporaryContext = wglCreateContext(*m_pHDC);

		if(TemporaryContext == NULL)
		{
			return BD_ERROR;
		}

		// Make the temporary context to the current one
		wglMakeCurrent(NULL, NULL);
		wglMakeCurrent(*m_pHDC, TemporaryContext);

		// Attributes for the OGL 3.3 context
		int Attribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			0
		};

		// We need the proc address for the function
		// we are going to use for OGL 3.3 context creation.
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
		if((wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB")) = NULL)
		{
			return BD_ERROR;
		}

		// Create the context
		if((m_Context = wglCreateContextAttribsARB(*m_pHDC, 0, Attribs)) != NULL)
		{
			// Delete the old temporary context
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(TemporaryContext);

			// Make the new ogl 3 context to the current one.
			wglMakeCurrent(*m_pHDC, m_Context);

			m_eRenderType = RENDERERTYPE_OPENGL3;
		}
		else
		{
			// The creation of the OGL 3.3 context failed, use the temporary > 3.3 context instead.
			m_Context = TemporaryContext;
			m_eRenderType = RENDERERTYPE_OPENGL2;
		}

		// Load all the opengl extensions
		if(GlExt::Load() == false)
		{
			return BD_ERROR;
		}

		return BD_OK;
	}

	void OpenGLRenderer::StartScene()
	{

	}

	void OpenGLRenderer::EndScene()
	{
		SwapBuffers(*m_pHDC);
	}

	void OpenGLRenderer::SetClearColor(const BD_FLOAT32 r, const BD_FLOAT32 g, const BD_FLOAT32 b, const BD_FLOAT32 a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLRenderer::SetClearDepth(float depth)
	{
		glClearDepth(depth);
	}

	void OpenGLRenderer::SetViewport(const BD_UINT32 lx, const BD_UINT32 ly, const BD_UINT32 hx, const BD_UINT32 hy)
	{
		glViewport(lx, ly, hx, hy);
	}

	void OpenGLRenderer::SetLineWidth(const BD_FLOAT32 width)
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

}