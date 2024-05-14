#ifndef EC_GROUP
#define EC_GROUP
#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

//#define SAFE_MODE


class ECGroup
{
    public:
        const cpp_int A;
        const cpp_int B;
        const cpp_int MOD;


        ECGroup(cpp_int a, cpp_int b, cpp_int p);

        bool friend operator==(ECGroup lhs, ECGroup rhs)
        {
            return lhs.A == rhs.A && lhs.B == rhs.B && lhs.MOD == rhs.MOD;
        } 


        bool friend operator!=(ECGroup lhs, ECGroup rhs)
        {
            return !(lhs == rhs);
        }
};






#endif