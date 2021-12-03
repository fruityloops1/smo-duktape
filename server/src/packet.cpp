#include "types.h"
#include <cstring>
#include <packet.h>

#include <arpa/inet.h>
#include <iostream>
#include <unordered_map>

void smo::InPacketLog::parse(const u8* data, u32 len)
{
    type = (LogType) data[0];
    message = std::string(data + 1, data + len);
}

void smo::InPacketLog::on(smo::Client &sender, smo::Server& server)
{
    static const std::unordered_map<LogType, std::string> logTypeStrings =
        { {LogType::Log, "LOG"}, {LogType::Warning, "WARNING"}, {LogType::Error, "ERROR"}, {LogType::Fatal, "FATAL"} };
    
    struct in_addr ip;
    ip.s_addr = sender.addr;
    const char* ipString = inet_ntoa(ip);
    
    if (sender.name.empty())
        std::cout << "[" << logTypeStrings.at(type) << "] <" << ipString << ">: " << message << std::endl;
    else
        std::cout << "[" << logTypeStrings.at(type) << "] <" << sender.name << ">: " << message << std::endl;
}