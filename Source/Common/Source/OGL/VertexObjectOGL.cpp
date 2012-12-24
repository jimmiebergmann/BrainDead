#include <OGL/VertexObjectOGL.hpp>

namespace BD
{

	// Setting the static render mode values.
	GLenum VertexObjectOGL::s_RenderModes[3] = { GL_TRIANGLES, GL_LINES, GL_LINE_STRIP };


	VertexObjectOGL::VertexObjectOGL() :
		m_VertexArrayObject(0),
		m_pVertexBufferObject(BD_NULL)
	{
		m_Loaded = BD_FALSE;
		m_TotalPieceSize = 0;
	}

	VertexObjectOGL::~VertexObjectOGL()
	{
		// Unload all the VBOs
		if(m_pVertexBufferObject != BD_NULL)
		{
			for(BD_MEMSIZE i = 0; i < m_VertexBufferObjectCount; i++)
			{

			}

			delete [ ] m_pVertexBufferObject;
			m_pVertexBufferObject = BD_NULL;
		}



		m_BufferVector.clear();
		m_Loaded = BD_FALSE;
	}

	BD_UINT32 VertexObjectOGL::AddVertexBuffer( BD_FLOAT32 * p_pBuffer, BD_UINT32 p_VertexSize,
			BD_UINT32 & p_VertexIndex )
	{
		// Make sure the vertex buffer isn't NULL:
		if( p_pBuffer  == BD_NULL )
		{
			return BD_ERROR;
		}

		// Add the buffer to a temporary struct which is being used in the Load function.
		BufferStruct BufferData;
		BufferData.pBuffer = p_pBuffer;
		BufferData.VertexSize = p_VertexSize;

		p_VertexIndex = m_BufferVector.size();
		m_BufferVector.push_back( BufferData );

		return BD_OK;
	}

	BD_UINT32 VertexObjectOGL::Load( BD_UINT32 p_PieceCount, BD_UINT32 p_PieceSize )
	{
		if( m_Loaded = BD_TRUE || p_PieceCount == 0 || p_PieceSize == 0 )
		{
			return BD_ERROR;
		}

		m_Loaded = BD_FALSE;
		m_BufferVector.clear();

		// Load the vertex buffer object
		//dglGenVertexArrays(1, &m_VertexArrayObject);
		//dglBindVertexArray(m_VertexArrayObject);
 

		// Allocate memory for the VBOs

		

		// Load every single vertex array object.


		m_TotalPieceSize = p_PieceCount * p_PieceSize;

		m_Loaded = BD_TRUE;
		return BD_OK;
	}

	void VertexObjectOGL::Render(eRenderMode p_Mode)
	{
		// Make sure the vertex object is loaded.
		if(m_Loaded == BD_FALSE)
		{
			return;
		}

		bglBindVertexArray(m_VertexArrayObject);
		glDrawArrays(s_RenderModes[ (int)( p_Mode ) ], 0, m_TotalPieceSize);
		bglBindVertexArray(0);

	}

}