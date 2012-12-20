#include <Renderer/Renderer.hpp>

namespace BD
{

	Renderer::Renderer() :
		m_Created(BD_FALSE),
		m_eRenderType(RENDERERTYPE_NONE)
	{
	}

	BD_BOOL Renderer::IsCreated() const
	{
		return m_Created;
	}

}