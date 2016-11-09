#include "../json_writer.h"
#include "../json_writer_helper.h"
#include <tap.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


void
test_helper_empty_object(void) {
  char *expected = "{}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");

  JSON_WRAP(&ctx, f) {
    JSON_OBJECT() {

    }
  }

  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


void
test_helper_one_key_object(void) {
  char *expected = "{\n  \"foo\": 123\n}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");

  JSON_WRAP(&ctx, f) {
    JSON_OBJECT() {
      JSON_KEY_VALUE("foo", 123);
    }
  }

  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


void
test_helper_two_key_object(void) {
  char *expected = "{\n  \"foo\": 123,\n  \"bar\": \"baz\"\n}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");

  JSON_WRAP(&ctx, f) {
    JSON_OBJECT() {
      JSON_KEY_VALUE("foo", 123);
      JSON_KEY_VALUE("bar", "baz");
    }
  }

  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


void
test_helper_one_element_array(void) {
  char *expected = "{\n  \"foo\": [\n    123\n  ]\n}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");


  JSON_WRAP(&ctx, f) {
    JSON_OBJECT() {
      JSON_KEY("foo");
      JSON_ARRAY() {
        JSON_VALUE(123);
      }
    }
  }

  json_writer_finalize(&ctx);
  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


void
test_helper_two_element_array(void) {
  char *expected = "{\n  \"foo\": [\n    123,\n    456\n  ]\n}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");

  JSON_WRAP(&ctx, f) {
    JSON_OBJECT() {
      JSON_KEY("foo");
      JSON_ARRAY() {
        JSON_VALUE(123);
        JSON_VALUE(456);
      }
    }
  }

  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


void
test_helper_simple_nested_object(void) {
  char *expected = "{\n  \"foo\": {\n    \"bar\": 123\n  }\n}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");

  JSON_WRAP(&ctx, f) {
    JSON_OBJECT() {
      JSON_KEY("foo");
      JSON_OBJECT() {
        JSON_KEY_VALUE("bar", 123);
      }
    }
  }

  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


void
test_helper_complex_nested_object(void) {
  char *expected = \
    "{\n  \"foo\": {\n    \"bar\": 123,\n"
    "    \"ping\": \"pong\"\n  },\n  \"key\": 456\n}";
  struct json_writer ctx;
  FILE *f;
  char buffer[128];

  diag("---[ %s ]---", __func__);

  memset(buffer, 0x00, sizeof(buffer));
  f = fmemopen(buffer, sizeof(buffer), "wb");

  JSON_WRAP(&ctx, f) {
    JSON_OBJECT() {
      JSON_KEY("foo");
      JSON_OBJECT() {
        JSON_KEY_VALUE("bar", 123);
        JSON_KEY_VALUE("ping", "pong");
      }

      JSON_KEY_VALUE("key", 456);
    }
  }

  fflush(f);
  fclose(f);

  is(buffer, expected, "should have correct output");
}


int
main(int argc, char **argv) {
  plan(NO_PLAN);
  test_helper_empty_object();
  test_helper_one_key_object();
  test_helper_two_key_object();
  test_helper_one_element_array();
  test_helper_two_element_array();
  test_helper_simple_nested_object();
  test_helper_complex_nested_object();
  done_testing();
}
