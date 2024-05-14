#ifndef SECP256K1_H
#define SECP256K1_H


#include "ec_element.hpp"
#include "ec_group.hpp"
#include "field_element.hpp"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;



namespace secp256k1
{
    const cpp_int A = 0;
    const cpp_int B = 7;
    const cpp_int P = cpp_int("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
    const cpp_int Gx = cpp_int("55066263022277343669578718895168534326250603453777594175500187360389116729240");
    const cpp_int Gy =  cpp_int("32670510020758816978083085130507043184471273380659243275938904335757337482424" );
    const cpp_int N = cpp_int("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141"); 


}



class  Signature
{   
    public:
        cpp_int r;
        cpp_int s;

        Signature(cpp_int r, cpp_int s): r(r), s(s){}

};


class PublicKey
{
    public:
        cpp_int px;
        cpp_int py;

        PublicKey(cpp_int px, cpp_int py): px(px), py(py) {}
};



class PrivateKey
{
    private:
        cpp_int e;
    
    public:
        PrivateKey(cpp_int e_): e(e_){}

        Signature sign(cpp_int hashed_z);

        PublicKey generatePublicKey();

};




class S256Point
{
    private:
        cpp_int gx;
        cpp_int gy;
        ECElement point = ECElement(secp256k1::Gx, secp256k1::Gy, ECGroup(secp256k1::A, secp256k1::B, secp256k1::P));

        // this is helper constructor
        S256Point(ECElement ece);

        // these are helper operator
        friend S256Point operator*(S256Point lhs, FieldElement f);
        friend S256Point operator*(FieldElement f, S256Point rhs);
    
    public:
    
        S256Point();
        S256Point(cpp_int times_);
        S256Point(cpp_int gx_, cpp_int gy_);
    


        cpp_int get_gx(){   return gx;}
        cpp_int get_gy(){   return gy;}

    
    

        friend S256Point operator+(S256Point lhs, S256Point rhs);
        friend S256Point operator-(S256Point lhs, S256Point rhs);
        S256Point& operator+=(S256Point rhs);
        S256Point& operator-=(S256Point rhs);
        
        friend S256Point operator*(S256Point lhs, cpp_int k);
        friend S256Point operator*(cpp_int k, S256Point rhs);
        friend S256Point operator/(S256Point lhs, cpp_int k);
        friend bool operator==(S256Point lhs, S256Point rhs);
        friend bool operator!=(S256Point lhs, S256Point rhs);


        static bool verify(cpp_int z, Signature sign, PublicKey pub_key);


};













#endif