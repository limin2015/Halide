#include "PyFunc.h"

#include "PyBinaryOperators.h"
#include "PyBuffer.h"
#include "PyExpr.h"
#include "PyFunc_Ref.h"
#include "PyFunc_VarOrRVar.h"
#include "PyFunc_gpu.h"
#include "PyScheduleMethods.h"
#include "PyStage.h"

namespace Halide {
namespace PythonBindings {

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
    define_var_or_rvar(m);

    // TODO: move to its own file
    // TODO: incomplete
    auto looplevel_class = py::class_<LoopLevel>(m, "LoopLevel")
        .def(py::init<>())
        .def("inlined", &LoopLevel::inlined)
        .def("root", &LoopLevel::root)
    ;

    auto func_class = py::class_<Func>(m, "Func")
        .def(py::init<>())
        .def(py::init<std::string>())
        .def(py::init<Expr>())
        // TODO: this overload shouldn't be necessary, but for reasons that
        // aren't clear, PyBind isn't doing the implicit Buffer -> Realization
        // conversion here, and is choosing the std::vector<int> variant, which
        // crashes. Adding an explicit overload for Buffer<> heals it.
        .def("realize", [](Func &f, Buffer<> b, const Target &t) -> void {
            f.realize(Realization(b), t);
        }, py::arg("dst"), py::arg("target") = Target())
        .def("realize", [](Func &f, std::vector<Buffer<>> b, const Target &t) -> void {
            f.realize(Realization(b), t);
        }, py::arg("dst"), py::arg("target") = Target())
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

        // TODO: is there a way to avoid the combinations?
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
        .def("__setitem__", [](Func &func, const Expr &lhs, const Expr &rhs) -> Stage {
            return func(lhs) = rhs;
        })
        .def("__setitem__", [](Func &func, const std::vector<Expr> &lhs, const Expr &rhs) -> Stage {
            return func(lhs) = rhs;
        })
        .def("__setitem__", [](Func &func, const Expr &lhs, const std::vector<Expr> &rhs) -> Stage {
            return func(lhs) = Tuple(rhs);
        })
        .def("__setitem__", [](Func &func, const std::vector<Expr> &lhs, const std::vector<Expr> &rhs) -> Stage {
            return func(lhs) = Tuple(rhs);
        })

        .def("bound", &Func::bound)

        .def("reorder_storage", (Func &(Func::*)(const std::vector<Var> &)) &Func::reorder_storage, py::arg("dims"))
        .def("reorder_storage", [](Func &func, py::args args) -> Func & {
            std::vector<Var> dims;
            dims.reserve(args.size());
            for (auto &a : args) {
                dims.push_back(a.cast<Var>());
            }
            return func.reorder_storage(dims);
        })

        .def("compute_at", (Func &(Func::*)(Func, Var)) &Func::compute_at)
        .def("compute_at", (Func &(Func::*)(Func, RVar)) &Func::compute_at)
        .def("compute_at", (Func &(Func::*)(LoopLevel)) &Func::compute_at)

        .def("compute_root", &Func::compute_root)

        .def("compile_to_bitcode",
            (void (Func::*)(const std::string &, const std::vector<Argument> &, const std::string &, const Target &target)) &Func::compile_to_bitcode,
            py::arg("filename"), py::arg("arguments"), py::arg("fn_name"), py::arg("target") = get_target_from_environment())
        .def("compile_to_bitcode",
            (void (Func::*)(const std::string &, const std::vector<Argument> &, const Target &target)) &Func::compile_to_bitcode,
            py::arg("filename"), py::arg("arguments"), py::arg("target") = get_target_from_environment())

        .def("compile_to_llvm_assembly",
            (void (Func::*)(const std::string &, const std::vector<Argument> &, const std::string &, const Target &target)) &Func::compile_to_llvm_assembly,
            py::arg("filename"), py::arg("arguments"), py::arg("fn_name"), py::arg("target") = get_target_from_environment())
        .def("compile_to_llvm_assembly",
            (void (Func::*)(const std::string &, const std::vector<Argument> &, const Target &target)) &Func::compile_to_llvm_assembly,
            py::arg("filename"), py::arg("arguments"), py::arg("target") = get_target_from_environment())

        .def("compile_to_object",
            (void (Func::*)(const std::string &, const std::vector<Argument> &, const std::string &, const Target &target)) &Func::compile_to_object,
            py::arg("filename"), py::arg("arguments"), py::arg("fn_name"), py::arg("target") = get_target_from_environment())
        .def("compile_to_object",
            (void (Func::*)(const std::string &, const std::vector<Argument> &, const Target &target)) &Func::compile_to_object,
            py::arg("filename"), py::arg("arguments"), py::arg("target") = get_target_from_environment())

        .def("compile_to_header", &Func::compile_to_header,
            py::arg("filename"), py::arg("arguments"), py::arg("fn_name") = "", py::arg("target") = get_target_from_environment())

        .def("compile_to_assembly",
            (void (Func::*)(const std::string &, const std::vector<Argument> &, const std::string &, const Target &target)) &Func::compile_to_assembly,
            py::arg("filename"), py::arg("arguments"), py::arg("fn_name"), py::arg("target") = get_target_from_environment())
        .def("compile_to_assembly",
            (void (Func::*)(const std::string &, const std::vector<Argument> &, const Target &target)) &Func::compile_to_assembly,
            py::arg("filename"), py::arg("arguments"), py::arg("target") = get_target_from_environment())

        .def("compile_to_c", &Func::compile_to_c,
            py::arg("filename"), py::arg("arguments"), py::arg("fn_name") = "", py::arg("target") = get_target_from_environment())

        .def("compile_to_lowered_stmt", &Func::compile_to_lowered_stmt,
            py::arg("filename"), py::arg("arguments"), py::arg("fmt") = Text, py::arg("target") = get_target_from_environment())

        .def("compile_to_file", &Func::compile_to_file,
            py::arg("filename_prefix"), py::arg("arguments"), py::arg("fn_name") = "", py::arg("target") = get_target_from_environment())

        .def("compile_to_static_library", &Func::compile_to_static_library,
            py::arg("filename_prefix"), py::arg("arguments"), py::arg("fn_name") = "", py::arg("target") = get_target_from_environment())

        .def("compile_to_multitarget_static_library", &Func::compile_to_multitarget_static_library,
            py::arg("filename_prefix"), py::arg("arguments"), py::arg("targets"))

        .def("compile_to_module", &Func::compile_to_module,
            py::arg("arguments"), py::arg("fn_name") = "", py::arg("target") = get_target_from_environment())

        .def("compile_jit", &Func::compile_jit, py::arg("target") = get_jit_target_from_environment())

        .def("update", &Func::update, py::arg("idx") = 0)

        .def("trace_stores", &Func::trace_stores)
        .def("trace_realizations", &Func::trace_realizations)
        .def("print_loop_nest", &Func::print_loop_nest)

        .def("__repr__", [](const Func &func) -> std::string {
            std::ostringstream o;
            o << "<halide.Func '" << func.name() << "'>";
            return o.str();
        })
    ;

    add_schedule_methods(func_class);

    define_stage(m);
    // define_func_gpu_methods(func_class);
}

}  // namespace PythonBindings
}  // namespace Halide
