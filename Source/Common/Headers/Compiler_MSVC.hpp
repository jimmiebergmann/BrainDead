#ifndef __BRAINDEAD_COMPILER_MSVC_HPP__
#define __BRAINDEAD_COMPILER_MSVC_HPP__

#define PACKDATA_BEGIN( p_Align ) __declspec( align( p_Align ) )
#define PACKDATA_END( p_Align )

#define BD_INLINE		inline
#define BD_FORCE_INLINE	__forceinline
#define D_EXPLICIT		explicit

// VS 2010 and greater support C++11
#if( _MSC_VER >= 1600 )
#define BD_NULL nullptr
#else
#define BD_NULL NULL
#endif

#endif

