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
    *highBoostEQ.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 2300.0f, 2.0f, 3.0f);
    
    internalBoostMix.setWetMixProportion(0.5f);
    internalBoostMix.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    internalBoostMix.setWetLatency(1.0f);
    internalBoostMix.prepare(spec);
    
    internalWaveshaper.prepare(spec);
    
    internalWaveshaper.functionToUse = [](float x)
    {
        return (std::tanh(x * x) / std::tanh(x)) * 0.9f;
    };
    
        
}

void BoostStage::process(juce::dsp::AudioBlock<float> processBlock, juce::dsp::AudioBlock<float> dryBlock, double sampleRate)
{
    internalBoostMix.pushDrySamples(dryBlock);
    
    highBoostEQ.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    internalWaveshaper.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    internalBoostMix.mixWetSamples(processBlock);
    
}


