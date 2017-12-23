#include "PyFunc.h"

#include "PyBinaryOperators.h"
#include "PyBuffer.h"
#include "PyExpr.h"
#include "PyFunc_Ref.h"
#include "PyFunc_Stage.h"
#include "PyFunc_VarOrRVar.h"
#include "PyFunc_gpu.h"

namespace Halide {
namespace PythonBindings {

// py::object realization_to_python_object(const Realization &r) {
//     if (r.size() == 1) {
//         return buffer_to_python_object(r[0]);
//     } else {
//         py::list elts;
//         for (size_t i = 0; i < r.size(); i++) {
//             elts.append(buffer_to_python_object(r[i]));
//         }
//         return py::tuple(elts);
//     }
// }

// Realization python_object_to_realization(py::object obj) {
//     std::vector<Buffer<>> buffers;
//     py::extract<py::tuple> tuple_extract(obj);
//     if (tuple_extract.check()) {
//         py::tuple tup = tuple_extract();
//         for (ssize_t i = 0; i < py::len(tup); i++) {
//             buffers.push_back(python_object_to_buffer(tup[i]));
//         }
//     } else {
//         buffers.push_back(python_object_to_buffer(obj));
//     }
//     return Realization(buffers);
// }

// template <typename... Args>
// py::object func_realize(Func &f, Args... args) {
//     return realization_to_python_object(f.realize(args...));
// }

// template <typename... Args>
// void func_realize_into(Func &f, Args... args) {
//     f.realize(args...);
// }

// template <typename... Args>
// void func_realize_tuple(Func &f, py::tuple obj, Args... args) {
//     f.realize(python_object_to_realization(obj), args...);
// }

// void func_compile_jit0(Func &that) {
//     that.compile_jit();
// }

// void func_compile_jit1(Func &that, const Target &target = get_target_from_environment()) {
//     that.compile_jit(target);
// }

// void func_compile_to_bitcode0(Func &that, const std::string &filename,
//                               py::list args,
//                               const std::string fn_name = "",
//                               const Target &target = get_target_from_environment()) {
//     auto args_vec = python_collection_to_vector<Argument>(args);
//     that.compile_to_bitcode(filename, args_vec, fn_name, target);
// }

// BOOST_PYTHON_FUNCTION_OVERLOADS(func_compile_to_bitcode0_overloads, func_compile_to_bitcode0, 3, 5)

// void func_compile_to_object0(Func &that, const std::string &filename,
//                              py::list args,
//                              const std::string fn_name = "",
//                              const Target &target = get_target_from_environment()) {
//     auto args_vec = python_collection_to_vector<Argument>(args);
//     that.compile_to_object(filename, args_vec, fn_name, target);
// }

// BOOST_PYTHON_FUNCTION_OVERLOADS(func_compile_to_object0_overloads, func_compile_to_object0, 3, 5)

// void func_compile_to_header0(Func &that, const std::string &filename,
//                              py::list args,
//                              const std::string fn_name = "",
//                              const Target &target = get_target_from_environment()) {
//     auto args_vec = python_collection_to_vector<Argument>(args);
//     that.compile_to_header(filename, args_vec, fn_name, target);
// }

// BOOST_PYTHON_FUNCTION_OVERLOADS(func_compile_to_header0_overloads, func_compile_to_header0, 3, 5)

// void func_compile_to_assembly0(Func &that, const std::string &filename,
//                                py::list args,
//                                const std::string fn_name = "",
//                                const Target &target = get_target_from_environment()) {
//     auto args_vec = python_collection_to_vector<Argument>(args);
//     that.compile_to_assembly(filename, args_vec, fn_name, target);
// }

// BOOST_PYTHON_FUNCTION_OVERLOADS(func_compile_to_assembly0_overloads, func_compile_to_assembly0, 3, 5)

// void func_compile_to_c0(Func &that, const std::string &filename,
//                         py::list args,
//                         const std::string fn_name = "",
//                         const Target &target = get_target_from_environment()) {
//     auto args_vec = python_collection_to_vector<Argument>(args);
//     that.compile_to_c(filename, args_vec, fn_name, target);
// }

// BOOST_PYTHON_FUNCTION_OVERLOADS(func_compile_to_c0_overloads, func_compile_to_c0, 3, 5)

// void func_compile_to_file0(Func &that, const std::string &filename_prefix,
//                            py::list args,
//                            const std::string fn_name = "",
//                            const Target &target = get_target_from_environment()) {
//     auto args_vec = python_collection_to_vector<Argument>(args);
//     that.compile_to_file(filename_prefix, args_vec, fn_name, target);
// }

// BOOST_PYTHON_FUNCTION_OVERLOADS(func_compile_to_file0_overloads, func_compile_to_file0, 3, 5)

// void func_compile_to_lowered_stmt0(Func &that,
//                                    const std::string &filename,
//                                    py::list args,
//                                    StmtOutputFormat fmt = Text,
//                                    const Target &target = get_target_from_environment()) {
//     auto args_vec = python_collection_to_vector<Argument>(args);
//     that.compile_to_lowered_stmt(filename, args_vec, fmt, target);
// }

// BOOST_PYTHON_FUNCTION_OVERLOADS(func_compile_to_lowered_stmt0_overloads, func_compile_to_lowered_stmt0, 3, 5)

// // parallel, vectorize, unroll, tile, and reorder methods are shared with Stage class
// // and thus defined as template functions in the header

// Func &func_store_at0(Func &that, Func f, Var var) {
//     return that.store_at(f, var);
// }

// Func &func_store_at1(Func &that, Func f, RVar var) {
//     return that.store_at(f, var);
// }

// Func &func_compute_at0(Func &that, Func f, Var var) {
//     return that.compute_at(f, var);
// }

// Func &func_compute_at1(Func &that, Func f, RVar var) {
//     return that.compute_at(f, var);
// }

// FuncRef func_getitem_operator(Func &func, py::object arg) {
//     return func(python_tuple_to_expr_vector(arg));
// }

// Stage func_setitem_operator(Func &func, py::object lhs, py::object rhs) {
//     return (func(python_tuple_to_expr_vector(lhs)) =
//                 Tuple(python_tuple_to_expr_vector(rhs)));
// }

// void func_define_extern0(Func &that,
//                          const std::string &function_name,
//                          py::list params,
//                          Type output_type,
//                          int dimensionality) {
//     auto params_vec = python_collection_to_vector<ExternFuncArgument>(params);
//     return that.define_extern(function_name, params_vec, output_type, dimensionality);
// }

// void func_define_extern1(Func &that,
//                          const std::string &function_name,
//                          py::list params,
//                          py::list types,
//                          int dimensionality) {
//     auto params_vec = python_collection_to_vector<ExternFuncArgument>(params);
//     auto types_vec = python_collection_to_vector<Type>(types);
//     return that.define_extern(function_name, params_vec, types_vec, dimensionality);
// }

// py::tuple func_output_types(Func &func) {
//     py::list elts;
//     for (Type t : func.output_types()) {
//         elts.append(t);
//     }
//     return py::tuple(elts);
// }

void define_func(py::module &m) {
    py::enum_<StmtOutputFormat>(m, "StmtOutputFormat")
        .value("Text", StmtOutputFormat::Text)
        .value("HTML", StmtOutputFormat::HTML);

    py::enum_<TailStrategy>(m, "TailStrategy")
        .value("RoundUp", TailStrategy::RoundUp)
        .value("GuardWithIf", TailStrategy::GuardWithIf)
        .value("ShiftInwards", TailStrategy::ShiftInwards)
        .value("Auto", TailStrategy::Auto)
    ;

    define_func_ref(m);
    define_stage(m);
    define_var_or_rvar(m);

    // TODO: move to its own file
    // TODO: incomplete
    auto looplevel_class =
        py::class_<LoopLevel>(m, "LoopLevel")
        .def(py::init<>())
        .def("inlined", &LoopLevel::inlined)
        .def("root", &LoopLevel::root)
    ;

    auto func_class =
        py::class_<Func>(m, "Func")
        .def(py::init<>())
        .def(py::init<std::string>())
        .def(py::init<Expr>())
        .def("realize", (Realization (Func::*)(std::vector<int32_t>, const Target &)) &Func::realize,
            py::arg("sizes"), py::arg("target") = Target())
        .def("realize", (Realization (Func::*)(const Target &)) &Func::realize,
            py::arg("target") = Target())
        .def("realize", (Realization (Func::*)(int, const Target &)) &Func::realize,
            py::arg("x_size"), py::arg("target") = Target())
        .def("realize", (Realization (Func::*)(int, int, const Target &)) &Func::realize,
            py::arg("x_size"), py::arg("y_size"), py::arg("target") = Target())
        .def("realize", (Realization (Func::*)(int, int, int, const Target &)) &Func::realize,
            py::arg("x_size"), py::arg("y_size"), py::arg("z_size"), py::arg("target") = Target())
        .def("realize", (Realization (Func::*)(int, int, int, int, const Target &)) &Func::realize,
            py::arg("x_size"), py::arg("y_size"), py::arg("z_size"), py::arg("w_size"), py::arg("target") = Target())
        .def("realize", (void (Func::*)(Realization, const Target &)) &Func::realize,
            py::arg("dst"), py::arg("target") = Target())
        .def("name", &Func::name)
        // TODO: is there a way to avoid the combinations?
        .def("__getitem__", [](Func &func, const Expr &args) -> FuncRef {
            return func(args);
        })
        .def("__getitem__", [](Func &func, const std::vector<Expr> &args) -> FuncRef {
            return func(args);
        })
        .def("__getitem__", [](Func &func, const Var &args) -> FuncRef {
            return func(args);
        })
        .def("__getitem__", [](Func &func, const std::vector<Var> &args) -> FuncRef {
            return func(args);
        })
        .def("__setitem__", [](Func &func, const Var &lhs, const Expr &rhs) -> Stage {
            return func(lhs) = rhs;
        })
        .def("__setitem__", [](Func &func, const std::vector<Var> &lhs, const Expr &rhs) -> Stage {
            return func(lhs) = rhs;
        })
        .def("__setitem__", [](Func &func, const Var &lhs, const std::vector<Expr> &rhs) -> Stage {
            return func(lhs) = Tuple(rhs);
        })
        .def("__setitem__", [](Func &func, const std::vector<Var> &lhs, const std::vector<Expr> &rhs) -> Stage {
            return func(lhs) = Tuple(rhs);
        })
        .def("bound", &Func::bound)

        .def("tile", (Func &(Func::*)(VarOrRVar, VarOrRVar, VarOrRVar, VarOrRVar, VarOrRVar, VarOrRVar, Expr, Expr, TailStrategy)) &Func::tile,
            py::arg("x"), py::arg("y"), py::arg("xo"), py::arg("yo"), py::arg("xi"), py::arg("yi"), py::arg("xfactor"), py::arg("yfactor"), py::arg("tail") = TailStrategy::Auto)
        .def("tile", (Func &(Func::*)(VarOrRVar, VarOrRVar, VarOrRVar, VarOrRVar, Expr, Expr, TailStrategy)) &Func::tile,
            py::arg("x"), py::arg("y"), py::arg("xi"), py::arg("yi"), py::arg("xfactor"), py::arg("yfactor"), py::arg("tail") = TailStrategy::Auto)

        .def("parallel", (Func &(Func::*)(VarOrRVar)) &Func::parallel,
            py::arg("var"))
        .def("parallel", (Func &(Func::*)(VarOrRVar, Expr, TailStrategy)) &Func::parallel,
            py::arg("var"), py::arg("task_size"), py::arg("tail") = TailStrategy::Auto)

        .def("vectorize", (Func &(Func::*)(VarOrRVar)) &Func::vectorize,
            py::arg("var"))
        .def("vectorize", (Func &(Func::*)(VarOrRVar, Expr, TailStrategy)) &Func::vectorize,
            py::arg("var"), py::arg("factor"), py::arg("tail") = TailStrategy::Auto)

        .def("compute_at", (Func &(Func::*)(Func, Var)) &Func::compute_at)
        .def("compute_at", (Func &(Func::*)(Func, RVar)) &Func::compute_at)
        .def("compute_at", (Func &(Func::*)(LoopLevel)) &Func::compute_at)

    // func_class.def("compile_to_bitcode", &func_compile_to_bitcode0,
    //                func_compile_to_bitcode0_overloads(
    //                    py::args("filename", "args", "fn_name", "target"),
    //                    "Statically compile this function to llvm bitcode, with the "
    //                    "given filename (which should probably end in .bc), type "
    //                    "signature, and C function name (which defaults to the same name "
    //                    "as this halide function."));

    // func_class.def("compile_to_object", &func_compile_to_object0,
    //                func_compile_to_object0_overloads(
    //                    py::args("filename", "args", "fn_name", "target"),
    //                    "Statically compile this function to an object file, with the "
    //                    "given filename (which should probably end in .o or .obj), type "
    //                    "signature, and C function name (which defaults to the same name "
    //                    "as this halide function. You probably don't want to use this "
    //                    "directly; call compile_to_file instead."));

    // func_class.def("compile_to_header", &func_compile_to_header0,
    //                func_compile_to_header0_overloads(
    //                    py::args("filename", "args", "fn_name", "target"),
    //                    "Emit a header file with the given filename for this "
    //                    "function. The header will define a function with the type "
    //                    "signature given by the second argument, and a name given by the "
    //                    "third. The name defaults to the same name as this halide "
    //                    "function. You don't actually have to have defined this function "
    //                    "yet to call this. You probably don't want to use this directly; "
    //                    "call compile_to_file instead. "));

    // func_class.def("compile_to_assembly", &func_compile_to_assembly0,
    //                func_compile_to_assembly0_overloads(
    //                    py::args("filename", "args", "fn_name", "target"),
    //                    " Statically compile this function to text assembly equivalent "
    //                    " to the object file generated by compile_to_object. This is "
    //                    " useful for checking what Halide is producing without having to "
    //                    " disassemble anything, or if you need to feed the assembly into "
    //                    " some custom toolchain to produce an object file (e.g. iOS) "));

    // func_class.def("compile_to_c", &func_compile_to_c0,
    //                func_compile_to_c0_overloads(
    //                    py::args("filename", "args", "fn_name", "target"),
    //                    "Statically compile this function to C source code. This is "
    //                    "useful for providing fallback code paths that will compile on "
    //                    "many platforms. Vectorization will fail, and parallelization "
    //                    "will produce serial code."));

    // func_class.def("compile_to_file",
    //                &func_compile_to_file0,
    //                func_compile_to_file0_overloads(
    //                    py::args("filename_prefix", "args", "fn_name", "target"),
    //                    "Compile to object file and header pair, with the given arguments. "
    //                    "The name defaults to the same name as the Halide Func."));

    .def("compile_jit", &Func::compile_jit, py::arg("target") = get_jit_target_from_environment())

    // func_class.def("debug_to_file", &Func::debug_to_file,
    //                "When this function is compiled, include code that dumps its values "
    //                "to a file after it is realized, for the purpose of debugging. "
    //                "The file covers the realized extent at the point in the schedule that "
    //                "debug_to_file appears.\n"
    //                "If filename ends in \".tif\" or \".tiff\" (case insensitive) the file "
    //                "is in TIFF format and can be read by standard tools.");

    // func_class.def("compile_to_lowered_stmt", &func_compile_to_lowered_stmt0,
    //                func_compile_to_lowered_stmt0_overloads(
    //                    py::args("filename", "args", "fmt", "target"),
    //                    "Write out an internal representation of lowered code. Useful "
    //                    "for analyzing and debugging scheduling. Can emit html or plain text."));

    // func_class.def("print_loop_nest", &Func::print_loop_nest, ,
    //                "Write out the loop nests specified by the schedule for this "
    //                "Function. Helpful for understanding what a schedule is doing.");

    // .def("args", &Func::args, ,
    //                "Get the pure arguments.");

    // .def("value", &Func::value, ,
    //                "The right-hand-side value of the pure definition of this "
    //                "function. Causes an error if there's no pure definition, or if "
    //                "the function is defined to return multiple values.");

    // .def("values", &Func::values, ,
    //                "The values returned by this function. An error if the function "
    //                "has not been been defined. Returns a tuple with one element for "
    //                "functions defined to return a single value.");

    // .def("defined", &Func::defined, ,
    //                "Does this function have at least a pure definition.");

    // .def("update_args", &Func::update_args),
    //                py::return_value_policy<py::copy_const_reference>(),
    //                "Get the left-hand-side of the update definition. An empty "
    //                "vector if there's no update definition. If there are "
    //                "multiple update definitions for this function, use the "
    //                "argument to select which one you want.");

    // .def("update_value", &Func::update_value, (py::arg("idx") = 0),
    //                "Get the right-hand-side of an update definition. An error if "
    //                "there's no update definition. If there are multiple "
    //                "update definitions for this function, use the argument to "
    //                "select which one you want.");

    // .def("update_values", &Func::update_values, (py::arg("idx") = 0),
    //                "Get the right-hand-side of an update definition for "
    //                "functions that returns multiple values. An error if there's no "
    //                "update definition. Returns a Tuple with one element for "
    //                "functions that return a single value.");

    // .def("rvars", &Func::rvars, (py::arg("idx") = 0),
    //                "Get the reduction variables for an update definition, if there is one.");

    // func_class
    //     .def("has_update_definition", &Func::has_update_definition, ,
    //          "Does this function have at least one update definition?")
    //     .def("num_update_definitions", &Func::num_update_definitions, ,
    //          "How many update definitions does this function have?");

    // .def("is_extern", &Func::is_extern, ,
    //                "Is this function an external stage? That is, was it defined "
    //                "using define_extern?");

    // .def("define_extern", &func_define_extern0,
    //                py::args("function_name", "params", "output_type", "dimensionality"),
    //                "Add an extern definition for this Func. This lets you define a "
    //                "Func that represents an external pipeline stage. You can, for "
    //                "example, use it to wrap a call to an extern library such as "
    //                "fftw.")
    //     .def("define_extern", &func_define_extern1);

    // .def("output_types", &func_output_types, ,
    //                "Get the types of the outputs of this Func.");

    // .def("outputs", &Func::outputs, ,
    //                "Get the number of outputs of this Func. Corresponds to the "
    //                "size of the Tuple this Func was defined to return.");

    // .def("extern_function_name", &Func::extern_function_name, ,
    //                py::return_value_policy<py::copy_const_reference>(),
    //                "Get the name of the extern function called for an extern definition.");

    // .def("dimensions", &Func::dimensions, ,
    //                "The dimensionality (number of arguments) of this function. Zero if the function is not yet defined.");

    // // FIXME should share these definitions with Stage instead of having copy and paste code

    // .def("split", &func_split<Func>,
    //                py::return_internal_reference<1>(),
    //                "Split a dimension into inner and outer subdimensions with the "
    //                "given names, where the inner dimension iterates from 0 to "
    //                "factor-1. The inner and outer subdimensions can then be dealt "
    //                "with using the other scheduling calls. It's ok to reuse the old "
    //                "variable name as either the inner or outer variable.")
    //     .def("fuse", &Func::fuse,
    //          py::return_internal_reference<1>(),
    //          "Join two dimensions into a single fused dimenion. The fused "
    //          "dimension covers the product of the extents of the inner and "
    //          "outer dimensions given.")
    //     .def("serial", &Func::serial,
    //          py::return_internal_reference<1>(),
    //          "Mark a dimension to be traversed serially. This is the default.");

    // .def("parallel", &func_parallel0<Func>,
    //                py::return_internal_reference<1>(),
    //                "Mark a dimension (Var instance) to be traversed in parallel.")
    //     .def("parallel", &func_parallel1<Func>,
    //          py::return_internal_reference<1>());

    // .def("vectorize", &func_vectorize1<Func>,
    //                py::return_internal_reference<1>(),
    //                "Split a dimension (Var instance) by the given int factor, then vectorize the "
    //                "inner dimension. This is how you vectorize a loop of unknown "
    //                "size. The variable to be vectorized should be the innermost "
    //                "one. After this call, var refers to the outer dimension of the "
    //                "split.")
    //     .def("vectorize", &func_vectorize0<Func>,
    //          py::return_internal_reference<1>());

    // .def("unroll", &func_unroll1<Func>,
    //                py::return_internal_reference<1>(),
    //                "Split a dimension by the given factor, then unroll the inner "
    //                "dimension. This is how you unroll a loop of unknown size by "
    //                "some constant factor. After this call, var refers to the outer "
    //                "dimension of the split.")
    //     .def("unroll", &func_unroll0<Func>,
    //          py::return_internal_reference<1>());

    // .def("bound", &Func::bound,
    //                py::return_internal_reference<1>(),
    //                "Statically declare that the range over which a function should "
    //                "be evaluated is given by the second and third arguments. This "
    //                "can let Halide perform some optimizations. E.g. if you know "
    //                "there are going to be 4 color channels, you can completely "
    //                "vectorize the color channel dimension without the overhead of "
    //                "splitting it up. If bounds inference decides that it requires "
    //                "more of this function than the bounds you have stated, a "
    //                "runtime error will occur when you try to run your pipeline. ");

    // .def("tile", &func_tile0<Func>,
    //                py::return_internal_reference<1>(),
    //                "Split two dimensions at once by the given factors, and then "
    //                "reorder the resulting dimensions to be xi, yi, xo, yo from "
    //                "innermost outwards. This gives a tiled traversal.");

    // .def("tile", &func_tile1<Func>,
    //                py::return_internal_reference<1>(),
    //                "A shorter form of tile, which reuses the old variable names as the new outer dimensions");

    // .def("reorder", &func_reorder0<Func, py::tuple>,
    //                py::return_internal_reference<1>(),
    //                "Reorder variables to have the given nesting order, "
    //                "from innermost out")
    //     .def("reorder", &func_reorder0<Func, py::list>,
    //          py::return_internal_reference<1>(),
    //          "Reorder variables to have the given nesting order, "
    //          "from innermost out")
    //     .def("reorder", &func_reorder1<Func>, (py::arg("v0"), py::arg("v1") = py::object(),
    //                                            py::arg("v2") = py::object(), py::arg("v3") = py::object(),
    //                                            py::arg("v4") = py::object(), py::arg("v5") = py::object()),
    //          py::return_internal_reference<1>(),
    //          "Reorder variables to have the given nesting order, "
    //          "from innermost out");

    // .def("rename", &Func::rename,
    //                py::return_internal_reference<1>(),
    //                "Rename a dimension. Equivalent to split with a inner size of one.");

    // const std::string reorder_storage_doc =
    //     "Specify how the storage for the function is laid out. These "
    //     "calls let you specify the nesting order of the dimensions. For "
    //     "example, foo.reorder_storage(y, x) tells Halide to use "
    //     "column-major storage for any realizations of foo, without "
    //     "changing how you refer to foo in the code. You may want to do "
    //     "this if you intend to vectorize across y. When representing "
    //     "color images, foo.reorder_storage(c, x, y) specifies packed "
    //     "storage (red, green, and blue values adjacent in memory), and "
    //     "foo.reorder_storage(x, y, c) specifies planar storage (entire "
    //     "red, green, and blue images one after the other in memory).\n\n"
    //     "If you leave out some dimensions, those remain in the same "
    //     "positions in the nesting order while the specified variables "
    //     "are reordered around them.";
    // .def("reorder_storage", &func_reorder_storage0<Func, py::tuple>,
    //                py::return_internal_reference<1>(), reorder_storage_doc.c_str())
    //     .def("reorder_storage", &func_reorder_storage0<Func, py::list>,
    //          py::return_internal_reference<1>(), reorder_storage_doc.c_str())
    //     .def("reorder_storage", &func_reorder_storage1<Func>, (py::arg("v0"), py::arg("v1"),
    //                                                            py::arg("v2") = py::object(), py::arg("v3") = py::object(),
    //                                                            py::arg("v4") = py::object(), py::arg("v5") = py::object()),
    //          py::return_internal_reference<1>(), reorder_storage_doc.c_str());

    // .def("compute_at", &func_compute_at0,
    //                py::return_internal_reference<1>(),
    //                "Compute this function as needed for each unique value of the "
    //                "given var (can be a Var or an RVar) for the given calling function f.")
    //     .def("compute_at", &func_compute_at1,
    //          py::return_internal_reference<1>());

    // .def("compute_root", &Func::compute_root, ,
    //                py::return_internal_reference<1>(),
    //                "Compute all of this function once ahead of time.");

    // .def("store_at", &func_store_at0,
    //                py::return_internal_reference<1>(),
    //                "Allocate storage for this function within f's loop over "
    //                "var (can be a Var or an RVar). Scheduling storage is optional, and can be used to "
    //                "separate the loop level at which storage occurs from the loop "
    //                "level at which computation occurs to trade off between locality "
    //                "and redundant work.")
    //     .def("store_at", &func_store_at1,
    //          py::return_internal_reference<1>());

    // .def("store_root", &Func::store_root, ,
    //                py::return_internal_reference<1>(),
    //                "Equivalent to Func.store_at, but schedules storage outside the outermost loop.");

    // .def("compute_inline", &Func::compute_inline, ,
    //                py::return_internal_reference<1>(),
    //                "Aggressively inline all uses of this function. This is the "
    //                "default schedule, so you're unlikely to need to call this. For "
    //                "a reduction, that means it gets computed as close to the "
    //                "innermost loop as possible.");

    // .def("update", &Func::update, (py::arg("idx") = 0),
    //                "Get a handle on the update step of a reduction for the "
    //                "purposes of scheduling it. Only the pure dimensions of the "
    //                "update step can be meaningfully manipulated (see RDom).");

    // .def("function", &Func::function, ,
    //                "Get a handle on the internal halide function that this Func represents. "
    //                "Useful if you want to do introspection on Halide functions.")
    //     .def("trace_loads", &Func::trace_loads, ,
    //          py::return_internal_reference<1>(),
    //          "Trace all loads from this Func by emitting calls to "
    //          "halide_trace. If the Func is inlined, this has no effect.")
    //     .def("trace_stores", &Func::trace_stores, ,
    //          py::return_internal_reference<1>(),
    //          "Trace all stores to the buffer backing this Func by emitting "
    //          "calls to halide_trace. If the Func is inlined, this call has no effect.")
    //     .def("trace_realizations", &Func::trace_realizations, ,
    //          py::return_internal_reference<1>(),
    //          "Trace all realizations of this Func by emitting calls to halide_trace.");

    // .def("specialize", &Func::specialize,
    //                "Specialize a Func. This creates a special-case version of the "
    //                "Func where the given condition is true. The most effective "
    //                "conditions are those of the form param == value, and boolean "
    //                "Params. See C++ documentation for more details.");

        .def("__repr__", [](const Func &func) -> std::string {
            std::ostringstream o;
            o << "<halide.Func '" << func.name() << "'>";
            return o.str();
        })
    ;

    // define_func_gpu_methods(func_class);
}

}  // namespace PythonBindings
}  // namespace Halide
