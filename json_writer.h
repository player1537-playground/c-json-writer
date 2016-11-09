#ifndef _JSON_WRITER_H_
#define _JSON_WRITER_H_

#include <stdio.h>


#define JSON_WRITER_MAX_DEPTH 10


struct json_writer {
  FILE *f;
  int depth;
  int index[JSON_WRITER_MAX_DEPTH];
  int in_array[JSON_WRITER_MAX_DEPTH];
};


void
json_writer_init(struct json_writer *ctx, FILE *f);


void
json_writer_finalize(struct json_writer *ctx);


void
json_writer_open(struct json_writer *ctx);


void
json_writer_close(struct json_writer *ctx);


void
json_writer_indent(struct json_writer *ctx);


void
json_writer_key(struct json_writer *ctx, char *key);


void
json_writer_d(struct json_writer *ctx, int value);


void
json_writer_s(struct json_writer *ctx, char *value);


void
json_writer_array_start(struct json_writer *ctx);


void
json_writer_array_end(struct json_writer *ctx);


#endif
