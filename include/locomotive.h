#ifdef LOCOMOTIVE_EXPORTS
#define LOCOMOTIVE_API __declspec(dllexport)
#else
#define LOCOMOTIVE_API __declspec(dllimport)
#endif