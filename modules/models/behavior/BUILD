cc_library(
    name = "behavior",
    hdrs = [
        "behavior_model.hpp",
    ],
    deps = [
        "//modules/commons:commons",
        "//modules/models/dynamic:dynamic"
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name="include",
    hdrs= ["behavior_model.hpp"],
    deps = [
        "//modules/models/behavior/constant_velocity:include",
        "//modules/models/behavior/dynamic_model:include",
        "//modules/models/behavior/idm:include",
        "//modules/models/behavior/longitudinal_acceleration:include",
        "//modules/models/behavior/motion_primitives:include",
    ],
    visibility = ["//visibility:public"],
)

#cpplint()
