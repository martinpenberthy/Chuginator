/*
  ==============================================================================

    Stage1.h
    Created: 4 Jul 2023 12:39:14pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class GainStage
{
    public:
        GainStage(std::string func);
        GainStage();
        ~GainStage();
        
        void prepare(juce::dsp::ProcessSpec spec, float preGain, float mix);
        void process(juce::dsp::AudioBlock<float> drySampsBlock, juce::dsp::AudioBlock<float> processBlock, float preGain, float mix);
        void setWaveshapeFunc(std::string func);
    
    
        //juce::StringArray distTypeListCopy;
    
    private:
        juce::dsp::Gain<float> preGain1;
        juce::dsp::WaveShaper<float> waveshaper1;
        juce::dsp::DryWetMixer<float> mix1;
    
};
