---
title: Inf::Type

---

# Inf::Type



 [More...](#detailed-description)


`#include <PBTypes.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| bool | **[Assert](/doxygen/Classes/struct_inf_1_1_type/#function-assert)**(IPB_Session * session, IPB_Value * pb_value) |
| std::wstring | **[GetPBName](/doxygen/Classes/struct_inf_1_1_type/#function-getpbname)**(std::wstring argument_name) =delete |
| T | **[FromArgument](/doxygen/Classes/struct_inf_1_1_type/#function-fromargument)**(IPB_Session * session, IPB_Value * pb_value, bool acquire) =delete |
| PBXRESULT | **[SetValue](/doxygen/Classes/struct_inf_1_1_type/#function-setvalue)**(IPB_Session * session, IPB_Value * pb_value, const T & t) =delete |
| PBXRESULT | **[Return](/doxygen/Classes/struct_inf_1_1_type/#function-return)**(IPB_Session * session, PBCallInfo * ci, const T & t) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| constexpr wchar_t | **[PBSignature](/doxygen/Classes/struct_inf_1_1_type/#variable-pbsignature)**  |
| constexpr pbvalue_type | **[PBType](/doxygen/Classes/struct_inf_1_1_type/#variable-pbtype)**  |

## Detailed Description

```cpp
template <typename T >
struct Inf::Type;
```


**Template Parameters**: 

  * **T** The related [Type](/doxygen/Classes/struct_inf_1_1_type/)


This is the Genereic [Type](/doxygen/Classes/struct_inf_1_1_type/) struct, each PBType implements the Fields it needs. You can Access any one of the Functions using e.g. Type<T>::PBSignature.

## Public Functions Documentation

### function Assert

```cpp
static inline bool Assert(
    IPB_Session * session,
    IPB_Value * pb_value
)
```


**Parameters**: 

  * **session** Current Session 
  * **pb_value** The Value to check 


**Return**: true if its okay to convert, false otherwise. 

This Function returns whether the IPB_Value can be used to retrieve the specified type.


### function GetPBName

```cpp
static inline std::wstring GetPBName(
    std::wstring argument_name
) =delete
```


**Parameters**: 

  * **argument_name** The name to put between type and [] 


**Return**: The combined string 

This Function is used to generate the Description of a Method, it needs to take in the name of the argument so we can add [] at the end of arrays. This wont add any spaces between the type and argument_name.


### function FromArgument

```cpp
static inline T FromArgument(
    IPB_Session * session,
    IPB_Value * pb_value,
    bool acquire
) =delete
```


**Parameters**: 

  * **session** Current Session 
  * **pb_value** The value to get retrieve the [Type](/doxygen/Classes/struct_inf_1_1_type/) from 
  * **acquire** Whether or not to take ownership of the type, only relevant for complex types. The [Type](/doxygen/Classes/struct_inf_1_1_type/) will free itself 


**Return**: The returned [Type](/doxygen/Classes/struct_inf_1_1_type/)

This Function Retrieves the specified [Type](/doxygen/Classes/struct_inf_1_1_type/) from an IPB_Value.


### function SetValue

```cpp
static inline PBXRESULT SetValue(
    IPB_Session * session,
    IPB_Value * pb_value,
    const T & t
) =delete
```


**Parameters**: 

  * **session** Current Session 
  * **pb_value** Value to set 
  * **t** [Type](/doxygen/Classes/struct_inf_1_1_type/) to set Value to 


This sets a value to a specified [Type](/doxygen/Classes/struct_inf_1_1_type/).


### function Return

```cpp
static inline PBXRESULT Return(
    IPB_Session * session,
    PBCallInfo * ci,
    const T & t
)
```


**Parameters**: 

  * **session** Current Session 
  * **ci** The Callback info to set the returnValue of 
  * **t** [Type](/doxygen/Classes/struct_inf_1_1_type/) to set returnValue to 


Basically the same as SetValue. Currently only used so that [PBArray](/doxygen/Classes/class_inf_1_1_p_b_array/) can delete this function.


## Public Attributes Documentation

### variable PBSignature

```cpp
static constexpr wchar_t PBSignature = L' ';
```


### variable PBType

```cpp
static constexpr pbvalue_type PBType = pbvalue_notype;
```


-------------------------------

Updated on 2022-08-25 at 16:29:24 +0200