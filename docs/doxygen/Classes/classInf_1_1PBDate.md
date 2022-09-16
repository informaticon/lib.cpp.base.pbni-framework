---
title: Inf::PBDate

---

# Inf::PBDate



 [More...](#detailed-description)


`#include <PBDateTimes.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBDate](/docs/doxygen/Classes/classInf_1_1PBDate.md#function-pbdate)**(IPB_Session * session, pbdate date) |
| | **[PBDate](/docs/doxygen/Classes/classInf_1_1PBDate.md#function-pbdate)**(IPB_Session * session, pbint years, pbint months, pbint days) |
| std::tuple< pbint, pbint, pbint > | **[GetDate](/docs/doxygen/Classes/classInf_1_1PBDate.md#function-getdate)**() const |
| void | **[SetDate](/docs/doxygen/Classes/classInf_1_1PBDate.md#function-setdate)**(pbint years, pbint months, pbint days) |
| bool | **[IsNull](/docs/doxygen/Classes/classInf_1_1PBDate.md#function-isnull)**() const |
| void | **[SetToNull](/docs/doxygen/Classes/classInf_1_1PBDate.md#function-settonull)**() |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/docs/doxygen/Classes/classInf_1_1PBDate.md#friend-type)**  |
| class | **[PBObject](/docs/doxygen/Classes/classInf_1_1PBDate.md#friend-pbobject)**  |

## Detailed Description

```cpp
class Inf::PBDate;
```


This is a Wrapper for pbdate. 

## Public Functions Documentation

### function PBDate

```cpp
PBDate(
    IPB_Session * session,
    pbdate date
)
```


**Parameters**: 

  * **session** Current session 
  * **date** The exsiting pbdate or 0 


Creates a Wrapper to an already existing pbdate. Will be Null if date is 0.


### function PBDate

```cpp
PBDate(
    IPB_Session * session,
    pbint years,
    pbint months,
    pbint days
)
```


**Parameters**: 

  * **session** Current Session 
  * **years** The years to set 
  * **months** The months to set 
  * **days** The days to set 


Creates a new pbdate.


### function GetDate

```cpp
std::tuple< pbint, pbint, pbint > GetDate() const
```


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)** If Null 
  * **[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)** If PowerBuilder function doesnt return PBX_SUCESS 


**Return**: years, months, days

Gets the Date from PowerBuilder.


### function SetDate

```cpp
void SetDate(
    pbint years,
    pbint months,
    pbint days
)
```


**Parameters**: 

  * **years** Years to set 
  * **months** Months to set 
  * **days** Days to set


**Exceptions**: 

  * **[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)** If PowerBuilder function doesnt return PBX_SUCESS 


Sets the Date in PowerBuilder. Creates a new Date if is Null.


### function IsNull

```cpp
bool IsNull() const
```


Checks whether the pbdate is Null 


### function SetToNull

```cpp
void SetToNull()
```


Sets the pbdate to Null. 


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