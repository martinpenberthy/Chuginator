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
    //PREGAIN2
    preGain2.prepare(spec);
    preGain2.setGainDecibels(preGain);
    
    //MIX2
    mix2.setWetMixProportion(mix);
    mix2.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    mix2.setWetLatency(1.0f);
    mix2.prepare(spec);
    
    //WAVESHAPER2
    /*waveshaper2.functionToUse = [](float x)
    {
        return x / (std::abs(x) + 1);
    };*/
    waveshaper2.prepare(spec);
}


void Stage2::process(juce::dsp::AudioBlock<float> drySampsBlock, juce::dsp::AudioBlock<float> processBlock, float preGain, float mix)
{
    //juce::dsp::AudioBlock<float> drySampsBlock1 (buffer);
    mix2.pushDrySamples(drySampsBlock);
    mix2.setWetMixProportion(mix);

    //PREGAIN2
    float newPreGain2 = preGain;
    if(preGain2.getGainDecibels() != newPreGain2)
        preGain2.setGainDecibels(newPreGain2);
    preGain2.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    //WAVESHAPER2
    waveshaper2.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    mix2.mixWetSamples(processBlock);
}


void Stage2::setWaveshapeFunc(std::string func)
{
    if(func == "Amp1")
    {
        waveshaper2.functionToUse = [](float x)
        {
            float param = 0.9f;
            return ((x / (std::abs(x) + param) * 1.5f ) / (x * x + (0.0f - 1.0f) * std::abs(x) + 1.0f)) * 0.7f;
        };
        
    }
    else if(func == "Amp2")
    {
        waveshaper2.functionToUse = [](float x)
        {
            return (x * (std::abs(x) + 0.9f)) * 1.5f / (x * x + (0.3f) * (0.1f / std::abs(x)) + 1.0f) * 0.6f;
        };
    }
    else if(func == "Amp3")
    {
        waveshaper2.functionToUse = [](float x)
        {
            return x / (std::abs(x) + 1);
        };
    }
    else if(func == "Tanh")
    {
        waveshaper2.functionToUse = [](float x)
        {
            //return (std::tanh (x * x) / std::tanh(x)) * 0.8f;
            return std::tanh(x);
        };
    }
    else if(func == "Atan")
    {
        waveshaper2.functionToUse = [](float x)
        {
            return std::atan(x);
        };
    }
    else if(func == "HalfRect")
    {
        waveshaper2.functionToUse = [](float x)
        {
            if(x < 0.0f)
                return 0.0f;
            else
                return x * 0.5f;
        };
    }else if (func == "Screamer")
    {
        waveshaper2.functionToUse = [](float x)
        {
            return (std::tanh(x * x) / std::tanh(x)) * 0.9f;
        };
    }

}

