#if WINDOWS
    #if LOCOMOTIVE_EXPORTS
        #define LOCOMOTIVE_API __declspec(dllexport)
    #else
        #define LOCOMOTIVE_API __declspec(dllimport)
    #endif
#else
    #define LOCOMOTIVE_API __attribute__((visibility("default")))
#endif