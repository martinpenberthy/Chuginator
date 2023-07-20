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
    /*waveshaper1.functionToUse = [](float x)
    {
        return x / (std::abs(x) + 1);
    };*/
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
    if(func == "Amp1")
    {
        waveshaper1.functionToUse = [](float x)
        {
            float param = 0.9f;
            return ((x / (std::abs(x) + param) * 1.5f ) / (x * x + (0.0f - 1.0f) * std::abs(x) + 1.0f)) * 0.7f;
        };
        
    }
    else if(func == "Amp2")
    {
        waveshaper1.functionToUse = [](float x)
        {
            return (x * (std::abs(x) + 0.9f)) * 1.5f / (x * x + (0.3f) * (0.1f / std::abs(x)) + 1.0f) * 0.6f;
        };
    }
    else if(func == "Amp3")
    {
        waveshaper1.functionToUse = [](float x)
        {
            return x / (std::abs(x) + 1);
        };
    }
    else if(func == "Tanh")
    {
        waveshaper1.functionToUse = [](float x)
        {
            //return (std::tanh (x * x) / std::tanh(x)) * 0.8f;
            return std::tanh(x);
        };
    }
    else if(func == "Atan")
    {
        waveshaper1.functionToUse = [](float x)
        {
            return std::atan(x);
        };
    }
    else if(func == "HalfRect")
    {
        waveshaper1.functionToUse = [](float x)
        {
            if(x < 0.0f)
                return 0.0f;
            else
                return x * 0.5f;
        };
    }

}

