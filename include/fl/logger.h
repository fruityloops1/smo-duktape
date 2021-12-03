#pragma once

#include <fl/server.h>

namespace smo
{
    void log(Server& server, const char* message, OutPacketLog::LogType type);
}