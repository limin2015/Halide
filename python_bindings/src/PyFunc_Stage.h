#ifndef HALIDE_PYTHON_BINDINGS_PYFUNC_STAGE_H
#define HALIDE_PYTHON_BINDINGS_PYFUNC_STAGE_H

#include "PyHalide.h"

namespace Halide {
namespace PythonBindings {

void define_stage(py::module &m);

}  // namespace PythonBindings
}  // namespace Halide

#endif  // HALIDE_PYTHON_BINDINGS_PYFUNC_STAGE_H
