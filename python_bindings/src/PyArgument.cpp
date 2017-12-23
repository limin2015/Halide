#include "PyArgument.h"

namespace Halide {
namespace PythonBindings {

void define_argument(py::module &m) {
    py::enum_<Argument::Kind>(m, "ArgumentKind")
        .value("InputScalar", Argument::Kind::InputScalar)
        .value("InputBuffer", Argument::Kind::InputBuffer)
        .value("OutputBuffer", Argument::Kind::OutputBuffer);

    auto argument_class =
        py::class_<Argument>(m, "Argument")
        .def(py::init<>())
        // .def(py::init<const std::string &, Argument::Kind, const Type &, int, Expr, Expr, Expr>(),
        //     py::arg("name"), py::arg("kind"), py::arg("type"), py::arg("dimensions"),
        //     py::arg("default") = Expr(), py::arg("min") = Expr(), py::arg("max") = Expr())
        // .def(py::init<Buffer<>>(), py::arg("buffer"))
        // .def_readonly("name", &Argument::name)
        // .def_readonly("kind", &Argument::kind)
        // .def_readonly("dimensions", &Argument::dimensions)
        // .def_readonly("type", &Argument::type)
        // .def_readonly("default", &Argument::def)
        // .def_readonly("min", &Argument::min)
        // .def_readonly("max", &Argument::max)
        // .def("is_buffer", &Argument::is_buffer)
        // .def("is_scalar", &Argument::is_scalar)
        // .def("is_input", &Argument::is_input)
        // .def("is_output", &Argument::is_output)
    ;
}

}  // namespace PythonBindings
}  // namespace Halide
