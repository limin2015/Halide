#ifndef HALIDE_PYTHON_BINDINGS_PYSCHEDULEMETHODS_H
#define HALIDE_PYTHON_BINDINGS_PYSCHEDULEMETHODS_H

#include "PyHalide.h"

namespace Halide {
namespace PythonBindings {

template <typename PythonClass>
NO_INLINE void add_schedule_methods(PythonClass &class_instance) {
    using T = typename PythonClass::type;

    class_instance

    .def("reorder", (T &(T::*)(const std::vector<VarOrRVar> &)) &T::reorder, py::arg("vars"))
    .def("reorder", [](T &t, py::args args) -> T & {
        std::vector<VarOrRVar> vars;
        vars.reserve(args.size());
        for (auto &a : args) {
            vars.push_back(a.cast<VarOrRVar>());
        }
        return t.reorder(vars);
    })

    .def("unroll", (T &(T::*)(VarOrRVar)) &T::unroll,
        py::arg("var"))
    .def("unroll", (T &(T::*)(VarOrRVar, Expr, TailStrategy)) &T::unroll,
        py::arg("var"), py::arg("factor"), py::arg("tail") = TailStrategy::Auto)

    .def("split", (T &(T::*)(VarOrRVar, VarOrRVar, VarOrRVar, Expr, TailStrategy)) &T::split,
        py::arg("old"), py::arg("outer"), py::arg("inner"), py::arg("factor"), py::arg("tail") = TailStrategy::Auto)

    .def("fuse", &T::fuse,
        py::arg("inner"), py::arg("outer"), py::arg("fused"))

    .def("tile", (T &(T::*)(VarOrRVar, VarOrRVar, VarOrRVar, VarOrRVar, VarOrRVar, VarOrRVar, Expr, Expr, TailStrategy)) &T::tile,
        py::arg("x"), py::arg("y"), py::arg("xo"), py::arg("yo"), py::arg("xi"), py::arg("yi"), py::arg("xfactor"), py::arg("yfactor"), py::arg("tail") = TailStrategy::Auto)
    .def("tile", (T &(T::*)(VarOrRVar, VarOrRVar, VarOrRVar, VarOrRVar, Expr, Expr, TailStrategy)) &T::tile,
        py::arg("x"), py::arg("y"), py::arg("xi"), py::arg("yi"), py::arg("xfactor"), py::arg("yfactor"), py::arg("tail") = TailStrategy::Auto)

    .def("reorder", (T &(T::*)(const std::vector<VarOrRVar> &)) &T::reorder, py::arg("vars"))
    .def("reorder", [](T &t, py::args args) -> T & {
        std::vector<VarOrRVar> vars;
        vars.reserve(args.size());
        for (auto &a : args) {
            vars.push_back(a.cast<VarOrRVar>());
        }
        return t.reorder(vars);
    })

    .def("parallel", (T &(T::*)(VarOrRVar)) &T::parallel,
        py::arg("var"))
    .def("parallel", (T &(T::*)(VarOrRVar, Expr, TailStrategy)) &T::parallel,
        py::arg("var"), py::arg("task_size"), py::arg("tail") = TailStrategy::Auto)

    .def("vectorize", (T &(T::*)(VarOrRVar)) &T::vectorize,
        py::arg("var"))
    .def("vectorize", (T &(T::*)(VarOrRVar, Expr, TailStrategy)) &T::vectorize,
        py::arg("var"), py::arg("factor"), py::arg("tail") = TailStrategy::Auto)

    ;
}

}  // namespace PythonBindings
}  // namespace Halide

#endif  // HALIDE_PYTHON_BINDINGS_PYSCHEDULEMETHODS_H
