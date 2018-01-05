#include "PyRDom.h"

#include "PyBinaryOperators.h"

namespace Halide {
namespace PythonBindings {

void define_rvar(py::module &m) {
    auto rvar_class = py::class_<RVar>(m, "RVar")
        .def(py::init<>())
        .def(py::init<std::string>(), py::arg("name"))
        .def("min", &RVar::min)
        .def("extent", &RVar::extent)
        .def("name", &RVar::name)
    ;

    py::implicitly_convertible<RVar, Expr>();

    add_binary_operators(rvar_class);  // define operators with int, rvars, and exprs
    // add_binary_operators_with<Expr>(rvar_class);
}

void define_rdom(py::module &m) {
    define_rvar(m);

    auto rdom_class = py::class_<RDom>(m, "RDom")
        .def(py::init<>())
        .def(py::init<Buffer<>>(), py::arg("buffer"))
        .def(py::init<OutputImageParam>(), py::arg("image_param"))
        .def(py::init([](py::args args) -> RDom {
            std::string name;
            std::vector<std::pair<Expr, Expr>> v;
            for (size_t i = 0; i < args.size(); i += 2) {
                if (i+1 >= args.size()) {
                    name = args[i].cast<std::string>();
                } else {
                    v.push_back({args[i].cast<Expr>(), args[i+1].cast<Expr>()});
                }
            }
            return RDom(v, name);
        }))
        .def("domain", &RDom::domain)
        .def("defined", &RDom::defined)
        .def("same_as", &RDom::same_as)
        .def("dimensions", &RDom::dimensions)
        .def("where", &RDom::where, py::arg("predicate"))
        .def_readonly("x", &RDom::x)
        .def_readonly("y", &RDom::y)
        .def_readonly("z", &RDom::z)
        .def_readonly("w", &RDom::w);

    py::implicitly_convertible<RDom, Expr>();
    py::implicitly_convertible<RDom, RVar>();

    // add_binary_operators(rdom_class);  // define operators with int, rdom and exprs
    // add_binary_operators_with<Expr>(rdom_class);
}

}  // namespace PythonBindings
}  // namespace Halide
