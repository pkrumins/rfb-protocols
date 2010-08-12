#include <node.h>

#include "hextilenode.h"

using namespace v8;

extern "C" void
init(Handle<Object> target)
{
    HandleScope scope;

    Hextile::Initialize(target);
}

