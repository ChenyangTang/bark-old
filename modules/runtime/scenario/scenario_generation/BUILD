py_library(
    name = "scenario_generation",
    srcs = ["scenario_generation.py",
            "uniform_vehicle_distribution.py",
            "model_json_conversion.py",
            "deterministic.py"],
    data = ['//python:bark.so'],
    imports = ['../../../python'],
    deps = ["//modules/runtime/scenario:scenario",],
    visibility = ["//visibility:public"],
)