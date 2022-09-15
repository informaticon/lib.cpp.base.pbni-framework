# PBNI Framework - Errors
---

The PBNI Framework catches every `std::exception`, and forwards it to PowerBuilder. To be able to make descriptive Errors, the `Inf::PBNI_Exception` was created. It holds a Key-Value Store of WStrings. This Store will be passed over to PowerBuilder. The `Inf::PBNI_Exception` also adds a StackTrace Value to its store using `boost::stacktrace`.  

Here are a list of Extensions that get thrown by the Framework.

 - Inf::PBNI_IndexOutOfBounds
 - Inf::PBNI_NullPointerException
 - Inf::PBNI_InvalidFieldException
 - Inf::PBNI_IncorrectArgumentsException
 - Inf::PBNI_PowerBuilderException

You can create your own by extending Inf::PBNI_Exception.
