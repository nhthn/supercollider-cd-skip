// PluginCDSkip.hpp
// Nathan Ho (nathan.waikin.ho@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace SCCDSkip {

class CDSkip : public SCUnit {
public:
    CDSkip();

    // Destructor
    // ~CDSkip();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace SCCDSkip
