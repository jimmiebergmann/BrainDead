#ifndef __DAWN_VERTEX_OBJECT_OGL_HPP__
#define __DAWN_VERTEX_OBJECT_OGL_HPP__

#include <VertexObject.hpp>
#include <OGL/OpenGL.hpp>

namespace BD
{
	class VertexObjectOGL : public VertexObject
	{

	public:

		VertexObjectOGL();
		virtual ~VertexObjectOGL();
		virtual BD_UINT32 AddVertexBuffer( BD_FLOAT32 * p_Buffer, BD_UINT32 p_VertexSize,
			BD_UINT32 & p_VertexIndex );
		virtual BD_UINT32 Load( BD_UINT32 p_PieceCount, BD_UINT32 p_PieceSize );

	private:

		

	};

}

#endif

