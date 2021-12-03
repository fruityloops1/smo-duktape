#include "sead/prim/seadSafeString.h"
#include <fl/packet.h>
#include <str.h>
#include <mem.h>

namespace smo
{
    u32 OutPacketLog::calcLen()
    {
        return strlen(message) + 1;
    }

    void OutPacketLog::construct(u8* dst)
    {
        *dst = type;
        strcpy((char*) dst + 1, message);
    }
}