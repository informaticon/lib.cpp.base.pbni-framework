---
title: Inf

---

# Inf



## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Inf::IClassDescription](/docs/doxygen/Classes/classInf_1_1IClassDescription.md)**  |
| class | **[Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md)**  |
| class | **[Inf::PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md)**  |
| class | **[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)**  |
| class | **[Inf::PBNI_InvalidFieldException](/docs/doxygen/Classes/classInf_1_1PBNI__InvalidFieldException.md)**  |
| class | **[Inf::PBNI_IncorrectArgumentsException](/docs/doxygen/Classes/classInf_1_1PBNI__IncorrectArgumentsException.md)**  |
| class | **[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)**  |
| class | **[Inf::PBNI_Class](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md)**  |
| class | **[Inf::PBNI_Framework](/docs/doxygen/Classes/classInf_1_1PBNI__Framework.md)**  |
| class | **[Inf::IMethodDescription](/docs/doxygen/Classes/classInf_1_1IMethodDescription.md)**  |
| class | **[Inf::PBObject](/docs/doxygen/Classes/classInf_1_1PBObject.md)**  |
| class | **[Inf::PBBlob](/docs/doxygen/Classes/classInf_1_1PBBlob.md)**  |
| class | **[Inf::PBTime](/docs/doxygen/Classes/classInf_1_1PBTime.md)**  |
| class | **[Inf::PBDate](/docs/doxygen/Classes/classInf_1_1PBDate.md)**  |
| class | **[Inf::PBDateTime](/docs/doxygen/Classes/classInf_1_1PBDateTime.md)**  |
| class | **[Inf::PBDecimal](/docs/doxygen/Classes/classInf_1_1PBDecimal.md)**  |
| class | **[Inf::PBString](/docs/doxygen/Classes/classInf_1_1PBString.md)**  |
| struct | **[Inf::Type](/docs/doxygen/Classes/structInf_1_1Type.md)**  |

## Types

