#pragma once

#ifdef __unix__
    #define RESET   "\033[0m"
    #define GRAY    "\033[30m"
    #define RED     "\033[31m"
    #define GREEN   "\033[32m"
    #define YELLOW  "\033[33m"
    #define BLUE    "\033[34m"
    #define MAGENTA "\033[35m"
    #define CYAN    "\033[36m"
    #define WHITE   "\033[37m"
#else
    #define RESET   ""
    #define GRAY    ""
    #define RED     ""
    #define GREEN   ""
    #define YELLOW  ""
    #define BLUE    ""
    #define MAGENTA ""
    #define CYAN    ""
    #define WHITE   ""
#endif
