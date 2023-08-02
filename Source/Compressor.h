/*
  ==============================================================================

    Compressor.h
    Created: 2 Aug 2023 3:19:16pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Compressor
{
public:
    Compressor();
    ~Compressor();
    
    void prepare(juce::dsp::ProcessSpec spec, float thresh, float ratio, float attack, float release);
    void process(juce::dsp::AudioBlock<float> processBlock, float thresh, float ratio, float attack, float release);

private:
    juce::dsp::Compressor<float> compressor;
    float currentThresh;
    float currentRatio;
    float currentAttack;
    float currentRelease;
    
    
};
