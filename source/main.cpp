#include "fl/packet.h"
#include "sead/prim/seadSafeString.h"
#include <al/util.hpp>
#include <game/StageScene.hpp>

#include <fl/logger.h>
#include <fl/scripting/scripting.h>
#include <mem.h>
#include <nn/os.hpp>

void threadFunc(void* args)
{
    smo::Server* server = (smo::Server*) args;
    nn::TimeSpan w = nn::TimeSpan::FromNanoSeconds(1000000);
    while (true)
    {
        server->handlePacket();
        nn::os::YieldThread();
        nn::os::SleepThread(w);
    }
}

void stageSceneHook() {

    __asm ("MOV X19, X0");

    StageScene* stageScene;
    __asm ("MOV %[result], X0" : [result] "=r" (stageScene));

    static fl::scripting::Engine engine;
    smo::Server& server = smo::Server::instance();
    static bool init = false;
    if (!init)
    {
        server.connect("192.168.188.109", 7901);
        nn::os::ThreadType* thread = (nn::os::ThreadType*) aligned_alloc(4, sizeof(nn::os::ThreadType));
        const u32 stackSize = 0x5000;
        void* threadStack = aligned_alloc(0x1000, stackSize);
        nn::os::CreateThread(thread, threadFunc, &server, threadStack, stackSize, 16, 0);
        nn::os::SetThreadName(thread, "UDP Thread");
        nn::os::StartThread(thread);
        engine.init();
        init = true;
    }

    if (al::isPadTriggerPressLeftStick(-1))
    {
        smo::log(server, engine.test(), smo::OutPacketLog::LogType::Log);
    }
    
    __asm ("MOV X0, %[input]" : [input] "=r" (stageScene));
}
