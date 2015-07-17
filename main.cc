// Testing Airy implementation

#include <iostream>
#include <limits>
#include <complex>

#include "airy.h"

int main() {

  Airy airy;
  std::complex<double> z(100, -50);
  std::cout.precision(std::numeric_limits<double>::digits10);
  std::cout << "z = " << z << "\n";
  std::cout << "Ai = " << airy.ai(z) << "\n";
  std::cout << "Bi = " << airy.bi(z) << "\n";
}
