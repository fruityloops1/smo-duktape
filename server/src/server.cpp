#include <ratio>
#include <server.h>
#include <packet.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <thread>
#include <iostream>
#include <fstream>

#define MAX_PACKET_SIZE 0x400

#define IN_PACKET(TYPE) case smo::InPacketType::TYPE: {\
                InPacket##TYPE p;\
                p.parse(data + 1, length - 1);\
                p.on(*this, *parent);\
                break;}

namespace smo
{
    void smo::Client::connect()
    {
        struct in_addr ip;
        ip.s_addr = uid;
        std::cout << "Client connected from " << inet_ntoa(ip) << std::endl;
    }

    void smo::Client::handlePacket(Server* parent, u8* data, s32 length)
    {
        if (length < 1) return;
        switch ((InPacketType) data[0])
        {
            case smo::InPacketType::DummyInit:
            {
                break;
            }
            case smo::InPacketType::Init:
            {
                connect();
                break;
            }
            IN_PACKET(Log)
            default: break;
        }
    }

    void smo::Client::sendPacket(Server* parent, smo::OutPacket& packet, smo::OutPacketType type)
    {
        u32 len = packet.calcLen();
        u8* packetData = new u8[len + 1];
        packet.construct(packetData + 1);
        packetData[0] = (u8) type;
        sendto(parent->getSocket(), packetData, len + 1, 0, (struct sockaddr*) &client, sizeof(client));
        delete[] packetData;
    }

    bool smo::Server::disconnect(u64 uid)
    {
        if (clients.find(uid) != clients.end())
        {
            clients.erase(uid);
            return true;
        } else return false;
    }

    u8 smo::Server::start(u16 port)
    {
        struct sockaddr_in addr, cli;

        socketfd = socket(AF_INET, SOCK_DGRAM, 0);

        if (socketfd == -1) return 1;

        setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, nullptr, sizeof(int));

        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(port);

        int rval = bind(socketfd, (struct sockaddr*) &addr, sizeof(addr));
        if (rval != 0) return 2;

        listen(socketfd, 2);

        u8 buf[12288];
        s32 size = 0;

        std::thread loop(&smo::Server::loopThread, this);
        loop.detach();

        while (true)
        {
            s32 length = sizeof(cli);

            struct sockaddr_in client;
            socklen_t addrSize;

            if ((size = recvfrom(socketfd, buf, sizeof(buf), 0, (struct sockaddr *) &client, &addrSize)) < 0) continue;
            u64 uid = client.sin_addr.s_addr + client.sin_port;

            Client& c = clients[uid];
            
            c.uid = uid;
            c.addr = client.sin_addr.s_addr;
            c.client = client;
            c.handlePacket(this, buf, size);
        }

        return 0;
    }

    void smo::Server::loopThread()
    {
        using namespace std::chrono_literals;
        while (true)
        {
            std::this_thread::sleep_for(10000ms);
        }
    }

    s32 smo::Server::getSocket() {return socketfd;}
}