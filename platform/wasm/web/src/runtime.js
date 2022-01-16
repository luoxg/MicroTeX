'use strict'

import Module from "../gen/clatexmath-wasm";

let runtime = {};

function initRuntime() {
  return Module().then(r => {
    runtime = r;
    return runtime;
  });
}

export {runtime, initRuntime};
