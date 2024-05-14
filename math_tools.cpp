#include <vector>
#include "math_tools.hpp"
#include "field_element.hpp"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;


// judge whether n is prime number
bool is_prime(cpp_int n)
{
    if(n <= 1)
    {
        return false;
    }

    if(n == 2)
    {
        return true;
    }


    std::vector<bool> numbers;

    for (cpp_int i = 0; i <= n; i++)
    {
        numbers.push_back(true);
    }

    const cpp_int sqrt_n = sqrt(n) + 1;

    for(size_t i = 2; i <= sqrt_n; i++)
    {
        if (!numbers[i])
        {
            continue;
        }
        else
        {
            for(size_t j = i * i ; j <= n; j += i)
            {
                numbers[j] = false;
            }
        }

        if(!numbers.back()){    return false;}
    }

    return true;

}






bool is_EC(cpp_int a_, cpp_int b_, cpp_int p)
{
    FieldElement a = FieldElement(a_, p);
    FieldElement b = FieldElement(b_, p);
    FieldElement ZERO = FieldElement::ZERO(p);
    return -16 * (4 * a * a * a + 27 * b * b) != ZERO;
}