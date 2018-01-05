#include "PyRealization.h"

namespace Halide {
namespace PythonBindings {

void define_realization(py::module &m) {
    // TODO: incomplete
    auto realization_class = py::class_<Realization>(m, "Realization")
        .def(py::init<Buffer<> &>())
        .def(py::init<std::vector<Buffer<>> &>())
        .def("size", &Realization::size)
        .def("__getitem__", [](Realization &r, size_t x) -> Buffer<> {
            return r[x];
        })
    ;
}

}  // namespace PythonBindings
}  // namespace Halide
