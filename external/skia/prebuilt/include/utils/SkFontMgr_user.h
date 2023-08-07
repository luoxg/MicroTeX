/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkFontMgr_user_DEFINED
#define SkFontMgr_user_DEFINED

#include "include/core/SkFontMgr.h"
#include "include/core/SkFontStyle.h"
#include "include/core/SkRefCnt.h"
#include "include/core/SkString.h"
#include "include/core/SkTypes.h"
#include "include/private/base/SkTArray.h"
#include "include/utils/SkCustomTypeface.h"

/**
 *  SkFontStyleSet_User
 *
 *  This class is used by SkFontMgr_User to hold SkTypeface_User families.
 */
class SkFontStyleSet_User : public SkFontStyleSet {
public:
    explicit SkFontStyleSet_User(const SkString familyName);

    /** Should only be called during the initial build phase. */
    void appendTypeface(sk_sp<SkTypeface> typeface);
    int count() override;
    void getStyle(int index, SkFontStyle* style, SkString* name) override;
    sk_sp<SkTypeface> createTypeface(int index) override;
    sk_sp<SkTypeface> matchStyle(const SkFontStyle& pattern) override;
    SkString getFamilyName();

private:
    skia_private::TArray<sk_sp<SkTypeface>> fStyles;
    SkString fFamilyName;

    friend class SkFontMgr_User;
};

/**
 *  SkFontMgr_User
 *
 *  This class is essentially a collection of SkFontStyleSet_User,
 *  one SkFontStyleSet_User for each family. This class may be modified
 *  to load fonts from any source by changing the initialization.
 */
class SkFontMgr_User : public SkFontMgr {
public:
    typedef skia_private::TArray<sk_sp<SkFontStyleSet_User>> Families;

    explicit SkFontMgr_User(const SkString familyName, sk_sp<SkTypeface> typeface);

    explicit SkFontMgr_User(const SkString familyName, skia_private::TArray<sk_sp<SkTypeface>> typefaces);

protected:
    int onCountFamilies() const override;
    void onGetFamilyName(int index, SkString* familyName) const override;
    sk_sp<SkFontStyleSet> onCreateStyleSet(int index) const override;
    sk_sp<SkFontStyleSet> onMatchFamily(const char familyName[]) const override;
    sk_sp<SkTypeface> onMatchFamilyStyle(const char familyName[],
                                         const SkFontStyle& fontStyle) const override;
    sk_sp<SkTypeface> onMatchFamilyStyleCharacter(const char familyName[], const SkFontStyle&,
                                                  const char* bcp47[], int bcp47Count,
                                                  SkUnichar character) const override;
    sk_sp<SkTypeface> onMakeFromData(sk_sp<SkData> data, int ttcIndex) const override;
    sk_sp<SkTypeface> onMakeFromStreamIndex(std::unique_ptr<SkStreamAsset>, int ttcIndex) const override;
    sk_sp<SkTypeface> onMakeFromStreamArgs(std::unique_ptr<SkStreamAsset>, const SkFontArguments&) const override;
    sk_sp<SkTypeface> onMakeFromFile(const char path[], int ttcIndex) const override;
    sk_sp<SkTypeface> onLegacyMakeTypeface(const char familyName[], SkFontStyle style) const override;

private:
    Families fFamilies;
};

#endif
