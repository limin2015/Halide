#include "PyImageParam.h"

#include "PyType.h"

namespace Halide {
namespace PythonBindings {

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
        .def("dimensions", &ImageParam::dimensions)
        .def("left", &ImageParam::left)
        .def("right", &ImageParam::right)
        .def("top", &ImageParam::top)
        .def("bottom", &ImageParam::bottom)

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


}  // namespace PythonBindings
}  // namespace Halide
