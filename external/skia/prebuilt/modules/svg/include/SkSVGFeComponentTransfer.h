/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGFeComponentTransfer_DEFINED
#define SkSVGFeComponentTransfer_DEFINED

#include "modules/svg/include/SkSVGFe.h"
#include "modules/svg/include/SkSVGTypes.h"

class SK_API SkSVGFeComponentTransfer : public SkSVGFe {
public:
    static sk_sp<SkSVGFeComponentTransfer> Make() { return sk_sp<SkSVGFeComponentTransfer>(new SkSVGFeComponentTransfer()); }

protected:
    sk_sp<SkImageFilter> onMakeImageFilter(const SkSVGRenderContext&,
                                           const SkSVGFilterContext&) const override;

    std::vector<SkSVGFeInputType> getInputs() const override { return { }; }

private:
    SkSVGFeComponentTransfer() : INHERITED(SkSVGTag::kFeComponentTransfer) {}

    using INHERITED = SkSVGFe;
};

#endif  // SkSVGFeComponentTransfer_DEFINED
