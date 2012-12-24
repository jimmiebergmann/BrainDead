#ifndef __BRAINDEAD_VERTEX_OBJECT_HPP__
#define __BRAINDEAD_VERTEX_OBJECT_HPP__

#include <DataTypes.hpp>
#include <vector>

namespace BD
{

	class VertexObject
	{

	public:

		enum eRenderMode
		{
			RENDERMODE_NONE = 0,
			RENDERMODE_TRIANGLES = 1,
			RENDERMODE_LINES = 2,
			RENDERMODE_LINE_STRIP = 3
		};

		virtual ~VertexObject( ) { }
		virtual BD_UINT32 AddVertexBuffer( BD_FLOAT32 * p_Buffer, BD_UINT32 p_VertexSize,
			BD_UINT32 & p_VertexIndex ) = 0;
		virtual BD_UINT32 Load( BD_UINT32 p_PieceCount, BD_UINT32 p_PieceSize ) = 0;
		BD_INLINE BD_BOOL IsLoaded( ) const { return m_Loaded; }

	protected:

		struct BufferStruct
		{
			BD_FLOAT32 * pBuffer;
			BD_UINT32 VertexSize;	// How many bytes per vertex? 2 / 3 ?
		};

		BD_BOOL m_Loaded;
		std::vector<BufferStruct> m_BufferVector;

	};

}

#endif