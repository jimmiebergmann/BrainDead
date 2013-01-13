#ifndef __BRAINDEAD_LEVEL_HPP__
#define __BRAINDEAD_LEVEL_HPP__

#include <DataTypes.hpp>
#include <Renderer.hpp>
#include <Random.hpp>
#include <Font.hpp>

#define BD_LEVEL_TILE_SIZE 32
#define BD_LEVEL_TILE_ZOOM 3


namespace BD
{

	class Level
	{

	public:

		Level( Renderer * p_pRenderer );
		~Level( );
		BD_UINT32 Load( );
		void Generate( );
		BD_UINT32 Update( BD_FLOAT64 p_DeltaTime );
		BD_UINT32 Render( );
		BD_INLINE BD_BOOL IsLoaded( ) const { return m_Loaded; }

	private:

		BD_BOOL m_Loaded;
		BD_BOOL m_Generated;
		Renderer * m_pRenderer;
		Font * m_pFont;

	};

}


#endif