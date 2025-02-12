/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGIDMapper_DEFINED
#define SkSVGIDMapper_DEFINED

#include "include/core/SkRefCnt.h"
#include "src/core/SkTHash.h"

class SkString;
class SkSVGNode;
class SkSVGDOM;

using SkSVGIDMapper = skia_private::THashMap<SkString, sk_sp<SkSVGNode>>;
using SkSVGDOMMapper = skia_private::THashMap<SkString, sk_sp<SkSVGDOM>>;

#endif // SkSVGIDMapper_DEFINED
