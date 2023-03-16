# Setting up a PBNI Extension
---

## Example Extension
It is easiest to just modify the example extension found [here](https://github.com/informaticon/div.cpp.base.pbni-framework-usage-example). 

## CMake
If you have copied the Example Extension you can skip this step, you just need to rename the Library name inside `CMakeLists.txt`.

Otherwise add this Repository as a Subfolder in your CMake File (Either as a Git Submodule or in a global Folder). Then include/link the Target.

```cmake
add_subdirectory(path/to/this/repo)
target_link_libraries(my_target PRIVATE libPBNIFramework)
```

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
