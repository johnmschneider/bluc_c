/**
 * File provides annotations (macros) to specify whether a pointer
 *  is managed by the class, or managed by the caller of
 *  the class.
 *
 * These macros currently don't do anything other than add information
 *  to the code.
 */


 /*
  * Indicates that the memory management of this pointer
  *  is managed by the calling class/function.    
  */
#define JMS_BORROWED_PTR(ptr) ptr*

/*
 * Indicates that the memory management of this pointer
 *  is managed by this class/function.
 */
#define JMS_OWNED_PTR(ptr) ptr*

/**
 * Indicates that the memory management of this pointer
 *  is being transferred to the calling function.
 */
#define JMS_XFER_PTR(ptr) ptr*