# PBNI Framework - PowerBuilder Variables
---


## Types
All types used by PowerBuilder Framework start with `Inf::PB`, when you declare Methods, you should only use those. You can use References in your Methods Arguments, these will be saved to PowerBuilder once the Method ends. You cannot use References as Return Value, or Pointers anywhere.

#### Primitives
Primitive Types are copied to C++. They can be used in operations and are implicitly Cast into their C++ counterparts.  
In PowerBuilder, even primitive Types can be Null, and if you use `Inf::PB<Type>` you should always check using `.IsNull()`. Otherwise the Framework will throw an `Inf::PBNI_NullPointerException`.
```cpp
Inf::PBInt i(10);
Inf::PBReal r(6.75f);

r.IsNull();

Inf::PBDouble d = i + r;

pbdouble cpp_d = d;
```
You can use the ``Inf::PB<Type>``s directly for basically everything, but I suggest you copy them over to a C++ variable, then you don't need to worry about the Values being null.
When comparing Primitive types to C++ types, you should cast the variable into the C Type:
```cpp
Inf::PBInt i(22);

if ((pbint) i > 10) {
    ...
}
```

#### Complex
Everything, that isn't a Number, Boolean, Char or Byte, is a complex Type (except Decimal, which is complex). The Values of the complex types are owned by PowerBuilder and the provided `Inf::PB<Type>`s are just Wrappers to the PowerBuilder Objects. These types can also be Null, so make sure to check.

```cpp
// Creates a Null Time
Inf::PBTime time(m_Session, 0);
// Time is no longer Null
time.SetTime(23, 59, 59.999);

// Creates a new PowerBuilder String, converts normal strings to wstrings
Inf::PBString str(m_Session, "Some string");
std::wstring wstr = str.GetWString();
```

Most of the Types are straightforward. It starts getting a bit more complicated with Arrays and Objects.
#### Arrays
Array are a Class Template. These are the arguments:

 1. The type of the Arrays' Items 
 2. .. 4. The dimensions of the array if it is a Bounded Array, if you leave this empty it will be an Unbounded Array

When accessing values of Unbounded Arrays, you can give one int as Index. For Bounded Arrays you need to give an `std::array` as Indices. The Indices go from 1 to N inclusive. Otherwise it will throw an `Inf::PBNI_IndexOutOfBounds`. When setting an Index in an Unbounded Array, you don't need to worry about being out of Bounds, it will just extend the Array.  
PowerBuilder doesn't support returning Arrays directly. So you can't do it in an extension either.

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

#### Objects
Template Arguments:

 1. The ID of the PowerBuilder class, generally `group.type` but if both are the same you can just do `group`
 2. The type of the Group, can be `pbgroup_structure`, `pbgroup_userobject`, `pbgroup_datawindow` ...

Some aliased Object Types are provided, like Inf::PBStruct<..>, which is just Inf::PBObject<.., pbgroup_structure>
To Set Fields you can just use SetField. To Get a Field you need to give the Type you want to be returned as a Template Parameter. 

```cpp
// Instantiate a new object
Inf::PBObject<L"u_person"> charles(m_Session);

// Use function Overloads
charles.SetField(L"d_height", Inf::PBDouble(1.98));
// Give a Type and let it cast automatically
charles.SetField<Inf::PBUint>(L"ui_age", 54);
// Give a Type to return
Inf::PBString name = charles.GetField<Inf::PBString>("s_full_name");

```

##### Arrays and Objects combined
When using an Array of objects, the Types can get pretty long. Then you can use Type Aliases or the `auto` keyword. 

```cpp
using PersonArray = Inf::PBArray<Inf::PBObject<L"u_group.it_person">>

auto siblings = charles.GetField<PersonArray>(L"ar_siblings");
```


## Variable LifeTime
Since primitive Types are stored by value, you can keep them in Memory as long as you want. But complex Types get deleted once the Method Call ends. So don't this.

```cpp
#INF_REGISTER_FUNC(StorePerson, L"of_store_person", L"au_object")
void StoreObject(Inf::PBObject<L"u_person"> person)
{
    this->m_Person = person; // This wont work
}
```

If you want to keep the Value alive after the function. You need to copy over the Value into C++ (into a `std::string`, `std::vector`, `boost::decimal`, ...).  
For ``Inf::PBObjects``, you can use `m_Session->AddGlobalRef(person)` and `m_Session->RemoveGlobalRef(person)`. With ``Inf::PBArrays`` you can do `IPB_Session::AcquireArrayItemValue` and `IPB_Session::ReleaseArrayItemValue` respectively.


## Global variables
To access global variables, use `IPB_Session::GetGlobalVarID;` and `IPB_Session::Get<Type>GlobalVar;` then you can instantiate an `Inf::PB<Type>` using the returned PowerBuilder type.

```cpp	
// Complex type
pbboolean is_null;
pbobject pb_gu_e = m_Session->GetObjectGlobalVar(session->GetGlobalVarID(L"gu_e"), is_null);

// Create a Wrapper to it
Inf::PBObject<L"u_error_manager"> gu_e(m_Session, pb_gu_e);

// For primitive types
pbboolean is_null;
Inf::PBInt pb_gi_num = m_Session->GetIntGlobalVar(session->GetGlobalVarID(L"gi_num"), is_null);
if ( is_null )
    pb_gi_num.SetToNull();
```
