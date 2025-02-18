#include "Library/Camera/CameraPoser.h"

#include "Library/Camera/CameraPoserFlag.h"
#include "Library/Camera/CameraPoserFunction.h"
#include "Library/Camera/SnapShotCameraCtrl.h"
#include "Library/Yaml/ByamlIter.h"
#include "Library/Yaml/ByamlUtil.h"

namespace al {

void CameraPoser::startSnapShotModeCore() {
    if (mSnapShotCtrl)
        mSnapShotCtrl->start(mFovyDegree);
    startSnapShotMode();
}

void CameraPoser::endSnapShotModeCore() {
    endSnapShotMode();
}

f32 CameraPoser::getFovyDegree() const {
    if (alCameraPoserFunction::isSnapShotMode(this) && mSnapShotCtrl)
        return mSnapShotCtrl->getFovyDegree();
    return mFovyDegree;
}

}  // namespace al
