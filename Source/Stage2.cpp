/*
  ==============================================================================

    Stage2.cpp
    Created: 4 Jul 2023 1:27:14pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#include "Stage2.h"

Stage2::Stage2()
{
}

Stage2::~Stage2()
{
}

void Stage2::prepare(juce::dsp::ProcessSpec spec, float preGain, float mix)
{
    //PREGAIN1
    preGain2.prepare(spec);
    preGain2.setGainDecibels(preGain);
    
    //MIX1
    mix2.setWetMixProportion(mix);
    mix2.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    mix2.setWetLatency(1.0f);
    mix2.prepare(spec);
    
    //WAVESHAPER1
    waveshaper2.functionToUse = [](float x)
    {
        return x / (std::abs(x) + 1);
    };
    waveshaper2.prepare(spec);
}


void Stage2::process(juce::dsp::AudioBlock<float> drySampsBlock, juce::dsp::AudioBlock<float> processBlock, float preGain, float mix)
{
    //juce::dsp::AudioBlock<float> drySampsBlock1 (buffer);
    mix2.pushDrySamples(drySampsBlock);
    mix2.setWetMixProportion(mix);

    //PREGAIN1
    float newPreGain2 = preGain;
    if(preGain2.getGainDecibels() != newPreGain2)
        preGain2.setGainDecibels(newPreGain2);
    preGain2.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    //WAVESHAPER1
    waveshaper2.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    mix2.mixWetSamples(processBlock);
}
