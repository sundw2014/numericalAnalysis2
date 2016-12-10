// #include "lnx.h"
// #include "high_precision.h"
// #include <cmath>
//
// #define Taylor_series_length 10000
//
// hp_Number ln_Taylor(double x)
// {
//     hp_Number e(E);
//     hp_Number t = hp_Number(x)/e.pow(5);
//     // hp_Number t("0.5");
//     hp_Number result(0);
//     for(int i=1;i<Taylor_series_length+1;i++)
//     {
//         int sign = ((i-1)%2)?-1:1;
//         bool isAdd = (sign==1);
//
//         hp_Number term = mpf_power((t-hp_Number(1)).getValue(),i)/hp_Number(i);
//
//         if(isAdd){
//             result = result + term;
//         }
//         else{
//             result = result - term;
//         }
//     }
//     return result+hp_Number(5);
// }
// hp_Number ln_integration(double x)
// {
//
// }
// hp_Number ln_fake(double x)
// {
//
// }
