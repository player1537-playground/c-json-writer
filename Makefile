MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

################
# Environment Variables

ifndef CC
CC := gcc
endif

ifndef CFLAGS
CFLAGS := -std=gnu11 -Wall -Werror -pedantic -g -Ilibtap -I.
endif

ifndef LIBS
LIBS :=
endif

ifndef VALGRIND
VALGRIND := valgrind
endif

ifndef VALGRIND_FLAGS
VALGRIND_FLAGS := --leak-check=full --track-origins=yes --quiet --suppressions=macos.supp
endif

################
# Standard Targets

.PHONY: all
all:

.PHONY: test
test: test_json_writer

.PHONY: clean
clean:
	find . -name '*~' -print -delete
	rm -rf build

################
# Project Targets

.PHONY: test_json_writer
test_json_writer: build/test_json_writer
	$(VALGRIND) $(VALGRIND_FLAGS) $<

.PHONY: test_json_writer_helper
test_json_writer_helper: build/test_json_writer_helper
	$(VALGRIND) $(VALGRIND_FLAGS) $<

################
# Source Transformations

mp:
	mkdir -p $@

mp/mp.h: | mp
	wget 'http://www.chiark.greenend.org.uk/~sgtatham/mp/mp.h' -O $@


libtap:
	git submodule update $@

libtap/tap.c: | libtap

libtap/tap.h: | libtap


json_writer_helper.h: mp/mp.h


build download gen:
	mkdir -p $@

build/json_writer.o: json_writer.c json_writer.h | build
	$(CC) $(CFLAGS) -c -o $@ $(filter %.c,$^)


build/test_json_writer.o: t/test_json_writer.c json_writer.h
build/test_json_writer.o: libtap/tap.h | build
	$(CC) $(CFLAGS) -c -o $@ $(filter %.c,$^)

build/test_json_writer_helper.o: t/test_json_writer_helper.c json_writer.h
build/test_json_writer_helper.o: json_writer_helper.h libtap/tap.h | build
	$(CC) $(CFLAGS) -c -o $@ $(filter %.c,$^)

build/tap.o: libtap/tap.c libtap/tap.h | build
	$(CC) $(CFLAGS) -c -o $@ $(filter %.c,$^)


build/test_json_writer: build/test_json_writer.o build/json_writer.o
build/test_json_writer: build/tap.o | build
	$(CC) -o $@ $^ $(LIBS)


build/test_json_writer_helper: build/test_json_writer_helper.o
build/test_json_writer_helper: build/json_writer.o build/tap.o | build
	$(CC) -o $@ $^ $(LIBS)
