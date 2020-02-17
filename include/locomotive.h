#if WINDOWS
    #ifdef LOCOMOTIVE_EXPORTS
        #define LOCOMOTIVE_API __declspec(dllexport)
    #else
        #define LOCOMOTIVE_API __declspec(dllimport)
    #endif
#else
    #ifdef LOCOMOTIVE_EXPORTS
        #define LOCOMOTIVE_API __attribute__((visibility("default")))
    #endif
#endif