/*
  ==============================================================================

    NoiseGateStage.h
    Created: 12 Jul 2023 1:41:31pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class NoiseGateStage
{
public:
    NoiseGateStage();
    ~NoiseGateStage();

    
private:
    juce::dsp::NoiseGate<float> noiseGate;
    
    
    
};
