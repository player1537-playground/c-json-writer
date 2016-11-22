#include "json_writer.h"
#include <stdio.h>


void
json_writer_init(struct json_writer *ctx, FILE *f) {
  ctx->f = f;
  ctx->depth = 0;
  ctx->in_array[ctx->depth] = 0;
  ctx->index[ctx->depth] = 0;
}


void
json_writer_finalize(struct json_writer *ctx) {
  ctx->f = NULL;
}


void
json_writer_open(struct json_writer *ctx) {
  fprintf(ctx->f, "{");
  ctx->depth++;
  ctx->index[ctx->depth] = 0;
  ctx->in_array[ctx->depth] = 0;
}


void
json_writer_close(struct json_writer *ctx) {
  if (ctx->index[ctx->depth] != 0) {
    fprintf(ctx->f, "\n");
  }
  ctx->depth--;
  if (ctx->index[ctx->depth] != 0) {
    json_writer_indent(ctx);
  }
  fprintf(ctx->f, "}");
}


void
json_writer_indent(struct json_writer *ctx) {
  int i;

  for (i=0; i<ctx->depth; ++i) {
    fprintf(ctx->f, "  ");
  }
}


void
json_writer_key(struct json_writer *ctx, char *key) {
  if (ctx->index[ctx->depth] != 0) {
    fprintf(ctx->f, ",");
  }
  fprintf(ctx->f, "\n");
  json_writer_indent(ctx);
  fprintf(ctx->f, "\"%s\": ", key);
  ctx->index[ctx->depth]++;
}


void
json_writer_d(struct json_writer *ctx, int value) {
  if (ctx->in_array[ctx->depth]) {
    if (ctx->index[ctx->depth] != 0) {
      fprintf(ctx->f, ",");
    }
    fprintf(ctx->f, "\n");
    json_writer_indent(ctx);
    ctx->index[ctx->depth]++;
  }
  fprintf(ctx->f, "%d", value);
}


void
json_writer_s(struct json_writer *ctx, char *value) {
  if (ctx->in_array[ctx->depth]) {
    if (ctx->index[ctx->depth] != 0) {
      fprintf(ctx->f, ",");
      fprintf(ctx->f, "\n");
      json_writer_indent(ctx);
    }
    ctx->index[ctx->depth]++;
  }
  fprintf(ctx->f, "\"%s\"", value);
}


void
json_writer_f(struct json_writer *ctx, float value) {
  if (ctx->in_array[ctx->depth]) {
    if (ctx->index[ctx->depth] != 0) {
      fprintf(ctx->f, ",");
      fprintf(ctx->f, "\n");
      json_writer_indent(ctx);
    }
    ctx->index[ctx->depth]++;
  }
  fprintf(ctx->f, "%g", value);
}


void
json_writer_lf(struct json_writer *ctx, double value) {
  if (ctx->in_array[ctx->depth]) {
    if (ctx->index[ctx->depth] != 0) {
      fprintf(ctx->f, ",");
      fprintf(ctx->f, "\n");
      json_writer_indent(ctx);
    }
    ctx->index[ctx->depth]++;
  }
  fprintf(ctx->f, "%lg", value);
}


void
json_writer_array_start(struct json_writer *ctx) {
  fprintf(ctx->f, "[");
  ctx->depth++;
  ctx->index[ctx->depth] = 0;
  ctx->in_array[ctx->depth] = 1;
}


void
json_writer_array_end(struct json_writer *ctx) {
  if (ctx->index[ctx->depth] != 0) {
    fprintf(ctx->f, "\n");
  }
  ctx->depth--;
  if (ctx->index[ctx->depth] != 0) {
    json_writer_indent(ctx);
  }
  fprintf(ctx->f, "]");
}
