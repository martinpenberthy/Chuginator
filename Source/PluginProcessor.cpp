/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChuginatorAudioProcessor::ChuginatorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), treeState(*this, nullptr, juce::Identifier("PARAMETERS"), createParameterLayout())
#endif
{
    treeState.state.addListener(this);

}

ChuginatorAudioProcessor::~ChuginatorAudioProcessor()
{
}


juce::AudioProcessorValueTreeState::ParameterLayout ChuginatorAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    //Input and Output parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"INPUTGAIN", 1}, "InputGain", -96.0f, 48.0f, 0.0f));

    return {params.begin(), params.end()};
}

//==============================================================================
const juce::String ChuginatorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChuginatorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChuginatorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ChuginatorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ChuginatorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChuginatorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChuginatorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChuginatorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ChuginatorAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChuginatorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ChuginatorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    inputGain.prepare(spec);
    inputGain.setGainDecibels(*treeState.getRawParameterValue("INPUTGAIN"));
}

void ChuginatorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChuginatorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ChuginatorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //INPUTGAIN
    inputGain.setGainDecibels(*treeState.getRawParameterValue("INPUTGAIN"));
    juce::dsp::AudioBlock<float> inputGainBlock (buffer);
    inputGain.process(juce::dsp::ProcessContextReplacing<float>(inputGainBlock));
}

//==============================================================================
bool ChuginatorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ChuginatorAudioProcessor::createEditor()
{
    return new ChuginatorAudioProcessorEditor (*this);
}

//==============================================================================
void ChuginatorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ChuginatorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChuginatorAudioProcessor();
}
