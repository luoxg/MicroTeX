/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGA_DEFINED
#define SkSVGA_DEFINED

#include "modules/svg/include/SkSVGContainer.h"

class SK_API SkSVGA : public SkSVGContainer {
public:
    static sk_sp<SkSVGA> Make() { return sk_sp<SkSVGA>(new SkSVGA()); }

private:
    SkSVGA() : INHERITED(SkSVGTag::kA) { }

    using INHERITED = SkSVGContainer;
};

#endif // SkSVGA_DEFINED
