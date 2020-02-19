#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#if defined(__WIN__) || defined(_WIN32) || defined(_WIN64)
    #if LOCOMOTIVE_EXPORTS
        #define LOCOMOTIVE_API __declspec(dllexport)
    #else
        #define LOCOMOTIVE_API __declspec(dllimport)
    #endif
#else
    #define LOCOMOTIVE_API __attribute__((visibility("default")))
#endif

#endif
