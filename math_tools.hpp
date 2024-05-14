#ifndef MATH_TOOLS_H
#define MATH_TOOLS_H

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;


bool is_prime(cpp_int n);
bool is_EC(cpp_int a_, cpp_int b_, cpp_int p);



#endif