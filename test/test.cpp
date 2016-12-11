#include <iostream>
#include <iomanip>
#include "lnx.h"
#include "high_precision.h"

int main (void)
{
    hp_Number a("0.12345"),b("-0.11111");
    hp_Number c = a+b;
    std::string sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;

    hp_Number d("0.0000000000009"),e("100");
    c = d+e;
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;

    hp_Number f("1000.123456789"),g("100.111111111000");
    c = f-g;
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;

    c = g-f;
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;

    hp_Number h("1000.123456789"),i("100.111111111000");
    c = h*i;
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;

    hp_Number j("9999.123456789"),k("-99.111111111000");
    c = j*k;
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;
    // std::cout << std::fixed << std::setprecision(500) << "sum is " << ln_Taylor(x).getValue() << "\n";

    hp_Number l("9999.123456789"),m("-99.111111111000");
    c = l/m;
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;

    hp_Number n("99"),o("11");
    c = n/o;
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;

    hp_Number p("1"),q("1000.09709");
    c = p/q;
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;

    hp_Number r("1");
    c = p.pow(100);
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;

    hp_Number t("1.1");
    c = t.pow(100);
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;

    c = ln_Taylor(10.5);
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;

    c = ln_integration(10.5);
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;

    c = ln_inverseHyperbolic(10.5);
    sign="";
    if(c.sign==-1){
        sign = "-";
    }
    std::cout<<sign<<"0."<<c.significand<<"*10^"<<c.exponent<<std::endl;
    return 0;
}
