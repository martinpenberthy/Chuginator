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
    NoiseGateStage()
    {
    }


    ~NoiseGateStage()
    {
    }

    /*
     * juce::dsp::ProcessSpec spec : the ProcessSpec object to use
     * float thresh : The threshold value to set and use
     */
    void prepare(juce::dsp::ProcessSpec spec, float thresh)
    {
        noiseGate.reset();
        noiseGate.prepare(spec);
        
        //Set values for the noise gate
        noiseGate.setThreshold(thresh);
        noiseGate.setRatio(3.0f);
        noiseGate.setAttack(20.0f);
        noiseGate.setRelease(20.0f);
        
        currentThresh = thresh;
    }

    /*
     * juce::dsp::AudioBlock<float> processBlock : the block to process
     * float thresh : The threshold value to set and use
     */
    void process(juce::dsp::AudioBlock<float> processBlock, float thresh)
    {
        if(thresh != currentThresh)
        {
            noiseGate.setThreshold(thresh);
            currentThresh = thresh;
        }
        noiseGate.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    }

    
private:
    juce::dsp::NoiseGate<float> noiseGate;
    
    float currentThresh;
    float currentRatio;
    float currentAttack;
    float currentRelease;
    
    
    
};
