#pragma once

#include <gfx/seadCamera.h>
#include <math/seadMatrix.h>
#include <math/seadQuat.h>
#include <math/seadVector.h>

#include "Library/Area/IUseAreaObj.h"
#include "Library/Audio/IUseAudioKeeper.h"
#include "Library/Collision/IUseCollision.h"
#include "Library/HostIO/HioNode.h"
#include "Library/HostIO/IUseName.h"
#include "Library/Nerve/IUseNerve.h"
#include "Library/Rail/IUseRail.h"

namespace al {
class AudioDirector;
class ByamlIter;
class CameraAngleCtrlInfo;
class CameraAngleSwingInfo;
class CameraArrowCollider;
class CameraFlagCtrl;
class CameraInputHolder;
class CameraObjectRequestInfo;
class CameraOffsetCtrlPreset;
class CameraParamMoveLimit;
class CameraPoserFlag;
struct CameraStartInfo;
class CameraTargetAreaLimitter;
class CameraTargetHolder;
class CameraTurnInfo;
class CameraVerticalAbsorber;
class CameraViewInfo;
class GyroCameraCtrl;
class Nerve;
struct OrthoProjectionInfo;
class PlacementInfo;
class RailKeeper;
class SnapShotCameraCtrl;

class CameraPoser : public HioNode,
                    public IUseAreaObj,
                    public IUseAudioKeeper,
                    public IUseCollision,
                    public IUseName,
                    public IUseNerve,
                    public IUseRail {
public:
    CameraPoser(const char* poserName);

    virtual AreaObjDirector* getAreaObjDirector() const override;
    virtual void init();
    virtual void initByPlacementObj(const PlacementInfo&);
    virtual void endInit();
    virtual void start(const CameraStartInfo&);
    virtual void update();
    virtual void end();
    virtual void loadParam(const ByamlIter&);
    virtual void makeLookAtCamera(sead::LookAtCamera*) const;
    virtual void receiveRequestFromObject(const CameraObjectRequestInfo&);
    virtual bool isZooming() const;
    virtual bool isEnableRotateByPad() const;
    virtual void startSnapShotMode();
    virtual void endSnapShotMode();

    virtual const char* getName() const override;
    virtual CollisionDirector* getCollisionDirector() const override;
    virtual NerveKeeper* getNerveKeeper() const override;
    virtual AudioKeeper* getAudioKeeper() const override;
    virtual RailRider* getRailRider() const override;

    virtual void load(const ByamlIter&);
    virtual void movement();
    virtual void calcCameraPose(sead::LookAtCamera*) const;
    virtual void requestTurnToDirection(const CameraTurnInfo*);

    bool isInterpoleByCameraDistance() const;
    bool isInterpoleEaseOut() const;
    bool isEndInterpoleByStep() const;
    bool isFirstCalc() const;

    void initNerve(const Nerve* nerve, s32 num);
    void initArrowCollider(CameraArrowCollider* arrowCollider);
    void initAudioKeeper(const char* name);
    void initRail(const PlacementInfo& placementInfo);
    void initLocalInterpole();
    void initLookAtInterpole(f32);
    void initOrthoProjectionParam();
    void tryInitAreaLimitter(const PlacementInfo& placementInfo);
    void tryCalcOrthoProjectionInfo(OrthoProjectionInfo* projectionInfo);

    void makeLookAtCameraPrev(sead::LookAtCamera* cam) const;
    void makeLookAtCameraPost(sead::LookAtCamera* cam) const;
    void makeLookAtCameraLast(sead::LookAtCamera* cam) const;
    void makeLookAtCameraCollide(sead::LookAtCamera* cam) const;

    void getInterpoleStep();
    void setInterpoleStep(s32);
    void resetInterpoleStep();
    void setInterpoleEaseOut();
    void getEndInterpoleStep();

    void appear(const CameraStartInfo& startInfo);
    void calcCameraPose(sead::LookAtCamera* cam);
    void receiveRequestFromObjectCore(const CameraObjectRequestInfo& objRequestInfo);

    void startSnapShotModeCore();
    void endSnapShotModeCore();

    f32 getFovyDegree() const;
    f32 getSceneFovyDegree() const;
    CameraInputHolder* getInputHolder() const;
    CameraTargetHolder* getTargetHolder() const;

    struct CameraInterpolateStep {
        s32 mStepType;
        s32 mStepNum;
    };

    static_assert(sizeof(CameraInterpolateStep) == 0x8);

    struct CameraInterpolateParams {
        CameraInterpolateStep mStep;
        bool mIsEaseOut;
        bool mIsInterpolate;
    };

    static_assert(sizeof(CameraInterpolateParams) == 0xC);

    struct CameraPoserStruct {
        f32 mSceneFovyDegree;
        AreaObjDirector* mAreaObjDirector;
        CollisionDirector* mCollisionDirector;
        AudioDirector* mAudioDirector;
        CameraInputHolder* mInputHolder;
        CameraTargetHolder* mTargetHolder;
        CameraFlagCtrl* mFlagCtrl;
    };

    struct OrthoProjectionParam {
        bool mIsSetOrthoProjectionInfo;
        f32 mOrthoProjectionNearClipWidth;
        f32 mOrthoProjectionNearClipHeight;
    };

    static_assert(sizeof(OrthoProjectionParam) == 0xC);

    // get
    const sead::Vector3f& getPosition() const { return mPosition; };

    const sead::Vector3f& getTargetTrans() const { return mTargetTrans; };

    const sead::Vector3f& getCameraUp() const { return mCameraUp; };

    const sead::Matrix34f& getViewMtx() const { return mViewMtx; };

    CameraViewInfo* getViewInfo() const { return mViewInfo; }

    // set
    void setPosition(const sead::Vector3f& vec) { mPosition.set(vec); };

    void setTargetTrans(const sead::Vector3f& vec) { mTargetTrans.set(vec); };

    void setCameraUp(const sead::Vector3f& vec) { mCameraUp.set(vec); };

    void setViewMtx(const sead::Matrix34f& mtx) { mViewMtx = mtx; }

    void setFovyDegree(f32 fovy) { mFovyDegree = fovy; }

private:
    const char* mPoserName;
    s32 mActiveState;  // 0 = not start, 1 = running, 2 = ended
    sead::Vector3f mPosition;
    sead::Vector3f mTargetTrans;
    sead::Vector3f mCameraUp;
    f32 mFovyDegree;
    f32 _60;
    sead::Matrix34f mViewMtx;
    bool _98;
    CameraPoserStruct* mPoserStruct;
    CameraViewInfo* mViewInfo;
    CameraPoserFlag* mPoserFlag;
    CameraVerticalAbsorber* mVerticalAbsorber;
    CameraAngleCtrlInfo* mAngleCtrlInfo;
    CameraAngleSwingInfo* mAngleSwingInfo;
    CameraArrowCollider* mArrowCollider;
    CameraOffsetCtrlPreset* mOffsetCtrlPreset;
    void* mLocalInterpole;   // size = 0x20
    void* mLookAtInterpole;  // size = 0x10
    CameraParamMoveLimit* mParamMoveLimit;
    CameraTargetAreaLimitter* mTargetAreaLimitter;
    GyroCameraCtrl* mGyroCtrl;
    SnapShotCameraCtrl* mSnapShotCtrl;
    AudioKeeper* mAudioKeeper;
    NerveKeeper* mNerveKeeper;
    RailKeeper* mRailKeeper;
    CameraInterpolateParams* mInterpolate;
    CameraInterpolateStep* mInterpolateStep;
    OrthoProjectionParam* mOrthoProjectionParam;
};

static_assert(sizeof(CameraPoser) == 0x140);

}  // namespace al
