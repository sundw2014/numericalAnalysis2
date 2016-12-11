#include <iostream>
#include <iomanip>
#include "lnx.h"
#include "high_precision.h"

using namespace std;

int main (void)
{
    hp_Number result;
    char key;
    double x;

    cout << "intput x:";
    cin >> x;
    cout<<"select method:\r\n0. Taylor series\r\n1. integration\r\n2. inverse hyperbolic\r\n";
    cin >> key;
    switch(key)
    {
      case '0':
      {
          result = ln_Taylor(x);
          break;
      }
      case '1':
      {
          result = ln_integration(x);
          break;
      }
      case '2':
      {
          result = ln_inverseHyperbolic(x);
          break;
      }
      default:
      {
          cerr<<"wrong input"<<std::endl;
          return 1;
      }
    }

    string sign="";
    if(result.sign==-1){
        sign = "-";
    }
    cout<<sign<<"0."<<result.significand.substr(0,20)<<"*10^"<<result.exponent<<std::endl;
    return 0;
}
