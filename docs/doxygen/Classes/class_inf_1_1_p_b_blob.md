---
title: Inf::PBBlob

---

# Inf::PBBlob



 [More...](#detailed-description)


`#include <PBBlob.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBBlob](/doxygen/Classes/class_inf_1_1_p_b_blob/#function-pbblob)**(IPB_Session * session, pbblob blob) |
| | **[PBBlob](/doxygen/Classes/class_inf_1_1_p_b_blob/#function-pbblob)**(IPB_Session * session, pbbyte * data, pblong size) |
| void | **[SetData](/doxygen/Classes/class_inf_1_1_p_b_blob/#function-setdata)**(pbbyte * data, pblong size) |
| pbbyte * | **[GetData](/doxygen/Classes/class_inf_1_1_p_b_blob/#function-getdata)**() const |
| pblong | **[Size](/doxygen/Classes/class_inf_1_1_p_b_blob/#function-size)**() const |
| bool | **[IsNull](/doxygen/Classes/class_inf_1_1_p_b_blob/#function-isnull)**() const |
| void | **[SetToNull](/doxygen/Classes/class_inf_1_1_p_b_blob/#function-settonull)**() |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/doxygen/Classes/class_inf_1_1_p_b_blob/#friend-type)**  |
| class | **[PBArray](/doxygen/Classes/class_inf_1_1_p_b_blob/#friend-pbarray)**  |
| class | **[PBObject](/doxygen/Classes/class_inf_1_1_p_b_blob/#friend-pbobject)**  |

## Detailed Description

```cpp
class Inf::PBBlob;
```


Small Wrapper for pbblob. 

## Public Functions Documentation

### function PBBlob

```cpp
PBBlob(
    IPB_Session * session,
    pbblob blob
)
```


**Parameters**: 

  * **session** Current session 
  * **blob** The exsiting pbblob or 0 


Creates a Wrapper to an already existing pbblob. Will be Null if blob is 0.


### function PBBlob

```cpp
PBBlob(
    IPB_Session * session,
    pbbyte * data,
    pblong size
)
```


**Parameters**: 

  * **session** Current Session 
  * **data** The data to copy 
  * **size** The size of the data in bytes 


Creates a new pbblob by copying the provided data.


### function SetData

```cpp
void SetData(
    pbbyte * data,
    pblong size
)
```


**Parameters**: 

  * **data** Pointer to the Data 
  * **size** Size of the Data 


Copies the Data to PowerBuilder. Creates a new Blob if Null.


### function GetData

```cpp
pbbyte * GetData() const
```


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** if Null 


**Return**: Pointer to the PowerBuilder Data

Retrieves a Pointer to the Raw Data.


### function Size

```cpp
pblong Size() const
```


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** if Null 


**Return**: Size in Bytes

Gets the size from PowerBuilder.


### function IsNull

```cpp
bool IsNull() const
```


**Return**: Is Null 

Checks whether pbblob is Null.


### function SetToNull

```cpp
void SetToNull()
```


Sets pbblob to Null. 


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

Updated on 2022-08-25 at 16:29:23 +0200