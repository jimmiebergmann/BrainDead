#ifndef __BRAINDEAD_TEXTURE_HPP__
#define __BRAINDEAD_TEXTURE_HPP__

#include <DataTypes.hpp>
#include <Image.hpp>

namespace BD
{

	class Texture 
	{

	public:

		virtual ~Texture( ) { }
		virtual BD_UINT32 Load( const Image & p_Image) = 0;
		virtual void Bind( BD_UINT32 p_Index ) = 0;
		virtual void Unbind( ) = 0;
		// Filter functions
		// ...

		BD_INLINE BD_BOOL IsLoaded( ) { return m_Loaded; };

	protected:

		BD_BOOL m_Loaded;

	};

}

#endif
