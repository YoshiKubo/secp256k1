#include "secp256k1.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include "ec_element.hpp"
#include "ec_group.hpp"

#include <iostream>




using namespace boost::multiprecision;

int main(void)
{
    std::cout << "P: " << secp256k1::P << std::endl;
    std::cout << "Gx: " << secp256k1::Gx << std::endl;
    std::cout << "Gy: " << secp256k1::Gy << std::endl;
    std::cout << "N: " << secp256k1::N << std::endl;


    
    



    
    return 0;
}