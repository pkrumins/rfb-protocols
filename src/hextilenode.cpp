#include "common.h"
#include "hextilenode.h"

using namespace v8;
using namespace node;

void
HextileNode::Initialize(Handle<Object> target)
{
    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(New);
    t->InstanceTemplate()->SetInternalFieldCount(1);
    NODE_SET_PROTOTYPE_METHOD(t, "decodeSync", DecodeSync);
    NODE_SET_PROTOTYPE_METHOD(t, "setBackground", SetBackground);
    NODE_SET_PROTOTYPE_METHOD(t, "setForeground", SetForeground);
    NODE_SET_PROTOTYPE_METHOD(t, "rect", Rect);
    NODE_SET_PROTOTYPE_METHOD(t, "colorRect", ColorRect);
    NODE_SET_PROTOTYPE_METHOD(t, "fgbgRect", FgBgRect);
    target->Set(String::NewSymbol("Hextile"), t->GetFunction());
}

HextileNode::HextileNode(int wwidth, int hheight)
    : hextile(wwidth, hheight) {}

void
HextileNode::SetBackground(unsigned int color)
{
    hextile.set_background(color);
}

void
HextileNode::SetForeground(unsigned int color)
{
    hextile.set_foreground(color);
}

void
HextileNode::Rect(unsigned char *buf, int len, int x, int y, int w, int h)
{
    hextile.rect(buf, len, x, y, w, h);
}

void
HextileNode::ColorRect(unsigned int color, int x, int y, int w, int h)
{
    hextile.color_rect(color, x, y, w, h);
}

void
HextileNode::FgBgRect(int x, int y, int w, int h)
{
    hextile.fgbg_rect(x, y, w, h);
}

Handle<Value>
HextileNode::DecodeSync()
{
    HandleScope scope;

    hextile.decode();
    return scope.Close(Encode((char *)hextile.get(), hextile.get_len(), BINARY));
}

Handle<Value>
HextileNode::New(const Arguments &args)
{
    HandleScope scope;

    if (args.Length() < 2)
        return VException("Two arguments required - width and height.");
    if (!args[0]->IsInt32())
        return VException("First argument must be integer width.");
    if (!args[1]->IsInt32())
        return VException("Second argument must be integer height.");

    int width = args[0]->Int32Value();
    int height = args[1]->Int32Value();

    HextileNode *hex = new HextileNode(width, height);
    hex->Wrap(args.This());
    return args.This();
}

Handle<Value>
HextileNode::SetBackground(const Arguments &args)
{
    HandleScope scope;

    if (args.Length() != 1)
        return VException("One argument required - background color.");
    if (!args[0]->IsInt32())
        return VException("First argument must be integer color.");

    int color = args[0]->Int32Value();

    HextileNode *hex = ObjectWrap::Unwrap<HextileNode>(args.This());
    hex->SetBackground(color);

    return Undefined();
}

Handle<Value>
HextileNode::SetForeground(const Arguments &args)
{
    HandleScope scope;

    if (args.Length() != 1)
        return VException("One argument required - foreground color.");
    if (!args[0]->IsInt32())
        return VException("First argument must be integer color.");

    int color = args[0]->Int32Value();

    HextileNode *hex = ObjectWrap::Unwrap<HextileNode>(args.This());
    hex->SetForeground(color);

    return Undefined();
}

Handle<Value>
HextileNode::Rect(const Arguments &args)
{
    HandleScope scope;

    if (args.Length() != 5)
        return VException("Five arguments required - buffer, x, y, w, h.");

    if (!Buffer::HasInstance(args[0]))
        return VException("First argument must be Buffer.");
    if (!args[1]->IsInt32())
        return VException("Second argument must be integer x.");
    if (!args[2]->IsInt32())
        return VException("Third argument must be integer y.");
    if (!args[3]->IsInt32())
        return VException("Fourth argument must be integer w.");
    if (!args[4]->IsInt32())
        return VException("Fifth argument must be integer h.");

    HextileNode *hex = ObjectWrap::Unwrap<HextileNode>(args.This());
    Buffer *buf = ObjectWrap::Unwrap<Buffer>(args[0]->ToObject());
    int x = args[1]->Int32Value();
    int y = args[2]->Int32Value();
    int w = args[3]->Int32Value();
    int h = args[4]->Int32Value();

    hex->Rect((unsigned char *)buf->data(), buf->length(), x, y, w, h);

    return Undefined();
}

Handle<Value>
HextileNode::ColorRect(const Arguments &args)
{
    HandleScope scope;

    if (args.Length() != 5)
        return VException("Five arguments required - color, x, y, w, h.");

    if (!args[0]->IsInt32())
        return VException("First argument must be integer pixel color.");
    if (!args[1]->IsInt32())
        return VException("Second argument must be integer x.");
    if (!args[2]->IsInt32())
        return VException("Third argument must be integer y.");
    if (!args[3]->IsInt32())
        return VException("Fourth argument must be integer w.");
    if (!args[4]->IsInt32())
        return VException("Fifth argument must be integer h.");

    HextileNode *hex = ObjectWrap::Unwrap<HextileNode>(args.This());
    int color = args[0]->Int32Value();
    int x = args[1]->Int32Value();
    int y = args[2]->Int32Value();
    int w = args[3]->Int32Value();
    int h = args[4]->Int32Value();

    hex->ColorRect(color, x, y, w, h);

    return Undefined();
}

Handle<Value>
HextileNode::FgBgRect(const Arguments &args)
{
    HandleScope scope;

    if (args.Length() != 4)
        return VException("Four arguments required - x, y, w, h.");

    if (!args[0]->IsInt32())
        return VException("First argument must be integer x.");
    if (!args[1]->IsInt32())
        return VException("Second argument must be integer y.");
    if (!args[2]->IsInt32())
        return VException("Third argument must be integer w.");
    if (!args[3]->IsInt32())
        return VException("Fourth argument must be integer h.");

    HextileNode *hex = ObjectWrap::Unwrap<HextileNode>(args.This());
    int x = args[0]->Int32Value();
    int y = args[1]->Int32Value();
    int w = args[2]->Int32Value();
    int h = args[3]->Int32Value();

    hex->FgBgRect(x, y, w, h);

    return Undefined();
}

Handle<Value>
HextileNode::DecodeSync(const Arguments &args)
{
    HandleScope scope;

    HextileNode *hex = ObjectWrap::Unwrap<HextileNode>(args.This());
    return scope.Close(hex->DecodeSync());
}

