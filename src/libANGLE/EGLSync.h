//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// EGLSync.h: Defines the egl::Sync classes, which support the EGL_KHR_fence_sync,
// EGL_KHR_wait_sync and EGL 1.5 sync objects.

#ifndef LIBANGLE_EGLSYNC_H_
#define LIBANGLE_EGLSYNC_H_

#include "libANGLE/Debug.h"
#include "libANGLE/Error.h"
#include "libANGLE/RefCountObject.h"

#include "common/angleutils.h"

namespace rx
{
class EGLImplFactory;
class EGLSyncImpl;
}  // namespace rx

namespace egl
{
class Sync final : public angle::RefCountObject<Display, angle::Result>
{
  public:
    Sync(rx::EGLImplFactory *factory, EGLenum type, const AttributeMap &attribs);
    ~Sync() override;

    void onDestroy(const Display *display) override;

    Error initialize(const Display *display);
    Error clientWait(const Display *display, EGLint flags, EGLTime timeout, EGLint *outResult);
    Error serverWait(const Display *display, EGLint flags);
    Error getStatus(const Display *display, EGLint *outStatus) const;

    EGLenum getType() const { return mType; }
    EGLint getCondition() const { return mCondition; }

  private:
    std::unique_ptr<rx::EGLSyncImpl> mFence;

    EGLenum mType;
    static constexpr EGLint mCondition = EGL_SYNC_PRIOR_COMMANDS_COMPLETE_KHR;
};

}  // namespace egl

#endif  // LIBANGLE_FENCE_H_
