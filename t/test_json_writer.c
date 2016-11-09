#include "../json_writer.h"
#include <tap.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


void
test_empty_object(void) {
  char *expected = "{}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");
  json_writer_init(&ctx, f);

  json_writer_open(&ctx); {
  }; json_writer_close(&ctx);

  json_writer_finalize(&ctx);
  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


void
test_one_key_object(void) {
  char *expected = "{\n  \"foo\": 123\n}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");
  json_writer_init(&ctx, f);

  json_writer_open(&ctx); {

    json_writer_key(&ctx, "foo");
    json_writer_d(&ctx, 123);

  }; json_writer_close(&ctx);

  json_writer_finalize(&ctx);
  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


void
test_two_key_object(void) {
  char *expected = "{\n  \"foo\": 123,\n  \"bar\": \"baz\"\n}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");
  json_writer_init(&ctx, f);

  json_writer_open(&ctx); {

    json_writer_key(&ctx, "foo");
    json_writer_d(&ctx, 123);

    json_writer_key(&ctx, "bar");
    json_writer_s(&ctx, "baz");

  }; json_writer_close(&ctx);

  json_writer_finalize(&ctx);
  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


void
test_one_element_array(void) {
  char *expected = "{\n  \"foo\": [\n    123\n  ]\n}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");
  json_writer_init(&ctx, f);

  json_writer_open(&ctx); {

    json_writer_key(&ctx, "foo");
    json_writer_array_start(&ctx); {
      json_writer_d(&ctx, 123);
    }; json_writer_array_end(&ctx);

  }; json_writer_close(&ctx);

  json_writer_finalize(&ctx);
  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


void
test_two_element_array(void) {
  char *expected = "{\n  \"foo\": [\n    123,\n    456\n  ]\n}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");
  json_writer_init(&ctx, f);

  json_writer_open(&ctx); {

    json_writer_key(&ctx, "foo");
    json_writer_array_start(&ctx); {
      json_writer_d(&ctx, 123);
      json_writer_d(&ctx, 456);
    }; json_writer_array_end(&ctx);

  }; json_writer_close(&ctx);

  json_writer_finalize(&ctx);
  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


void
test_simple_nested_object(void) {
  char *expected = "{\n  \"foo\": {\n    \"bar\": 123\n  }\n}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");
  json_writer_init(&ctx, f);

  json_writer_open(&ctx); {

    json_writer_key(&ctx, "foo");
    json_writer_open(&ctx); {

      json_writer_key(&ctx, "bar");
      json_writer_d(&ctx, 123);

    }; json_writer_close(&ctx);

  }; json_writer_close(&ctx);

  json_writer_finalize(&ctx);
  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


void
test_complex_nested_object(void) {
  char *expected = \
    "{\n  \"foo\": {\n    \"bar\": 123,\n"
    "    \"ping\": \"pong\"\n  },\n  \"key\": 456\n}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");
  json_writer_init(&ctx, f);

  json_writer_open(&ctx); {

    json_writer_key(&ctx, "foo");
    json_writer_open(&ctx); {

      json_writer_key(&ctx, "bar");
      json_writer_d(&ctx, 123);

      json_writer_key(&ctx, "ping");
      json_writer_s(&ctx, "pong");

    }; json_writer_close(&ctx);

    json_writer_key(&ctx, "key");
    json_writer_d(&ctx, 456);

  }; json_writer_close(&ctx);

  json_writer_finalize(&ctx);
  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


int
main(int argc, char **argv) {
  plan(NO_PLAN);
  test_empty_object();
  test_one_key_object();
  test_two_key_object();
  test_one_element_array();
  test_two_element_array();
  test_simple_nested_object();
  test_complex_nested_object();
  done_testing();
}
