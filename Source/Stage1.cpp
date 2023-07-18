/*
  ==============================================================================

    Stage1.cpp
    Created: 4 Jul 2023 12:39:14pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#include "Stage1.h"


Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}

void Stage1::prepare(juce::dsp::ProcessSpec spec, float preGain, float mix)
{
    //PREGAIN1
    preGain1.prepare(spec);
    preGain1.setGainDecibels(preGain);
    
    //MIX1
    mix1.setWetMixProportion(mix);
    mix1.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    mix1.setWetLatency(1.0f);
    mix1.prepare(spec);
    
    //WAVESHAPER1
    waveshaper1.functionToUse = [](float x)
    {
        return x / (std::abs(x) + 1);
    };
    waveshaper1.prepare(spec);
}


void Stage1::process(juce::dsp::AudioBlock<float> drySampsBlock, juce::dsp::AudioBlock<float> processBlock, float preGain, float mix)
{
    //juce::dsp::AudioBlock<float> drySampsBlock1 (buffer);
    mix1.pushDrySamples(drySampsBlock);
    mix1.setWetMixProportion(mix);

    //PREGAIN1
    float newPreGain1 = preGain;
    if(preGain1.getGainDecibels() != newPreGain1)
        preGain1.setGainDecibels(newPreGain1);
    preGain1.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    //WAVESHAPER1
    waveshaper1.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    mix1.mixWetSamples(processBlock);
}



void Stage1::setWaveshapeFunc(std::string func)
{
}
