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

void EQStage::prepare(juce::dsp::ProcessSpec spec, float lowGain, float midGain, float highGain, double sampleRate)
{
    lowEQ.reset();
    lowEQ.prepare(spec);
    *lowEQ.state = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 300.0f, 1.3f, checkGain(lowGain));
    
    midEQ.reset();
    midEQ.prepare(spec);
    *midEQ.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 500.0f, 3.1f, checkGain(midGain));
    
    highEQ.reset();
    highEQ.prepare(spec);
    *highEQ.state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 1700.0f, 1.9f, checkGain(highGain));
}

void EQStage::process(float lowGain, float midGain, float highGain, juce::dsp::AudioBlock<float> processBlock, double sampleRate)
{
    //LOW
    *lowEQ.state = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 300.0f, 1.3f, checkGain(lowGain));
    lowEQ.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    //MID
    *midEQ.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 500.0f, 3.1f, checkGain(midGain));
    midEQ.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    
    //HIGH
    *highEQ.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 1700.0f, 1.9f, checkGain(highGain));
    highEQ.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
}


