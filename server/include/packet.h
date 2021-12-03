#pragma once

#include <string>
#include <types.h>
#include <unordered_map>
#include <vector>
#include <server.h>

namespace smo
{
    class Client;
    class Server;
    enum class InPacketType : u8
    {
        DummyInit = 0, Init = 1, Log = 2
    };
    
    class InPacket
    {
    public:
        virtual void parse(const u8* data, u32 len) {}
        virtual void on(smo::Client& sender, smo::Server& server) {}
    };

    enum class OutPacketType : u8
    {
        
    };
    
    class OutPacket
    {
    public:
        virtual u32 calcLen() {return 0;}
        virtual void construct(u8* dst) {}
    };

    class InPacketLog : public InPacket
    {
        enum LogType : u8
        {
            Log = 0, Warning = 1, Error = 2, Fatal = 3
        };
        LogType type;
        std::string message;
    public:
        void parse(const u8* data, u32 len);
        void on(smo::Client& sender, smo::Server& server);
    };
}