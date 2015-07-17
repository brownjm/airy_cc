#include "airy.h"

Airy::Airy() {
  // initialize Python interpreter
  Py_Initialize();
  if (!Py_IsInitialized()) throw std::runtime_error("Could not initialize Python interpreter");
  
  // import mpmath module
  mpmath = PyImport_ImportModule("mpmath");
  if (!mpmath) throw std::runtime_error("Could not import mpmath");
  
  // get references to airy functions
  airyai = PyObject_GetAttrString(mpmath, "airyai");
  if (!PyCallable_Check(airyai)) throw std::runtime_error("Could not load mpmath.airyai");
  airybi = PyObject_GetAttrString(mpmath, "airybi");
  if (!PyCallable_Check(airybi)) throw std::runtime_error("Could not load mpmath.airybi");
}

Airy::~Airy() {
  // reduce ref count for module and functions
  Py_DECREF(airybi);
  Py_DECREF(airyai);
  Py_DECREF(mpmath);


  // close interpreter
  Py_Finalize();
}

std::complex<double> Airy::ai(std::complex<double> z, int derivative) {
  return execute(airyai, z, derivative);
}

std::complex<double> Airy::bi(std::complex<double> z, int derivative) {
  return execute(airybi, z, derivative);
}

std::complex<double> Airy::execute(PyObject* func, std::complex<double> z, int derivative) {
  // convert C++ types to Python objects
  PyObject* py_z = PyComplex_FromDoubles(z.real(), z.imag());
  PyObject* py_d = PyLong_FromLong(derivative);

  // pack them into an argument tuple
  PyObject* args = PyTuple_New(2);
  PyTuple_SetItem(args, 0, py_z); // SetItem takes over ownership
  PyTuple_SetItem(args, 1, py_d);

  // call python function with arguments
  // function returned multi-precision complex MPC
  PyObject* mpc_result = PyObject_Call(func, args, NULL);
  Py_DECREF(args);

  // convert result from MPC_complex -> Python complex -> C++ complex
  Py_complex py_result = PyComplex_AsCComplex(mpc_result);
  Py_DECREF(mpc_result);
  std::complex<double> result(py_result.real, py_result.imag);
  return result;
}
