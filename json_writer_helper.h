#ifndef _JSON_WRITER_HELPER_H_
#define _JSON_WRITER_HELPER_H_

#include "mp.h"


#define JSON_WRAP(ctx_pointer, f)                               \
  MPP_DECLARE(1, struct json_writer *_ctx_p = (ctx_pointer))    \
  MPP_BEFORE(2, json_writer_init(_ctx_p, f))                    \
  MPP_AFTER(3, json_writer_finalize(_ctx_p))


#define JSON_OBJECT()                           \
  MPP_BEFORE(1, json_writer_open(_ctx_p))       \
  MPP_AFTER(2, json_writer_close(_ctx_p))


#define JSON_ARRAY()                                    \
  MPP_BEFORE(1, json_writer_array_start(_ctx_p))        \
  MPP_AFTER(2, json_writer_array_end(_ctx_p))


#define JSON_KEY(key)                           \
  json_writer_key(_ctx_p, (key))


#define JSON_KEY_VALUE(key, value)              \
  do {                                          \
    JSON_KEY((key));                            \
    JSON_VALUE((value));                        \
  } while (0)


#define JSON_VALUE(value)                       \
  _Generic((value),                             \
           char*: json_writer_s,                \
           int: json_writer_d,                  \
           float: json_writer_f,                \
           double: json_writer_lf               \
           )(_ctx_p, (value))


#endif
