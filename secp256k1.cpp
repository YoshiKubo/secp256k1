#include "secp256k1.hpp"
#include "ec_group.hpp"
#include "ec_element.hpp"
#include "field_element.hpp"
#include <exception>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

S256Point::S256Point()
{
    gx = point.get_x();
    gy = point.get_y();
}

S256Point::S256Point(cpp_int times_)
{
    point *= times_; 
    gx = point.get_x();
    gy = point.get_y();
}

S256Point::S256Point(cpp_int gx_, cpp_int gy_)
{
    point.set_xy(gx_, gy_);
    gx = gx_;
    gy = gy_;
}


S256Point::S256Point(ECElement ece)
{
    point.set_xy(ece.get_x(), ece.get_y());
    gx = point.get_x();
    gy = point.get_y();
}




// +operator
S256Point operator+(S256Point lhs, S256Point rhs)
{
    ECElement point = lhs.point + rhs.point;
    
    return S256Point(point);
}



// -operator
S256Point operator-(S256Point lhs, S256Point rhs)
{
    ECElement point = lhs.point - rhs.point;

    return S256Point(point);
}


// += operator
S256Point& S256Point::operator+=(S256Point rhs)
{
    point += rhs.point;
    gx = point.get_x();
    gy = point.get_y();
    return *this;
}



// -= operator
S256Point& S256Point::operator-=(S256Point rhs)
{
    point -= rhs.point;
    gx = point.get_x();
    gy = point.get_y();
    return *this;
}



// * operator
S256Point operator*(S256Point lhs, cpp_int k)
{
    ECElement point = lhs.point * k;
    return S256Point(point);
}

//SECP256K1 operator*(cpp_int k, SECP256K1 rhs)
//{
//    ECElement point = k * rhs.point;
//    return SECP256K1(point);
//}


//these are helper operator 
S256Point operator*(S256Point lhs, FieldElement f)
{
    return lhs * f.x;
}

//SECP256K1 operator*(FieldElement f, SECP256K1 rhs)
//{
//    return f.x * rhs;
//}





// /operator
S256Point operator/(S256Point lhs, cpp_int k)
{
    FieldElement f = 1 / (FieldElement(k, secp256k1::N));
    return lhs * f;
}


bool operator==(S256Point lhs, S256Point rhs)
{
    return lhs.point == rhs.point;
}

bool operator!=(S256Point lhs, S256Point rhs)
{
    return lhs.point != rhs.point;
}



// verify whether signature is valid
bool S256Point::verify(cpp_int z, Signature sign, PublicKey pub_key)
{
    const cpp_int N = secp256k1::N;
    FieldElement uu = FieldElement(z, N)/sign.s;
    FieldElement vv = FieldElement(sign.r, N)/sign.s;

    cpp_int u = uu.x;
    cpp_int v = vv.x;


    S256Point pub_point = S256Point(pub_key.px, pub_key.py);
    S256Point base_point = S256Point(1);

    S256Point r_candidate = u * base_point  + v * pub_point;

    return (sign.r == r_candidate.get_gx());
}





Signature PrivateKey::sign(cpp_int hashed_z)
{
    boost::random::random_device seed_gen;
    boost::random::mt19937 gen(seed_gen);

    const cpp_int N = secp256k1::N;
    boost::random::uniform_real_distribution dist(cpp_int("0"), N);

    cpp_int k = dist(gen);
    S256Point r = S256Point(k);
    cpp_int rx = r.get_gx();

    FieldElement ss = FieldElement(hashed_z + rx * e, N) / k;
    cpp_int s = ss.x;

    return Signature(rx, s);
}


PublicKey PrivateKey::generatePublicKey()
{
    S256Point p = S256Point(e);
    return PublicKey(p.get_gx(), p.get_gy());
}






