# lib.cpp.base.pbni-framework
Framework for creating PowerBuilder Extensions using PBNI


## Dependencies
PowerBuilder PBNI

## CMake
Either add this repository as a submodule in your own repository, or just add it as a subfolder somewhere in your cmake source folder. \
You should already have a complete Cmake file which takes your source files and compiles them to a dll. \

After your cmake target add these lines:
```cmake
add_subdirectory(path/to/this/repo)
target_link_libraries(my_target PRIVATE libPBNIFramework)
```

## Code
To create a PBNI class, publicly extend Inf::PBNI_Class, you need to add a costructor and forward all arguments to INf::PBNI_Class, you can also put other stuff inside the constructor.
```cpp
// MyExtensionClass.h

#include <Framework.h>

class MyExtensionClass : public Inf::PBNI_Class
{
	MyExtensionClass(IPB_Session* session, pbobject pbobj, std::wstring pb_class_name)
		: Inf::PBNI_Class(session, pbobj, pb_class_name)
	{ }

	// Put your methods somewhere here
	void Example(Inf::PBInt some_number);
}
```

Then define all your functions. Inside a .cpp file use INF_REGISTER_CLASS, and INF_REGISTER_FUNC.
```cpp
// MyExtensionClass.cpp

#include "your_pbni_class.h"

#include <WinUser.h>
#include <ClassDescription.h>

// This will be the Name of the PowerBuilder user object.
#INF_REGISTER_CLASS(MyExtensionClass, L"u_my_extension_class");

// The second argument is the name used by PowerBuilder, after the 2nd argument, the argument names follow.
#INF_REGISTER_FUNC(Example, L"of_example", L"ai_some_number");
void MyExtensionClass::Example(Inf::PBInt some_number)
{
	MessageBoxW(NULL, L"This is an example", L"Message", MB_OK);
}

```
\
You don't need to add any PBNI entry points. Those are all handled by ``PBEntry.cpp``.


### Types
All types that are used are in the namespace Inf and start with PB. \
\
These are primitive types. They are copied over from PowerBuilder. 

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

You can basically use these types directly. But if you perform a lot of operations, its better to copy them to a C++ datatype, because a Null checks happens everytime you do an Operation.

```cpp
Inf::PBInt i(10);
Inf::PBReal r(6.75f);

Inf::PBDouble d = i + r;

pbdouble cpp_d = d;
```


Complex types dont get copied automatically, they are just wrappers, you can call Getters and Setters on them.

 - Inf::PBDecimal
 - Inf::PBTime
 - Inf::PBDate
 - Inf::PBDateTime
 - Inf::PBString
 - Inf::PBBlob
 - Inf::PBArray
 - Inf::PBObject

```cpp
// Creates a Null Time
Inf::PBTime time(m_Session, 0);
// Time is no longer Null
time.SetTime(23, 59, 59.999);


// Creates a new PowerBuilder String, converts normal strings to wstrings
Inf::PBString str(m_Session, "Some string");
std::wstring wstr = str.GetWString();
```

Arrays and Objects are the only types that use templates.
#### Arrays
Arrays' template arguments are:

 1. The type of the Arrays' Items 
 2. (.. 4.) The dimensions of the array if it is a Bounded Array, if you leave this empty it will be an Unbounded Array. Maximum of 3 Dimensions

When accessing values of Unbounded Arrays, you can give one int as Index. For Bounded Arrays you need to give an std::array as Indices. The Indices go from 1 to N inclusive.

```cpp
// Unbounded Array of Ints
Inf::PBArray<Inf::PBInt> integers;
integers.Set(20, 15)

// 1D Bounded Array of Floats
Inf::PBArray<Inf::PBReal, 100> floats;
integers.Get({ 63 })

// 2D 6x4 Bounded Array of Strings
Inf::PBArray<Inf::PBString, 6, 4> strings;
integers.Set({ 1, 4 }, L"Some value")
```

### Objects
Template Arguments:
 1. The ID of the PowerBuilder class, generally `Group.Type` but if both are the same you can just do `Group`.
 2. The type of the Group, can be `pbgroup_structure`, `pbgroup_userobject`, `pbgroup_datawindow` ... There are already some predefined types like Inf::PBStruct, which is just Inf::PBObject<.., pbgroup_structure>.

To Set Fields you can just use SetField. To Get a Field you need to give the Type you want to get as a Template Parameter. For Arrays and Objects you need to use `{Get,Set}{ArrayField,ObjectField}<...>`, because it's easier to handle than `GetField<Inf::PBArray<L"test">>`.

```cpp
// Instantiate a new object
Inf::PBObject<L"u_person"> charles(m_Session);

charles.SetField(L"ul_age", 54);
// Getting Arrays
charles.GetArrayField<Inf::PBString>(L"ar_siblings");

auto props = charles.GetObjectField<L"u_person.iu_properties">(L"iu_properties");
props.SetField(L"s_hair_color", L"orange");
```


### Variable LifeTime
Complex PowerBuilder variables get deleted once the functino call ends. If you want to store a value into a member variable, you need to copy it over to your own memory. There are alternatives for some types. For PBObjects, you can use ``m_Session->AddGlobalRef()``, just make sure to ``m_Session->RemoveGlobalRef()``, once you are done using it. With PBArrays you can do ``m_Session->AcquireArrayItemValue()`` and ``m_Session->ReleaseArrayItemValue()`` respectively.


### Global variables
To access global variables, use ``m_Session->GetGlobalVarID();`` and ``m_Session->Get<Type>GlobalVar();`` then you can instantiate an `Inf::PB<Type>` using the returned PowerBuilder type.

```cpp	
// Get the PowerBuilder object
pbboolean is_null;
pbobject pb_gu_e = m_Session->GetObjectGlobalVar(session->GetGlobalVarID(L"gu_e"), is_null);

// Create a Wrapper to it
Inf::PBObject<L"u_error_manager"> gu_e(m_Session, pb_gu_e);
```

### Errors
You can call errors from inside C++ using throw. There is a PowerBuilder style exception called Inf::PBNI_Exception. It has a key value store and automatically creates a stacktrace using boost. Heres a list of exceptions that are thrown by the framework:

 - Inf::PBNI_IndexOutOfBounds
 - Inf::PBNI_NullPointerException
 - Inf::PBNI_InvalidFieldException
 - Inf::PBNI_IncorrectArgumentsException
 - Inf::PBNI_PowerBuilderException

You can create your own by extending Inf::PBNI_Exception.


## Example
Check out [this repository](https://github.com/informaticon/div.cpp.base.pbni-framework-usage-example) for a complete example. Or [this one](https://github.com/informaticon/lib.pbni.base.tse) for an actual usage. 
