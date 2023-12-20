# Setting up a PBNI Extension
---
## Prerequisites
Firstly you need to install [Visual Studio](https://visualstudio.microsoft.com/downloads/), [cmake](https://cmake.org/install/) and [vcpkg](https://vcpkg.io/en/getting-started.html).

## Extension Template
It is easiest to use this github [template](https://github.com/informaticon/div.cpp.base.pbni-extension-template).
After creating the new repo follow the steps in the Readme to finish setting it up.


## Building
To build the CMakeProject, open a terminal and run this command:
```ps
cmake . -B build --preset vcpkg
```
It creates a new folder called `build/` and creates a Visual Studio Solution inside it. You can open it and and edit your code inside Visual Studio. There you have multiple targets, when you build your library, it will create an `out/{Build_Configuration}` folder in your project, in there you will find the `.dll`s.

While developing its recommended to use the `Debug` Configuration, this way it won't optimize the code and thus compile faster, it will also add Stacktraces to PBNI Exceptions. When Releasing you should use `MinSizeRel`, this will optimize code and shrink File size but Exceptions wont have stacktraces, you also won't be able to use Breakpoints.

If you build `INSTALL` instead, it will build your library and then copy the `.dll` to the `A3_LIB_PATH` you specified.

## Importing
To add the DLL to PowerBuilder, right click on a Library and choose `Import PB Extension`. The DLL you choose has to be inside the current working Directory of the PowerBuilder Application, which for most cases means the `lib/` Folder.

## Creating new Source Files
New files should be creates in the `src/` directory only, this means that you shouldn't create new Files in Visual Studio, since those would be created inside the build directory.
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


## Development
You shouldn't run the Install target if the PowerBuilder Application is currently running (Not the Editor), Since you will get weird Errors telling you that you don't have Permissions to overwrite the DLL.

### Visual Studio
#### Debugging
During development you can build with the Debug target, this will allow you to set Breakpoints in Visual Studio.
To attach to PowerBuilder, open the PB Workspace and then inside Visual Studio go to `Debug > Attach to Process... (Ctrl+Alt+P)` and choose the PBXXX.exe process you want (XXX being the PowerBuilder version).

### VSCode
If you prefer VSCode over Visual Studio, you can do that. To make it work nicely with AutoCompletion and building you need these extensions:
 - C/C++ Extension Pack

Even when using VSCode you still need to install Visual Studio to get the build environment.

*These files already exist in the Extension Template:*

#### Building
And a `CMakePresets.json` file:
```json
{
    "version": 6,
    "configurePresets": [
        {
            "name": "vcpkg",
            "architecture": "Win32",
            "toolchainFile": "C:/vcpkg/scripts/buildsystems/vcpkg.cmake",
            "cacheVariables": {
                "CMAKE_GENERATOR_PLATFORM": "Win32", // Need both this and architecture, because some bug
                "VCPKG_TARGET_TRIPLET": "x86-windows-static"
            }
        }
    ],
    "buildPresets": [
        {
            "name": "Debug",
            "configurePreset": "vcpkg",
            "configuration": "Debug",
            "targets": [ "install", "<Name of your CMake library>" ]
        },
        {
            "name": "MinSizeRel",
            "configurePreset": "vcpkg",
            "configuration": "MinSizeRel",
            "targets": [ "install", "<Name of your CMake library>" ]
        }
    ]
}
```

You'll need to change the targets of the buildPresets to the name you gave your library in `CMakeLists.txt`.
Then go to the CMake tab and choose the Preset and buildPreset, or just run `> CMake: Configure`. You can now run `> Cmake: Build` to build or install the DLL.

#### Autocomplete
You need a `.vscode/c_cpp_properties.json` file:
```json
{
    "configurations": [
        {
            "name": "Win32",
            "defines": [
                "VSCODE" // Because the VSCode C++ extension can't handle __VA_OPT__(,), we had to add a special case
            ],
            "configurationProvider": "ms-vscode.cmake-tools"
        }
    ],
    "version": 4
}
```

#### Debugging
Create `.vscode/launch.json`:
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(Windows) Attach",
            "type": "cppvsdbg",
            "request": "attach",
        }
    ]
}
```
Now when you hit F5, it will ask you which process to attach to, choose the PBXXX.exe process that you want.