#ifndef LATEX_ATOM_FONT_H
#define LATEX_ATOM_FONT_H

#include "atom/atom.h"
#include "graphic/font_style.h"
#include "env/env.h"

namespace tex {

class FontStyleAtom : public Atom {
private:
  FontStyle _style = FontStyle::none;
  bool _mathMode = false;
  bool _nested = false;

  sptr<Atom> _atom;

public:
  FontStyleAtom() = delete;

  FontStyleAtom(FontStyle style, bool isMathMode, const sptr<Atom>& atom, bool nested = false)
    : _style(style), _mathMode(isMathMode), _atom(atom), _nested(nested) {}

  AtomType leftType() const override {
    return _atom->leftType();
  }

  AtomType rightType() const override {
    return _atom->rightType();
  }

  sptr<Box> createBox(Env& env) override;
};

/** Atom to modify math font and style */
class MathFontAtom : public Atom {
private:
  MathStyle _mathStyle;
  std::string _name;

public:
  MathFontAtom(MathStyle style, std::string name)
    : _mathStyle(style), _name(std::move(name)) {}

  sptr<Box> createBox(Env& env) override;
};

}

#endif //LATEX_ATOM_FONT_H