/*
  ==============================================================================

    NoiseGateStage.cpp
    Created: 12 Jul 2023 1:41:31pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#include "NoiseGateStage.h"


NoiseGateStage::NoiseGateStage()
{
}


NoiseGateStage::~NoiseGateStage()
{
}

void NoiseGateStage::prepare(juce::dsp::ProcessSpec spec, float thresh, float ratio, float attack, float release)
{
    noiseGate.prepare(spec);
    
    noiseGate.setThreshold(thresh);
    noiseGate.setRatio(ratio);
    noiseGate.setAttack(attack);
    noiseGate.setRelease(release);
    
    currentThresh = thresh;
    currentRatio = ratio;
    currentAttack = attack;
    currentRelease = release;
}

void NoiseGateStage::process(juce::dsp::AudioBlock<float> processBlock, float thresh, float ratio, float attack, float release)
{
    if(thresh != currentThresh)
    {
        noiseGate.setThreshold(thresh);
        currentThresh = thresh;
    }
    
    if(ratio != currentRatio)
    {
        noiseGate.setRatio(ratio);
        currentRatio = ratio;
    }
    
    if(attack != currentAttack)
    {
        noiseGate.setAttack(attack);
        currentAttack = attack;
    }
    
    if(release != currentRelease)
    {
        noiseGate.setRelease(release);
        currentRelease = release;   
    }
    
    noiseGate.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
}

