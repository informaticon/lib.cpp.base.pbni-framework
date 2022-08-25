---
title: Inf::PBDecimal

---

# Inf::PBDecimal



 [More...](#detailed-description)


`#include <PBNumbers.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBDecimal](/doxygen/Classes/class_inf_1_1_p_b_decimal/#function-pbdecimal)**(IPB_Session * session, pbdec dec) |
| | **[PBDecimal](/doxygen/Classes/class_inf_1_1_p_b_decimal/#function-pbdecimal)**(IPB_Session * session, const Helper::PBDecimalImpl & value) |
| void | **[SetDecimal](/doxygen/Classes/class_inf_1_1_p_b_decimal/#function-setdecimal)**(const Helper::PBDecimalImpl & value) |
| Helper::PBDecimalImpl | **[GetDecimal](/doxygen/Classes/class_inf_1_1_p_b_decimal/#function-getdecimal)**() const |
| bool | **[IsNull](/doxygen/Classes/class_inf_1_1_p_b_decimal/#function-isnull)**() const |
| void | **[SetToNull](/doxygen/Classes/class_inf_1_1_p_b_decimal/#function-settonull)**() |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/doxygen/Classes/class_inf_1_1_p_b_decimal/#friend-type)**  |
| class | **[PBArray](/doxygen/Classes/class_inf_1_1_p_b_decimal/#friend-pbarray)**  |
| class | **[PBObject](/doxygen/Classes/class_inf_1_1_p_b_decimal/#friend-pbobject)**  |

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

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** if Null 


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