# lib.cpp.base.pbni-framework
Framework for creating PowerBuilder Extensions using PBNI

## TODO
- Errors in powerbuilder

## Dependencies
Boost *(For decimals, Strong typedef)*\
PowerBuilder

## How to
Either add this repository as a submodule in your own repository, or just add it as a subfolder somewhere in your cmake source folder. \
You should already have a complete Cmake file which takes your source files and compiles them to a dll. \

Before you create your target add these:
```cmake
set(CMAKE_CXX_STANDARD 20)
# To be able to use __VA_OPT__
add_compile_options("/Zc:preprocessor")
```

After your cmake target add these lines:
```cmake
# For includes and linkages
set(PBNI_DIR "C:/Program Files (x86)/Appeon/PowerBuilder 17.0/SDK/PBNI" CACHE PATH "PATH of PowerBuilder Native Interface SDK")
set(PBNI_INCLUDE_DIR "${PBNI_DIR}/include" CACHE PATH "PowerBuilder Native Interface header files location")
set(PBNI_LIBRARY "${PBNI_DIR}/lib/pbni.lib" CACHE FILEPATH "PowerBuilder Native Interface library for release target")

set(BOOST_INCLUDE_DIR "C:/Program Files/boost/boost_1_79_0" CACHE PATH "Header files for boost library")

# For source file compiling
set(PBNI_TARGET <Name of your CMAKE Target>)
set(SUBFOLDER "lib.cpp.base.pbni-framework")
include("${SUBFOLDER}/lib.cpp.base.pbni-framework.cmake")
```

### Code
If you want to create a PBNI class, include lib.cpp.base.pbni-framework/Framework.h. Then make a class and publicly extend Inf::PBNI_Class, you need to implement the method GetPBName like so:
```cpp
	inline std::wstring GetPBName() override { return L"u_pbni_ex; }
```
This will be the name of your class on powerbuilders side.\
Then define all your functions. Inside a .cpp file include lib.cpp.base.pbni-framework/ClassDescription.h and use INF_REGISTER_CLASS, and INF_REGISTER_FUNC to register all your func, to see how to do it exactly look at the example.\
\
You don't need to add any DLL or PBNI related things. That is all handled by lib.cpp.base.pbni-framework/dllmain.cpp.

### Example
Check out [this](https://github.com/informaticon/div.cpp.miw.pbni-framework-example) repository to see how it can be done.
