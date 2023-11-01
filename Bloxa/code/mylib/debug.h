#ifndef DEBUG_H
#define DEBUG_H
///----------------------------------------------------------------------------|
/// "debug.h"
///----------------------------------------------------------------------------:
#include <iostream>
#include <string_view>

#define MYDEBUG
#ifdef  MYDEBUG
    #define ASSERT(U) if(!(U)) {std::cout  << "\aASSERT: FILE: "   \
                                       << cutpath(__FILE__)    \
                                       << ", LINE: "           \
                                       << __LINE__ << '\n' ; ll}
    #define ppp  std::cin.get();
    #define sss  std::wcout << "\nSIGNAL\n";ln
    #define l(a) std::cout  << #a << ": " << (a) << '\n';
    #define ln   std::cout  << '\n';
#else
    #define ASSERT(U)
    #define ppp
    #define sss
    #define l(a)
    #define ln
#endif

inline std::string cutpath  (std::string s)
{   auto p = s.find  ("code");
    return   s.substr(p , s.size() - p);
}

struct  CustomException : public std::exception
{       CustomException(int line, const char* filename, const char* mess = "")
        {   reason  = "ERROR_EXCEPTION:\n  File: ";
            reason += cut(filename);
            reason += "\n  Line: ";
            reason += std::to_string(line);
            reason += "\n  Mess: ";

            if(std::string_view(mess) != "")
            {    reason += mess;
                 reason += "\n";
            }
            else reason += "...\n";
        }

    std::string_view BASE = "code";
    std::string      reason;

    virtual const char* what() const throw()
    {   return  reason.c_str();
    }

    std::string cut(std::string  s)
    {   const auto pos = s.find  (BASE) + BASE.size () + 1;
        return           s.substr(pos, s.size() - pos);
    }
};


#define ERROR_EXCEPTION         (CustomException(__LINE__, __FILE__))
#define ERROR_EXCEPTION_MESS(M) (CustomException(__LINE__, __FILE__, M))

#define IFERROR_EXCEPTION(A) if((A)) \
    throw(CustomException(__LINE__, __FILE__, #A));

#define TESTCLASS(A,n) void testclass_##A##_##n()
#define TESTRUN(A,n)   testclass_##A##_##n()

#endif // DEBUG_H
