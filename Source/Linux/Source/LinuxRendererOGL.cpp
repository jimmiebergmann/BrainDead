#include <LinuxRendererOGL.hpp>
#include <Debugger.hpp>

namespace BD
{
	LinuxRendererOGL::LinuxRendererOGL( )
	{
	}

	LinuxRendererOGL::~LinuxRendererOGL( )
	{
	}

	BD_UINT32 LinuxRendererOGL::Create( const Window &p_Window )
	{
		m_WinData = p_Window.Data( );

		return BD_OK;
	}

	void LinuxRendererOGL::StartScene( )
	{
		GLbitfield Flags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
			GL_STENCIL_BUFFER_BIT;

		bglClear( Flags );
	}

	void LinuxRendererOGL::EndScene( )
	{
		glXSwapBuffers( m_WinData.pDisplay, m_WinData.Window );
	}

	void LinuxRendererOGL::SetClearColor( const BD_FLOAT32 p_Red,
		const BD_FLOAT32 p_Green, const BD_FLOAT32 p_Blue,
		const BD_FLOAT32 p_Alpha )
	{
		bglClearColor( p_Red, p_Green, p_Blue, 1.0f );
	}
	
	void LinuxRendererOGL::SetClearDepth( const BD_FLOAT32 p_Depth )
	{
	}

	void LinuxRendererOGL::SetViewport( const BD_UINT32 p_X,
		const BD_UINT32 p_Y, const BD_UINT32 p_Width,
		const BD_UINT32 p_Height )
	{
	}

	void LinuxRendererOGL::SetLineWidth( const BD_FLOAT32 p_Width )
	{
	}

	void LinuxRendererOGL::ClearColor( )
	{
	}

	void LinuxRendererOGL::ClearDepth( )
	{
	}

	void LinuxRendererOGL::EnableTexture( )
	{
	}

	void LinuxRendererOGL::DisableTexture( )
	{
	}

	void LinuxRendererOGL::EnableAlpha( )
	{
	}

	void LinuxRendererOGL::DisableAlpha( )
	{
	}

	void LinuxRendererOGL::EnableDepthTest( )
	{
	}

	void LinuxRendererOGL::DisableDepthTest( )
	{
	}

	void LinuxRendererOGL::EnableSmoothLines( )
	{
	}

	void LinuxRendererOGL::DisableSmoothLines( )
	{
	}

}

