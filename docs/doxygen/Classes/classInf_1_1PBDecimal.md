---
title: Inf::PBDecimal

---

# Inf::PBDecimal



 [More...](#detailed-description)


`#include <PBNumbers.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBDecimal](/docs/doxygen/Classes/classInf_1_1PBDecimal.md#function-pbdecimal)**(IPB_Session * session, pbdec dec) |
| | **[PBDecimal](/docs/doxygen/Classes/classInf_1_1PBDecimal.md#function-pbdecimal)**(IPB_Session * session, const Helper::PBDecimalImpl & value) |
| void | **[SetDecimal](/docs/doxygen/Classes/classInf_1_1PBDecimal.md#function-setdecimal)**(const Helper::PBDecimalImpl & value) |
| Helper::PBDecimalImpl | **[GetDecimal](/docs/doxygen/Classes/classInf_1_1PBDecimal.md#function-getdecimal)**() const |
| bool | **[IsNull](/docs/doxygen/Classes/classInf_1_1PBDecimal.md#function-isnull)**() const |
| void | **[SetToNull](/docs/doxygen/Classes/classInf_1_1PBDecimal.md#function-settonull)**() |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/docs/doxygen/Classes/classInf_1_1PBDecimal.md#friend-type)**  |
| class | **[PBObject](/docs/doxygen/Classes/classInf_1_1PBDecimal.md#friend-pbobject)**  |

## Detailed Description

```cpp
class Inf::PBDecimal;
```


Small Wrapper for pbdec. 

## Public Functions Documentation

### function PBDecimal

```cpp
PBDecimal(
    IPB_Session * session,
    pbdec dec
)
```


**Parameters**: 

  * **session** Current session 
  * **dec** The exsiting pbdec or 0 


Creates a Wrapper to an already existing pbdec. Will be Null if dec is 0.


### function PBDecimal

```cpp
PBDecimal(
    IPB_Session * session,
    const Helper::PBDecimalImpl & value
)
```


**Parameters**: 

  * **session** Current Session 
  * **value** The Decimal to copy 


Creates a new pbdec.


### function SetDecimal

```cpp
void SetDecimal(
    const Helper::PBDecimalImpl & value
)
```


**Parameters**: 

  * **value** The Decimal to copy 


Copies the Decimal string to PowerBuilder, crates a new Decimal if Null.


### function GetDecimal

```cpp
Helper::PBDecimalImpl GetDecimal() const
```


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)** if Null 


**Return**: Boost Decimal

Copies the Decimal from PowerBuilder.


### function IsNull

```cpp
bool IsNull() const
```


**Return**: Is Null 

Checks whether pbdec is Null.


### function SetToNull

```cpp
void SetToNull()
```


Sets pbdec to Null. 


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

Updated on 2022-09-16 at 11:32:55 +0200