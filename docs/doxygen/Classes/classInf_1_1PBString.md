---
title: Inf::PBString

---

# Inf::PBString



 [More...](#detailed-description)


`#include <PBString.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBString](/docs/doxygen/Classes/classInf_1_1PBString.md#function-pbstring)**(IPB_Session * session, pbstring pb_string) |
| | **[PBString](/docs/doxygen/Classes/classInf_1_1PBString.md#function-pbstring)**(IPB_Session * session, const std::string & str) |
| | **[PBString](/docs/doxygen/Classes/classInf_1_1PBString.md#function-pbstring)**(IPB_Session * session, const std::wstring & wstr) |
| std::string | **[GetString](/docs/doxygen/Classes/classInf_1_1PBString.md#function-getstring)**() const |
| std::wstring | **[GetWString](/docs/doxygen/Classes/classInf_1_1PBString.md#function-getwstring)**() const |
| void | **[SetString](/docs/doxygen/Classes/classInf_1_1PBString.md#function-setstring)**(const std::string & str) |
| void | **[SetWString](/docs/doxygen/Classes/classInf_1_1PBString.md#function-setwstring)**(const std::wstring & wstr) |
| pblong | **[Size](/docs/doxygen/Classes/classInf_1_1PBString.md#function-size)**() const |
| bool | **[IsNull](/docs/doxygen/Classes/classInf_1_1PBString.md#function-isnull)**() const |
| void | **[SetToNull](/docs/doxygen/Classes/classInf_1_1PBString.md#function-settonull)**() |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/docs/doxygen/Classes/classInf_1_1PBString.md#friend-type)**  |
| class | **[PBObject](/docs/doxygen/Classes/classInf_1_1PBString.md#friend-pbobject)**  |

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

  * **[PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)** If String is Null 


**Return**: Ansi String

Reads the String and converts it to an Ansi String.


### function GetWString

```cpp
std::wstring GetWString() const
```


**Exceptions**: 

  * **[PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)** If String is Null 


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

  * **[PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)** If String is Null 


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


### friend PBObject

```cpp
friend class PBObject(
    PBObject 
);
```


-------------------------------

Updated on 2022-09-15 at 20:34:45 +0200