#include <iostream>
#include <iomanip>
#include "lnx.h"
#include <gmpxx.h>

int main (void)
{
  double x = 8;

  std::cout << std::fixed << std::setprecision(500) << "sum is " << ln_Taylor(x).getValue() << "\n";

  return 0;
}
