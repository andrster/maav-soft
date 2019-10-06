// THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
// BY HAND!!
//
// Generated by lcm-gen

#include "tanfan/messaging/dji_t.h"
#include <string.h>

static int __dji_t_hash_computed;
static uint64_t __dji_t_hash;

uint64_t __dji_t_hash_recursive(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == __dji_t_get_hash) return 0;

    __lcm_hash_ptr cp;
    cp.parent = p;
    cp.v = (void *)__dji_t_get_hash;
    (void)cp;

    uint64_t hash = (uint64_t)0x224b3eb1f5267c30LL + __float_hash_recursive(&cp) +
                    __float_hash_recursive(&cp) + __float_hash_recursive(&cp) +
                    __float_hash_recursive(&cp);

    return (hash << 1) + ((hash >> 63) & 1);
}

int64_t __dji_t_get_hash(void)
{
    if (!__dji_t_hash_computed)
    {
        __dji_t_hash = (int64_t)__dji_t_hash_recursive(NULL);
        __dji_t_hash_computed = 1;
    }

    return __dji_t_hash;
}

int __dji_t_encode_array(void *buf, int offset, int maxlen, const dji_t *p, int elements)
{
    int pos = 0, element;
    int thislen;

    for (element = 0; element < elements; element++)
    {
        thislen = __float_encode_array(buf, offset + pos, maxlen - pos, &(p[element].roll), 1);
        if (thislen < 0)
            return thislen;
        else
            pos += thislen;

        thislen = __float_encode_array(buf, offset + pos, maxlen - pos, &(p[element].pitch), 1);
        if (thislen < 0)
            return thislen;
        else
            pos += thislen;

        thislen = __float_encode_array(buf, offset + pos, maxlen - pos, &(p[element].yaw), 1);
        if (thislen < 0)
            return thislen;
        else
            pos += thislen;

        thislen = __float_encode_array(buf, offset + pos, maxlen - pos, &(p[element].thrust), 1);
        if (thislen < 0)
            return thislen;
        else
            pos += thislen;
    }
    return pos;
}

int dji_t_encode(void *buf, int offset, int maxlen, const dji_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __dji_t_get_hash();

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if (thislen < 0)
        return thislen;
    else
        pos += thislen;

    thislen = __dji_t_encode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0)
        return thislen;
    else
        pos += thislen;

    return pos;
}

int __dji_t_encoded_array_size(const dji_t *p, int elements)
{
    int size = 0, element;
    for (element = 0; element < elements; element++)
    {
        size += __float_encoded_array_size(&(p[element].roll), 1);

        size += __float_encoded_array_size(&(p[element].pitch), 1);

        size += __float_encoded_array_size(&(p[element].yaw), 1);

        size += __float_encoded_array_size(&(p[element].thrust), 1);
    }
    return size;
}

int dji_t_encoded_size(const dji_t *p) { return 8 + __dji_t_encoded_array_size(p, 1); }
int __dji_t_decode_array(const void *buf, int offset, int maxlen, dji_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++)
    {
        thislen = __float_decode_array(buf, offset + pos, maxlen - pos, &(p[element].roll), 1);
        if (thislen < 0)
            return thislen;
        else
            pos += thislen;

        thislen = __float_decode_array(buf, offset + pos, maxlen - pos, &(p[element].pitch), 1);
        if (thislen < 0)
            return thislen;
        else
            pos += thislen;

        thislen = __float_decode_array(buf, offset + pos, maxlen - pos, &(p[element].yaw), 1);
        if (thislen < 0)
            return thislen;
        else
            pos += thislen;

        thislen = __float_decode_array(buf, offset + pos, maxlen - pos, &(p[element].thrust), 1);
        if (thislen < 0)
            return thislen;
        else
            pos += thislen;
    }
    return pos;
}

int __dji_t_decode_array_cleanup(dji_t *p, int elements)
{
    int element;
    for (element = 0; element < elements; element++)
    {
        __float_decode_array_cleanup(&(p[element].roll), 1);

        __float_decode_array_cleanup(&(p[element].pitch), 1);

        __float_decode_array_cleanup(&(p[element].yaw), 1);

        __float_decode_array_cleanup(&(p[element].thrust), 1);
    }
    return 0;
}

int dji_t_decode(const void *buf, int offset, int maxlen, dji_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __dji_t_get_hash();

    int64_t this_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this_hash, 1);
    if (thislen < 0)
        return thislen;
    else
        pos += thislen;
    if (this_hash != hash) return -1;

    thislen = __dji_t_decode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0)
        return thislen;
    else
        pos += thislen;

    return pos;
}

int dji_t_decode_cleanup(dji_t *p) { return __dji_t_decode_array_cleanup(p, 1); }
int __dji_t_clone_array(const dji_t *p, dji_t *q, int elements)
{
    int element;
    for (element = 0; element < elements; element++)
    {
        __float_clone_array(&(p[element].roll), &(q[element].roll), 1);

        __float_clone_array(&(p[element].pitch), &(q[element].pitch), 1);

        __float_clone_array(&(p[element].yaw), &(q[element].yaw), 1);

        __float_clone_array(&(p[element].thrust), &(q[element].thrust), 1);
    }
    return 0;
}

dji_t *dji_t_copy(const dji_t *p)
{
    dji_t *q = (dji_t *)malloc(sizeof(dji_t));
    __dji_t_clone_array(p, q, 1);
    return q;
}

void dji_t_destroy(dji_t *p)
{
    __dji_t_decode_array_cleanup(p, 1);
    free(p);
}
