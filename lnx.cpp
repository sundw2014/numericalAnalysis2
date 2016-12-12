#include "lnx.h"
#include "high_precision.h"
#include <cmath>
#include <algorithm>
#include <thread>
#include <iostream>

#define Taylor_series_length 100

hp_Number Simpson_method(int n, hp_Number a, hp_Number b);
hp_Number Romberg_method(int n, hp_Number a, hp_Number b);

hp_Number ln_Taylor(double x)
{
    hp_Number e(E);
    int frc = std::ceil(std::log(x));
    hp_Number t = hp_Number(std::to_string(x))/e.pow(frc);
    t = t - hp_Number("1");

    hp_Number result("0");
    hp_Number tmpPower("1");

    for(int i=1;i<Taylor_series_length+1;i++)
    {
        int sign = ((i-1)%2)?-1:1;
        bool isAdd = (sign==1);
        tmpPower = tmpPower * t;
        hp_Number term = tmpPower/hp_Number(std::to_string(i));

        if(isAdd){
            result = result + term;
        }
        else{
            result = result - term;
        }
    }
    return result + hp_Number(std::to_string(frc));
}
hp_Number ln_integration(double x)
{
    hp_Number e(E);
    int frc = std::ceil(std::log(x));
    hp_Number t = hp_Number(std::to_string(x))/e.pow(frc);

    hp_Number a = t;
    hp_Number b = hp_Number("1");
    int n = 300;
    hp_Number result;

    result = Romberg_method(n,a,b);
    result = hp_Number(std::to_string(frc)) - result;
    return result;
}

hp_Number ln_inverseHyperbolic(double x)
{
    hp_Number e(E);
    hp_Number One = hp_Number("1");
    hp_Number _x = hp_Number(std::to_string(x));
    int frc = std::ceil(std::log(x));
    _x = _x/e.pow(frc);

    hp_Number t = (_x-One)/(_x+One);
    hp_Number t_pow2 = t.pow(2);
    hp_Number result;
    int n = 30;

    hp_Number tmpPower = t;
    for(int i=0;i<n;i++){
        result = result + tmpPower/hp_Number(std::to_string(2*i+1));
        tmpPower = tmpPower * t_pow2;
    }
    result = result * hp_Number("2");
    return result + hp_Number(std::to_string(frc));
}

// f(x)=1/x
hp_Number Simpson_method(int n, hp_Number a, hp_Number b)
{
    hp_Number h = (b - a)/hp_Number(std::to_string(n));

    // 常数1
    hp_Number One = hp_Number("1");
    hp_Number term1("0"), term2("0");
    hp_Number sumX = a;

    for(int k=1;k<n;k++)
    {
        sumX = sumX + h;
        term1 = term1 + One/sumX;
    }

    sumX = a;
    sumX = sumX + hp_Number(std::to_string(0.5))*h;
    for(int k=0;k<n;k++)
    {
        term2 = term2 + One/sumX;
        sumX = sumX + h;
    }

    hp_Number result;
    result = h/hp_Number("6")*(hp_Number("2")*term1 + hp_Number("4")*term2 + One/a + One/b);
    return result;
}

hp_Number Romberg_method(int n, hp_Number a, hp_Number b)
{
    return Simpson_method(4*n,a,b)*hp_Number(std::to_string(64*16))/hp_Number(std::to_string(63*15))\
        + Simpson_method(2*n,a,b)*hp_Number(std::to_string(-64-16))/hp_Number(std::to_string(63*15))\
        + Simpson_method(n,a,b)*hp_Number(std::to_string(1))/hp_Number(std::to_string(63*15));
}
