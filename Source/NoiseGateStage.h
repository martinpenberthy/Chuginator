/*
  ==============================================================================

    NoiseGateStage.h
    Created: 12 Jul 2023 1:41:31pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class NoiseGateStage : public juce::Component
{
public:
    NoiseGateStage();
    ~NoiseGateStage();

    void prepare(juce::dsp::ProcessSpec spec, float thresh);//, float ratio, float attack, float release);
    void process(juce::dsp::AudioBlock<float> processBlock, float thresh);//float ratio, float attack, float release);
    
private:
    juce::dsp::NoiseGate<float> noiseGate;
    
    float currentThresh;
    float currentRatio;
    float currentAttack;
    float currentRelease;
    
    
    
};
