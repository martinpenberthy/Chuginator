/*
  ==============================================================================

    Stage3.cpp
    Created: 6 Jul 2023 1:50:34pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#include "Stage3.h"

Stage3::Stage3()
{
}

Stage3::~Stage3()
{
}

void Stage3::prepare(juce::dsp::ProcessSpec spec, float preGain, float mix)
{
    //PREGAIN3
    preGain3.prepare(spec);
    preGain3.setGainDecibels(preGain);
    
    //MIX3
    mix3.setWetMixProportion(mix);
    mix3.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    mix3.setWetLatency(1.0f);
    mix3.prepare(spec);
    
    //WAVESHAPER3
    waveshaper3.functionToUse = [](float x)
    {
        return x / (std::abs(x) + 1);
    };
    waveshaper3.prepare(spec);
}


void Stage3::process(juce::dsp::AudioBlock<float> drySampsBlock, juce::dsp::AudioBlock<float> processBlock, float preGain, float mix)
{
    //juce::dsp::AudioBlock<float> drySampsBlock1 (buffer);
    mix3.pushDrySamples(drySampsBlock);
    mix3.setWetMixProportion(mix);

    //PREGAIN3
    float newPreGain3 = preGain;
    if(preGain3.getGainDecibels() != newPreGain3)
        preGain3.setGainDecibels(newPreGain3);
    preGain3.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    //WAVESHAPER3
    waveshaper3.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    mix3.mixWetSamples(processBlock);
}
