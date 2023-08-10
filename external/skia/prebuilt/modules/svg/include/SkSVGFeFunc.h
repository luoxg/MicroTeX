/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGFeFunc_DEFINED
#define SkSVGFeFunc_DEFINED

#include "modules/svg/include/SkSVGFe.h"
#include "modules/svg/include/SkSVGTypes.h"

class SK_API SkSVGFeFunc : public SkSVGFe {
public:
    static bool IsFuncEffect(const sk_sp<SkSVGNode>& node) {
        switch (node->tag()) {
            case SkSVGTag::kFeFuncA:
            case SkSVGTag::kFeFuncB:
            case SkSVGTag::kFeFuncG:
            case SkSVGTag::kFeFuncR:
                return true;
            default:
                return false;
        }
    }

    static void makeIdentityTable(uint8_t table[256]);

    SVG_ATTR(Type, SkSVGFeFuncType::Type,  SkSVGFeFuncType::Type::kIdentity)
    SVG_OPTIONAL_ATTR(Slope             ,  SkSVGNumberType)
    SVG_OPTIONAL_ATTR(TableValues       ,  SkSVGFeColorMatrixValues)
    SVG_OPTIONAL_ATTR(Intercept         ,  SkSVGNumberType)
    SVG_OPTIONAL_ATTR(Amplitude         ,  SkSVGNumberType)
    SVG_OPTIONAL_ATTR(Exponent          ,  SkSVGNumberType)
    SVG_OPTIONAL_ATTR(Offset            ,  SkSVGNumberType)

    void makeTableData(uint8_t table[256]) const;

    virtual uint8_t tableIndex() const = 0;

protected:
    SkSVGFeFunc(SkSVGTag t) : INHERITED(t) {}

    bool parseAndSetAttribute(const char*, const char*) override;

    std::vector<SkSVGFeInputType> getInputs() const override { return {this->getIn()}; }

    sk_sp<SkImageFilter> onMakeImageFilter(const SkSVGRenderContext&,
                                           const SkSVGFilterContext&) const override { return nullptr; }

private:

    void makeGammaTable(uint8_t table[256]) const;
    void makeLinearTable(uint8_t table[256]) const;
    void makeTableTable(uint8_t table[256]) const;
    void makeDiscreteTable(uint8_t table[256]) const;

    std::vector<uint8_t> tableFloatToUint8() const;

    using INHERITED = SkSVGFe;
};

class SK_API SkSVGFeFuncA : public SkSVGFeFunc {
public:
    static sk_sp<SkSVGFeFuncA> Make() { return sk_sp<SkSVGFeFuncA>(new SkSVGFeFuncA()); }

protected:
    uint8_t tableIndex() const override { return 0; }

private:
    SkSVGFeFuncA() : INHERITED(SkSVGTag::kFeFuncA) {}

    using INHERITED = SkSVGFeFunc;
};

class SK_API SkSVGFeFuncB : public SkSVGFeFunc {
public:
    static sk_sp<SkSVGFeFuncB> Make() { return sk_sp<SkSVGFeFuncB>(new SkSVGFeFuncB()); }

protected:
    uint8_t tableIndex() const override { return 3; }

private:
    SkSVGFeFuncB() : INHERITED(SkSVGTag::kFeFuncB) {}

    using INHERITED = SkSVGFeFunc;
};

class SK_API SkSVGFeFuncG : public SkSVGFeFunc {
public:
    static sk_sp<SkSVGFeFuncG> Make() { return sk_sp<SkSVGFeFuncG>(new SkSVGFeFuncG()); }

protected:
    uint8_t tableIndex() const override { return 2; }

private:
    SkSVGFeFuncG() : INHERITED(SkSVGTag::kFeFuncG) {}

    using INHERITED = SkSVGFeFunc;
};

class SK_API SkSVGFeFuncR : public SkSVGFeFunc {
public:
    static sk_sp<SkSVGFeFuncR> Make() { return sk_sp<SkSVGFeFuncR>(new SkSVGFeFuncR()); }

protected:
    uint8_t tableIndex() const override { return 1; }

private:
    SkSVGFeFuncR() : INHERITED(SkSVGTag::kFeFuncR) {}

    using INHERITED = SkSVGFeFunc;
};

#endif  // SkSVGFeFunc_DEFINED
