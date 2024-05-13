# Informaticon PBNI Framework
Libraries for creating PowerBuilder Extensions using PowerBuilder Native Interface (PBNI).

> [!IMPORTANT]
> Only tested for PowerBuilder x86 builds.

## Runtime dependencies
 - [Informaticon Exception Framework](https://github.com/informaticon/lib.pb.base.exception-framework)
 - Microsoft Visual C++

## Usage
If you are creating a new project, you can use this [template repository](https://github.com/informaticon/div.cpp.base.pbni-extension-template).
You can find some (partially outdated) examples over [there](https://github.com/informaticon/div.cpp.base.pbni-framework-usage-example).

To check how to create classes and export functions, you can also check out one of these repositories (only available to Informaticon employees):
 - [lib.pbni.base.tse](https://github.com/informaticon/lib.pbni.base.tse)
 - [lib.pbni.base.string-utils](https://github.com/informaticon/lib.pbni.base.string-utils)
 - [lib.pbni.base.pepper](https://github.com/informaticon/lib.pbni.base.pepper)
 - [lib.pbni.base.mail-client](https://github.com/informaticon/lib.pbni.base.mail-client)
 - [lib.pbni.base.libcurl](https://github.com/informaticon/lib.pbni.base.libcurl)
 - [lib.pbni.base.serializer](https://github.com/informaticon/lib.pbni.base.serializer)
 - [lib.pbni.base.graphics-utils](https://github.com/informaticon/lib.pbni.base.graphics-utils)

## Documentation
This repository uses Doxygen and MKDocs for documentation.
You may need to have the following software to build/view the documentation:
* [Doxygen](https://www.doxygen.nl) (on Windows: `choco install doxygen`)
* [Doxybook2](https://github.com/matusnovak/doxybook2) (on Windows: `choco install doxybook2`)
* [MkDocs](https://www.mkdocs.org/) (install it with `pip install mkdocs`)
* On Windows you have to manually install make (`choco install make`)

To generate and view the documentation locally, run `make` and `make serve`.
This will create and open a Web documentation on `localhost:8000`.

> [!TIP]
> You can also check out the pre-compiled documentation on Github instead:
> https://github.com/informaticon/lib.cpp.base.pbni-framework/blob/main/docs/index.md.

If you want regenerate the documentation for Github, you have to run `make doxygen` and `make doxybook-git` before committing.

## How to build
This is a cpp library, you only have to build it for testing purposes, otherwise you use it in your C++ project (see PBNI Template).

### Requirements

- PowerBuilder PBNI Library
- CMake ([direct download](https://cmake.org/download/) or via [choco](https://community.chocolatey.org/packages/cmake))
- * Microsoft Visual C++ Build Tools (e.g. from [MS Visual Studio 2022 Community Edition](https://visualstudio.microsoft.com/de/vs/community/))
- vcpkg (to get these libraries):
  - boost-stacktrace
  - boost-utility
  - boost-multiprecision
  - boost-algorithm

```ps1
vcpkg install --triplet=x86-windows-static `
	boost-stacktrace `
	boost-utility `
	boost-multiprecision `
	boost-algorithm
```

### Tests
Build the test dll by running
```ps1
cmake -S .\test\cpp\ -B .\test\cpp\build --preset vcpkg
cmake --build .\test\cpp\build --target install
```

Run tests by doing
```ps1
make -C test/pb tests
```

## How to contribute
Please read [CONTRIBUTING.md](CONTRIBUTING.md) before sending a pull request.
