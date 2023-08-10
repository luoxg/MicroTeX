//
// Created by lxg on 2023/7/29.
//

#ifndef CBOX_SKIA_UTILS_H
#define CBOX_SKIA_UTILS_H

#include "iostream"
#include "include/core/SkBitmap.h"
#include "include/core/SkStream.h"
#include "include/utils/SkBase64.h"
#include "include/encode/SkPngEncoder.h"
#include "src/core//SkImagePriv.h"

namespace SkUtils {

    std::string encode64(const std::string& src);

    std::string decode64(const std::string& src);

    bool compress(SkWStream* out, const SkBitmap& bitmap, const SkPngEncoder::Options& options = SkPngEncoder::Options());

    bool compress(const std::string& fileName, const SkBitmap& bitmap, const SkPngEncoder::Options& options = SkPngEncoder::Options());

    sk_sp<SkImage> asImage(const SkBitmap& bitmap, SkCopyPixelsMode mode = SkCopyPixelsMode::kNever_SkCopyPixelsMode);

    sk_sp<SkImage> fromFile(const std::string& path);

    sk_sp<SkImage> fromStream(std::unique_ptr<SkStream> stream);

    sk_sp<SkImage> fromSkData(const sk_sp<SkData>& data);

}

#endif //CBOX_SKIA_UTILS_H
