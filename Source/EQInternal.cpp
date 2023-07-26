/*
  ==============================================================================

    EQInternal.cpp
    Created: 26 Jul 2023 3:58:14pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#include "EQInternal.h"
EQInternal::EQInternal()
{
    
}


EQInternal::~EQInternal()
{
    
}



void EQInternal::prepare(juce::dsp::ProcessSpec spec, double sampleRate)
{
    highBoostEQ.prepare(spec);
    *highBoostEQ.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 1500.0f, 0.6f, 1.5f);

}

void EQInternal::process( juce::dsp::AudioBlock<float> processBlock, double sampleRate)
{
    highBoostEQ.process(juce::dsp::ProcessContextReplacing<float>(processBlock));

}


