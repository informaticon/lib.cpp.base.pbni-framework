# External Libraries
---

## Using VCPKG

The PBNI Framework uses VCPKG as its package manager, so the simplest way to add external libraries, is to just install some library using
```ps
vcpkg install --triplet=x86-windows-static library-name
```
The x86-windows-static triplet is used so that the external library is directly built into the final dll, this way we don't have to provide additional dlls.
After installing, vcpkg should tell you the package name, this will be in the CMake File.

After installing the package, you need to add it to the `CMakeLists.txt` file. To do this, go to the very bottom of the file, where you should see a `target_link_libraries` option. Before that open, import the package using `find_package`, and then add the packages name to the `target_link_library` option. Heres an example of how to add Pocos JSON Parser. 
```cmake
find_package(Poco REQUIRED JSON)

add_subdirectory(extern)

target_link_libraries(libMailClient
PRIVATE
	libPBNIFramework
	Poco::JSON
)
```


## Local Libraries

If you want to add a local library, you need 2 things, a static `.lib` file. and an `include/` folder. If you are not sure which ones you need, ask Simon Reichenbach or Micha Wehrli.

Once you've gathered your required files. Create a Subfolder in the `extern/` folder and setup your folders like so:
```
├── extern/
│   ├── lib.cpp.base.pbni-framework/
│   │   └── ...
│   ├── your.library.name/
│   │   ├── lib/
│   │   │   └── your-library.lib
│   │   ├── include/
│   │   │   ├──  some_header.h
│   │   │   └──  another_header.h
│   │   └── CMakeLists.txt
│   └── CMakeLists.txt
├── ...
└── CMakeLists.txt
```
Put your `.lib` file into the lib/ subfolder and the contents of your `include/` folder into the `include/` subfolder. Then Create the `CMakeLists.txt` file on the same level as the `lib/` and `include/` folders. Inside it add:
```cmake
# extern/your.library.name/CMakeLists.txt
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)


##################################################
#                    libYours                    #
##################################################

add_library(libYours STATIC IMPORTED GLOBAL)

set_target_properties(libYours
PROPERTIES
	IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/your-library.lib
)

target_include_directories(libYours
INTERFACE
	include
)
```
You should replace the `libYours` with a suitable name and put the correct `.lib` file name.

Then on the CMakeLists of the extern folder add the line:
```cmake
# extern/CMakeLists.txt
add_subdirectory(your.library.name)
```

And finally in the topmost CMakeLists.txt, add your library to the  `target_link_libraries` option:
```cmake
# CMakeLists.txt

...

target_link_libraries(libMailClient
PRIVATE
	libPBNIFramework
    libYours
)
```