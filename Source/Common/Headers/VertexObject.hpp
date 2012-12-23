#ifndef __BRAINDEAD_VERTEX_OBJECT_HPP__
#define __BRAINDEAD_VERTEX_OBJECT_HPP__

#include <DataTypes.hpp>

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
		BD_INLINE BD_BOOL IsLoaded( ) const { return m_Loaded; }

	protected:

		BD_BOOL m_Loaded;

	};

}

#endif