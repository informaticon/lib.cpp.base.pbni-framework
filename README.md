# lib.cpp.base.pbni-framework
Framework for creating PowerBuilder Extensions using PBNI.

## Dependencies
 - PowerBuilder PBNI Library
 - vcpkg (to use Boost)

## Vcpkg dependencies
```ps1
vcpkg install --triplet=x86-windows-static `
	boost-stacktrace `
	boost-utility `
	boost-multiprecision `
	boost-algorithm
```

## Usage
If you are creating a new Project, use the [template](https://github.com/informaticon/div.cpp.base.pbni-extension-template)

To check how you create Classes and export Functions, check out one of the Repos currently using the PBNI Framework:
 - [lib.pbni.base.tse](https://github.com/informaticon/lib.pbni.base.tse)
 - [lib.pbni.base.string-utils](https://github.com/informaticon/lib.pbni.base.string-utils)
 - [lib.pbni.base.pepper](https://github.com/informaticon/lib.pbni.base.pepper)
 - [lib.pbni.base.mail-client](https://github.com/informaticon/lib.pbni.base.mail-client)
 - [lib.pbni.base.libcurl](https://github.com/informaticon/lib.pbni.base.libcurl)
 - [lib.pbni.base.serializer](https://github.com/informaticon/lib.pbni.base.serializer)
 - [lib.pbni.base.graphics-utils](https://github.com/informaticon/lib.pbni.base.graphics-utils)


## Documentation
The docs are also on [Slab](https://slab.informaticon.com/posts/lib-cpp-base-pbni-framework-viyzp8mr)

This repository uses Doxygen and MKDocs for documentation.
You may need to have the following software to build/view the documentation:
* [Doxygen](https://www.doxygen.nl) (on Windows: `choco install doxygen`)
* [Doxybook2](https://github.com/matusnovak/doxybook2) (on Windows: `choco install doxybook2`)
* [MkDocs](https://www.mkdocs.org/) (install it with `pip install mkdocs`)
* On Windows you have to manually install make (`choco install make`)

To generate and view the documentation locally, run `make` and `make serve`.
This will create and open a Web documentation on `localhost:8000`. Alternatively you can open docs/index.md in your browser.

If you want regenerate the documentation for Github, you have to run `make doxygen` and `make doxybook-git` before committing.


## Tests
Build the test dll by running
```ps1
cmake -S .\test\cpp\ -B .\test\cpp\build --preset vcpkg
cmake --build .\test\cpp\build --target install
```

Run tests by doing
```ps1
make -C test/pb tests
```
