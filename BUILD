cc_library(
    name = "otera_lib",
    srcs = glob(["srcs/*.cc"]),
    hdrs = glob(["srcs/*.h"]),
)

cc_test(
    name = "otera_test",
    srcs = glob(["test/*.cc"]),
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
