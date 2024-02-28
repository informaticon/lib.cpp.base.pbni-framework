# PowerBuilder
---

## Wrapper Classes

All of the PBNI Libraries have Wrapper Class on the PowerBuilder side, because:
 - They can be used to Document the Class with Comments
 - To change the namespace of the Object (e.g. u_pbni_file -> u_fsu_file)
 - To add AutoInstantiation
 - To add simple Utility Functions that don't need to be written in C++

To make the Wrapper class its prefer to Composition instead of Inheritance, because:
 - When you have a PBNI Class open in PowerBuilder IDE, it will lock the DLL, and make it so you can't rebuild it without closing the File Editor (This includes Classes that inherit from PBNI Classes)
 - When you set the inheriting Class to AutoInstantiate, PowerBuilder will fail to correctly call the destructor of the non AutoInstantiating Base PBNI Class
 - To be able to have Methods that are not exposed to the Users

Though it can still be useful to inherit the PBNI Class while developing, so you don't have to copy the Method Signatures

