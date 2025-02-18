#pragma once

#include <basis/seadTypes.h>

namespace al {

class ByamlIter;

class CameraPoserFlag {
public:
    CameraPoserFlag();

    void load(const ByamlIter& iter);
    bool isValidKeepPreSelfPoseNextCamera();

    bool mIsFirstCalc = true;
    bool mIsOffVerticalAbsorb = true;
    bool mIsInvalidCollider = false;
    bool _3 = false;
    bool mIsValidKeepPreSelfPoseNextCameraByParam = false;
    bool _5 = false;
    bool mIsInvalidKeepPreSelfPoseNextCameraOverWriteProgram = false;
    bool mIsInvalidKeepDistanceNextCamera = false;
    bool _8 = false;
    bool _9 = false;
    bool mIsInvalidChangeSubjective = false;
    bool _11 = false;
    bool _12 = false;
    bool mIsInvalidPreCameraEndAfterInterpole = false;
    bool mIsStopUpdateGyro = false;  // 0xE
};  // https://github.com/Amethyst-szs/time-travel-standalone/blob/84cc30773007c7a94768a30c11b98f942fcee22d/include/al/camera/CameraPoserFlag.h#L7

static_assert(sizeof(CameraPoserFlag) == 0xF);
}  // namespace al
