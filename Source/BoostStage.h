/*
  ==============================================================================

    BoostStage.h
    Created: 7 Aug 2023 7:41:37pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>


class BoostStage
{
public:
    BoostStage();
    ~BoostStage();
    
    void prepare(juce::dsp::ProcessSpec spec, double sampleRate);
    void process(juce::dsp::AudioBlock<float> processBlock, juce::dsp::AudioBlock<float> dryBlock, double sampleRate);


private:
    using IIRFilter = juce::dsp::IIR::Filter<float>;
    using IIRCoefs = juce::dsp::IIR::Coefficients<float>;
    
    juce::dsp::ProcessorDuplicator<IIRFilter, IIRCoefs> highBoostEQ, lowCutEQ;
    
    juce::dsp::Gain<float> internalPreGain;
    juce::dsp::DryWetMixer<float> internalBoostMix;
    
    juce::dsp::WaveShaper<float> internalWaveshaper;
    
    //juce::dsp::ProcessorDuplicator<IIRFilter, IIRCoefs> internalLowEQ;
    
};
