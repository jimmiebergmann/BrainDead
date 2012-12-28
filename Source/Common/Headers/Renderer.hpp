#ifndef __BRAINDEAD_RENDERER_HPP__
#define __BRAINDEAD_RENDERER_HPP__

#include <DataTypes.hpp>
#include <Window.hpp>
#include <Texture.hpp>
#include <VertexObject.hpp>
#include <Shader.hpp>
#include <ShaderProgram.hpp>

namespace BD
{

	class Renderer
	{

	public:

		enum eRendererType
		{
			RENDERERTYPE_NONE = 0,
			RENDERERTYPE_OPENGL3 = 1,
			RENDERERTYPE_OPENGL2 = 2
		};

		virtual ~Renderer( ){ }
		virtual BD_UINT32 Create( const Window & p_Window ) = 0;
		virtual Texture * CreateTexture( ) = 0;
		virtual VertexObject * CreateVertexObject( ) = 0;
		virtual Shader * CreateShader( const Shader::eShaderType p_ShaderType) = 0;
		virtual ShaderProgram * CreateShaderProgram( ) = 0;
		virtual void StartScene( ) = 0;
		virtual void EndScene( ) = 0;
		virtual void SetClearColor( const BD_FLOAT32 p_R, const BD_FLOAT32 p_G, const BD_FLOAT32 p_B, const BD_FLOAT32 p_A ) = 0;
		virtual void SetClearDepth( BD_FLOAT32 p_Depth ) = 0;
		virtual void SetViewport( const BD_UINT32 p_LX, const BD_UINT32 p_LY, const BD_UINT32 p_HX, const BD_UINT32 p_HY ) = 0; // Lower and higher coordinates
		virtual void SetLineWidth( const BD_FLOAT32 p_Width ) = 0;
		virtual void ClearColor( ) = 0;
		virtual void ClearDepth( ) = 0;
		virtual void EnableTexture( ) = 0;
		virtual void DisableTexture( ) = 0;
		virtual void EnableAlpha( ) = 0;
		virtual void DisableAlpha( ) = 0;
		virtual void EnableDepthTest( ) = 0;
		virtual void DisableDepthTest( ) = 0;
		virtual void EnableSmoothLines( ) = 0;
		virtual void DisableSmoothLines( ) = 0;
		virtual BD_BOOL IsCreated( ) const = 0;
		virtual eRendererType GetRendererType( ) const = 0;
	};
}

#endif
