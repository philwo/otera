# otera

Otera is a simple templating engine written in C++14 as part of a programming exercise.

It does not require any third-party libraries, except [googletest](https://github.com/google/googletest) for its
test suite.

It was not security-reviewed and I didn't have time to check for memory issues with ASAN or a fuzzer yet, so please don't use it for production.

## What can Otera do?

- Otera is designed as a reusable C++ library.
- Otera is testable and even comes with a few tests. The full test suite hasn't been written yet, though.
- Otera processes data from an input stream, reacts to commands embedded in the stream and writes the output to an output stream.
- Supported commands are `print`, `foreach` and `if`:
  - print: `Hello {{ parameter }}!`
  - foreach: `{% foreach fruit in fruits %} {{ fruit }} {% end %}`
  - if: `{% if count > 3 %}Wow, you have more than 3 fruits!{% end %}`
- Commands can be arbitrarily nested.
- Print nice error messages for most syntax errors including line and column numbers.

## How to use Otera in your project

Otera uses Bazel as its build system. You can build Otera and run its test suite like this:

```
git clone https://github.com/philwo/otera.git
cd otera
bazel test //...
```

If you want to use Otera in your own project as a library, you can add it to your WORKSPACE file like this:

```
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "otera",
    sha256 = "3d940650a26df1e6cab47d8d58cd55335cefc76434798f583da9ccd329c883e8",
    strip_prefix = "otera-ed7861c585cfd8643a316a2b1b1e146cf34dc6fd",
    url = "https://github.com/philwo/otera/archive/ed7861c585cfd8643a316a2b1b1e146cf34dc6fd.zip",
)
```

Then depend on it like this in your BUILD file:

```
cc_binary(
    name = "mytool",
    srcs = ["mytool.cc"],
    deps = [
        "@otera//:otera_lib",
    ],
)
```

### API reference

Otera has a pretty simple API:
- Templates are rendered by the `otera::Template` class.
- Parameters are looked up in an `otera::Environment`.
- The value of parameters is managed by a wrapper class: `otera::Value`.

You can check the included [tests](https://github.com/philwo/otera/tree/master/test) for
usage examples, but here's a quick example:

- Write your template, e.g. to a file:

```
First line.

{{ header }}

This is a list of items:
{% foreach item in somearray %}
{% if item != "Citrus" %}
- {{ item }}
{% end %}
{% end %}

{% if 3 == 3 %}
Yes, 3 == 3.
{% end %}

{{ footer }}

Last line.
```

- Render the template:

```C++
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "otera/Otera.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << argv[0] << " <input.txt>" << std::endl;
        return 1;
    }

    // Load our template from a file.
    std::unique_ptr<std::ifstream> input_file = std::make_unique<std::ifstream>(argv[1]);

    if (input_file->fail()) {
        std::cerr << "Could not open input file." << std::endl;
        return 1;
    }

    // Create an environment that holds our parameters.
    otera::Environment env;
    env.SetParameter("header", otera::Value("Hello world!"));
    env.SetParameter("somearray", otera::Value(
            std::vector<otera::Value>{otera::Value("Apple"), otera::Value("Banana"), otera::Value("Citrus")}));
    env.SetParameter("footer", otera::Value("That's it!"));

    // Load, parse and render the template into an output stream.
    std::stringstream result;
    otera::Template otmpl(std::move(input_file));
    try {
        otmpl.Render(env, result);
    } catch (const std::invalid_argument &e) {
        std::cerr << "Error while parsing template:" << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Print the output.
    std::cout << result.str();

    return 0;
}
```

## Technical notes

### What does "Otera" mean?
Otera (お寺) means "temple" in Japanese.
It's just a play on words, because the other popular templating engine that I like to use is called Jinja2 (which means "shrine"). ;)

### How does Otera parse the template?
Otera uses a simple character based parser that goes through the input stream in one linear iteration and builds an AST on the fly.

The AST is made up of objects that inherit from the base class `Expression`. The currently implemented ones are:
- ProgramExpression, which represents the root of the tree. Other expressions are attached to its list of children.
- ConstantExpression, which represents just a constant string that will be printed as is.
- PrintParameterExpression, which represents the `{{ variable_name }}` command.
- ForEachExpression and IfExpression, which respectively represent the `{% foreach item in container %}` and the `{% if A != B %}` commands.

In order to implement command nesting, the parser uses an `std::stack` to keep track of the current depth of the command graph.
It knows that "foreach" and "if" represent nodes that can hold their own children, while constant expressions and print commands do not.
This results in a transformation from an input template like this:

```
Hello World.

{{ header }}

This is a list of items:
{% foreach item in somearray %}
{% if item != "Citrus" %}
- {{ item }}
{% end %}
{% end %}

Last line.
```

to an AST like this:

```
ProgramExpression
\- ConstantExpression: "Hello World.\n\n"
\- PrintParameterExpression: header
\- ConstantExpression: "\n\nThis is a list of items:\n"
\- ForEachExpression: item in somearray
   \- IfExpression: item != "Citrus"
      \- ConstantExpression: "- "
      \- PrintParameterExpression: item
      \- ConstantExpression: "\n"
\- ConstantExpression: "\nLast line.\n"
```
