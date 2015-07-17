// Simple C++ interface to Airy functions in 3rd party Python library mpmath
#ifndef AIRY_H_
#define AIRY_H_

#include <Python.h> // must be first include

#include <stdexcept>
#include <complex>

class Airy {
public:
  Airy();
  ~Airy();

  // calculate airy functions to nth order derivative in complex plane
  // negative powers are integrals of airy functions
  std::complex<double> ai(std::complex<double> z, int derivative=0);
  std::complex<double> bi(std::complex<double> z, int derivative=0);

private:
  PyObject* mpmath;     // module
  PyObject* airyai;     // mpmath.airyai(z)
  PyObject* airybi;     // mpmath.airybi(z)
  inline std::complex<double> execute(PyObject* func, std::complex<double> z, int derivative);
};

#endif // AIRY_H_
