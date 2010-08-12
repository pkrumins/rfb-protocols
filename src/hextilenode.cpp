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
    target->Set(String::NewSymbol("Hextile"), t->GetFunction());
}

HextileNode::HextileNode(int wwidth, int hheight)
    : hextile(wwidth, hheight) {}

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
HextileNode::DecodeSync(const Arguments &args)
{
    HandleScope scope;

    HextileNode *hex = ObjectWrap::Unwrap<HextileNode>(args.This());
    return scope.Close(hex->DecodeSync());
}

