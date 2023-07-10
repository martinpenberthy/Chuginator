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


void EQStage::prepare(float lowGain, double sampleRate)
{
    lowEQ.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 100.0f, 0.6f, lowGain);
}

void EQStage::process(float lowGain, juce::dsp::AudioBlock<float> processBlock, double sampleRate)
{
    lowEQ.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 100.0f, 0.6f, lowGain);
    lowEQ.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    
}

