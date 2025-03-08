#ifndef STATIC_CTORS_DTORS_H
#define STATIC_CTORS_DTORS_H

/**
 * Runs the static constructors of *all* classes that have static constructors.
 */
void jms_static_ctors_run(void);

/**
 * Runs the static destructors of *all* classes that have static destructors.
 */
void jms_static_dtors_run(void);

#endif