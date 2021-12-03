#pragma once

#include <nn/mem.h>
#include <duktape/duktape.h>

namespace fl { namespace scripting
{

    class Engine
    {
    private:
        void eval(const char* source);

        duk_context* mainCtx;
        void* udata = nullptr;
        bool run = false;
    public:
        void init();
        const char* test();
    };
    
    static nn::mem::StandardAllocator* allocator = nullptr;
    static void fatal(void* udata, const char* msg);
}
}