#include "env/env.h"
#include "env/units.h"

using namespace std;
using namespace tex;

float Env::PIXELS_PER_POINT = 1.f;

void Env::setDpi(float dpi) {
  PIXELS_PER_POINT = dpi / 72.f;
}

float Env::pixelsPerPoint() {
  return PIXELS_PER_POINT;
}

float Env::scale() const {
  if (_style < TexStyle::script) return 1;
  auto math = _fc->mathFont().otf().mathConsts();
  i16 percent = (
    _style < TexStyle::scriptScript
    ? math->scriptPercentScaleDown()
    : math->scriptScriptPercentScaleDown()
  );
  return percent / 100.f;
}

inline Env& Env::setTextWidth(UnitType unit, float width) {
  _textWidth = Units::fsize(unit, width, *this);
  return *this;
}

inline Env& Env::setLineSpace(UnitType unit, float space) {
  _lineSpace = Units::fsize(unit, space, *this);
  return *this;
}

inline const MathConsts& Env::mathConsts() const {
  return *_fc->mathFont().otf().mathConsts();
}

float Env::upem() const {
  return _fc->mathFont().otf().em();
}

float Env::em() const {
  return upem() * scale();
}

float Env::ppem() const {
  return PIXELS_PER_POINT * _textSize;
}

float Env::xHeight() const {
  return _fc->getFont(lastFontId())->otf().xHeight() * scale();
}

float Env::space() const {
  return _fc->mathFont().otf().space() * scale();
}

float Env::ruleThickness() const {
  return mathConsts().fractionRuleThickness() * scale();
}

float Env::axisHeight() const {
  return mathConsts().axisHeight() * scale();
}

void Env::addFontStyle(FontStyle style) {
  auto dummy = static_cast<u16>(_fontStyle) | static_cast<u16>(style);
  _fontStyle = static_cast<FontStyle>(dummy);
}

void Env::removeFontStyle(FontStyle style) {
  auto dummy = static_cast<u16>(_fontStyle) & (~static_cast<u16>(style));
  _fontStyle = static_cast<FontStyle>(dummy);
}

TexStyle Env::crampStyle() const {
  const i8 style = static_cast<i8>(_style);
  return static_cast<TexStyle>(style % 2 == 1 ? style : style + 1);
}

TexStyle Env::dnomStyle() const {
  const i8 style = static_cast<i8>(_style);
  return static_cast<TexStyle>(2 * (style / 2) + 1 + 2 - 2 * (style / 6));
}

TexStyle Env::numStyle() const {
  const i8 style = static_cast<i8>(_style);
  return static_cast<TexStyle>(style + 2 - 2 * (style / 6));
}

TexStyle Env::rootStyle() const {
  return TexStyle::scriptScript;
}

TexStyle Env::subStyle() const {
  const i8 style = static_cast<i8>(_style);
  return static_cast<TexStyle>(2 * (style / 4) + 4 + 1);
}

TexStyle Env::supStyle() const {
  const i8 style = static_cast<i8>(_style);
  return static_cast<TexStyle>(2 * (style / 4) + 4 + (style % 2));
}

Char Env::getChar(c32 code, bool isMathMode, FontStyle style) const {
  const auto targetStyle = style == FontStyle::invalid ? _fontStyle : style;
  auto chr = _fc->getChar(code, targetStyle, isMathMode);
  chr._scale = scale();
  return chr;
}

Char Env::getChar(const Symbol& sym) const {
  auto chr = _fc->getChar(sym);
  chr._scale = scale();
  return chr;
}