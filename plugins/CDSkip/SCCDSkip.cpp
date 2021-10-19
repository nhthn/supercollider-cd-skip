#include <limits>

#include "SC_PlugIn.hpp"
#include "SCCDSkip.hpp"

static InterfaceTable* ft;

namespace SCCDSkip {

SCCDSkip::SCCDSkip()
    : m_skipTriggerLast(0),
    m_resetTriggerLast(0)
{
    clear(1);

    mCalcFunc = make_calc_function<SCCDSkip, &SCCDSkip::next>();

    float sampleRate = mWorld->mSampleRate;
    float maxDelay = in0(2);

    int memoryLength = CDSkip::CDSkip::getMemoryLength(sampleRate, maxDelay);
    m_memory = static_cast<float*>(RTAlloc(mWorld, sizeof(float) * memoryLength));
    if (m_memory == nullptr) {
        mCalcFunc = make_calc_function<SCCDSkip, &SCCDSkip::clear>();
        return;
    }

    uint32_t seed = 1 + mParent->mRGen->irand(std::numeric_limits<int32>::max() - 1);

    m_core = std::make_unique<CDSkip::CDSkip>(sampleRate, maxDelay, m_memory, seed);
    m_core->setAutoMode(true);
}

SCCDSkip::~SCCDSkip() {
    RTFree(mWorld, m_memory);
}

void SCCDSkip::clear(int nSamples) {
    for (int i = 0; i < nSamples; i++) {
        out(0)[i] = 0;
        out(1)[i] = 0;
    }
}

void SCCDSkip::next(int nSamples) {
    const float* inLeft = in(0);
    const float* inRight = in(1);

    float* outLeft = out(0);
    float* outRight = out(1);

    bool autoMode = in0(3) > 0;
    float autoSpeed = in0(4);
    const float* skipTrigger = in(5);
    const float* resetTrigger = in(6);
    const float* pos = in(7);

    bool freeze = in0(8) > 0;
    bool clean = in0(9) > 0;

    m_core->setAutoMode(autoMode);
    m_core->setAutoModeSpeed(autoSpeed);
    m_core->setCleanMode(clean);
    m_core->setFrozen(freeze);

    for (int i = 0; i < nSamples; i++) {
        if (m_skipTriggerLast <= 0 && skipTrigger[i] > 0) {
            m_core->skip(pos[i]);
        } else if (m_resetTriggerLast <= 0 && resetTrigger[i] > 0) {
            m_core->skipRelativeToWritePos(pos[i]);
        }
        m_skipTriggerLast = skipTrigger[i];
        m_resetTriggerLast = resetTrigger[i];

        auto outFrame = m_core->process(std::make_pair(inLeft[i], inRight[i]));
        outLeft[i] = outFrame.first;
        outRight[i] = outFrame.second;
    }
}

} // namespace SCCDSkip

PluginLoad(CDSkipUGens) {
    ft = inTable;
    registerUnit<SCCDSkip::SCCDSkip>(ft, "CDSkip", false);
}
