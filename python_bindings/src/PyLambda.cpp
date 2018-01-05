#include "PyLambda.h"

namespace Halide {
namespace PythonBindings {

void define_lambda(py::module &m) {
    // TODO: 'lambda' is a reserved word in Python, so we
    // can't use it for a function. Using 'halide_lambda' for now.
    m.def("halide_lambda", [](py::args args) -> Func {
        std::vector<Var> vars;
        vars.reserve(args.size() - 1);
        for (size_t i = 0; i < args.size() - 1; i++) {
            vars.push_back(args[i].cast<Var>());
        }
        Expr e = args[args.size() - 1].cast<Expr>();
        Func f("lambda" + Internal::unique_name('_'));
        f(vars) = e;
        return f;
    });
}

}  // namespace PythonBindings
}  // namespace Halide
