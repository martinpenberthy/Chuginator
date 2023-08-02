/*
  ==============================================================================

    Compressor.cpp
    Created: 2 Aug 2023 3:19:16pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#include "Compressor.h"

Compressor::Compressor()
{
}

Compressor::~Compressor()
{
}

void Compressor::prepare(juce::dsp::ProcessSpec spec, float thresh, float ratio, float attack, float release)
{
    compressor.prepare(spec);
    
    compressor.setThreshold(thresh);
    compressor.setRatio(ratio);
    compressor.setAttack(attack);
    compressor.setRelease(release);
}

void Compressor::process(juce::dsp::AudioBlock<float> processBlock, float thresh, float ratio, float attack, float release)
{
    if(thresh != currentThresh)
    {
        compressor.setThreshold(thresh);
        currentThresh = thresh;
    }
    
    if(ratio != currentRatio)
    {
        compressor.setRatio(ratio);
        currentRatio = ratio;
    }
    
    if(attack != currentAttack)
    {
        compressor.setAttack(attack);
        currentAttack = attack;
    }
    
    if(release != currentRelease)
    {
        compressor.setRelease(release);
        currentRelease = release;
    }
    
    compressor.process(processBlock);
    
}



