#ifndef __BRAINDEAD_RENDERER_HPP__
#define __BRAINDEAD_RENDERER_HPP__

#include <DataTypes.hpp>
#include <Window.hpp>
#include <OGL/OpenGL.hpp>

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

		virtual BD_UINT32 Create( const Window & p_Window) = 0;
		virtual void StartScene() = 0;
		virtual void EndScene() = 0;
		virtual void SetClearColor(const BD_FLOAT32 r, const BD_FLOAT32 g, const BD_FLOAT32 b, const BD_FLOAT32 a) = 0;
		virtual void SetClearDepth(const BD_FLOAT32 depth) = 0;
		virtual void SetViewport(const BD_UINT32 lx, const BD_UINT32 ly,const BD_UINT32 hx, const BD_UINT32 hy) = 0; // Lower and higher coordinates
		virtual void SetLineWidth(const BD_FLOAT32 width) = 0;
		virtual void ClearColor() = 0;
		virtual void ClearDepth() = 0;
		virtual void EnableTexture() = 0;
		virtual void DisableTexture() = 0;
		virtual void EnableAlpha() = 0;
		virtual void DisableAlpha() = 0;
		virtual void EnableDepthTest() = 0;
		virtual void DisableDepthTest() = 0;
		virtual void EnableSmoothLines() = 0;
		virtual void DisableSmoothLines() = 0;
		virtual	BD_BOOL IsCreated() const = 0;
		virtual eRendererType GetRendererType() const = 0;

	};
}

#endif
