#include "field_element.hpp"
#include "ec_group.hpp"
#include "ec_element.hpp"
#include "math_tools.hpp"
#include "exception.hpp"


#include <exception>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;


//ECElement object's constructor
ECElement::ECElement(cpp_int x_, cpp_int y_, ECGroup ecg_, bool is_zero_)
: x(FieldElement(x_, ecg_.MOD)), y(FieldElement(y_, ecg_.MOD)), ECG(ecg_), is_zero(is_zero_)
{
    try
    {
        if(is_zero)
        {
            if(x_ == 0 && y_ == 0)
            {
                return;
            }
            else
            {
                throw ECZeroException();
            }
        }

        else if (y * y != x * x * x + ECG.A * x + ECG.B)
        {
            throw PointOnECException(x_, y_, ecg_.A, ecg_.B, ecg_.MOD);
        }
    }
    catch(ECZeroException& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    } 
    catch(PointOnECException& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);

    }
}



ECElement::ECElement(cpp_int x_, cpp_int y_, ECGroup ecg_)
:x(FieldElement(x_, ecg_.MOD)), y(FieldElement(y_, ecg_.MOD)), ECG(ecg_)
{
    is_zero = false;

    try
    {
        if (y * y != x * x * x + ECG.A * x + ECG.B)
        {
            throw PointOnECException(x_, y_, ecg_.A, ecg_.B, ecg_.MOD);
        }
        
    }
    catch(PointOnECException& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    
}



//zero of ECElement object
ECElement ECElement::ZERO(ECGroup ecg_)
{
    ECElement zero(0, 0, ecg_, true);
    return zero;
}



// setter
// when setter boosts, new value pair (x_, y_) is checked if this pair is on the ecliptic curve
void ECElement::set_xy(cpp_int x_, cpp_int y_)
{
    cpp_int mod = ECG.MOD;
    cpp_int a = ECG.A;
    cpp_int b = ECG.B;

    FieldElement xx = FieldElement(x_, mod);
    FieldElement yy = FieldElement(y_, mod); 

    try
    {
        if (yy * yy != xx * xx * xx + a * xx + b)
        {
            throw PointOnECException(x_, y_, a, b, mod);
        }
    }
    catch(PointOnECException& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }


    x.x = x_;
    y.x = y_;

}






// == operator
bool operator==(ECElement lhs, ECElement rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.ECG == rhs.ECG && lhs.is_zero == rhs.is_zero;
}



// != operator
bool operator!=(ECElement lhs, ECElement rhs)
{
    return !(lhs == rhs);
}





// + operator
ECElement operator+(ECElement lhs, ECElement rhs)
{
    try
    {
        if(lhs.ECG != rhs.ECG)
        {
            throw std::runtime_error("These two poinnts are not on the same ecliptic curve group");
        }

        else if (lhs == rhs)
        {
            FieldElement s = (3 * lhs.x * lhs.x + lhs.ECG.A) / (2 * lhs.y);
            FieldElement x_ret = s * s - 2 * lhs.x;
            FieldElement y_ret = s * (lhs.x - x_ret) - lhs.y;

            return ECElement(x_ret.x, y_ret.x, lhs.ECG);
        }

        else if ( lhs == ECElement::ZERO(rhs.ECG))
        {
            return rhs;
        }

        else if (rhs == ECElement::ZERO(lhs.ECG))
        {
            return lhs;
        }

        else if (lhs.x == rhs.x && lhs.y != rhs.y)
        {
            return ECElement::ZERO(lhs.ECG);
        }

        else
        {
            FieldElement s = (rhs.y - lhs.y)/(rhs.x - lhs.x);
            FieldElement x_ret = s * s - lhs.x - rhs.x;
            FieldElement y_ret = s * (lhs.x - x_ret) - lhs.y;
            return ECElement(x_ret.x, y_ret.x, lhs.ECG);

        }
        
    }
    catch(const std::exception& err_msg)
    {
        std::cerr << err_msg.what() << std::endl;
        exit(1);
    }


    return ECElement::ZERO(lhs.ECG);
    
}





// - operator
ECElement ECElement::operator-()
{
    cpp_int x_ = x.x;
    cpp_int y_ = y.x;
    return ECElement(x_, -y_, ECG);
}

ECElement operator-(ECElement lhs, ECElement rhs)
{
    return lhs + (-rhs);
}




// += operator
ECElement& ECElement::operator+=(ECElement rhs)
{
    ECElement temp = *this + rhs;

    x.x = temp.x.x;
    y.x = temp.y.x;
    is_zero = temp.is_zero;

    return *this;
}



// -= operator
ECElement& ECElement::operator-=(ECElement rhs)
{
    *this += (- rhs);
    return *this;
}



ECElement times(ECElement a, cpp_int k)
{
    ECElement ret = ECElement::ZERO(a.ECG);
    ECElement temp = a;

    cpp_int digit;

    while(k != 0)
    {
        digit = k % 2;
        if(digit != 0)
        {
            ret += temp;
        }
        
        temp += temp;
        k /= 2;

    }


    return ret;
}


ECElement operator*(ECElement a, cpp_int k)
{
    if (k > 0)
    {
        return times(a, k);
    }

    else if (k == 0)
    {
        return ECElement::ZERO(a.ECG);
    }

    else   //(k < 0)
    {
        return times(-a, -k);
    }
}


ECElement operator*(int64_t k, ECElement rhs)
{
    return rhs * k;
}



ECElement& ECElement::operator*=(cpp_int k)
{
    ECElement temp = *this * k;

    x.x = temp.x.x;
    y.x = temp.y.x;
    return *this;
}

        


