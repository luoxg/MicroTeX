/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSVGSymbol_DEFINED
#define SKSVGSymbol_DEFINED

#include "modules/svg/include/SkSVGContainer.h"

class SK_API SkSVGSymbol : public SkSVGContainer {
public:
    static sk_sp<SkSVGSymbol> Make() { return sk_sp<SkSVGSymbol>(new SkSVGSymbol()); }

    SVG_ATTR(X                  , SkSVGLength, SkSVGLength(0))
    SVG_ATTR(Y                  , SkSVGLength, SkSVGLength(0))
    SVG_ATTR(Width              , SkSVGLength, SkSVGLength(100, SkSVGLength::Unit::kPercentage))
    SVG_ATTR(Height             , SkSVGLength, SkSVGLength(100, SkSVGLength::Unit::kPercentage))
    SVG_ATTR(PreserveAspectRatio, SkSVGPreserveAspectRatio, SkSVGPreserveAspectRatio())
    SVG_OPTIONAL_ATTR(ViewBox   , SkSVGViewBoxType)

protected:
    bool onPrepareToRender(SkSVGRenderContext*) const override;

    void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

private:
    SkSVGSymbol() : INHERITED(SkSVGTag::kSymbol) { }

    bool parseAndSetAttribute(const char*, const char*) override;

    using INHERITED = SkSVGContainer;
};

#endif // SKSVGSymbol_DEFINED
