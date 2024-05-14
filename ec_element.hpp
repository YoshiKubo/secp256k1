#ifndef EC_ELEMENT
#define EC_ELEMENT

#include "ec_group.hpp"
#include "field_element.hpp"
#include <tuple>
#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;



class ECElement
{
    protected:
        FieldElement x;
        FieldElement y;
        bool is_zero;

        // this constructor is made for difinition of ZERO, so user cannot access this 4 arguments constructor
        ECElement(cpp_int x_, cpp_int y_, ECGroup ecg_, bool is_zero_);


    public:
        const ECGroup ECG;

        ECElement(cpp_int x_, cpp_int y_, ECGroup ecg_);
        static ECElement ZERO(ECGroup ecg_);

        std::tuple<cpp_int, cpp_int> get_xy(){return std::make_tuple(x.x, y.x);}
        cpp_int get_x(){return x.x;}
        cpp_int get_y(){return y.x;}

        void set_xy(cpp_int x, cpp_int y);


        ECElement& operator=(ECElement rhs);

        friend ECElement operator+(ECElement lhs, ECElement rhs);
        friend ECElement operator-(ECElement lhs, ECElement rhs);
        ECElement operator-();

        ECElement& operator+=(ECElement rhs);
        ECElement& operator-=(ECElement rhs);
        

        friend ECElement operator*(ECElement lhs, cpp_int k);
        friend ECElement operator*(cpp_int k, ECElement rhs);
        ECElement& operator*=(cpp_int k);

        friend bool operator==(ECElement lhs, ECElement rhs);
        friend bool operator!=(ECElement lhs, ECElement rhs);




        

        
};





#endif
