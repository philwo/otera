# otera

Otera is a simple templating engine written in C++ as part of a programming exercise.

## Requirements

- Otera should be designed as a reusable C++ library.
- Otera should be testable and ideally come with a test suite.
- Otera should process data from an input stream, react to commands embedded in the stream and write the output to an output stream.
- Supported commands are `print`, `foreach` and `if`.
- Command arguments can be variables. Variables can come from:
  - a set of input variables given to the template engine
  - the `foreach` command

## Notes during development

https://docs.bazel.build/versions/master/bazel-and-cpp.html
https://docs.bazel.build/versions/master/cpp-use-cases.html
- Upgrade GoogleTest to 1.8.1.
