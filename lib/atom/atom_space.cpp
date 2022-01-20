#include "atom/atom_space.h"
#include "core/glue.h"
#include "env/env.h"
#include "env/units.h"
#include "box/box_single.h"

using namespace std;
using namespace tex;

sptr<Box> SpaceAtom::createBox(Env& env) {
  if (!_blankSpace) {
    float w = Units::fsize(_wUnit, _width, env);
    float h = Units::fsize(_hUnit, _height, env);
    float d = Units::fsize(_dUnit, _depth, env);
    return sptrOf<StrutBox>(w, h, d, 0.f);
  }
  if (_blankType == SpaceType::none) {
    return sptrOf<StrutBox>(env.space(), 0.f, 0.f, 0.f);
  }
  return Glue::get(_blankType, env);
}