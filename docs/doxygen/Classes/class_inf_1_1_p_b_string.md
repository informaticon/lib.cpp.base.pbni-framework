---
title: Inf::PBString

---

# Inf::PBString



 [More...](#detailed-description)


`#include <PBString.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBString](/doxygen/Classes/class_inf_1_1_p_b_string/#function-pbstring)**(IPB_Session * session, pbstring pb_string) |
| | **[PBString](/doxygen/Classes/class_inf_1_1_p_b_string/#function-pbstring)**(IPB_Session * session, const std::string & str) |
| | **[PBString](/doxygen/Classes/class_inf_1_1_p_b_string/#function-pbstring)**(IPB_Session * session, const std::wstring & wstr) |
| std::string | **[GetString](/doxygen/Classes/class_inf_1_1_p_b_string/#function-getstring)**() const |
| std::wstring | **[GetWString](/doxygen/Classes/class_inf_1_1_p_b_string/#function-getwstring)**() const |
| void | **[SetString](/doxygen/Classes/class_inf_1_1_p_b_string/#function-setstring)**(const std::string & str) |
| void | **[SetWString](/doxygen/Classes/class_inf_1_1_p_b_string/#function-setwstring)**(const std::wstring & wstr) |
| pblong | **[Size](/doxygen/Classes/class_inf_1_1_p_b_string/#function-size)**() const |
| bool | **[IsNull](/doxygen/Classes/class_inf_1_1_p_b_string/#function-isnull)**() const |
| void | **[SetToNull](/doxygen/Classes/class_inf_1_1_p_b_string/#function-settonull)**() |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/doxygen/Classes/class_inf_1_1_p_b_string/#friend-type)**  |
| class | **[PBArray](/doxygen/Classes/class_inf_1_1_p_b_string/#friend-pbarray)**  |
| class | **[PBObject](/doxygen/Classes/class_inf_1_1_p_b_string/#friend-pbobject)**  |

## Detailed Description

```cpp
class Inf::PBString;
```


This is a simple Wrapper to be able to get/set an std::string or std::wstring from/to a pbstring. This Class doesnt store any Data of the String. 

## Public Functions Documentation

### function PBString

```cpp
PBString(
    IPB_Session * session,
    pbstring pb_string
)
```


**Parameters**: 

  * **session** Current Session 
  * **pb_string** The existing pb_string or 0 


Creates a Wrapper to an already existing pb_string. Will be Null if pbstring is 0.


### function PBString

```cpp
PBString(
    IPB_Session * session,
    const std::string & str
)
```


**Parameters**: 

  * **session** Current Session 
  * **str** String to copy 


Creates a new pbstring, converts the String to unicode and copies it.


### function PBString

```cpp
PBString(
    IPB_Session * session,
    const std::wstring & wstr
)
```


**Parameters**: 

  * **session** Current Session 
  * **wstr** WString to copy 


Creates a new pbstring and writes the WString to it.


### function GetString

```cpp
std::string GetString() const
```


**Exceptions**: 

  * **[PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If String is Null 


**Return**: Ansi String

Reads the String and converts it to an Ansi String.


### function GetWString

```cpp
std::wstring GetWString() const
```


**Exceptions**: 

  * **[PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If String is Null 


**Return**: Unicode String

Gets the String from Poerbuilder.


### function SetString

```cpp
void SetString(
    const std::string & str
)
```


**Parameters**: 

  * **str** The String to copy 


Converts and copies the String to PowerBuilder.


### function SetWString

```cpp
void SetWString(
    const std::wstring & wstr
)
```


**Parameters**: 

  * **wstr** The WString to copy 


Copies the WString to PowerBuilder.


### function Size

```cpp
pblong Size() const
```


**Exceptions**: 

  * **[PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If String is Null 


**Return**: The size in bytes without Terminator.

Gets the Size from PowerBuilder.


### function IsNull

```cpp
bool IsNull() const
```


Checks whether the pbstring is Null. 


### function SetToNull

```cpp
void SetToNull()
```


Sets the pbstring to Null. 


## Friends

### friend Type

```cpp
friend struct Type(
    Type 
);
```


### friend PBArray

```cpp
friend class PBArray(
    PBArray 
);
```


### friend PBObject

```cpp
friend class PBObject(
    PBObject 
);
```


-------------------------------

Updated on 2022-08-25 at 16:29:24 +0200