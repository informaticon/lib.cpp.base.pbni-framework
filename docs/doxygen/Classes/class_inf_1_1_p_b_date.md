---
title: Inf::PBDate

---

# Inf::PBDate



 [More...](#detailed-description)


`#include <PBDateTimes.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBDate](/doxygen/Classes/class_inf_1_1_p_b_date/#function-pbdate)**(IPB_Session * session, pbdate date) |
| | **[PBDate](/doxygen/Classes/class_inf_1_1_p_b_date/#function-pbdate)**(IPB_Session * session, pbint years, pbint months, pbint days) |
| std::tuple< pbint, pbint, pbint > | **[GetDate](/doxygen/Classes/class_inf_1_1_p_b_date/#function-getdate)**() const |
| void | **[SetDate](/doxygen/Classes/class_inf_1_1_p_b_date/#function-setdate)**(pbint years, pbint months, pbint days) |
| bool | **[IsNull](/doxygen/Classes/class_inf_1_1_p_b_date/#function-isnull)**() const |
| void | **[SetToNull](/doxygen/Classes/class_inf_1_1_p_b_date/#function-settonull)**() |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/doxygen/Classes/class_inf_1_1_p_b_date/#friend-type)**  |
| class | **[PBArray](/doxygen/Classes/class_inf_1_1_p_b_date/#friend-pbarray)**  |
| class | **[PBObject](/doxygen/Classes/class_inf_1_1_p_b_date/#friend-pbobject)**  |

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

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If Null 
  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If PowerBuilder function doesnt return PBX_SUCESS 


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

  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If PowerBuilder function doesnt return PBX_SUCESS 


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