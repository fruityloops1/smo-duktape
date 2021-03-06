#pragma once

namespace al
{
    class LiveActor;

    class AreaObj {

    };

}

#include "sead/math/seadVector.h"
#include "sead/prim/seadSafeString.h"
#include "sead/heap/seadHeap.h"
#include "sead/controller/seadControllerMgr.h"
#include "al/scene/Scene.h"
#include "al/PlayerHolder/PlayerHolder.h"
#include "al/audio/AudioKeeper.h"
#include "al/camera/Projection.h"
#include "al/layout/IUseLayout.h"
#include "game/Player/PlayerActorHakoniwa.h"

#include "nn/ui2d/Texture.h"

#include "types.h"

namespace al
{

    // General Input functions

    bool isPadTriggerUp(int port);
    bool isPadTriggerDown(int port);
    bool isPadTriggerLeft(int port);
    bool isPadTriggerPressLeftStick(int port);
    bool isPadTriggerRight(int port);

    bool isPadTriggerA(int port);
    bool isPadTriggerB(int port);
    bool isPadTriggerX(int port);
    bool isPadTriggerY(int port);

    bool isPadTriggerZL(int port);
    bool isPadTriggerZR(int port);

    bool isPadTriggerL(int port);
    bool isPadTriggerR(int port);

    bool isPadHoldUp(int port);
    bool isPadHoldDown(int port);
    bool isPadHoldLeft(int port);
    bool isPadHoldRight(int port);

    bool isPadHoldA(int port);
    bool isPadHoldB(int port);
    bool isPadHoldX(int port);
    bool isPadHoldY(int port);

    bool isPadHoldL(int port);
    bool isPadHoldR(int port);

    bool isPadHoldZL(int port);
    bool isPadHoldZR(int port);

    sead::Vector2f *getLeftStick(int);
    sead::Vector2f *getRightStick(int);

    // getters
    
    sead::Vector3f *getTrans(al::LiveActor const *);

    sead::Vector3f *getTransPtr(al::LiveActor *);

    sead::Vector3f *getGravity(al::LiveActor const *);

    sead::Vector3f *getUp(al::LiveActor const *);

    sead::Vector3f *getUpPtr(al::LiveActor *);

    sead::Vector3f *getFront(al::LiveActor const *);

    sead::Vector3f *getCameraUp(al::IUseCamera const *, int);

    sead::Vector3f *getScale(al::LiveActor const *);

    float *getScaleX(al::LiveActor *);

    float *getScaleY(al::LiveActor *);

    float *getScaleZ(al::LiveActor *);

    al::PlayerHolder *getScenePlayerHolder(al::Scene const *);

    PlayerActorHakoniwa *getPlayerActor(al::LiveActor const *, int);

    PlayerActorHakoniwa *tryGetPlayerActor(al::PlayerHolder const *, int);

    sead::Heap *getCurrentHeap(void);

    al::Projection *getProjection(al::IUseCamera const *, int);

    int getSubActorNum(al::LiveActor const *);

    al::LiveActor *getSubActor(al::LiveActor const *, int);

    sead::Vector3f *getVelocity(al::LiveActor const *);

    sead::Quatf *getQuat(al::LiveActor const *);

    int getPlayerControllerPort(int);

    bool isValidReplayController(unsigned int port);
    sead::Controller* getReplayController(unsigned int param_1);

    int getMainControllerPort();

    char const *getActionName(al::LiveActor const *);

    char const *getActionFrame(al::LiveActor const *);

    sead::Vector3f *getCameraPos(al::IUseCamera const *, int);

    float calcSpeed(al::LiveActor const *);
    float calcSpeedH(al::LiveActor const *);
    float calcSpeedV(al::LiveActor const *);
    
    // setters

    void setTransY(al::LiveActor *, float);

    void setTrans(al::LiveActor *, sead::Vector3f const &);

    void setScaleAll(al::LiveActor *, float);

    void setGravity(al::LiveActor const *, sead::Vector3f const &);

    void setFront(al::LiveActor *, sead::Vector3f const &);

    void setQuat(al::LiveActor *, const sead::Quatf &);

    void setPaneTexture(al::IUseLayout *, char const *, nn::ui2d::TextureInfo const *);

    //void setPaneString(al::IUseLayout *layout, char const *paneName, char16_t const *, ushort);

    void setPaneStringFormat(al::IUseLayout *layout, char const *paneName, char const *format,...);

    void setVelocityZero(al::LiveActor *);

    // calc functions

    f32 calcDistance(al::LiveActor const *, al::LiveActor const*); // calculates distance between two actors

    f32 calcDistance(al::LiveActor const *, sead::Vector3f const&); // calculates distance between an actor and a position in the world

    // bools

    bool isInAreaObj(al::LiveActor const *, const char *);

    bool isInDeathArea(al::LiveActor const *);

    bool getArg(int *, const al::ActorInitInfo &, const char *); // gets an int argument from the actorinitinfo by a char* key

    bool isActiveDemo(const al::Scene *);

    bool isAreaTarget(al::LiveActor const *);

    // math

    float powerIn(float base, float exponent);
    float powerOut(float base, float exponent);

    float squareIn(float value);

    // misc

    al::AreaObj *tryFindAreaObj(al::LiveActor const *, const char *);

    bool tryGetAreaObjArg(int *, al::AreaObj const *, const char *);
    bool tryGetAreaObjArg(float *, al::AreaObj const *, const char *);
    bool tryGetAreaObjArg(bool *, al::AreaObj const *, const char *);

    bool tryGetAreaObjStringArg(const char **, al::AreaObj const *, const char *);

    bool tryGetArg(int *, const al::ActorInitInfo &, const char *);
    bool tryGetArg(float *, const al::ActorInitInfo &, const char *);
    bool tryGetArg(bool *, const al::ActorInitInfo  &, const char *);

    bool tryGetStringArg(const char **, al::ActorInitInfo const *, const char *);

    bool isEqualString(const char *stringA, const char *stringB);

    void offCollide(al::LiveActor *);
    void onCollide(al::LiveActor *);

    void startAction(al::LiveActor *, char const *);

    bool tryStartSe(al::IUseAudioKeeper const *, sead::SafeStringBase<char> const &);

    void startSe(al::IUseAudioKeeper const *, sead::SafeStringBase<char> const &);

    void startHitReaction(al::LiveActor const *, char const*);

    void calcCameraUpDir(sead::Vector3f *, al::IUseCamera const*, int);

    const unsigned char *tryGetBymlFromArcName(sead::SafeStringBase<char> const &, sead::SafeStringBase<char> const &);

    void initActor(al::LiveActor *, al::ActorInitInfo const &);


}
