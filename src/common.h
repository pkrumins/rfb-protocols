#ifndef COMMON_H
#define COMMON_H

#include <v8.h>

v8::Handle<v8::Value> ErrorException(const char *msg);
v8::Handle<v8::Value> VException(const char *msg);

#endif

