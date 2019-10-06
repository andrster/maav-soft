// THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
// BY HAND!!
//
// Generated by lcm-gen

#include <stdint.h>
#include <stdlib.h>
#include "lcm_coretypes.h"

#ifndef _emergency_t_h
#define _emergency_t_h

#ifdef __cplusplus
extern "C" {
#endif

#define EMERGENCY_T_NORMAL 0
#define EMERGENCY_T_LOW_BATTERY 1
#define EMERGENCY_T_KILL 2

typedef struct _emergency_t emergency_t;
struct _emergency_t
{
    int8_t status;
};

/**
 * Create a deep copy of a emergency_t.
 * When no longer needed, destroy it with emergency_t_destroy()
 */
emergency_t *emergency_t_copy(const emergency_t *to_copy);

/**
 * Destroy an instance of emergency_t created by emergency_t_copy()
 */
void emergency_t_destroy(emergency_t *to_destroy);

/**
 * Encode a message of type emergency_t into binary form.
 *
 * @param buf The output buffer.
 * @param offset Encoding starts at this byte offset into @p buf.
 * @param maxlen Maximum number of bytes to write.  This should generally
 *               be equal to emergency_t_encoded_size().
 * @param msg The message to encode.
 * @return The number of bytes encoded, or <0 if an error occured.
 */
int emergency_t_encode(void *buf, int offset, int maxlen, const emergency_t *p);

/**
 * Decode a message of type emergency_t from binary form.
 * When decoding messages containing strings or variable-length arrays, this
 * function may allocate memory.  When finished with the decoded message,
 * release allocated resources with emergency_t_decode_cleanup().
 *
 * @param buf The buffer containing the encoded message
 * @param offset The byte offset into @p buf where the encoded message starts.
 * @param maxlen The maximum number of bytes to read while decoding.
 * @param msg Output parameter where the decoded message is stored
 * @return The number of bytes decoded, or <0 if an error occured.
 */
int emergency_t_decode(const void *buf, int offset, int maxlen, emergency_t *msg);

/**
 * Release resources allocated by emergency_t_decode()
 * @return 0
 */
int emergency_t_decode_cleanup(emergency_t *p);

/**
 * Check how many bytes are required to encode a message of type emergency_t
 */
int emergency_t_encoded_size(const emergency_t *p);

// LCM support functions. Users should not call these
int64_t __emergency_t_get_hash(void);
int64_t __emergency_t_hash_recursive(const __lcm_hash_ptr *p);
int __emergency_t_encode_array(
    void *buf, int offset, int maxlen, const emergency_t *p, int elements);
int __emergency_t_decode_array(
    const void *buf, int offset, int maxlen, emergency_t *p, int elements);
int __emergency_t_decode_array_cleanup(emergency_t *p, int elements);
int __emergency_t_encoded_array_size(const emergency_t *p, int elements);
int __emergency_t_clone_array(const emergency_t *p, emergency_t *q, int elements);

#ifdef __cplusplus
}
#endif

#endif
