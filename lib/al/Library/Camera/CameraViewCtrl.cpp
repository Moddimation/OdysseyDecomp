#include "Library/Camera/CameraViewCtrl.h"

namespace al {

PauseCameraCtrl::PauseCameraCtrl(f32 v) : mIsPause(false), _4(v) {};
SceneCameraViewCtrl::SceneCameraViewCtrl() : _8("Start"), _10(0) {};
SceneCameraCtrl::SceneCameraCtrl() : mViewNumMax(0), mViewArray(0), _10(0), _18(0) {};

}  // namespace al
