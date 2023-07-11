/*
  ==============================================================================

    EQStage.cpp
    Created: 10 Jul 2023 4:01:33pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#include "EQStage.h"


EQStage::EQStage()
{
    
}


EQStage::~EQStage()
{
    
}

float EQStage::checkGain(float gain)
{
    if(gain == 0.00f)
        return 0.01f;
    else
        return gain;
}

void EQStage::prepare(juce::dsp::ProcessSpec spec, float lowGain, double sampleRate)
{
    lowEQ.prepare(spec);
    *lowEQ.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 100.0f, 0.6f, checkGain(lowGain));
}

void EQStage::process(float lowGain, juce::dsp::AudioBlock<float> processBlock, double sampleRate)
{
    *lowEQ.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 100.0f, 0.6f, checkGain(lowGain));
    lowEQ.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    
}


