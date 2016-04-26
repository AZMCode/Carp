#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include "types.h"
#include "platform.h"

#ifdef WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

typedef int unknown;
typedef void* typevar;
typedef void* any;

typedef char* string;

EXPORT int intsqrt(int x) { return (int)sqrt(x); }
EXPORT float itof(int x) { return (float)x; }
EXPORT float dtof(double x) { return (float)x; }
EXPORT double ftod(float x) { return (double)x; }

#ifdef max
#undef max
#endif
EXPORT int max(int x, int y) {
  return x > y ? x : y;
}

EXPORT string itos(int x) {
  char *s = malloc(sizeof(char) * 32);
  snprintf(s, 32, "%d", x);
  return s;
}

EXPORT bool nullQMARK(void *p) {
  return p == NULL;
}

EXPORT bool not(bool x) {
  return !x;
}

EXPORT void panicBANG(string msg) {
  printf("Error: %s\n", msg);
  exit(1);
}

EXPORT void print(string msg) {
  printf("%s", msg);
}

EXPORT void println(string msg) {
  assert(msg);
  printf("%s\n", msg);
}

// This function is used for testing of the ownership system
EXPORT void eat_string(char *s) {
  free(s);
}

EXPORT char *string_copy(char *s) {
  return strdup(s);
}

EXPORT char *string_append(char *s1, char *s2) {
  char *new_str = malloc(strlen(s1) + strlen(s2) + 1);
  new_str[0] = '\0';
  strcat(new_str, s1);
  strcat(new_str, s2);
  return new_str;
}

EXPORT bool file_existsQMARK(char *filename) {
  FILE *f = fopen(filename, "r");
  bool result = f != NULL;
  if(result) {
    fclose(f);
  }
  return result;
}

EXPORT int inc(x) { return x + 1; }
EXPORT int dec(x) { return x - 1; }

EXPORT void async(void *f) {
  //printf("Async starting.\n");
  carp_thread_t th = carp_thread_create(f, "Async");
  carp_thread_destroy(th);
  //printf("Async done.\n");
}

EXPORT int last_index_of(string s, char c) {
  int len = (int)strlen(s);
  for(int i = len - 1; i >= 0; i--) {
    if(s[i] == c) {
      return i;
    }
  }
  return -1;
}

EXPORT string substring(string s, int index) {
  if(index >= strlen(s)) {
    panicBANG("substring out of bounds");
  }
  const char *sub = s + index;
  return strdup(sub);
}

EXPORT string file_path_component(string s) {
  int i = last_index_of(s, '/');
  return substring(s, i + 1);
}

EXPORT string get_input() {
  char in[1024];
  fgets(in, 1024, stdin);
  return strdup(in);
}

EXPORT int mod(int x, int y) {
  return x % y;
}

#ifdef WIN32
EXPORT void sleep(int millis) {
  carp_sleep(millis);
}
#endif

EXPORT CARP_PLATFORM platform() {
	return carp_get_platform();
}

EXPORT string get_normal_console_color() {
  #ifdef WIN32
  return strdup("");
  #else
  return strdup("\e[0m");
  #endif
}

EXPORT string get_console_color(int x) {
  #ifdef WIN32
  return strdup("");
  #else
  char buffer[16];
  snprintf(buffer, 16, "\e[3%dm", x);
  return strdup(buffer);
  #endif
}
