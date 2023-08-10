/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGResourceProvider_DEFINED
#define SkSVGResourceProvider_DEFINED

#include "modules/skresources/include/SkResources.h"

using namespace skresources;
class SkSVGResourceHandler;

class SK_API SkSVGResourceProvider : public ResourceProvider {
public:
    static sk_sp<SkSVGResourceProvider> Make(SkString base_dir,
                                             std::unique_ptr<SkSVGResourceHandler> handler = nullptr,
                                             bool predecode = true,
                                             bool cached = true);
protected:
    sk_sp<SkData> load(const char resource_path[],
                       const char resource_name[]) const override;

    std::unique_ptr<SkStream> loadStream(const char resource_path[],
                                         const char resource_name[]) const override;

    sk_sp<ImageAsset> loadImageAsset(const char resource_path[],
                                     const char resource_name[]) const;

    sk_sp<ImageAsset> loadImageAsset(const char resource_path[],
                                     const char resource_name[],
                                     const char resource_id[]) const override;

    sk_sp<SkTypeface> loadTypeface(const char name[],
                                   const char url[]) const override;

    sk_sp<SkData> loadFont(const char name[],
                           const char url[]) const override;

    sk_sp<ExternalTrackAsset> loadAudioAsset(const char resource_path[],
                                             const char resource_name[],
                                             const char resource_id[]) override;

private:
    explicit SkSVGResourceProvider(SkString base_dir,
                                   std::unique_ptr<SkSVGResourceHandler> handler = nullptr,
                                   bool predecode = true, bool cached = true);

    const SkString fDir;
    std::unique_ptr<SkSVGResourceHandler> fHandler;
    const bool fPredecode;
    const bool fCached;

    mutable SkMutex fMutex;
    mutable skia_private::THashMap<SkString, sk_sp<ImageAsset>> fImageCache;

    using INHERITED = ResourceProvider;
};

class SkSVGResourceHandler {
public:
    SkSVGResourceHandler() = default;

    virtual ~SkSVGResourceHandler() = default;

    virtual sk_sp<SkData> load(const char resource_path[],
                               const char resource_name[]) {
        return nullptr;
    }

    virtual std::unique_ptr<SkStream> loadStream(const char resource_path[],
                                                 const char resource_name[]) {
        return nullptr;
    }
};

#endif  // SkSVGResourceProvider_DEFINED
