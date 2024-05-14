#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;


class IsPrimeException: public std::exception
{
    private:
        std::string err_msg;
    
    public:
        IsPrimeException(cpp_int p);
        std::string what(){     return err_msg;}
};




class ECZeroException: public std::exception
{
    private:
        std::string err_msg;
    
    public:
        ECZeroException();
        std::string what(){     return err_msg;}
    
};



class PointOnECException: public std::exception
{
    private:
        std::string err_msg;
    
    public:
        PointOnECException(cpp_int x, cpp_int y, cpp_int A, cpp_int B, cpp_int MOD);
        std::string what(){     return err_msg;}
};



class IsECException: public std::exception
{
    private:
        std::string err_msg;
    
    public:
        IsECException(cpp_int A, cpp_int B, cpp_int MOD);
        std::string what(){     return err_msg;}
    
};





#endif