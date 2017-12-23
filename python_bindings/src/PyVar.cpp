#include "PyVar.h"

#include "PyBinaryOperators.h"

namespace Halide {
namespace PythonBindings {

namespace {

std::string var_repr(const Var &var) {
    std::ostringstream o;
    o << "<halide.Var '" << var.name() << "'>";
    return o.str();
}

}  // namespace

void define_var(py::module &m) {
    bool (Var::*is_implicit_member)() const = &Var::is_implicit;
    int (Var::*implicit_index_member)() const = &Var::implicit_index;
    bool (Var::*is_placeholder_member)() const = &Var::is_placeholder;
    bool (*is_implicit_static)(const std::string &) = &Var::is_implicit;
    int (*implicit_index_static)(const std::string &) = &Var::implicit_index;
    bool (*is_placeholder_static)(const std::string &) = &Var::is_placeholder;

    auto var_class =
        py::class_<Var>(m, "Var")
            .def(py::init<>())
            .def(py::init<std::string>())
            .def("name", &Var::name)
            .def("same_as", &Var::same_as)
            .def("implicit", &Var::implicit)
            .def("is_implicit", is_implicit_member)
            .def("implicit_index", implicit_index_member)
            .def("is_placeholder", is_placeholder_member)
            .def("is_implicit", is_implicit_static)
            .def("implicit_index", implicit_index_static)
            .def("is_placeholder", is_placeholder_static)
            .def("outermost", &Var::outermost)
            .def("__repr__", &var_repr)
            .def("__str__", &Var::name)
            // TODO: Python doesn't have explicit type-conversion casting;
            // providing an explicit convert-to-Expr method here seems potentially
            // useful. Overthinking it? Is the best name 'as_expr()', 'expr()', or something else?
            // .def("as_expr", (Expr (Var::*)()) &Var::operator Expr)
    ;

    add_binary_operators(var_class);
    // add_binary_operators_with<Expr>(var_class);

    py::implicitly_convertible<Var, Expr>();

    m.attr("_") = Halide::_;
    m.attr("_0") = Halide::_0;
    m.attr("_1") = Halide::_1;
    m.attr("_2") = Halide::_2;
    m.attr("_3") = Halide::_3;
    m.attr("_4") = Halide::_4;
    m.attr("_5") = Halide::_5;
    m.attr("_6") = Halide::_6;
    m.attr("_7") = Halide::_7;
    m.attr("_8") = Halide::_8;
    m.attr("_9") = Halide::_9;
}

}  // namespace PythonBindings
}  // namespace Halide
