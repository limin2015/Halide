#ifndef HALIDE_PYTHON_BINDINGS_PYHALIDE_H
#define HALIDE_PYTHON_BINDINGS_PYHALIDE_H

#undef NDEBUG

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

// Some very-commonly-used headers here, to simplify things.
#include <iostream>
#include <string>
#include <vector>

// Everyone needs Halide.h
#include "Halide.h"

namespace Halide {
namespace PythonBindings {

namespace py = pybind11;

}  // namespace PythonBindings
}  // namespace Halide


#endif  // HALIDE_PYTHON_BINDINGS_PYHALIDE_H
