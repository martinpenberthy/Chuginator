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

    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"PREEQ", 1}, "PreEQ", 1.0f, 10.0f, 5.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"PREGAIN1", 1}, "Gain1", 0.0f, 48.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"MIX1", 1}, "Mix1", 0.0f, 1.0f, 0.5f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"PREGAIN2", 1}, "Gain2", 0.0f, 48.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"MIX2", 1}, "Mix2", 0.0f, 1.0f, 0.5f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"PREGAIN3", 1}, "Gain3", 0.0f, 48.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"MIX3", 1}, "Mix3", 0.0f, 1.0f, 0.5f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"OUTPUTGAIN", 1}, "OutputGain", -96.0f, 48.0f, 0.0f));

    return {params.begin(), params.end()};
}

void ChuginatorAudioProcessor::updatePreEQ()
{
    float preEQFreq = *treeState.getRawParameterValue("PREEQ");
    
    *preEQ.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), preEQFreq * 1000.0f, 0.2f, 0.3f);
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
    
    //INPUTGAIN
    inputGain.prepare(spec);
    inputGain.setGainDecibels(*treeState.getRawParameterValue("INPUTGAIN"));
    
    //PREEQ
    preEQ.prepare(spec);
    updatePreEQ();

    /*=====================================================================*/
    gainStage1.prepare(spec, *treeState.getRawParameterValue("PREGAIN1"), *treeState.getRawParameterValue("MIX1"));
    //PREGAIN1
    /*preGain1.prepare(spec);
    preGain1.setGainDecibels(*treeState.getRawParameterValue("PREGAIN1"));
    
    //MIX1
    mix1.setWetMixProportion(*treeState.getRawParameterValue("MIX1"));
    mix1.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    mix1.setWetLatency(1.0f);
    mix1.prepare(spec);
    
    //WAVESHAPER1
    waveshaper1.functionToUse = [](float x)
    {
        return x / (std::abs(x) + 1);
    };
    waveshaper1.prepare(spec);
    */
    
    /*=====================================================================*/
    //PREGAIN2
    preGain2.prepare(spec);
    preGain2.setGainDecibels(*treeState.getRawParameterValue("PREGAIN2"));
    
    //MIX2
    mix2.setWetMixProportion(*treeState.getRawParameterValue("MIX2"));
    mix2.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    mix2.setWetLatency(1.0f);
    mix2.prepare(spec);
    
    //WAVESHAPER2
    waveshaper2.functionToUse = [](float x)
    {
        return x / (std::abs(x) + 1);
    };
    waveshaper2.prepare(spec);
    
    
    /*=====================================================================*/
    //PREGAIN3
    preGain3.prepare(spec);
    preGain3.setGainDecibels(*treeState.getRawParameterValue("PREGAIN3"));
    
    //MIX3
    mix3.setWetMixProportion(*treeState.getRawParameterValue("MIX3"));
    mix3.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    mix3.setWetLatency(1.0f);
    mix3.prepare(spec);
    
    //WAVESHAPER3
    waveshaper3.functionToUse = [](float x)
    {
        return x / (std::abs(x) + 1);
    };
    waveshaper3.prepare(spec);
    
    
    

    //OUTPUTGAIN
    outputGain.prepare(spec);
    outputGain.setGainDecibels(*treeState.getRawParameterValue("OUTPUTGAIN"));
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

    /*=====================================================================*/
    //INPUTGAIN
    float newInputGain = *treeState.getRawParameterValue("INPUTGAIN");
    if(inputGain.getGainDecibels() != newInputGain)
        inputGain.setGainDecibels(newInputGain);
    
    juce::dsp::AudioBlock<float> processBlock (buffer);
    inputGain.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    /*=====================================================================*/
    //PREEQ
    updatePreEQ();
    preEQ.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    /*=====================================================================*/
    juce::dsp::AudioBlock<float> drySampsBlock1 (buffer);
    gainStage1.process(drySampsBlock1, processBlock,*treeState.getRawParameterValue("PREGAIN1"), *treeState.getRawParameterValue("MIX1"));
    
    //MIXPREP1
    /*juce::dsp::AudioBlock<float> drySampsBlock1 (buffer);
    mix1.pushDrySamples(drySampsBlock1);
    mix1.setWetMixProportion(*treeState.getRawParameterValue("MIX1"));

    //PREGAIN1
    float newPreGain1 = *treeState.getRawParameterValue("PREGAIN1");
    if(preGain1.getGainDecibels() != newPreGain1)
        preGain1.setGainDecibels(newPreGain1);
    preGain1.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    //WAVESHAPER1
    waveshaper1.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    mix1.mixWetSamples(processBlock);*/
    
    
    /*=====================================================================*/
    //MIXPREP2
    juce::dsp::AudioBlock<float> drySampsBlock2 (buffer);
    mix2.pushDrySamples(drySampsBlock2);
    mix2.setWetMixProportion(*treeState.getRawParameterValue("MIX2"));
    
    //PREGAIN2
    float newPreGain2 = *treeState.getRawParameterValue("PREGAIN2");
    if(preGain2.getGainDecibels() != newPreGain2)
        preGain2.setGainDecibels(newPreGain2);
    preGain2.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    //WAVESHAPER2
    waveshaper2.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    mix2.mixWetSamples(processBlock);
    
    
    /*=====================================================================*/
    //MIXPREP3
    juce::dsp::AudioBlock<float> drySampsBlock3 (buffer);
    mix3.pushDrySamples(drySampsBlock3);
    mix3.setWetMixProportion(*treeState.getRawParameterValue("MIX3"));
    
    //PREGAIN3
    float newPreGain3 = *treeState.getRawParameterValue("PREGAIN3");
    if(preGain3.getGainDecibels() != newPreGain3)
        preGain3.setGainDecibels(newPreGain3);
    preGain3.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    //WAVESHAPER3
    waveshaper3.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    mix3.mixWetSamples(processBlock);
    
    
    
    
    
    /*=====================================================================*/
    //OUTPUTGAIN
    float newOutputGain = *treeState.getRawParameterValue("OUTPUTGAIN");
    if(outputGain.getGainDecibels() != newOutputGain)
        outputGain.setGainDecibels(newOutputGain);
    
    //juce::dsp::AudioBlock<float> outputGainBlock (buffer);
    outputGain.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
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
