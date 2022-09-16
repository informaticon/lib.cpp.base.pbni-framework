---
title: Inf::PBTime

---

# Inf::PBTime



 [More...](#detailed-description)


`#include <PBDateTimes.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBTime](/docs/doxygen/Classes/classInf_1_1PBTime.md#function-pbtime)**(IPB_Session * session, pbtime time) |
| | **[PBTime](/docs/doxygen/Classes/classInf_1_1PBTime.md#function-pbtime)**(IPB_Session * session, pbint hours, pbint minutes, pbdouble seconds) |
| std::tuple< pbint, pbint, pbdouble > | **[GetTime](/docs/doxygen/Classes/classInf_1_1PBTime.md#function-gettime)**() const |
| void | **[SetTime](/docs/doxygen/Classes/classInf_1_1PBTime.md#function-settime)**(pbint hours, pbint minutes, pbdouble seconds) |
| bool | **[IsNull](/docs/doxygen/Classes/classInf_1_1PBTime.md#function-isnull)**() const |
| void | **[SetToNull](/docs/doxygen/Classes/classInf_1_1PBTime.md#function-settonull)**() |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/docs/doxygen/Classes/classInf_1_1PBTime.md#friend-type)**  |
| class | **[PBObject](/docs/doxygen/Classes/classInf_1_1PBTime.md#friend-pbobject)**  |

## Detailed Description

```cpp
class Inf::PBTime;
```


This is a Wrapper for pbtime. 

## Public Functions Documentation

### function PBTime

```cpp
PBTime(
    IPB_Session * session,
    pbtime time
)
```


**Parameters**: 

  * **session** Current session 
  * **time** The exsiting pbtime or 0 


Creates a Wrapper to an already existing pbtime. Will be Null if time is 0.


### function PBTime

```cpp
PBTime(
    IPB_Session * session,
    pbint hours,
    pbint minutes,
    pbdouble seconds
)
```


**Parameters**: 

  * **session** Current Session 
  * **hours** The hour to set 
  * **minutes** The minute to set 
  * **seconds** The second to set 


Creates a new pbtime.


### function GetTime

```cpp
std::tuple< pbint, pbint, pbdouble > GetTime() const
```


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)** If Null 
  * **[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)** If PowerBuilder function doesnt return PBX_SUCESS 


**Return**: hours, minutes, seconds

Gets the Time from PowerBuilder.


### function SetTime

```cpp
void SetTime(
    pbint hours,
    pbint minutes,
    pbdouble seconds
)
```


**Parameters**: 

  * **hours** Hours to set 
  * **minutes** Minutes to set 
  * **seconds** Seconds to set


**Exceptions**: 

  * **[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)** If PowerBuilder function doesnt return PBX_SUCESS 


Sets the Time in PowerBuilder. Creates a new Time if is Null.


### function IsNull

```cpp
bool IsNull() const
```


Checks whether the pbtime is Null 


### function SetToNull

```cpp
void SetToNull()
```


Sets the pbtime to Null. 


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