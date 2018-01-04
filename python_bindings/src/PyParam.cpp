#include "PyParam.h"


#include "PyBinaryOperators.h"
#include "PyType.h"

namespace Halide {
namespace PythonBindings {

// Expr imageparam_to_expr_operator0(ImageParam &that, py::tuple args_passed) {
//     std::vector<Expr> expr_args;
//     // All ImageParam operator()(...) Expr and Var variants end up building a vector<Expr>
//     // all other variants are equivalent to this one
//     const size_t args_len = py::len(args_passed);
//     for (size_t i = 0; i < args_len; i += 1) {
//         expr_args.push_back(py::extract<Expr>(args_passed[i]));
//     }

//     return that(expr_args);
// }

// Expr imageparam_to_expr_operator1(ImageParam &that, Expr an_expr) {
//     std::vector<Expr> expr_args;
//     expr_args.push_back(an_expr);
//     // All ImageParam operator()(...) Expr and Var variants end up building a vector<Expr>
//     // all other variants are equivalent to this one
//     return that(expr_args);
// }

void define_image_param(py::module &m) {
    auto image_param_class =
        py::class_<ImageParam>(m, "ImageParam")
        .def(py::init<>())
        .def(py::init<Type, int>())
        .def(py::init<Type, int, std::string>())
        .def("name", &ImageParam::name)
        .def("set", &ImageParam::set)
        .def("get", &ImageParam::get)
        .def("reset", &ImageParam::reset)
        .def("__getitem__", [](ImageParam &im, const Expr &args) -> Expr {
            return im(args);
        })
        .def("__getitem__", [](ImageParam &im, const std::vector<Expr> &args) -> Expr {
            return im(args);
        })
        .def("width", &ImageParam::width)
        .def("height", &ImageParam::height)

        // .def("dimensions", &ImageParam::dimensions)
        // .def("channels", &ImageParam::channels, ,
        //      "Get an expression giving the extent in dimension 2, "
        //      "which by convention is the channel-count of the image")

        // .def("width", &ImageParam::width, ,
        //      "Get an expression giving the extent in dimension 0, which by "
        //      "convention is the width of the image")
        // .def("height", &ImageParam::height, ,
        //      "Get an expression giving the extent in dimension 1, which by "
        //      "convention is the height of the image")

        // .def("left", &ImageParam::left, ,
        //      "Get an expression giving the minimum coordinate in dimension 0, which "
        //      "by convention is the coordinate of the left edge of the image")
        // .def("right", &ImageParam::right, ,
        //      "Get an expression giving the maximum coordinate in dimension 0, which "
        //      "by convention is the coordinate of the right edge of the image")
        // .def("top", &ImageParam::top, ,
        //      "Get an expression giving the minimum coordinate in dimension 1, which "
        //      "by convention is the top of the image")
        // .def("bottom", &ImageParam::bottom, ,
        //      "Get an expression giving the maximum coordinate in dimension 1, which "
        //      "by convention is the bottom of the image")

        // .def("set", &image_param_set<uint8_t>, py::args("im"),
        //      "Bind a buffer to this ImageParam. Only relevant for jitting.")
        // .def("set", &image_param_set<uint16_t>, py::args("im"),
        //      "Bind a buffer to this ImageParam. Only relevant for jitting.")
        // .def("set", &image_param_set<uint32_t>, py::args("im"),
        //      "Bind a buffer to this ImageParam. Only relevant for jitting.")
        // .def("set", &image_param_set<int8_t>, py::args("im"),
        //      "Bind a buffer to this IageParam. Only relevant for jitting.")
        // .def("set", &image_param_set<int16_t>, py::args("im"),
        //      "Bind a buffer to this ImageParam. Only relevant for jitting.")
        // .def("set", &image_param_set<int32_t>, py::args("im"),
        //      "Bind a buffer to this ImageParam. Only relevant for jitting.")
        // .def("set", &image_param_set<float>, py::args("im"),
        //      "Bind a buffer to this ImageParam. Only relevant for jitting.")
        // .def("set", &image_param_set<double>, py::args("im"),
        //      "Bind a buffer to this ImageParam. Only relevant for jitting.")
        // .def("get", &image_param_get, ,
        //      "Get the buffer bound to this ImageParam. Only relevant for jitting.")
        // .def("__getitem__", &imageparam_to_expr_operator0, py::args("tuple"),
        //      "Construct an expression which loads from this image. "
        //      "The location is extended with enough implicit variables to match "
        //      "the dimensionality of the image (see \\ref Var::implicit).\n\n"
        //      "Call with: [x], [x,y], [x,y,z], or [x,y,z,w]")
        // .def("__getitem__", &imageparam_to_expr_operator1, py::args("expr"),
        //      "Construct an expression which loads from this image. "
        //      "The location is extended with enough implicit variables to match "
        //      "the dimensionality of the image (see \\ref Var::implicit).\n\n"
        //      "Call with: [x], [x,y], [x,y,z], or [x,y,z,w]")

        .def("__repr__", [](const ImageParam &im) -> std::string {
            std::ostringstream o;
            o << "<halide.ImageParam '" <<im.name() << "'";
            if (!im.defined()) {
                o << " (undefined)";
            } else {
                // TODO: add dimensions to this
                o << " type " << halide_type_to_string(im.type());
            }
            o << ">";
            return o.str();
        })
    ;

    py::implicitly_convertible<ImageParam, Argument>();

    // "Using a param as the argument to an external stage treats it as an Expr"
    //py::implicitly_convertible<ImageParam, ExternFuncArgument>();
}

// TODO: unimplemented?
void define_output_image_param() {

    //"A handle on the output buffer of a pipeline. Used to make static
    // "promises about the output size and stride."
    //class OutputImageParam {
    //protected:
    //    "A reference-counted handle on the internal parameter object"
    //    Internal::Parameter param;

    //    void add_implicit_args_if_placeholder(std::vector<Expr> &args,
    //                                          Expr last_arg,
    //                                          int total_args,
    //                                          bool *placeholder_seen) const;
    //public:

    //    "Construct a NULL image parameter handle."
    //    OutputImageParam() {}

    //    "Virtual destructor. Does nothing."
    //    EXPORT virtual ~OutputImageParam();

    //    "Construct an OutputImageParam that wraps an Internal Parameter object."
    //    EXPORT OutputImageParam(const Internal::Parameter &p);

    //    "Get the name of this Param"
    //    EXPORT const std::string &name() const;

    //    "Get the type of the image data this Param refers to"
    //    EXPORT Type type() const;

    //    "Is this parameter handle non-NULL"
    //    EXPORT bool defined();

    //    "Get an expression representing the minimum coordinates of this image
    //     "parameter in the given dimension."
    //    EXPORT Expr min(int x) const;

    //    "Get an expression representing the extent of this image
    //     "parameter in the given dimension"
    //    EXPORT Expr extent(int x) const;

    //    "Get an expression representing the stride of this image in the
    //     "given dimension"
    //    EXPORT Expr stride(int x) const;

    //    "Set the extent in a given dimension to equal the given
    //     "expression. Images passed in that fail this check will generate
    //     "a runtime error. Returns a reference to the ImageParam so that
    //     "these calls may be chained.
    //     *
    //     "This may help the compiler generate better
    //     "code. E.g:
    //     \code
    //     im.set_extent(0, 100);
    //     \endcode
    //     "tells the compiler that dimension zero must be of extent 100,
    //     "which may result in simplification of boundary checks. The
    //     "value can be an arbitrary expression:
    //     \code
    //     im.set_extent(0, im.extent(1));
    //     \endcode
    //     "declares that im is a square image (of unknown size), whereas:
    //     \code
    //     im.set_extent(0, (im.extent(0)/32)*32);
    //     \endcode
    //     "tells the compiler that the extent is a multiple of 32."
    //    EXPORT OutputImageParam &set_extent(int dim, Expr extent);

    //    "Set the min in a given dimension to equal the given
    //     "expression. Setting the mins to zero may simplify some
    //     "addressing math."
    //    EXPORT OutputImageParam &set_min(int dim, Expr min);

    //    "Set the stride in a given dimension to equal the given
    //     "value. This is particularly helpful to set when
    //     "vectorizing. Known strides for the vectorized dimension
    //     "generate better code."
    //    EXPORT OutputImageParam &set_stride(int dim, Expr stride);

    //    "Set the min and extent in one call."
    //    EXPORT OutputImageParam &set_bounds(int dim, Expr min, Expr extent);

    //    "Get the dimensionality of this image parameter"
    //    EXPORT int dimensions() const;

    //    "Get an expression giving the minimum coordinate in dimension 0, which
    //     "by convention is the coordinate of the left edge of the image"
    //    EXPORT Expr left() const;

    //    "Get an expression giving the maximum coordinate in dimension 0, which
    //     "by convention is the coordinate of the right edge of the image"
    //    EXPORT Expr right() const;

    //    "Get an expression giving the minimum coordinate in dimension 1, which
    //     "by convention is the top of the image"
    //    EXPORT Expr top() const;

    //    "Get an expression giving the maximum coordinate in dimension 1, which
    //     "by convention is the bottom of the image"
    //    EXPORT Expr bottom() const;

    //    "Get an expression giving the extent in dimension 0, which by
    //     "convention is the width of the image"
    //    EXPORT Expr width() const;

    //    "Get an expression giving the extent in dimension 1, which by
    //     "convention is the height of the image"
    //    EXPORT Expr height() const;

    //    "Get an expression giving the extent in dimension 2, which by
    //     "convention is the channel-count of the image"
    //    EXPORT Expr channels() const;

    //    "Get at the internal parameter object representing this ImageParam."
    //    EXPORT Internal::Parameter parameter() const;

    //    "Construct the appropriate argument matching this parameter,
    //     "for the purpose of generating the right type signature when
    //     "statically compiling halide pipelines."
    //    EXPORT virtual operator Argument() const;

    //    "Using a param as the argument to an external stage treats it
    //     "as an Expr"
    //    EXPORT operator ExternFuncArgument() const;
    //};
}

// template <typename T>
// void define_param_impl(py::module &m) {
//     const Type type = type_of<T>();
//     const std::string suffix = halide_type_to_string(type);
//     auto param_class =
//         // TODO: is it OK to pass a constructed c_str() here, or does PyBind11
//         // require a const literal?
//         py::class_<Param<T>>(m, ("_Param_" + halide_type_to_string(type)).c_str())
//         .def(py::init<>())
//         .def(py::init<std::string>())
//         .def(py::init<T>())
//         .def(py::init<std::string, T>())
//         .def(py::init<T, Expr, Expr>())
//         .def(py::init<std::string, T, Expr, Expr>())
//         .def("name", &Param<T>::name)
//         .def("is_explicit_name", &Param<T>::is_explicit_name)
//         .def("get", &Param<T>::get)
//         .def("set", &Param<T>::set)
//         .def("type", &Param<T>::type)
//         .def("set_range", &Param<T>::set_range)
//         .def("set_min_value", &Param<T>::set_min_value)
//         .def("set_max_value", &Param<T>::set_max_value)
//         .def("min_value", &Param<T>::min_value)
//         .def("max_value", &Param<T>::max_value)
//         .def("set_estimate", &Param<T>::set_estimate)
//         // .def("as_expr", (Expr (Param<T>::*)()) &Var::operator Expr)
//         // .def("as_ExternFuncArgument", (ExternFuncArgument (Param<T>::*)()) &Var::operator ExternFuncArgument)
//         // .def("as_Argument", (Argument (Param<T>::*)()) &Var::operator Argument)

//         .def("__repr__", [](const Param<T> &param) -> std::string {
//             std::ostringstream o;
//             o << "<halide.Param '" << param.name() << "'"
//               << " type " << halide_type_to_string(param.type()) << ">";
//             return o.str();
//         })
//     ;

//     //py::implicitly_convertible<Param<T>, Argument>();
//     //py::implicitly_convertible<Param<T>, ExternFuncArgument>();
//     py::implicitly_convertible<Param<T>, Expr>();

//     add_binary_operators(param_class);

//     // add_binary_operators_with<int>(param_class);
//     // add_binary_operators_with<float>(param_class);
//     // add_binary_operators_with<Expr>(param_class);

//     // add_binary_operators_with<Param<uint8_t>>(param_class);
//     // add_binary_operators_with<Param<uint16_t>>(param_class);
//     // add_binary_operators_with<Param<uint32_t>>(param_class);

//     // add_binary_operators_with<Param<int8_t>>(param_class);
//     // add_binary_operators_with<Param<int16_t>>(param_class);
//     // add_binary_operators_with<Param<int32_t>>(param_class);

//     // add_binary_operators_with<Param<float>>(param_class);
//     // add_binary_operators_with<Param<double>>(param_class);
// }

// template <typename T, typename... Args>
// py::object create_param_object(Args... args) {
//     typedef Param<T> ParamType;
//     typedef typename py::manage_new_object::apply<ParamType *>::type converter_t;
//     converter_t converter;
//     PyObject *obj = converter(new ParamType(args...));
//     return py::object(py::handle<>(obj));
// }

// struct end_of_recursion_t {};  // dummy helper type

// template <typename T = end_of_recursion_t, typename... Types>
// py::object create_param_impl(Type type, std::string name) {
//     if (type_of<T>() == type) {
//         if (!name.empty()) {
//             return create_param_object<T>(name);
//         } else {
//             return create_param_object<T>();
//         }
//     } else {
//         return create_param_impl<Types...>(type, name);  // keep recursing
//     }
// }

// template <>
// py::object create_param_impl<end_of_recursion_t>(Type type, std::string /*name*/) {  // end of recursion, did not find a matching type
//     throw std::invalid_argument("ParamFactory::create_param_impl received type not handled");
//     return py::object();
// }

// // TODO: int64, uint64, bool
// typedef boost::mpl::list<uint8_t, uint16_t, uint32_t,
//                          int8_t, int16_t, int32_t,
//                          float, double>
//     pixel_types_t;

// template <typename PixelTypes, typename... Args>
// struct create_param1_impl_t {
//     py::object operator()(Type type, py::object val, Args... args) {
//         typedef typename boost::mpl::front<PixelTypes>::type pixel_t;
//         if (type_of<pixel_t>() == type) {
//             py::extract<pixel_t> val_extract(val);
//             if (val_extract.check()) {
//                 pixel_t true_val = val_extract();
//                 return call_create_param_object<pixel_t>(true_val, args...);
//             } else {
//                 const std::string val_str = py::extract<std::string>(py::str(val));
//                 throw std::invalid_argument("ParamFactory::create_param1_impl called with "
//                                             "a value that could not be converted to the given type");
//             }
//         } else {  // keep recursing
//             typedef typename boost::mpl::pop_front<PixelTypes>::type pixels_types_tail_t;
//             return create_param1_impl_t<pixels_types_tail_t, Args...>()(type, val, args...);
//         }
//     }

//     template <typename T>
//     py::object call_create_param_object(T true_val) {
//         return create_param_object<T>(true_val);
//     }

//     template <typename T>
//     py::object call_create_param_object(T true_val, std::string name) {
//         return create_param_object<T>(name, true_val);
//     }

//     template <typename T>
//     py::object call_create_param_object(T true_val, std::string name, Expr min, Expr max) {
//         return create_param_object<T>(name, true_val, min, max);
//     }

//     template <typename T>
//     py::object call_create_param_object(T true_val, Expr min, Expr max) {
//         return create_param_object<T>(true_val, min, max);
//     }
// };

// template <typename... Args>
// struct create_param1_impl_t<boost::mpl::l_end::type, Args...> {
//     py::object operator()(Type type, py::object val, Args... args) {
//         // end of recursion, did not find a matching type
//         throw std::invalid_argument("ParamFactory::create_param1_impl received type not handled");
//         return py::object();
//     }
// };

// struct ParamFactory {
//     static py::object create_param0(Type type) {
//         return create_param_impl<bool, uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int16_t, int32_t, int64_t, float, double>(type, "");
//     }

//     static py::object create_param1(Type type, std::string name) {
//         return create_param_impl<
//             uint8_t, uint16_t, uint32_t,
//             int8_t, int16_t, int32_t,
//             float, double>(type, name);
//     }

//     static py::object create_param2(Type type, py::object val) {
//         return create_param1_impl_t<pixel_types_t>()(type, val);
//     }

//     static py::object create_param3(Type type, std::string name, py::object val) {
//         return create_param1_impl_t<pixel_types_t, std::string>()(type, val, name);
//     }

//     static py::object create_param4(Type type, py::object val, Expr min, Expr max) {
//         return create_param1_impl_t<pixel_types_t, Expr, Expr>()(type, val, min, max);
//     }

//     static py::object create_param5(Type type, std::string name, py::object val, Expr min, Expr max) {
//         return create_param1_impl_t<pixel_types_t, std::string, Expr, Expr>()(type, val, name, min, max);
//     }
// };

// TODO: roll this into Param<> a la Buffer<void>
// class DynamicParam {
//     /** A reference-counted handle on the internal parameter object */
//     Type param_type;
//     Internal::Parameter param;

// public:
//     explicit DynamicParam(Type t) :
//         param_type(t), param(param_type, false, 0, Internal::make_entity_name(this, "Halide::Param<?", 'p')) {}

//     explicit DynamicParam(Type t, const std::string &n) :
//         param_type(t), param(param_type, false, 0, n, /*is_explicit_name*/ true) {
//         check_name();
//     }

//     explicit DynamicParam(Type t, T val) :
//         param_type(t), param(param_type, false, 0, Internal::make_entity_name(this, "Halide::Param<?", 'p')) {
//         set(val);
//     }

//     /** Construct a scalar parameter of type T with the given name
//      * and an initial value of 'val'. */
//     DynamicParam(Type t, const std::string &n, T val) :
//         param_type(t), param(param_type, false, 0, n, /*is_explicit_name*/ true) {
//         check_name();
//         set(val);
//     }

//     DynamicParam(Type t, T val, Expr min, Expr max) :
//         param_type(t), param(param_type, false, 0, Internal::make_entity_name(this, "Halide::Param<?", 'p')) {
//         set_range(min, max);
//         set(val);
//     }

//     DynamicParam(Type t, const std::string &n, T val, Expr min, Expr max) :
//         param(param_type, false, 0, n, /*is_explicit_name*/ true) {
//         check_name();
//         set_range(min, max);
//         set(val);
//     }

//     /** Get the name of this parameter */
//     const std::string &name() const {
//         return param.name();
//     }

//     /** Get the current value of this parameter. Only meaningful when jitting. */
//     NO_INLINE T get() const {
//         return param.scalar<T>();
//     }

//     * Set the current value of this parameter. Only meaningful when jitting
//     void set(T val) {
//         param.set_scalar<T>(val);
//     }

//     /** Get the halide type of T */
//     Type type() const {
//         return param_type;
//     }

//     void set_range(Expr min, Expr max) {
//         set_min_value(min);
//         set_max_value(max);
//     }

//     void set_min_value(Expr min) {
//         if (min.defined() && min.type() != param_type) {
//             min = Internal::Cast::make(param_type, min);
//         }
//         param.set_min_value(min);
//     }

//     void set_max_value(Expr max) {
//         if (max.defined() && max.type() != param_type) {
//             max = Internal::Cast::make(param_type, max);
//         }
//         param.set_max_value(max);
//     }

//     Expr min_value() const {
//         return param.min_value();
//     }

//     Expr max_value() const {
//         return param.max_value();
//     }

//     void set_estimate(const T &value) {
//         param.set_estimate(Expr(value));
//     }

//     /** You can use this parameter as an expression in a halide
//      * function definition */
//     operator Expr() const {
//         return Internal::Variable::make(param_type, name(), param);
//     }

//     /** Using a param as the argument to an external stage treats it
//      * as an Expr */
//     operator ExternFuncArgument() const {
//         return Expr(*this);
//     }

//     /** Construct the appropriate argument matching this parameter,
//      * for the purpose of generating the right type signature when
//      * statically compiling halide pipelines. */
//     operator Argument() const {
//         return Argument(name(), Argument::InputScalar, type(), 0,
//             param.scalar_expr(), param.min_value(), param.max_value());
//     }
// };

void define_param(py::module &m) {
    auto param_class =
        py::class_<Param<>>(m, "Param")
        .def(py::init<Type>(), py::arg("type"))
        .def(py::init<Type, std::string>(), py::arg("type"), py::arg("name"))
        .def(py::init([](Type type, std::string name, float value) {
            Param<> p(type, name);
            p.set<float>(value);
            return p;
        }), py::arg("type"), py::arg("name"), py::arg("value"))
// TODO missing from C++ api
//        .def(py::init<Type, Expr, Expr>(), py::arg("type"), py::arg("min"), py::arg("max"))
//        .def(py::init<Type, std::string, Expr, Expr>(), py::arg("type"), py::arg("name"), py::arg("min"), py::arg("max"))
        .def("name", &Param<>::name)
//        .def("get", &Param<>::get)
        .def("set", [](Param<> &param, uint8_t value) -> void {
            param.set<uint8_t>(value);
        }, py::arg("value"))
        .def("type", &Param<>::type)
        // .def("set_range", &Param<>::set_range)
        // .def("set_min_value", &Param<>::set_min_value)
        // .def("set_max_value", &Param<>::set_max_value)
        // .def("min_value", &Param<>::min_value)
        // .def("max_value", &Param<>::max_value)
//        .def("set_estimate", &Param<>::set_estimate)
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

    //py::implicitly_convertible<Param<T>, Argument>();
    //py::implicitly_convertible<Param<T>, ExternFuncArgument>();
    py::implicitly_convertible<Param<>, Expr>();

    add_binary_operators(param_class);

    m.def("user_context_value", &user_context_value);

    define_image_param(m);
    // define_output_image_param();
}

}  // namespace PythonBindings
}  // namespace Halide
