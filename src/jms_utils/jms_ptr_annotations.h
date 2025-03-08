/**
 * File provides annotations (macros) to specify whether a pointer
 *  is managed by the class, or managed by the caller of
 *  the class.
 *
 * These macros currently don't do anything other than add information
 *  to the code.
 */


 /*
  * @brief Indicates that the memory management of this pointer
  *  is managed by the calling class/function.    
  */
#define JMS_BORROWED_PTR(ptr) ptr*

/*
 * Indicates that the memory management of this pointer
 *  is managed by this class/function.
 */
#define JMS_OWNED_PTR(ptr) ptr*

/**
 * @brief Indicates that the memory management of this function pointer
 *  is managed by the calling class/function.
 * @remarks This is a special case for function pointers. Because *of course* it has to be different.
 */
#define JMS_OWNED_FPTR(returnType, funcName, arguments) returnType (*ptr) (arguments)

/**
 * @brief Indicates that the memory management of this pointer
 *  is being transferred to the calling function.
 */
#define JMS_XFER_PTR(ptr) ptr*