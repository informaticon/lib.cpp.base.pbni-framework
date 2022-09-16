---
title: Inf::PBBlob

---

# Inf::PBBlob



 [More...](#detailed-description)


`#include <PBBlob.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBBlob](/docs/doxygen/Classes/classInf_1_1PBBlob.md#function-pbblob)**(IPB_Session * session, pbblob blob) |
| | **[PBBlob](/docs/doxygen/Classes/classInf_1_1PBBlob.md#function-pbblob)**(IPB_Session * session, pbbyte * data, pblong size) |
| void | **[SetData](/docs/doxygen/Classes/classInf_1_1PBBlob.md#function-setdata)**(pbbyte * data, pblong size) |
| pbbyte * | **[GetData](/docs/doxygen/Classes/classInf_1_1PBBlob.md#function-getdata)**() const |
| pblong | **[Size](/docs/doxygen/Classes/classInf_1_1PBBlob.md#function-size)**() const |
| bool | **[IsNull](/docs/doxygen/Classes/classInf_1_1PBBlob.md#function-isnull)**() const |
| void | **[SetToNull](/docs/doxygen/Classes/classInf_1_1PBBlob.md#function-settonull)**() |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/docs/doxygen/Classes/classInf_1_1PBBlob.md#friend-type)**  |
| class | **[PBObject](/docs/doxygen/Classes/classInf_1_1PBBlob.md#friend-pbobject)**  |

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

  * **[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)** if Null 


**Return**: Pointer to the PowerBuilder Data

Retrieves a Pointer to the Raw Data.


### function Size

```cpp
pblong Size() const
```


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)** if Null 


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


### friend PBObject

```cpp
friend class PBObject(
    PBObject 
);
```


-------------------------------

Updated on 2022-09-16 at 11:32:55 +0200