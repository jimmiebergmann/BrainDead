#include <WindowsRendererOGL.hpp>

namespace BD
{
	WindowsRendererOGL::~WindowsRendererOGL()
	{
		m_Created = BD_FALSE;
		wglMakeCurrent(BD_NULL, BD_NULL);

		if(m_Context)
		{
			wglDeleteContext(m_Context);
			m_Context = BD_NULL;
		}

	}

	WindowsRendererOGL::WindowsRendererOGL() :
		Renderer(),
		m_Context(BD_NULL),
		m_HDC(BD_NULL)
	{
	}

	BD_UINT32 WindowsRendererOGL::Create( const Window & p_Window)
	{
		m_eRendererType = RENDERERTYPE_NONE;

		// Make sure the window is created.
		if(p_Window.IsCreated() == false)
		{
			return BD_ERROR;
		}

		// Get the HDC from the window class, also make sure it's not null.
		if((m_HDC = p_Window.Data().DeviceContext) == BD_NULL)
		{
			return BD_ERROR;
		}

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

		if((PixelFormat = ChoosePixelFormat(m_HDC, &PFD)) == 0)
		{
			return BD_ERROR;
		}
		if((SetPixelFormat(m_HDC, PixelFormat, &PFD)) == BD_FALSE)
		{
			return BD_ERROR;
		}

		// Create a temporary regual context.
		// We need this context to create the 3.x context.
		HGLRC TemporaryContext = wglCreateContext(m_HDC);

		if(TemporaryContext == BD_NULL)
		{
			return BD_ERROR;
		}

		// Make the temporary context to the current one
		wglMakeCurrent(BD_NULL, BD_NULL);
		wglMakeCurrent(m_HDC, TemporaryContext);

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
		if((wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB")) == BD_NULL)
		{
			return BD_ERROR;
		}

		// Create the context
		if((m_Context = wglCreateContextAttribsARB(m_HDC, 0, Attribs)) != BD_NULL)
		{
			// Delete the old temporary context
			wglMakeCurrent(BD_NULL, BD_NULL);
			wglDeleteContext(TemporaryContext);

			// Make the new ogl 3 context to the current one.
			wglMakeCurrent(m_HDC, m_Context);

			m_eRendererType = RENDERERTYPE_OPENGL3;
		}
		else
		{
			// The creation of the OGL 3.3 context failed, use the temporary > 3.3 context instead.
			m_Context = TemporaryContext;
			m_eRendererType = RENDERERTYPE_OPENGL2;
		}

		// Load all the opengl extensions
		if(GlExt::Load() == BD_ERROR)
		{
			return BD_ERROR;
		}

		m_Created = BD_TRUE;
		return BD_OK;
	}


	void WindowsRendererOGL::StartScene()
	{

	}

	void WindowsRendererOGL::EndScene()
	{
		SwapBuffers(m_HDC);
	}

	void WindowsRendererOGL::SetClearColor(const BD_FLOAT32 r, const BD_FLOAT32 g, const BD_FLOAT32 b, const BD_FLOAT32 a)
	{
		glClearColor(r, g, b, a);
	}

	void WindowsRendererOGL::SetClearDepth(float depth)
	{
		glClearDepth(depth);
	}

	void WindowsRendererOGL::SetViewport(const BD_UINT32 lx, const BD_UINT32 ly, const BD_UINT32 hx, const BD_UINT32 hy)
	{
		glViewport(lx, ly, hx, hy);
	}

	void WindowsRendererOGL::SetLineWidth(const BD_FLOAT32 width)
	{
		glLineWidth(width);
	}

	void WindowsRendererOGL::ClearColor()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void WindowsRendererOGL::ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void WindowsRendererOGL::EnableTexture()
	{
		glEnable(GL_TEXTURE_2D);
	}

	void WindowsRendererOGL::DisableTexture()
	{
		glDisable(GL_TEXTURE_2D);
	}

	void WindowsRendererOGL::EnableAlpha()
	{
		/// We have to make this function customizable.
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glAlphaFunc(GL_GREATER, 0);
		glEnable(GL_ALPHA_TEST);
	}

	void WindowsRendererOGL::DisableAlpha()
	{
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
	}

	void WindowsRendererOGL::EnableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void WindowsRendererOGL::DisableDepthTest()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void WindowsRendererOGL::EnableSmoothLines()
	{
		glEnable(GL_LINE_SMOOTH);
	}

	void WindowsRendererOGL::DisableSmoothLines()
	{
		glDisable(GL_LINE_SMOOTH);
	}

}