#include <iostream>
#include <iomanip>
#include "lnx.h"
#include "high_precision.h"

using namespace std;

int main (void)
{
    hp_Number result;
    char key;
    double x = 1.0;

    std::cout<<"test begin"<<std::endl;
    for(int i=0;i<100;i++){
        std::string result[3];
        result[0] = ln_Taylor(x).significand.substr(0,21);
        result[1] = ln_integration(x).significand.substr(0,21);
        result[2] = ln_inverseHyperbolic(x).significand.substr(0,21);
        if(result[0]==result[1] && result[0]==result[2]){
            ;
        }
        else{
            std::cerr<<"[ERROR]: "<<"x="<<std::endl<<result[0]<<std::endl<<result[1]<<std::endl<<result[2]<<std::endl;
        }
        x = x + 1.0;
    }
    std::cout<<"test finished"<<std::endl;
    return 0;
}
