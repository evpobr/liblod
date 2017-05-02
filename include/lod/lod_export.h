#ifdef LOD_EXPORTS

#ifdef _WIN32
#define LOD_API __declspec(dllexport)
#endif

#endif

#ifdef LOD_IMPORTS

#ifdef _WIN32
#define LOD_API __declspec(dllimport)
#endif

#endif

#ifndef LOD_API
#define LOD_API
#endif
