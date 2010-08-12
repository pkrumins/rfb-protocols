#ifndef HEXTILENODE_H
#define HEXTILENODE_H

#include <node.h>
#include <node_buffer.h>

#include "hextile.h"

class HextileNode : public node::ObjectWrap {
    HextileDecoder hextile;

public:
    static void Initialize(v8::Handle<v8::Object> target);
    HextileNode(int wwidth, int hheight);
    ~HextileNode();

    void SetBackground(unsigned int color);
    void SetForeground(unsigned int color);
    void Rect(unsigned char *buf, int len, int x, int y, int w, int h);
    void ColorRect(unsigned int color, int x, int y, int w, int h);
    void FgBgRect(int x, int y, int w, int h);
    v8::Handle<v8::Value> DecodeSync();

    static v8::Handle<v8::Value> New(const v8::Arguments &args);
    static v8::Handle<v8::Value> SetBackground(const v8::Arguments &args);
    static v8::Handle<v8::Value> SetForeground(const v8::Arguments &args);
    static v8::Handle<v8::Value> Rect(const v8::Arguments &args);
    static v8::Handle<v8::Value> ColorRect(const v8::Arguments &args);
    static v8::Handle<v8::Value> FgBgRect(const v8::Arguments &args);
    static v8::Handle<v8::Value> DecodeSync(const v8::Arguments &args);
};

#endif

