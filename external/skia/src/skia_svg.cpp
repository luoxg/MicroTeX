//
// Created by lxg on 2023/7/28.
//

#include "skia-utils/skia_svg.h"
#include "skia-utils/skia_stream_wrapper.h"
#include "include/core/SkShader.h"
#include "include/core/SkColorFilter.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkFont.h"
#include "include/core/SkStream.h"
#include "include/core/SkImage.h"
#include "include/core/SkGraphics.h"
#include "include/encode/SkPngEncoder.h"
#include "modules/svg/include/SkSVGDOM.h"
#include "modules/svg/include/SkSVGSVG.h"
#include "src/utils/SkOSPath.h"

SkSVG::SkSVG(const SkColor background, bool predecode, bool cached) :
    fBackground(background), fPredecode(predecode), fCached(cached) {

}

SkSVG &SkSVG::setUri(const SkString &uri) {
    fUri = uri;
    return *this;
}

SkSVG &SkSVG::setCached(const bool cached) {
    fCached = cached;
    return *this;
}

SkSVG &SkSVG::setPredecode(const bool predecode) {
    fPredecode = predecode;
    return *this;
}

SkSVG &SkSVG::setBackground(const SkColor background) {
    fBackground = background;
    return *this;
}

SkSVG &SkSVG::setFontMgr(const sk_sp<SkFontMgr> &fontMgr) {
    fFontMgr = fontMgr;
    return *this;
}

SkSVG& SkSVG::setResourceProvider(const sk_sp<SkSVGResourceProvider>& resourceProvider) {
    fResourceProvider = resourceProvider;
    return *this;
}

const SkString &SkSVG::uri() {
    return fUri;
}

bool SkSVG::predecode() {
    return fPredecode;
}

bool SkSVG::cached() {
    return fCached;
}

SkColor SkSVG::background() {
    return fBackground;
}

SkSize SkSVG::size() {
    return fContainerSize;
}

SkSVG &SkSVG::make(const std::string &path) {
    return make(SkString(path));
}

SkSVG &SkSVG::make(const SkString &path) {
    auto builder = SkSVGDOM::Builder();
    SkFILEStream stream(path.c_str());
    if (fUri.isEmpty()) {
        fUri = SkOSPath::Dirname(path.c_str());
    }
    setResourceProvider(builder);
    fSVGDoc = builder.make(stream);
    fContainerSize = fSVGDoc->containerSize();
    return *this;
}

SkSVG &SkSVG::make(SkStream &stream) {
    auto builder = SkSVGDOM::Builder();
    setResourceProvider(builder);
    if ((fSVGDoc = builder.make(stream))) {
        fContainerSize = fSVGDoc->containerSize();
    }
    return *this;
}

SkSVG& SkSVG::make(std::shared_ptr<std::istream> &stream) {
    SkStreamWrapper input(stream);
    return make(input);
}

SkSVG &SkSVG::make(const char *data, size_t len) {
    auto builder = SkSVGDOM::Builder();
    setResourceProvider(builder);
    SkMemoryStream stream(data, len);
    if ((fSVGDoc = builder.make(stream))) {
        fContainerSize = fSVGDoc->containerSize();
    }
    return *this;
}

std::shared_ptr<SkBitmap> SkSVG::render() {
    std::shared_ptr<SkBitmap> bitmap = std::make_shared<SkBitmap>();
    if (fSVGDoc && !fContainerSize.isEmpty()) {
        SkGraphics::Init();
        bitmap->allocN32Pixels(fContainerSize.width(), fContainerSize.height());
        SkCanvas canvas(*bitmap);
        drawBackground(canvas);
        fSVGDoc->render(&canvas);
        SkGraphics::PurgeAllCaches();
    }
    return bitmap;
}

std::shared_ptr<SkBitmap> SkSVG::render(float scale) {
    std::shared_ptr<SkBitmap> bitmap = std::make_shared<SkBitmap>();
    if (fSVGDoc && !fContainerSize.isEmpty()) {
        SkGraphics::Init();
        bitmap->allocN32Pixels(fContainerSize.width() * scale, fContainerSize.height() * scale);
        SkCanvas canvas(*bitmap);
        drawBackground(canvas);
        canvas.scale(scale, scale);
        fSVGDoc->render(&canvas);
        SkGraphics::PurgeAllCaches();
    }
    return bitmap;
}

std::shared_ptr<SkBitmap> SkSVG::render(SkSize size) {
    if (fContainerSize.isEmpty()) {
        return std::make_shared<SkBitmap>();
    }
    float scale = std::min(size.width() / fContainerSize.width(), size.height() / fContainerSize.height());
    return render(scale);
}

void SkSVG::setResourceProvider(SkSVGDOM::Builder &builder) {
    if (!fResourceProvider && !fUri.isEmpty()) {
        fResourceProvider = SkSVGResourceProvider::Make(fUri, nullptr, fPredecode, fCached);
    }
    builder.setResourceProvider(fResourceProvider);
}

void SkSVG::drawBackground(SkCanvas& canvas) {
    if (fBackground != SK_ColorTRANSPARENT) {
        canvas.clear(fBackground);
    }
}