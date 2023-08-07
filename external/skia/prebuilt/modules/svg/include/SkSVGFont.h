/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGFont_DEFINED
#define SkSVGFont_DEFINED

#include "modules/svg/include/SkSVGHiddenContainer.h"
#include "include/utils/SkFontMgr_user.h"
#include "src/core//SkTHash.h"

using SkSVGTypeFaceMapper = skia_private::THashMap<SkString, skia_private::TArray<sk_sp<SkTypeface>>>;

class SK_API SkSVGFont : public SkSVGHiddenContainer {
public:
    static sk_sp<SkSVGFont> Make() { return sk_sp<SkSVGFont>(new SkSVGFont()); }

    SVG_ATTR(HorizAdvX, SkSVGNumberType, 0)

    void buildTypeface(SkSVGTypeFaceMapper* typefaceMapper);

protected:

    bool parseAndSetAttribute(const char*, const char*) override;

    SkPath onAsPath(const SkSVGRenderContext&) const override;

    SkRect onObjectBoundingBox(const SkSVGRenderContext&) const override;

private:
    SkSVGFont() : INHERITED(SkSVGTag::kFont) { }

    bool isFontEffect(const sk_sp<SkSVGNode>& node);

    using INHERITED = SkSVGHiddenContainer;
};

class SK_API SkSVGFontComponent : public SkSVGHiddenContainer {
public:

    void makeTypeface(SkCustomTypefaceBuilder& builder, SkString& family) const {
        this->onMakeTypeface(builder, family);
    }

protected:

    explicit SkSVGFontComponent(SkSVGTag t) : INHERITED(t) { }

    virtual void onMakeTypeface(class SkCustomTypefaceBuilder& builder, SkString& family) const = 0;

    SkPath onAsPath(const SkSVGRenderContext&) const override { return SkPath(); };

    SkRect onObjectBoundingBox(const SkSVGRenderContext&) const override { return SkRect::MakeEmpty(); };

private:

    using INHERITED = SkSVGHiddenContainer;
};

class SK_API SkSVGFontFace : public SkSVGFontComponent {
public:
    static sk_sp<SkSVGFontFace> Make() { return sk_sp<SkSVGFontFace>(new SkSVGFontFace()); }

    SVG_ATTR(FontFamily , SkSVGFontFamily  , SkSVGFontFamily(""))
    SVG_ATTR(FontStyle  , SkSVGFontStyle   , SkSVGFontStyle(SkSVGFontStyle::Type::kNormal))
    SVG_ATTR(FontWeight , SkSVGFontWeight  , SkSVGFontWeight(SkSVGFontWeight::Type::kNormal))
    SVG_ATTR(Panose     , SkString         , SkString())
    SVG_ATTR(Alphabetic , SkString         , SkString())
    SVG_ATTR(UnitsPerEm , SkSVGNumberType  , 1)
    SVG_ATTR(Ascent     , SkSVGNumberType  , 0)
    SVG_ATTR(Descent    , SkSVGNumberType  , 0)

protected:

    bool parseAndSetAttribute(const char*, const char*) override;

    void onMakeTypeface(SkCustomTypefaceBuilder& builder, SkString& family) const override;

private:
    SkSVGFontFace() : INHERITED(SkSVGTag::kFontFace) { }

    void setMetrics(SkCustomTypefaceBuilder& builder) const;

    void setFontStyle(SkCustomTypefaceBuilder& builder) const;

    using INHERITED = SkSVGFontComponent;
};

class SK_API SkSVGGlyph : public SkSVGFontComponent {
public:
    static sk_sp<SkSVGGlyph> Make() { return sk_sp<SkSVGGlyph>(new SkSVGGlyph()); }

    SVG_ATTR(Path       , SkPath          , SkPath())
    SVG_ATTR(Unicode    , SkString        , SkString())
    SVG_ATTR(GlyphName  , SkString        , SkString())
    SVG_ATTR(HorizAdvX  , SkSVGNumberType , 0)

protected:

    bool parseAndSetAttribute(const char*, const char*) override;

    void onMakeTypeface(SkCustomTypefaceBuilder& builder, SkString& family) const override;

private:
    SkSVGGlyph() : INHERITED(SkSVGTag::kGlyph) { }

    using INHERITED = SkSVGFontComponent;
};

class SK_API SkSVGMissingGlyph : public SkSVGFontComponent {
public:
    static sk_sp<SkSVGMissingGlyph> Make() { return sk_sp<SkSVGMissingGlyph>(new SkSVGMissingGlyph()); }

    SVG_ATTR(Path       , SkPath          , SkPath())
    SVG_ATTR(HorizAdvX  , SkSVGNumberType , 0)

protected:

    bool parseAndSetAttribute(const char*, const char*) override;

    void onMakeTypeface(SkCustomTypefaceBuilder& builder, SkString& family) const override;

private:
    SkSVGMissingGlyph() : INHERITED(SkSVGTag::kMissingGlyph) { }

    using INHERITED = SkSVGFontComponent;
};

#endif // SkSVGFont_DEFINED
