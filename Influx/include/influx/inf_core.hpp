#if defined(NEO_PLATFORM_WINDOWS)

	#define INF_EXPORT __declspec(dllexport)
	#define INF_IMPORT __declspec(dllimport)

	#if defined(INF_BUILD_DLL)
		#define INF_API INF_EXPORT
	#else
		#define INF_API INF_IMPORT
	#endif

#elif defined(NEO_PLATFORM_LINUX)

	#define INF_EXPORT 
	#define INF_IMPORT 
	#define INF_API
#endif