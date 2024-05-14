#ifndef FIELD_ELEMENT
#define FIELD_ELEMENT


#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;






class FieldElement
{
    
    public:

        cpp_int x;
        const cpp_int MOD;
    

        FieldElement(cpp_int x, cpp_int mod);

        static FieldElement ZERO(cpp_int p){return FieldElement(0, p);}

        


        friend FieldElement operator+(FieldElement lhs, FieldElement rhs);
        friend FieldElement operator+(FieldElement lhs, cpp_int k);
        friend FieldElement operator+(cpp_int k, FieldElement rhs);

        friend FieldElement operator-(FieldElement lhs, FieldElement rhs);
        friend FieldElement operator-(FieldElement lhs, cpp_int k);
        friend FieldElement operator-(cpp_int k, FieldElement rhs);
        FieldElement operator-();
        

        friend FieldElement operator*(FieldElement lhs, FieldElement rhs);
        friend FieldElement operator*(FieldElement lhs, cpp_int k);
        friend FieldElement operator*(cpp_int k, FieldElement rhs);

        friend FieldElement operator/(FieldElement lhs, FieldElement rhs);
        friend FieldElement operator/(FieldElement lhs, cpp_int k);
        friend FieldElement operator/(cpp_int k, FieldElement rhs);


        FieldElement& operator+=(FieldElement rhs);
        FieldElement& operator+=(cpp_int k);

        FieldElement& operator-=(FieldElement rhs);
        FieldElement& operator-=(cpp_int k);

        FieldElement& operator*=(FieldElement rhs);
        FieldElement& operator*=(cpp_int k);

        FieldElement& operator/=(FieldElement rhs);
        FieldElement& operator/=(cpp_int k);


        friend bool operator==(FieldElement lhs, FieldElement rhs);
        friend bool operator==(FieldElement lhs, cpp_int k);
        friend bool operator==(cpp_int k, FieldElement rhs);

        friend bool operator!=(FieldElement lhs, FieldElement rhs);
        friend bool operator!=(FieldElement lhs, cpp_int k);
        friend bool operator!=(cpp_int k, FieldElement rhs);


};




#endif