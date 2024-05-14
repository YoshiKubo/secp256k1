#include "ec_group.hpp"
#include "math_tools.hpp"
#include "exception.hpp"

#include <string>
#include <iostream>
#include <exception>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;








ECGroup::ECGroup(cpp_int a, cpp_int b, cpp_int p): A(a), B(b), MOD(p)
{
    try
    {
        #ifdef SAFE_MODE
        if(!is_prime(p))
        {
            throw IsPrimeException(p) ;
        }
        #endif

        if(!(is_EC(A, B, MOD)))
        {
            throw IsECException(A, B, MOD);
        }

    
    }
    catch(IsPrimeException& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    catch(IsECException& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
      
}