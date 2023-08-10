//
// Created by lxg on 2023/7/28.
//

#ifndef CBOX_SKIA_SVG_H
#define CBOX_SKIA_SVG_H

#include "iostream"
#include "memory"
#include "include/core/SkBitmap.h"
#include "include/core/SkString.h"
#include "include/core/SkColor.h"
#include "include/core/SkFontMgr.h"
#include "modules/svg/include/SkSVGDOM.h"
#include "modules/svg/include/SkSVGResourceProvider.h"

using namespace skresources;

class SkSVG {
public:
    SkSVG() = default;

    SkSVG(const SkColor background, bool predecode = true, bool cached = true);

    SkSVG& setUri(const SkString& uri);

    SkSVG& setCached(const bool cached);

    SkSVG& setPredecode(const bool predecode);

    SkSVG& setBackground(const SkColor background);

    SkSVG& setFontMgr(const sk_sp<SkFontMgr>& fontMgr);

    SkSVG& setResourceProvider(const sk_sp<SkSVGResourceProvider>& resourceProvider);

    const SkString& uri();
    bool predecode();
    bool cached();
    SkColor background();
    SkSize size();

    SkSVG& make(const SkString &path);
    SkSVG& make(const std::string &path);
    SkSVG& make(SkStream &stream);
    SkSVG& make(std::shared_ptr<std::istream> &stream);
    SkSVG& make(const char* data, size_t len);

    std::shared_ptr<SkBitmap> render();

    std::shared_ptr<SkBitmap> render(float scale);

    std::shared_ptr<SkBitmap> render(SkSize size);

private:
    void setResourceProvider(SkSVGDOM::Builder& builder);
    void drawBackground(SkCanvas& canvas);

private:
    SkColor                      fBackground{SK_ColorTRANSPARENT};
    bool                         fPredecode{true};
    bool                         fCached{true};
    SkString                     fUri;
    SkSize                       fContainerSize{0, 0};
    sk_sp<SkSVGDOM>              fSVGDoc;
    sk_sp<SkFontMgr>             fFontMgr;
    sk_sp<SkSVGResourceProvider> fResourceProvider;

};

#endif //CBOX_SKIA_SVG_H
