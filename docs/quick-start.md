# Setting up a PBNI Extension
---
## Prerequisites
Firstly you need to install [Visual Studio](https://visualstudio.microsoft.com/downloads/), [cmake](https://cmake.org/install/) and [vcpkg](https://vcpkg.io/en/getting-started.html).\
Then install the packages needed for the PBNI Framework:
```ps1
vcpkg install --triplet=x86-windows-static boost-stacktrace boost-utility boost-multiprecision
```

## Example Extension
It is easiest to just modify the example extension found [here](https://github.com/informaticon/div.cpp.base.pbni-framework-usage-example). 

## CMake
Inside the main CMakeLists.txt file, change the name of the library `libUsageExample` using a find and replace. You can also change the `OUTPUT_NAME` option, this will change the name the `.dll` will be given. Finally, it's recommended to change the `A3_LIB_PATH` option to the folder where the extension will be used.

## Building
To build the CMakeProject, open a terminal and run this command:
```ps
mkdir build; cd build

cmake .. -A Win32 `
         -DVCPKG_TARGET_TRIPLET=x86-windows-static `
         -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
```
It creates a new folder called `build/` and creates a Visual Studio Solution inside it. You can open it and and edit your code inside Visual Studio. There you have multiple targets, when you build your library, it will create an `out/{Build_Configuration}` folder in your project, in there you will find the `.dll`s.

While developing its recommended to use the `Debug` Configuration, this way it wont optimize the code and thus compile faster. When Releasing you should use `RelWithDebInfo`, this will optimize code and shrink Filesize but still keep the Debugging Information needed by boost Starcktrace to create verbose Exceptions.

If you build `INSTALL` instead, it will build your library and then copy the `.dll` to the `A3_LIB_PATH` you specified.


## Creating new Source Files
New files should be creates in the `src/` directory only, this means that you shouldn't create new Files in Visual Studio, since those would be creted inside the build directory.
Once you've created the Source File, edit the main CMakeLists.txt file by adding the file in the `add_library` option, you can also add it into a `source_group`, Source Groups are the Folders in Visual Studio.
```cmake
add_library(libUsageExample SHARED
	src/example.h
	src/example.cpp
	src/another_file.h
)

source_group("Source Files"
FILES
	src/example.h
	src/example.cpp
	src/another_file.h
)
```
After you've edited the CMake file, go back to Visual Studio and build `ZERO_CHECK`, that should reread the CMake file and add the newly created Source Files to the project.

## C++
For every User Object you want to add to PowerBuilder, create a .cpp file and a .h file.

#### Header
Inside the header file, create your Class and extend Inf::PBNI_Class `<Framework.h>`. You need to create a constructor and forward all arguments to PBNI_Class. Then you can add all your Method Declarations. The Argument and Return Types of your Methods should all be `Inf::PB<type>` or `void`.

```cpp
// MyExtensionClass.h
#include <ClassDescription.h>

class MyExtensionClass : public Inf::PBNI_Class
{
	// Put your methods here
	void Example(Inf::PBInt some_number);
}
```

#### Source
Inside the Source File call `INF_REGISTER_CLASS` once. Then define your Methods and register each using `INF_REGISTER_FUNC`.
```cpp
// MyExtensionClass.cpp
#include "your_pbni_class.h"
#include <WinUser.h>
#include <ClassDescription.h>

// This will be the Name of the PowerBuilder user object.
INF_REGISTER_CLASS(MyExtensionClass, L"u_my_extension_class");

// The second argument is the name used by PowerBuilder, after the 2nd argument, the argument names follow.
INF_REGISTER_FUNC(Example, L"of_example", L"ai_some_number");
void MyExtensionClass::Example(Inf::PBInt some_number)
{
	MessageBoxW(NULL, L"This is an example", L"Message", MB_OK);
}

```

Make sure to never use the `INF_REGISTER_[...]` functions inside a Header File, this way the header file could be included into multiple Source Files and gets run multiple times.  
Also make sure to register the Class before you register the Methods.

