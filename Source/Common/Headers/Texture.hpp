#ifndef __BRAINDEAD_TEXTURE_HPP__
#define __BRAINDEAD_TEXTURE_HPP__

#include <DataTypes.hpp>

namespace BD
{

	class Texture 
	{

	public:

		virtual ~Texture( );
		virtual BD_UINT32 Load( ) = 0;
		virtual BD_UINT32 Unload( ) = 0;
		virtual void Bind( );
		virtual void Unbind( );
		// Filter functions
		// ...

		BD_INLINE BD_BOOL IsLoaded( ) { return m_Loaded; };

	private:

		BD_BOOL m_Loaded;

	};

}

#endif
