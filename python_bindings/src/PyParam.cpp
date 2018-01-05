#include "PyParam.h"

#include "PyBinaryOperators.h"
#include "PyType.h"

namespace Halide {
namespace PythonBindings {

void define_param(py::module &m) {
    auto param_class =
        py::class_<Param<>>(m, "Param")
        .def(py::init<Type>(), py::arg("type"))
        .def(py::init<Type, std::string>(), py::arg("type"), py::arg("name"))
//        .def(py::init<Type, Expr, Expr>(), py::arg("type"), py::arg("min"), py::arg("max"))
//        .def(py::init<Type, std::string, Expr, Expr>(), py::arg("type"), py::arg("name"), py::arg("min"), py::arg("max"))
        .def("name", &Param<>::name)
//        .def("get", &Param<>::get)
        .def("type", &Param<>::type)
        .def("set_range", &Param<>::set_range)
        .def("set_min_value", &Param<>::set_min_value)
        .def("set_max_value", &Param<>::set_max_value)
        .def("min_value", &Param<>::min_value)
        .def("max_value", &Param<>::max_value)
        // .def("as_expr", (Expr (Param<T>::*)()) &Var::operator Expr)
        // .def("as_ExternFuncArgument", (ExternFuncArgument (Param<T>::*)()) &Var::operator ExternFuncArgument)
        // .def("as_Argument", (Argument (Param<T>::*)()) &Var::operator Argument)

        .def("__repr__", [](const Param<> &param) -> std::string {
            std::ostringstream o;
            o << "<halide.Param '" << param.name() << "'"
              << " type " << halide_type_to_string(param.type()) << ">";
            return o.str();
        })
    ;

// TODO: surely there's a terser way
#define PARAM_TEMPLATED_METHOD(TYPE) \
        param_class \
        .def(py::init([](Type type, std::string name, TYPE value) { \
            Param<> param(type, name); \
            param.set<TYPE>(value); \
            return param; \
        }), py::arg("type"), py::arg("name"), py::arg("value")) \
        .def("set", [](Param<> &param, TYPE value) -> void { \
            param.set<TYPE>(value); \
        }, py::arg("value")) \
        .def("set_estimate", [](Param<> &param, TYPE value) -> void { \
            param.set_estimate<TYPE>(value); \
        }, py::arg("value"));

    PARAM_TEMPLATED_METHOD(bool)
    PARAM_TEMPLATED_METHOD(uint8_t)
    PARAM_TEMPLATED_METHOD(uint16_t)
    PARAM_TEMPLATED_METHOD(uint32_t)
    PARAM_TEMPLATED_METHOD(uint64_t)
    PARAM_TEMPLATED_METHOD(int8_t)
    PARAM_TEMPLATED_METHOD(int16_t)
    PARAM_TEMPLATED_METHOD(int32_t)
    PARAM_TEMPLATED_METHOD(int64_t)
    PARAM_TEMPLATED_METHOD(float)
    PARAM_TEMPLATED_METHOD(double)

#undef PARAM_TEMPLATED_METHOD

    //py::implicitly_convertible<Param<T>, Argument>();
    //py::implicitly_convertible<Param<T>, ExternFuncArgument>();
    py::implicitly_convertible<Param<>, Expr>();

    add_binary_operators(param_class);

    m.def("user_context_value", &user_context_value);
}

}  // namespace PythonBindings
}  // namespace Halide
