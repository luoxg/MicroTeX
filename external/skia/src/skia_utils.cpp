//
// Created by lxg on 2023/7/29.
//

#include "skia-utils/skia_utils.h"
#include "include/core/SkStream.h"
#include "include/core/SkImage.h"
#include "include/codec/SkCodec.h"
#include "vector"

namespace SkUtils {

    std::string encode64(const std::string& src) {
        size_t len = (src.length() +2) / 3 * 4;
        std::vector<char> out;
        out.reserve(len);
        size_t outLen = SkBase64::Encode(src.c_str(), src.length(), out.data());
        return std::string(out.data(), outLen);
    }

    std::string decode64(const std::string& src) {
        size_t len = src.length() / 4 * 3;
        std::vector<char> out;
        out.reserve(len);
        size_t outLen = 0;
        SkBase64::Error error = SkBase64::Decode(src.c_str(), src.length(), out.data(), &outLen);
        if (error != SkBase64::kNoError) {
            return "";
        }
        return std::string(out.data(), outLen);
    }

    bool compress(SkWStream* out, const SkBitmap& bitmap, const SkPngEncoder::Options& options) {
        return SkPngEncoder::Encode(out, bitmap.pixmap(), options);
    }

    bool compress(const std::string& fileName, const SkBitmap& bitmap, const SkPngEncoder::Options& options) {
        SkFILEWStream out(fileName.data());
        return SkPngEncoder::Encode(&out, bitmap.pixmap(), options);
    }

    sk_sp<SkImage> asImage(const SkBitmap& bitmap, SkCopyPixelsMode mode) {
        return SkMakeImageFromRasterBitmap(bitmap, mode);
    }

    sk_sp<SkImage> fromFile(const std::string& path) {
        auto stream = SkStream::MakeFromFile(path.c_str());
        auto codec = SkCodec::MakeFromStream(std::move(stream));
        return codec == nullptr ? nullptr : std::get<0>(codec->getImage());
    }

    sk_sp<SkImage> fromStream(std::unique_ptr<SkStream> stream) {
        auto codec = SkCodec::MakeFromStream(std::move(stream));
        return codec == nullptr ? nullptr : std::get<0>(codec->getImage());
    }

    sk_sp<SkImage> fromSkData(const sk_sp<SkData>& data) {
        if (!data) {
            return nullptr;
        }
        const auto codec = SkCodec::MakeFromData(data);
        return codec == nullptr ? nullptr : std::get<0>(codec->getImage());
    }
}