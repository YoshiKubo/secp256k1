#include "field_element.hpp"
#include <iostream>
#include <string>
#include <exception>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;





FieldElement::FieldElement(cpp_int x_, cpp_int p): MOD(p)
{

    if(x_ > 0)
    {
        x = x_ % MOD;  
    }
    else if(x_ == 0)
    {
        x = 0;
    }
    else
    {
        cpp_int temp = (-x_) % MOD;
        x = MOD - temp;
    }
}






//*************************************************************************************************************************//
//*********************   In binary operator, double Field Element's instances have to have same MOD   ********************//
//*************************************************************************************************************************//
// + operator
FieldElement operator+(FieldElement lhs, FieldElement rhs){     return FieldElement(lhs.x + rhs.x, lhs.MOD);}
FieldElement operator+(FieldElement lhs, cpp_int k){    return FieldElement(lhs.x + k, lhs.MOD);}
FieldElement operator+(cpp_int k, FieldElement rhs){    return FieldElement(k + rhs.x, rhs.MOD);}

// += operator
FieldElement& FieldElement::operator+=(FieldElement rhs)
{
    FieldElement temp = *this + rhs;
    x = temp.x;
    return *this;
}
FieldElement& FieldElement::operator+=(cpp_int k)
{
    FieldElement temp = *this + k;
    x = temp.x;
    return *this;
}






// - operator
FieldElement operator-(FieldElement lhs, FieldElement rhs){     return FieldElement(lhs.x - rhs.x, lhs.MOD);}
FieldElement operator-(FieldElement lhs, cpp_int k){    return FieldElement(lhs.x - k, lhs.MOD);}
FieldElement operator-(cpp_int k, FieldElement rhs){    return FieldElement(k - rhs.x, rhs.MOD);}
FieldElement FieldElement::operator-(){     return FieldElement(- x, MOD);}



// -= operator
FieldElement& FieldElement::operator-=(FieldElement rhs)
{
    FieldElement temp = *this - rhs;
    x = temp.x;
    return *this;
}
FieldElement& FieldElement::operator-=(cpp_int k)
{
    FieldElement temp = *this - k;
    x = temp.x;
    return *this;
}





// * operator
FieldElement operator*(FieldElement lhs, FieldElement rhs){     return FieldElement(lhs.x * rhs.x, lhs.MOD);}
FieldElement operator*(FieldElement lhs, cpp_int k){    return FieldElement(lhs.x * k, lhs.MOD);}
FieldElement operator*(cpp_int k, FieldElement rhs){    return FieldElement(k * rhs.x, rhs.MOD);}


// *= operator
FieldElement& FieldElement::operator*=(FieldElement rhs)
{
    FieldElement temp = *this * rhs;
    x = temp.x;
    return *this;
}
FieldElement& FieldElement::operator*=(cpp_int k)
{
    FieldElement temp = *this * k;
    x = temp.x;
    return *this;
}






FieldElement pow(FieldElement a, cpp_int k)
{
    
    k = k % (a.MOD - 1);
    
    FieldElement ret = FieldElement(1, a.MOD);
    FieldElement temp = a;
    cpp_int digit;

    while(k != 0)
    {
        digit = k % 2;
        if(digit != 0)
        {
            ret *= temp;
        }
        
        temp *= temp;
        k /= 2;

    }


    return ret;
}





// == operator
bool operator==(FieldElement lhs, FieldElement rhs)
{
    FieldElement diff = lhs - rhs;
    return (diff.x % lhs.MOD == 0);
}
bool operator==(FieldElement lhs, cpp_int k)
{
    FieldElement diff = lhs - k;
    return (diff.x % lhs.MOD == 0);
}
bool operator==(cpp_int k, FieldElement rhs)
{
    FieldElement diff = k - rhs;
    return (diff.x  % rhs.MOD == 0);
}





// != operator
bool operator!=(FieldElement lhs, FieldElement rhs)
{
    return !(lhs == rhs);
}
bool operator!=(FieldElement lhs, cpp_int k)
{
    return !(lhs == k);
}
bool operator!=(cpp_int k, FieldElement rhs)
{
    return !(k == rhs);
}




// / operator
FieldElement operator/(FieldElement lhs, FieldElement rhs)
{
    try
    {
        if (rhs == FieldElement(0, lhs.MOD))
        {
            std::string err_msg = "Invalid operation: Dividing by zero.";
            throw std::runtime_error(err_msg);
        }

        

    }
    catch(std::exception& err_msg)
    {
        std::cerr << err_msg.what() << std::endl;
    }


    return lhs * pow(rhs, rhs.MOD - 2);
}
FieldElement operator/(FieldElement lhs, cpp_int k)
{
    return lhs / FieldElement(k, lhs.MOD);
}
FieldElement operator/(cpp_int k, FieldElement rhs)
{
    return FieldElement(k, rhs.MOD) / rhs;
}




// /= operator
FieldElement& FieldElement::operator/=(FieldElement rhs)
{
    FieldElement temp = *this / rhs;
    x = temp.x;
    return *this;
}
FieldElement& FieldElement::operator/=(cpp_int k)
{
    FieldElement temp = *this / k;
    x = temp.x;
    return *this;
}





