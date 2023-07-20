/*
  ==============================================================================

    Stage2.h
    Created: 4 Jul 2023 1:27:14pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Stage2
{
    public:
        Stage2();
        ~Stage2();
        
        void prepare(juce::dsp::ProcessSpec spec, float preGain, float mix);
        void process(juce::dsp::AudioBlock<float> drySampsBlock, juce::dsp::AudioBlock<float> processBlock, float preGain, float mix);
        void setWaveshapeFunc(std::string func);

    
    private:
        juce::dsp::Gain<float> preGain2;
        juce::dsp::WaveShaper<float> waveshaper2;
        juce::dsp::DryWetMixer<float> mix2;
};
