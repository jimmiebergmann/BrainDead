#ifndef __BRAINDEAD_WINDOWS_RENDERER_OGL_HPP__
#define __BRAINDEAD_WINDOWS_RENDERER_OGL_HPP__

#include <Renderer.hpp>
#include <OGL/OpenGL.hpp>

namespace BD
{
	class WindowsRendererOGL : public Renderer
	{

	public:

		virtual ~WindowsRendererOGL( );
		WindowsRendererOGL( );
		virtual BD_UINT32 Create( const Window & p_Window );
		virtual Texture * CreateTexture( );
		virtual VertexObject * CreateVertexObject( );
		virtual Shader * CreateShader(  const Shader::eShaderType p_ShaderType );
		virtual ShaderProgram * CreateShaderProgram( );
		virtual void StartScene( ) ;
		virtual void EndScene( );
		virtual void SetClearColor( const BD_FLOAT32 p_R, const BD_FLOAT32 p_G, const BD_FLOAT32 p_B, const BD_FLOAT32 p_A );
		virtual void SetClearDepth( BD_FLOAT32 p_Depth );
		virtual void SetViewport( const BD_UINT32 p_LX, const BD_UINT32 p_LY, const BD_UINT32 p_HX, const BD_UINT32 p_HY ); // Lower and higher coordinates
		virtual void SetLineWidth( const BD_FLOAT32 p_Width );
		virtual void ClearColor( );
		virtual void ClearDepth( );
		virtual void EnableTexture( );
		virtual void DisableTexture( );
		virtual void EnableAlpha( );
		virtual void DisableAlpha( );
		virtual void EnableDepthTest( );
		virtual void DisableDepthTest( );
		virtual void EnableSmoothLines( );
		virtual void DisableSmoothLines( );
		virtual BD_BOOL IsCreated( ) const { return m_Created; }
		virtual eRendererType GetRendererType( ) const { return m_eRendererType; }
		
	private:

		HGLRC m_Context;
		HDC m_HDC;

	};

}

#endif
