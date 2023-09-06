/*
  ==============================================================================

    Stage3.h
    Created: 6 Jul 2023 1:50:34pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Stage3
{
    public:
        Stage3();
        Stage3(std::string func);
        ~Stage3();
        
        void prepare(juce::dsp::ProcessSpec spec, float preGain, float mix);
        void process(juce::dsp::AudioBlock<float> drySampsBlock, juce::dsp::AudioBlock<float> processBlock, float preGain, float mix);
        void setWaveshapeFunc(std::string func);
    
    private:
        juce::dsp::Gain<float> preGain3;
        juce::dsp::WaveShaper<float> waveshaper3;
        juce::dsp::DryWetMixer<float> mix3;
};
