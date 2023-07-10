/*
  ==============================================================================

    EQStage.h
    Created: 10 Jul 2023 4:01:33pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class EQStage
{
    public:
        EQStage();
        ~EQStage();
        
        void prepare(float lowGain, double sampleRate);
    
    private:
        using IIRFilter = juce::dsp::IIR::Filter<float>;
        using IIRCoefs = juce::dsp::IIR::Coefficients<float>;
        
        juce::dsp::ProcessorDuplicator<IIRFilter, IIRCoefs> lowEQ, midEQ, highEQ;

    
};
