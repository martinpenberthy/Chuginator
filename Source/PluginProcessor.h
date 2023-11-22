/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GainStage.h"
#include "EQStage.h"
#include "EQInternal.h"
#include "NoiseGateStage.h"
#include "BoostStage.h"
#include "PresetManager.h"

#include <iostream>
#include <fstream>
#include <cmath>

//==============================================================================
/**
*/
class ChuginatorAudioProcessor  : public juce::AudioProcessor,   public juce::ValueTree::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    ChuginatorAudioProcessor();
    ~ChuginatorAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void updatePreEQ();
    void setFunctionToUse(int gainStageNum, std::string func);
    std::string getWaveshapeFuncParam(int gainStageNum);
    std::string getParamIntToString(int numOfDistType);
    
    void sanitizeBuffer(juce::AudioBuffer<float>& buffer);
    Service::PresetManager& getPresetManager(){return *presetManager;}
    
    juce::AudioProcessorValueTreeState treeState;
    
    juce::File root, savedFile;
    juce::dsp::Convolution irLoader;
    juce::ValueTree IRFilePathTree;

    
    std::string waveshapeFunction1;
    std::string waveshapeFunctionCurrent1;
    
    std::string waveshapeFunction2;
    std::string waveshapeFunctionCurrent2;
    
    std::string waveshapeFunction3;
    std::string waveshapeFunctionCurrent3;
    
private:
    juce::dsp::ProcessSpec spec;

    juce::dsp::Gain<float> inputGain;
    
    
    using IIRFilter = juce::dsp::IIR::Filter<float>;
    using IIRCoefs = juce::dsp::IIR::Coefficients<float>;
    juce::dsp::ProcessorDuplicator<IIRFilter, IIRCoefs> preEQ;
    
    EQInternal internalEQ;
    //GAIN1
    GainStage gainStage1;

    //Stage2 gainStage2;
    GainStage gainStage2;
   // Stage3 gainStage3;
    GainStage gainStage3;
    
    EQStage EQStage;
    
    NoiseGateStage noiseGateStage;
    BoostStage boostStage;
    
    juce::dsp::Gain<float> outputGain;
    
    std::ofstream debugFile;
    
    std::unique_ptr<Service::PresetManager> presetManager;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChuginatorAudioProcessor)
};
