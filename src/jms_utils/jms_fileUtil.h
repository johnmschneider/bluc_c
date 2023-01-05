#ifndef JMS_FILE_UTIL_H
#define JMS_FILE_UTIL_H
#include "jms_str.h"

/**
 * @brief reads the file specified by filePath into a jms_str
 *  and returns it. calling function is responsible for free'ing
 *  the jms_str
 */
jms_str* jms_readFile(const char* filePath);

#endif