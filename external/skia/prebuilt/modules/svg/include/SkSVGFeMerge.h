/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGFeMerge_DEFINED
#define SkSVGFeMerge_DEFINED

#include "modules/svg/include/SkSVGFe.h"
#include "modules/svg/include/SkSVGTypes.h"

class SK_API SkSVGFeMerge : public SkSVGFe {
public:
    static bool IsMergeEffect(const sk_sp<SkSVGNode>& node) {
        switch (node->tag()) {
            case SkSVGTag::kFeMergeNode:
                return true;
            default:
                return false;
        }
    }

    static sk_sp<SkSVGFeMerge> Make() { return sk_sp<SkSVGFeMerge>(new SkSVGFeMerge()); }

protected:

    std::vector<SkSVGFeInputType> getInputs() const override { return {}; }

    sk_sp<SkImageFilter> onMakeImageFilter(const SkSVGRenderContext&,
                                           const SkSVGFilterContext&) const override;

private:
    SkSVGFeMerge() : INHERITED(SkSVGTag::kFeMerge) {}

    using INHERITED = SkSVGFe;
};

class SK_API SkSVGFeMergeNode : public SkSVGFe {
public:
    static sk_sp<SkSVGFeMergeNode> Make() { return sk_sp<SkSVGFeMergeNode>(new SkSVGFeMergeNode()); }

protected:
    std::vector<SkSVGFeInputType> getInputs() const override { return {this->getIn()}; }

    sk_sp<SkImageFilter> onMakeImageFilter(const SkSVGRenderContext&,
                                           const SkSVGFilterContext&) const override;

private:
    SkSVGFeMergeNode() : INHERITED(SkSVGTag::kFeMergeNode) {}

    using INHERITED = SkSVGFe;
};

#endif  // SkSVGFeMerge_DEFINED