|                | Name           |
| -------------- | -------------- |
| using PBReal | **[PBFloat](/docs/doxygen/Namespaces/namespaceInf.md#using-pbfloat)**  |
| template <Helper::FixedString class_id\> <br>using [PBObject](/docs/doxygen/Classes/classInf_1_1PBObject.md)< class_id, pbgroup_structure > | **[PBStruct](/docs/doxygen/Namespaces/namespaceInf.md#using-pbstruct)**  |
| template <Helper::FixedString class_id\> <br>using [PBObject](/docs/doxygen/Classes/classInf_1_1PBObject.md)< class_id, pbgroup_window > | **[PBWindow](/docs/doxygen/Namespaces/namespaceInf.md#using-pbwindow)**  |
| template <Helper::FixedString class_id\> <br>using [PBObject](/docs/doxygen/Classes/classInf_1_1PBObject.md)< class_id, pbgroup_datawindow > | **[PBDataWindow](/docs/doxygen/Namespaces/namespaceInf.md#using-pbdatawindow)**  |

## Functions

|                | Name           |
| -------------- | -------------- |
| template <typename Item ,pblong... dims\> <br>| **[requires](/docs/doxygen/Namespaces/namespaceInf.md#function-requires)**(sizeof...(dims)<=3 &&!std::is_reference_v< Item > &&!std::is_pointer_v< Item > ) |
| template <typename ToStr ,typename... FromStr\> <br>ToStr | **[ConvertString](/docs/doxygen/Namespaces/namespaceInf.md#function-convertstring)**(FromStr... str) =delete |
| std::wstring | **[ConvertString](/docs/doxygen/Namespaces/namespaceInf.md#function-convertstring)**(const char * str, size_t size) |
| std::wstring | **[ConvertString](/docs/doxygen/Namespaces/namespaceInf.md#function-convertstring)**(const char * str) |
| std::wstring | **[ConvertString](/docs/doxygen/Namespaces/namespaceInf.md#function-convertstring)**(const std::string str) |
| std::string | **[ConvertString](/docs/doxygen/Namespaces/namespaceInf.md#function-convertstring)**(const wchar_t * wstr, size_t size) |
| std::string | **[ConvertString](/docs/doxygen/Namespaces/namespaceInf.md#function-convertstring)**(const wchar_t * wstr) |
| std::string | **[ConvertString](/docs/doxygen/Namespaces/namespaceInf.md#function-convertstring)**(const std::wstring wstr) |

## Types Documentation

### using PBFloat

```cpp
using Inf::PBFloat = typedef PBReal;
```


### using PBStruct

```cpp
template <Helper::FixedString class_id>
using Inf::PBStruct = typedef PBObject<class_id, pbgroup_structure>;
```


### using PBWindow

```cpp
template <Helper::FixedString class_id>
using Inf::PBWindow = typedef PBObject<class_id, pbgroup_window>;
```


### using PBDataWindow

```cpp
template <Helper::FixedString class_id>
using Inf::PBDataWindow = typedef PBObject<class_id, pbgroup_datawindow>;
```



## Functions Documentation

### function requires

```cpp
template <typename Item ,
pblong... dims>
requires(
    sizeof...(dims)<=3 &&!std::is_reference_v< Item > &&!std::is_pointer_v< Item > 
)
```


**Template Parameters**: 

  * **Item** [Type](/docs/doxygen/Classes/structInf_1_1Type.md) of the Array Items 
  * **...dims** The Bounds of the Bounded Array, Unbounded Array if empty 


Wrapper for simple Arrays.


Creates a Wrapper to an existing pbarray. Null if arr is 0

sessionCurrent session 

arrpbarray or 0


Creates a new Bounded or Unbounded Array.

sessionCurrent Session


Sets an Item in an Unbounded Array. Copies if Item is string or blob.

posThe Position 

tThe Value to set from

[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)If is Null 

[Inf::PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md)If out of bounds 

[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)If PowerBuilder function doesnt return PBX_SUCESS


Retrieves an Item in an Unbounded Array. If Item is complex, it will return a reference.

posThe Position 

The Value

[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)If is Null 

[Inf::PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md)If out of bounds


Sets an Item in an Unbounded Array To Null.

posThe Position

[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)If is Null 

[Inf::PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md)If out of bounds 

[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)If PowerBuilder function doesnt return PBX_SUCESS


Checks wheter an Item in an Unbounded Array is Null.

posThe Position 

Is Null

[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)If is Null 

[Inf::PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md)If out of bounds


Sets an Item in a Bounded Array. Copies if Item is string or blob.

posArray of Positions 

tThe Value to set from

[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)If is Null 

[Inf::PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md)If out of bounds 

[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)If PowerBuilder function doesnt return PBX_SUCESS


Retrieves an Item in a Bounded Array. If Item is complex, it will return a reference.

posArray of Positions 

The Value

[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)If is Null 

[Inf::PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md)If out of bounds


Sets an Item in a Bounded Array To Null.

posArray of Positions

[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)If is Null 

[Inf::PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md)If out of bounds 

[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)If PowerBuilder function doesnt return PBX_SUCESS


Checks wheter an Item in a Bounded Array is Null.

posArray of Positions 

Is Null

[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)If is Null 

[Inf::PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md)If out of bounds


Gets the Bounds of a Bounded Array From PowerBuilder.

An Array of Bounds


Retrieves the Length of the Array from PowerBuilder.

The Size

[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)If is Null


Check wether the pbarray is null.

Is Null


Sets the pbarray to Null.

This conversion operator is currently the only way of getting the pbarray.

The pbarray used for PowerBuilder functions


Constructor used to get an array out of a value and acquire if needed.

sessionCurrent Session 

valueIPB_Value holding the Array 

acquireWhether to take ownership of the IPB_Value


Asserts whether a position is inside a bounded Array.

posArray of Positions

[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)If is Null 

[Inf::PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md)If out of bounds


Asserts whether a position is inside an Unbounded Array.

posThe Position 

check_upper_boundWhether to Check if the Position is too big

[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)If is Null 

[Inf::PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md)If out of bounds


### function ConvertString

```cpp
template <typename ToStr ,
typename... FromStr>
ToStr ConvertString(
    FromStr... str
) =delete
```


**Template Parameters**: 

  * **ToStr** The [Type](/docs/doxygen/Classes/structInf_1_1Type.md) to be converted to 


These functions convert a String from Ansi to Unicode or back. They use Window's MultiByteToWideChar and WideCharToMultiByte functions (stringapiset.h)


### function ConvertString

```cpp
std::wstring ConvertString(
    const char * str,
    size_t size
)
```


### function ConvertString

```cpp
std::wstring ConvertString(
    const char * str
)
```


### function ConvertString

```cpp
std::wstring ConvertString(
    const std::string str
)
```


### function ConvertString

```cpp
std::string ConvertString(
    const wchar_t * wstr,
    size_t size
)
```


### function ConvertString

```cpp
std::string ConvertString(
    const wchar_t * wstr
)
```


### function ConvertString

```cpp
std::string ConvertString(
    const std::wstring wstr
)
```






-------------------------------

Updated on 2022-09-16 at 11:32:54 +0200