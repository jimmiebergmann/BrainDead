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
			RENDERMODE_TRIANGLES = 0,
			RENDERMODE_LINES = 1,
			RENDERMODE_LINE_STRIP = 2
		};

		virtual ~VertexObject( ) { }
		virtual BD_UINT32 AddVertexBuffer( BD_FLOAT32 * p_pBuffer, BD_UINT32 p_VertexSize,
			BD_UINT32 & p_VertexIndex ) = 0;
		virtual BD_UINT32 Load( BD_UINT32 p_PieceCount, BD_UINT32 p_PieceSize ) = 0;
		virtual void Render(eRenderMode p_Mode) = 0;
		virtual void RenderParts(eRenderMode p_Mode, BD_UINT32 p_Start, BD_UINT32 p_Length ) = 0;

		BD_INLINE BD_BOOL IsLoaded( ) const { return m_Loaded; }

	protected:

		struct BufferStruct
		{
			BD_FLOAT32 * pBuffer;
			BD_UINT32 VertexSize;	// How many bytes per vertex? 2 / 3 ?
		};

		BD_BOOL m_Loaded;
		BD_UINT32 m_TotalPieceSize;	// PieceCount + PieceSize
		std::vector<BufferStruct> m_BufferVector;

	};

}

#endif