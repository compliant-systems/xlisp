#include <windows.h> // must include for SEH to work

#ifndef WIN32
#error this is Windows build only
#endif // WIN32

#if _HAS_EXCEPTIONS
#error _HAS_EXCEPTIONS must not be 1 , add the /kernel switch to the cl command line
#endif

#include <vector>
#include <stdio.h>

// also would like to use 
// full nonstd in here
// #include <nonstd/whatever>

/*

Caveat Emptor: how to build with /kernel switch

it is not enough to just provide /kernel switch
one has to manually remove any /EH switch 
usually in  windows builds /EHsc is added by default

This will not stop the build but RTTI (/GR-) has to be  
also explicitly added as it is not switched off 
by using the /kernel switch
*/

static void does_not_compile(void)
{
    /*
    error C2980: C++ exception handling is not supported with /kernel
    try { throw 13; }
    catch (...) {}
    */
}

int main()
{
    __try {
        // also would like to use 
        // full nonstd in here
        std::vector<int> v_{ 1,2,3 };

        // std::out_of_range
        (void)v_.at(42);
    }
    __except ( EXCEPTION_EXECUTE_HANDLER /* aka 0*/) {
        puts("Structured Exception from MS STL was caught");
    }

    return 42;
}

