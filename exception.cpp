#include <exception>
#include <boost/multiprecision/cpp_int.hpp>

#include "exception.hpp"

using namespace boost::multiprecision;

IsPrimeException::IsPrimeException(cpp_int p)
{
    std::string p_str = p.str();
    std::string err_kind = "ECGroup constructor error: ";
    std::string msg = p_str + " is not prime number, so ECGroup object cannot not boost.";

    err_msg = err_kind + msg;
}



ECZeroException::ECZeroException()
{
    err_msg = "ECElement constructor error: This is not ZERO, and arguments is invalid";
}



PointOnECException::PointOnECException(cpp_int x, cpp_int y, cpp_int A, cpp_int B, cpp_int MOD)
{
    std::string err_kind = "ECElement constructor error: ";
    std::string x_str = x.str();
    std::string y_str = y.str();
    std::string a_str = A.str();
    std::string b_str = B.str();
    std::string mod_str = MOD.str();

    err_msg = "constructor error: (" + x_str + ", " + y_str + ") is not on the Ecliptic Curve: y**2 = x**3 + " + a_str  
    + "*x + " + b_str + " when modulo " + mod_str; 

}



IsECException::IsECException(cpp_int A, cpp_int B, cpp_int MOD)
{
    std::string err_kind = "ECGroup constructor error: ";
    std::string a_str = A.str();
    std::string b_str = B.str();
    std::string mod_str = MOD.str();
    err_msg = "when modulo " + mod_str + ", this parameter:  (" + a_str + ", "+ b_str 
    +  ") cannot meet definition of Ecliptic Curve.";

}




