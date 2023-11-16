/*
  ==============================================================================

    Stage1.cpp
    Created: 4 Jul 2023 12:39:14pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#include "GainStage.h"


GainStage::GainStage(std::string func)
{
    setWaveshapeFunc(func);
}

GainStage::GainStage()
{
}

GainStage::~GainStage()
{
}

void GainStage::prepare(juce::dsp::ProcessSpec spec, float preGain, float mix)
{
    
    //PREGAIN1
    preGain1.reset();
    preGain1.prepare(spec);
    preGain1.setGainDecibels(preGain);
    
    //MIX1
    mix1.reset();
    mix1.setWetMixProportion(mix);
    mix1.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    mix1.setWetLatency(1.0f);
    mix1.prepare(spec);
    
    //WAVESHAPER1
    /*waveshaper1.functionToUse = [](float x)
    {
        return x / (std::abs(x) + 1);
    };*/
    //      waveshaper1.reset();
    waveshaper1.reset();
    waveshaper1.prepare(spec);
}


void GainStage::process(juce::dsp::AudioBlock<float> drySampsBlock, juce::dsp::AudioBlock<float> processBlock, float preGain, float mix)
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


void GainStage::setWaveshapeFunc(std::string func)
{
    if(func == "Amp1")
    {
        waveshaper1.functionToUse = [](float x)
        {
            float param = 0.5f;
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
    else if(func == "HardClip")
    {
        waveshaper1.functionToUse = [](float x)
        {
            if(x < 0.0f && x < -0.7f)
                return -0.7f;
            else if(x > 0.0f && x > 0.7f)
                return 0.7f;
            else
                return x;
            
        };
    }else if (func == "Screamer")
    {
        waveshaper1.functionToUse = [](float x)
        {
            return (std::tanh(x * x) / std::tanh(x)) * 0.9f;
        };
    }

}

