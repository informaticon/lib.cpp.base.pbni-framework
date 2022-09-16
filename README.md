# lib.cpp.base.pbni-framework
Framework for creating PowerBuilder Extensions using PBNI.

## Dependencies
 - PowerBuilder PBNI
 - Boost (submodules)

## Example Usage
Check out [this repository](https://github.com/informaticon/div.cpp.base.pbni-framework-usage-example) for a documented example. Or [this one](https://github.com/informaticon/lib.pbni.base.tse) for an actual usage. 


## MKDocs
This repository uses MKDocs for documentation. To view it, you need to have python3 installed and `pip install mkdocs` then run `mkdocs serve`, it will create a Web documentation on `localhost:8000`. Alternatively you can open docs/index.md in your browser.

To build Doxygen you need to have [Doxygen](https://www.doxygen.nl) and [Doxybook2](https://github.com/matusnovak/doxybook2) installed, then run `make` and afterwards `make serve`.

If you want regenerate the documentation for Github, you have to run `make doxybook-git` before committing.
