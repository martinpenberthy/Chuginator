/*
  ==============================================================================

    EQInternal.h
    Created: 26 Jul 2023 3:58:14pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class EQInternal
{
public:
    EQInternal();
    ~EQInternal();
    
    void prepare(juce::dsp::ProcessSpec spec, double sampleRate);
    void process(juce::dsp::AudioBlock<float> processBlock, double sampleRate);


private:
    using IIRFilter = juce::dsp::IIR::Filter<float>;
    using IIRCoefs = juce::dsp::IIR::Coefficients<float>;
    
    juce::dsp::ProcessorDuplicator<IIRFilter, IIRCoefs> highBoostEQ;
    
    juce::dsp::ProcessorDuplicator<IIRFilter, IIRCoefs> internalLowEQ;
    
};
