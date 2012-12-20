#ifndef __BRAINDEAD_COMPILER_GCC_HPP__
#define __BRAINDEAD_COMPIELR_GCC_HPP__

#define BD_GCCVER ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + \
	__GNU_PATCHLEVEL__ )

#define PACKDATA_BEGIN( p_Align )
#define PACKDATA_END( p_Align ) __attribute__( ( __aligned__( p_Align ) ) )

#define BD_INLINE		__inline__
#define BD_FORCE_INLINE	__forceinline__
#define BD_EXPLICIT		explicit

// If GCC is greater than 4.6.0, enable C++11 features
#if BD_GCCVER >= 40600
#define BD_NULL	nullptr
#else
#define BD_NULL	NULL
#endif

#endif

