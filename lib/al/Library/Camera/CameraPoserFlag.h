#pragma once

#include <basis/seadTypes.h>

namespace al {

class ByamlIter;

class CameraPoserFlag {
public:
    CameraPoserFlag();

    void load(const ByamlIter& iter);
    bool isValidKeepPreSelfPoseNextCamera();
};

// size = 0xF;
}  // namespace al
