# lib.cpp.base.pbni-framework
Framework for creating PowerBuilder Extensions using PBNI.

## Dependencies
 - PowerBuilder PBNI
 - Boost (submodules)

## Example Usage
Check out [this repository](https://github.com/informaticon/div.cpp.base.pbni-framework-usage-example) for a documented example. Or [this one](https://github.com/informaticon/lib.pbni.base.tse) for an actual usage. 


## Documentation
This repository uses Doxygen and MKDocs for documentation.
You may need to have the following software to build/view the documentation:
* [Doxygen](https://www.doxygen.nl)
* [Doxybook2](https://github.com/matusnovak/doxybook2)
* [MkDocs](https://www.mkdocs.org/) (install it with `pip install mkdocs`)

To generate and view the documentation locally, run `make` and `make serve`.
This will create a Web documentation on `localhost:8000`. Alternatively you can open docs/index.md in your browser.

If you want regenerate the documentation for Github, you have to run `make` and `make doxybook-git` before committing.
