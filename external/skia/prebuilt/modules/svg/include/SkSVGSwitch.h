/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSVGSwitch_DEFINED
#define SKSVGSwitch_DEFINED

#include "modules/svg/include/SkSVGContainer.h"

class SK_API SkSVGSwitch : public SkSVGContainer {
public:
    static sk_sp<SkSVGSwitch> Make() { return sk_sp<SkSVGSwitch>(new SkSVGSwitch()); }

private:
    SkSVGSwitch() : INHERITED(SkSVGTag::kSymbol) { }

    using INHERITED = SkSVGContainer;
};

#endif // SKSVGSwitch_DEFINED
