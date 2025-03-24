#ifndef JMS_STR_H
#define JMS_STR_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "jms_ptr_annotations.h"
#include "jms_stdint.h"

struct jms_str;
typedef struct jms_str jms_str;

/**
 * @brief creates a *deep copy* of string *initialValue* and
 *  and manages the pointer for the deep copy.
 */
jms_str*    jms_str_init(
                JMS_BORROWED_PTR(const char) initialValue);

/**
 * @brief creates a *deep copy* of string *initialValue* and
 *  and manages the pointer for the deep copy.
 */
jms_str*    jms_str_init_str(
                JMS_BORROWED_PTR(jms_str) initialValue);

void        jms_str_del(
                JMS_OWNED_PTR(jms_str) self);


/**
 * @brief returns the length of the string (NOT including
 *  null term)
 */
size_t      jms_str_len(jms_str* self);

/**
 * @brief append string - appends thingToAppend to the end of self. 
 *  calling function is responsible for free'ing thingToAppend.
 */
void        jms_str_append_s(jms_str* self, jms_str* thingToAppend);

/**
 * @brief append c string - appends cStr to the end of self. cStr is
 *  -not- managed by this function.
 */
void        jms_str_append_cs(jms_str* self, const char* cStr);

/**
 * @brief append char - appends thingToAppend to the end of self
 */
void        jms_str_append_ch(jms_str* self, char thingToAppend);

/**
 * @brief returns the raw c string pointer for this string. this pointer
 *  is managed by the string class, do not free it.
 */
JMS_BORROWED_PTR(char)  jms_str_cStr(jms_str* self);

/**
 * @brief returns whether or not the values of the two strings are the same
 */
bool        jms_str_eq_s(jms_str* self, jms_str* other);

/**
 * @brief returns whether or not the values of the string and the c string are the same
 */
bool        jms_str_eq_cStr(jms_str* self, const char* other);

/**
 * @brief returns the char at the specified index.
 */
char        jms_str_charAt(jms_str* self, int32_t index);

/**
 * @brief resizes the string and sets the value to newValue
 */
void        jms_str_set_cStr(jms_str* self, const char* newValue);

/**
 * @brief Returns whether the string is an empty string (i.e., == "")
 */
bool        jms_str_isEmpty(jms_str* self);

/**
 * @brief Returns whether the string is a whitespace string (e.g., == " " or == "\t" or == "\n")
 */
bool        jms_str_isWhitespace(jms_str* self);

/**
 * @brief Returns whether the string is empty or consists entirely of whitespace
 */
bool        jms_str_isEmptyOrWhitespace(jms_str* self);

/**
 * @brief Returns a substring of the string from start to end (inclusive)
 */
JMS_XFER_PTR(jms_str) jms_str_substr(jms_str* self, ui32 startIndex, ui32 endIndex);

#endif