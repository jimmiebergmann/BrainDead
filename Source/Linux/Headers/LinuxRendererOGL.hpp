#ifndef __BRAINDEAD_LINUXRENDEREROGL_HPP__
#define __BRAINDEAD_LINUXRENDEREROGL_HPP__

#include <Renderer.hpp>
#include <OGL/OpenGL.hpp>

namespace BD
{
	class LinuxRendererOGL : public Renderer
	{
	public:
		LinuxRendererOGL( );
		virtual ~LinuxRendererOGL( );

		virtual BD_UINT32 Create( const Window &p_Window );
		virtual Texture * CreateTexture( );
		virtual VertexObject * CreateVertexObject( );
		virtual Shader * CreateShader(
			const Shader::eShaderType p_ShaderType );
		virtual ShaderProgram * CreateShaderProgram( );
		virtual void StartScene( );
		virtual void EndScene( );
		virtual void SetClearColor( const BD_FLOAT32 p_Red,
			const BD_FLOAT32 p_Green, const BD_FLOAT32 p_Blue,
			const BD_FLOAT32 p_Alpha );
		virtual void SetClearDepth( const BD_FLOAT32 p_Depth );
		virtual void SetViewport( const BD_UINT32 p_X, const BD_UINT32 p_Y,
			const BD_UINT32 p_Width, const BD_UINT32 p_Height );
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

	private:

		WINDATA	m_WinData;
	};
}

#endif

