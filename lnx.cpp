#include "lnx.h"
#include "high_precision.h"
#include <cmath>
#include <algorithm>
#include <thread>
#include <iostream>

#define Taylor_series_length 1000

hp_Number Simpson_method(int n, hp_Number a, hp_Number b);
hp_Number Romberg_method(int n, hp_Number a, hp_Number b);

hp_Number ln_Taylor(double x)
{
    hp_Number e(E);
    hp_Number t = hp_Number(std::to_string(x))/e.pow(5);
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
    return result + hp_Number("5");
}
hp_Number ln_integration(double _x)
{
    hp_Number h("0.01");
    hp_Number b = hp_Number(std::to_string(_x));
    hp_Number a = hp_Number("1");
    int n = std::ceil(((b-a)/h).getDouble());
    hp_Number result;

    // 龙贝格公式
    result = Romberg_method(2*n,a,b) * hp_Number(std::to_string((double)((128)/(128-1))))\
        + Romberg_method(n,a,b) * hp_Number(std::to_string((double)((-1)/(128-1))));
    // result = Simpson_method(2*n,a,b)*hp_Number(std::to_string((double)((16)/(15))))-\
    //     Simpson_method(n,a,b)*hp_Number(std::to_string((double)((1)/(15))));

    return result;
    // std::cout<<"n="<<n<<std::endl;
    // return Simpson_method(n,a,b);
}
// hp_Number ln_fake(double x)
// {
//
// }

// f(x)=1/x
hp_Number Simpson_method(int n, hp_Number a, hp_Number b)
{
    hp_Number h = (b - a)/hp_Number(std::to_string(n));

    // 常数1
    hp_Number One = hp_Number("1");
    hp_Number term1("0"), term2("0");
    hp_Number sumX("1");

    for(int k=1;k<n;k++)
    {
        sumX = sumX + h;
        term1 = term1 + One/sumX;
    }

    sumX = One;
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
    return Simpson_method(4*n,a,b)*hp_Number(std::to_string((double)((64*16)/(63*15))))\
    + Simpson_method(2*n,a,b)*hp_Number(std::to_string((double)((-64-16)/(63*15))))\
    + Simpson_method(n,a,b)*hp_Number(std::to_string((double)((1)/(63*15))));
}
