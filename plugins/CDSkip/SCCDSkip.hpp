#pragma once

#include <memory>

#include "SC_PlugIn.hpp"
#include "CDSkip.hpp"

namespace SCCDSkip {

class SCCDSkip : public SCUnit {
public:
    SCCDSkip();
    ~SCCDSkip();

private:
    void next(int nSamples);
    void clear(int nSamples);

    std::unique_ptr<CDSkip::CDSkip> m_core;
    float* m_memory;

    float m_skipTriggerLast;
    float m_resetTriggerLast;
};

} // namespace SCCDSkip
