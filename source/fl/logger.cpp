#include "duktape/duktape.h"
#include "fl/packet.h"
#include <fl/logger.h>
#include <str.h>
#include <nn/init.h>

namespace smo
{
    void log(Server& server, const char *message, OutPacketLog::LogType type)
    {
        OutPacketLog packet;
        packet.message = strdup((char*) message);
        packet.type = type;
        server.sendPacket(packet, OutPacketType::Log);
        nn::init::GetAllocator()->Free(packet.message);
    }
}