# lib.cpp.base.pbni-framework
Framework for creating PowerBuilder Extensions using PBNI


## Dependencies
PowerBuilder PBNI

## How to
Either add this repository as a submodule in your own repository, or just add it as a subfolder somewhere in your cmake source folder. \
You should already have a complete Cmake file which takes your source files and compiles them to a dll. \

After your cmake target add these lines:
```cmake
add_subdirectory(path/to/this/repo)
target_link_libraries(your_target PRIVATE libPBNIFramework)
```

### Code
If you want to create a PBNI class and publicly extend Inf::PBNI_Class, you need to implement the method GetPBName.
```cpp
// your_pbni_class.h

#include <Framework.h>

class your_pbni_class : public Inf_::PBNI_Class
{
	// This will be the name of your class on powerbuilders side.
	inline std::wstring GetPBName() override { return L"u_your_pbni_class"; }

	// Put your methods somewhere here
	void example(Inf::PBInt some_number);
}
```

Then define all your functions. Inside a .cpp file use INF_REGISTER_CLASS, and INF_REGISTER_FUNC to register all your functions.
```cpp
// your_pbni_class.cpp

#include "your_pbni_class.h"

#include <WinUser.h>
#include <ClassDescription.h>

// This needs to be the same name you have in GetPBName
#INF_REGISTER_CLASS(your_pbni_class, L"u_your_pbni_class");

// The second argument is the name used by PowerBuilder, after the 2nd argument, the argument names come
#INF_REGISTER_FUNC(example, L"of_example", L"ai_some_number");
void your_pbni_class::example(Inf::PBInt some_number)
{
	MessageBoxW(NULL, L"This is an example", L"Message", MB_OK);
}

```
\
You don't need to add any PBNI entry points. Those are all handled by ``<PBEntry.cpp>``.


### Types
All types that are used are in the namespace Inf and start with PB. \
\
These are primitive types. They are copied over from PowerBuilder. \
If you perform a lot of operations, its better to copy them to a C++ datatype, because a null check happens everytime you do an operation.

 - Inf::PBByte
 - Inf::PBBoolean
 - Inf::PBChar
 - Inf::PBInt
 - Inf::PBUint
 - Inf::PBLong
 - Inf::PBUlong
 - Inf::PBLongLong
 - Inf::PBReal
 - Inf::PBDouble


Complex types dont get copied automatically, they are just wrappers, you can call Getters and Setters on them.

 - Inf::PBDecimal
 - Inf::PBTime
 - Inf::PBDate
 - Inf::PBDateTime
 - Inf::PBString
 - Inf::PBBlob
 - Inf::PBArray
 - Inf::PBObject

### Errors
You can call errors from inside C++ using throw. There is a PowerBuilder style exception called PBNI_Exception. It has a key value store and automatically creates a stacktrace using boost. Heres a list of exceptions that are thrown by the framework:

 - PBNI_IndexOutOfBounds
 - PBNI_NullPointerException
 - PBNI_InvalidFieldException
 - PBNI_IncorrectArgumentsException
 - PBNI_PowerBuilderException

You can create your own by extending PBNI_Exception.

### Variable handling
Complex PowerBuilder variables get deleted once the functino call ends. If you want to store a value into a member variable, you need to copy it over to your own memory. There are alternatives for some types. For PBObjects, you can use m_Session->AddGlobalRef(), just make sure to m_Session->RemoveGlobalRef(), once you are done using it. With PBArrays you can do m_Session->AcquireArrayItemValue() and m_Session->ReleaseArrayItemValue() respectively.


### Example
Check out [this](https://github.com/informaticon/div.cpp.miw.pbni-framework-example) repository to see a complete example.