// PluginCDSkip.cpp
// Nathan Ho (nathan.waikin.ho@gmail.com)

#include "SC_PlugIn.hpp"
#include "CDSkip.hpp"

static InterfaceTable* ft;

namespace SCCDSkip {

CDSkip::CDSkip() {
    mCalcFunc = make_calc_function<CDSkip, &CDSkip::next>();
    next(1);
}

void CDSkip::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(1);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }
}

} // namespace SCCDSkip

PluginLoad(CDSkipUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<SCCDSkip::CDSkip>(ft, "CDSkip", false);
}
