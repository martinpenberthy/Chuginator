/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
    
    juce::AudioProcessorValueTreeState treeState;


private:
    juce::dsp::ProcessSpec spec;

    juce::dsp::Gain<float> inputGain;
    
    
    using IIRFilter = juce::dsp::IIR::Filter<float>;
    using IIRCoefs = juce::dsp::IIR::Coefficients<float>;
    juce::dsp::ProcessorDuplicator<IIRFilter, IIRCoefs> preEQ;
    
    //GAIN1
    juce::dsp::Gain<float> preGain1;
    juce::dsp::WaveShaper<float> waveshaper1;
    
    juce::dsp::Gain<float> preGain2;
    juce::dsp::WaveShaper<float> waveshaper2;
    
    juce::dsp::DryWetMixer<float> mix1;
    juce::dsp::DryWetMixer<float> mix2;
    
    juce::dsp::Gain<float> outputGain;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChuginatorAudioProcessor)
};
