cc_library(
    name = "otera_lib",
    srcs = glob(["otera/**/*.cc"]),
    hdrs = glob(["otera/**/*.h"]),
)

cc_test(
    name = "otera_test",
    srcs = glob(["test/*.cc"]),
    data = glob(["test/data/**"]),
    deps = [
        ":otera_lib",
        "@gtest//:gtest_main",
    ],
)

cc_binary(
    name = "otera",
    srcs = ["main.cc"],
    deps = [":otera_lib"],
)
