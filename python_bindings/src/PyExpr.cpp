 #include "PyExpr.h"


#include "PyBinaryOperators.h"
#include "PyType.h"

namespace Halide {
namespace PythonBindings {

void define_expr(py::module &m) {
    auto expr_class =
        py::class_<Expr>(m, "Expr")
            // PyBind11 searches in declared order,
            // int should be tried before float conversion
            .def(py::init<int>())
            .def(py::init<float>())
            .def(py::init<double>())
            .def(py::init<std::string>())
            .def(py::init([](const Var &v) -> Expr { return v; }))
            .def(py::init([](const FuncRef &f) -> Expr { return f; }))
            .def(py::init([](const RVar &r) -> Expr { return r; }))
            .def("type", &Expr::type)
            .def("__repr__", [](const Expr &e) -> std::string {
                std::ostringstream o;
                o << "<halide.Expr of type " << halide_type_to_string(e.type()) << ">";
                return o.str();
            })
    ;

    add_binary_operators(expr_class);

    // implicitly_convertible declaration order matters,
    // int should be tried before float conversion
    py::implicitly_convertible<int, Expr>();
    py::implicitly_convertible<float, Expr>();
    py::implicitly_convertible<double, Expr>();

    py::enum_<DeviceAPI>(m, "DeviceAPI")
        .value("None", DeviceAPI::None)
        .value("Host", DeviceAPI::Host)
        .value("Default_GPU", DeviceAPI::Default_GPU)
        .value("CUDA", DeviceAPI::CUDA)
        .value("OpenCL", DeviceAPI::OpenCL)
        .value("GLSL", DeviceAPI::GLSL)
        .value("OpenGLCompute", DeviceAPI::OpenGLCompute)
        .value("Metal", DeviceAPI::Metal)
        .value("Hexagon", DeviceAPI::Hexagon);
}

}  // namespace PythonBindings
}  // namespace Halide
