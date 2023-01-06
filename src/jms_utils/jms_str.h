#ifndef JMS_STR_H
#define JMS_STR_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct jms_str;
typedef struct jms_str jms_str;

/**
 * @brief creates a *deep copy* of string *source* and
 *  wraps it around the string class
 */
jms_str*    jms_str_init(const char* source);
void        jms_str_del(jms_str* self);


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
 *  is managed by the string class, do not free.
 */
char*       jms_str_cStr(jms_str* self);

/**
 * @brief returns whether the values of the two strings are the same
 */
bool        jms_str_eq_s(jms_str* self, jms_str* other);

/**
 * @brief returns the underlying c string
 */
bool        jms_str_eq_cStr(jms_str* self, const char* other);


char        jms_str_charAt(jms_str* self, int32_t index);

/**
 * @brief resizes the string and sets the value to newValue
 */
void        jms_str_set_cStr(jms_str* self, const char* newValue);

#endif