/*
  ==============================================================================

    BoostStage.cpp
    Created: 7 Aug 2023 7:41:37pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#include "BoostStage.h"

BoostStage::BoostStage()
{
    
}


BoostStage::~BoostStage()
{
    
}

void BoostStage::prepare(juce::dsp::ProcessSpec spec, double sampleRate)
{
    highBoostEQ.prepare(spec);
    *highBoostEQ.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 2300.0f, 1.0f, 3.0f);
    
    //internalLowEQ.prepare(spec);
    //*internalLowEQ.state = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 400.0f, 0.4f, 0.1f);

}

void BoostStage::process( juce::dsp::AudioBlock<float> processBlock, double sampleRate)
{
    highBoostEQ.process(juce::dsp::ProcessContextReplacing<float>(processBlock));

    //internalLowEQ.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
}


