#include "duktape/duk_config.h"
#include "duktape/duktape.h"
#include "fl/server.h"
#include "nn/mem.h"
#include <fl/scripting/scripting.h>
#include <fl/logger.h>
#include <nn/init.h>

namespace fl { namespace scripting
{

    void* dmalloc(void* udata, duk_size_t size)
    {
        if (allocator)
            return allocator->Allocate(size);
        return nullptr;
    }

    void* drealloc(void* udata, void* ptr, duk_size_t size)
    {
        if (allocator)
            return allocator->Reallocate(ptr, size);
        return nullptr;
    }

    void dfree(void* udata, void* ptr)
    {
        if (allocator)
            allocator->Free(ptr);
    }

    void fatal(void* udata, const char* msg)
    {

    }

    void Engine::init()
    {
        allocator = nn::init::GetAllocator();
        mainCtx = duk_create_heap(dmalloc, drealloc, dfree, udata, fatal);
    }

    void Engine::eval(const char* source)
    {
        duk_eval_string(mainCtx, source);
        duk_pop(mainCtx);
    }

    const char* Engine::test() // free return value or leak
    {
        eval("function update() {return \"Hello from JS\";}");
        duk_get_global_string(mainCtx, "update");
        duk_call(mainCtx, 0);
        const char* rv = duk_get_string(mainCtx, -1);
        duk_pop(mainCtx);
        return rv;
    }

}
}