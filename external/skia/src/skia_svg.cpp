//
// Created by lxg on 2023/7/28.
//

#include "skia-utils/skia_svg.h"
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
        canvas.clear(fBackground);
        fSVGDoc->render(&canvas);
        SkGraphics::PurgeAllCaches();
    }
    return bitmap;
}

void SkSVG::setResourceProvider(SkSVGDOM::Builder &builder) {
    if (fUri.isEmpty()) {
        return;
    }
    sk_sp<ResourceProvider> provider = FileResourceProvider::Make(fUri, fPredecode);
    provider = DataURIResourceProviderProxy::Make(provider, fPredecode);
    if (fCached) {
        provider = CachingResourceProvider::Make(provider);
    }
    builder.setResourceProvider(provider);
}