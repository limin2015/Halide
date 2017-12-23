#include "PyFunc_Stage.h"

#include "PyFunc.h"
#include "PyFunc_gpu.h"

namespace Halide {
namespace PythonBindings {

void define_stage(py::module &m) {
    // only defined so that boost::python knows about these classes,
    // not (yet) meant to be created or manipulated by the user
    auto stage_class =
        py::class_<Stage>(m, "Stage")
    ;
    //         .def("dump_argument_list", &Stage::dump_argument_list, ,
    //              "Return a string describing the current var list taking into "
    //              "account all the splits, reorders, and tiles.")
    //         .def("name", &Stage::name, ,
    //              "Return the name of this stage, e.g. \"f.update(2)\"")
    //         .def("allow_race_conditions", &Stage::allow_race_conditions, ,
    //              py::return_internal_reference<1>());

    // // Scheduling calls that control how the domain of this stage is traversed.
    // // "See the documentation for Func for the meanings."

    // stage_class
    //     .def("split", &func_split<Stage>, py::args("old", "outer", "inner", "factor"),
    //          py::return_internal_reference<1>(),
    //          "Split a dimension into inner and outer subdimensions with the "
    //          "given names, where the inner dimension iterates from 0 to "
    //          "factor-1. The inner and outer subdimensions can then be dealt "
    //          "with using the other scheduling calls. It's ok to reuse the old "
    //          "variable name as either the inner or outer variable.")
    //     .def("fuse", &Stage::fuse, py::args("inner", "outer", "fused"),
    //          py::return_internal_reference<1>(),
    //          "Join two dimensions into a single fused dimenion. The fused "
    //          "dimension covers the product of the extents of the inner and "
    //          "outer dimensions given.")
    //     .def("serial", &Stage::serial, py::args("var"),
    //          py::return_internal_reference<1>(),
    //          "Mark a dimension to be traversed serially. This is the default.");

    // stage_class.def("parallel", &func_parallel0<Stage>, py::args("var"),
    //                 py::return_internal_reference<1>(),
    //                 "Mark a dimension (Var instance) to be traversed in parallel.")
    //     .def("parallel", &func_parallel1<Stage>, py::args("var", "factor"),
    //          py::return_internal_reference<1>());

    // stage_class.def("vectorize", &func_vectorize1<Stage>, py::args("var", "factor"),
    //                 py::return_internal_reference<1>(),
    //                 "Split a dimension (Var instance) by the given int factor, then vectorize the "
    //                 "inner dimension. This is how you vectorize a loop of unknown "
    //                 "size. The variable to be vectorized should be the innermost "
    //                 "one. After this call, var refers to the outer dimension of the "
    //                 "split.")
    //     .def("vectorize", &func_vectorize0<Stage>, py::args("var"),
    //          py::return_internal_reference<1>());

    // stage_class.def("unroll", &func_unroll1<Stage>, py::args("var", "factor"),
    //                 py::return_internal_reference<1>(),
    //                 "Split a dimension by the given factor, then unroll the inner "
    //                 "dimension. This is how you unroll a loop of unknown size by "
    //                 "some constant factor. After this call, var refers to the outer "
    //                 "dimension of the split.")
    //     .def("unroll", &func_unroll0<Stage>, py::args("var"),
    //          py::return_internal_reference<1>());

    // stage_class.def("tile", &func_tile0<Stage>, py::args("x", "y", "xo", "yo", "xi", "yi", "xfactor", "yfactor"),
    //                 py::return_internal_reference<1>(),
    //                 "Split two dimensions at once by the given factors, and then "
    //                 "reorder the resulting dimensions to be xi, yi, xo, yo from "
    //                 "innermost outwards. This gives a tiled traversal.")
    //     .def("tile", &func_tile1<Stage>, py::args("x", "y", "xi", "yi", "xfactor", "yfactor"),
    //          py::return_internal_reference<1>(),
    //          "A shorter form of tile, which reuses the old variable names as the new outer dimensions");

    // stage_class.def("reorder", &func_reorder0<Stage, py::tuple>, py::args("vars"),
    //                 py::return_internal_reference<1>(),
    //                 "Reorder variables to have the given nesting order, "
    //                 "from innermost out")
    //     .def("reorder", &func_reorder0<Stage, py::list>, py::args("vars"),
    //          py::return_internal_reference<1>(),
    //          "Reorder variables to have the given nesting order, "
    //          "from innermost out")
    //     .def("reorder", &func_reorder1<Stage>, (py::arg("v0"), py::arg("v1") = py::object(),
    //                                             py::arg("v2") = py::object(), py::arg("v3") = py::object(),
    //                                             py::arg("v4") = py::object(), py::arg("v5") = py::object()),
    //          py::return_internal_reference<1>(),
    //          "Reorder variables to have the given nesting order, "
    //          "from innermost out");

    // stage_class.def("rename", &Stage::rename, py::args("old_name", "new_name"),
    //                 py::return_internal_reference<1>(),
    //                 "Rename a dimension. Equivalent to split with a inner size of one.");

    // stage_class.def("specialize", &Stage::specialize, py::args("condition"),
    //                 "Specialize a Func (Stage). This creates a special-case version of the "
    //                 "Func where the given condition is true. The most effective "
    //                 "conditions are those of the form param == value, and boolean "
    //                 "Params. See C++ documentation for more details.");

    // define_func_or_stage_gpu_methods<Stage>(stage_class);
}

}  // namespace PythonBindings
}  // namespace Halide
