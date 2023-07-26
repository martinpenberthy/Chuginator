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
    variableTree =
    {
        "Variables", {},
        {
            { "Group", {{"name", "IR Vars"}},
                {
                    {"Parameter", {{"id", "file1"}, {"value", "/"}}},
                    {"Parameter", {{"id", "root"}, {"value", "/"}}}
                }
            }
        }
    };
    

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
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID {"GAIN1ONOFF", 1}, "Gain1OnOff", false));
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {"TYPE1", 1}, "Type1",
                                                                  juce::StringArray{
                                                                                    "Amp1",
                                                                                    "Amp2",
                                                                                    "Amp3",
                                                                                    "Tanh",
                                                                                    "Atan",
                                                                                    "HalfRect"
                                                                                },
                                                                                    1));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"PREGAIN2", 1}, "Gain2", 0.0f, 48.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"MIX2", 1}, "Mix2", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID {"GAIN2ONOFF", 1}, "Gain2OnOff", false));
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {"TYPE2", 1}, "Type2",
                                                                  juce::StringArray{
                                                                                    "Amp1",
                                                                                    "Amp2",
                                                                                    "Amp3",
                                                                                    "Tanh",
                                                                                    "Atan",
                                                                                    "HalfRect"
                                                                                },
                                                                                    1));
    
    
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"PREGAIN3", 1}, "Gain3", 0.0f, 48.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"MIX3", 1}, "Mix3", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID {"GAIN3ONOFF", 1}, "Gain3OnOff", false));
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {"TYPE3", 1}, "Type3",
                                                                  juce::StringArray{
                                                                                    "Amp1",
                                                                                    "Amp2",
                                                                                    "Amp3",
                                                                                    "Tanh",
                                                                                    "Atan",
                                                                                    "HalfRect"
                                                                                },
                                                                                    1));
    
    //EQs
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"LOW", 1}, "Low", 0.0f, 2.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"MID", 1}, "Mid", 0.0f, 2.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"HIGH", 1}, "High", 0.0f, 2.0f, 1.0f));
    
    //Noise Gate
    params.push_back(std::make_unique<juce::AudioParameterInt>(juce::ParameterID{"THRESHOLD", 1}, "Threshold", -96, 6, 1));
    params.push_back(std::make_unique<juce::AudioParameterInt>(juce::ParameterID{"RATIO", 1}, "Ratio", 1, 10, 1));
    params.push_back(std::make_unique<juce::AudioParameterInt>(juce::ParameterID{"ATTACK", 1}, "Attack", 1, 300, 20));
    params.push_back(std::make_unique<juce::AudioParameterInt>(juce::ParameterID{"RELEASE", 1}, "Release", 1, 700, 20));
    
    
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

    internalLowEQ.prepare(spec);
    *internalLowEQ.state = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 400.0f, 0.4f, 0.1f);
    
    /*=====================================================================*/
    //gainStage1.distTypeListCopy = distTypeList;
    gainStage1.prepare(spec, *treeState.getRawParameterValue("PREGAIN1"),
                             *treeState.getRawParameterValue("MIX1"));
    
    std::string gainStage1Func = getWaveshapeFuncParam(1);
    setFunctionToUse(1, gainStage1Func);
    waveshapeFunction1 = gainStage1Func;

    
    /*=====================================================================*/
    gainStage2.prepare(spec, *treeState.getRawParameterValue("PREGAIN2"),
                             *treeState.getRawParameterValue("MIX2"));
    
    std::string gainStage2Func = getWaveshapeFuncParam(2);
    setFunctionToUse(2, gainStage2Func);
    waveshapeFunction2 = gainStage2Func;
    
    /*=====================================================================*/
    gainStage3.prepare(spec, *treeState.getRawParameterValue("PREGAIN3"),
                             *treeState.getRawParameterValue("MIX3"));
    
    std::string gainStage3Func = getWaveshapeFuncParam(3);
    setFunctionToUse(3, gainStage3Func);
    waveshapeFunction3 = gainStage3Func;
    
    /*=====================================================================*/
    //EQ
    EQStage.prepare(spec, *treeState.getRawParameterValue("LOW"),
                          *treeState.getRawParameterValue("MID"),
                          *treeState.getRawParameterValue("HIGH"),
                          sampleRate);
    //Noise Gate
    noiseGateStage.prepare(spec, *treeState.getRawParameterValue("THRESHOLD"),
                                 *treeState.getRawParameterValue("RATIO"),
                                 *treeState.getRawParameterValue("ATTACK"),
                                 *treeState.getRawParameterValue("RELEASE"));
    
    //OUTPUTGAIN
    outputGain.prepare(spec);
    outputGain.setGainDecibels(*treeState.getRawParameterValue("OUTPUTGAIN"));
    
    //Prepare convolution
    irLoader.reset();
    irLoader.prepare(spec);
    
    if(savedFile.existsAsFile())
    {
        irLoader.loadImpulseResponse(savedFile, juce::dsp::Convolution::Stereo::yes,juce::dsp::Convolution::Trim::yes, 0);
    }
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
    
    //INTERNALLOWEQ
    internalLowEQ.process(juce::dsp::ProcessContextReplacing<float>(processBlock));

    
    //NOISEGATE
    noiseGateStage.process(processBlock,
                           *treeState.getRawParameterValue("THRESHOLD"),
                           *treeState.getRawParameterValue("RATIO"),
                           *treeState.getRawParameterValue("ATTACK"),
                           *treeState.getRawParameterValue("RELEASE"));
    
    
    /*=====================================================================*/
    //PREEQ
    updatePreEQ();
    preEQ.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    
    /*=====================================================================*/
    if(*treeState.getRawParameterValue("GAIN1ONOFF"))
    {
        //Update waveshape function if needed
        if(waveshapeFunction1 != waveshapeFunctionCurrent1)
            setFunctionToUse(1, waveshapeFunction1);

        juce::dsp::AudioBlock<float> drySampsBlock1 (buffer);
        
        gainStage1.process(drySampsBlock1, processBlock,
                           *treeState.getRawParameterValue("PREGAIN1"),
                           *treeState.getRawParameterValue("MIX1"));
    }
    
    /*=====================================================================*/

    if(*treeState.getRawParameterValue("GAIN2ONOFF"))
    {
        //Update waveshape function if needed
        if(waveshapeFunction2 != waveshapeFunctionCurrent2)
            setFunctionToUse(2, waveshapeFunction2);
        
        juce::dsp::AudioBlock<float> drySampsBlock2 (buffer);
        
        gainStage2.process(drySampsBlock2, processBlock,
                           *treeState.getRawParameterValue("PREGAIN2"),
                           *treeState.getRawParameterValue("MIX2"));
    }
    /*=====================================================================*/
    
    if(*treeState.getRawParameterValue("GAIN3ONOFF"))
    {
        //Update waveshape function if needed
        if(waveshapeFunction3 != waveshapeFunctionCurrent3)
            setFunctionToUse(3, waveshapeFunction3);
        
        juce::dsp::AudioBlock<float> drySampsBlock3 (buffer);
        
        gainStage3.process(drySampsBlock3, processBlock,
                           *treeState.getRawParameterValue("PREGAIN3"),
                           *treeState.getRawParameterValue("MIX3"));
    }
    
    
    EQStage.process(*treeState.getRawParameterValue("LOW"),
                    *treeState.getRawParameterValue("MID"),
                    *treeState.getRawParameterValue("HIGH"),
                    processBlock, getSampleRate());
    
    //If there is an IR loaded, process it
    if(irLoader.getCurrentIRSize() > 0)
        irLoader.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    
    
    /*=====================================================================*/
    //OUTPUTGAIN
    float newOutputGain = *treeState.getRawParameterValue("OUTPUTGAIN");
    if(outputGain.getGainDecibels() != newOutputGain)
        outputGain.setGainDecibels(newOutputGain);
    
    //juce::dsp::AudioBlock<float> outputGainBlock (buffer);
    outputGain.process(juce::dsp::ProcessContextReplacing<float>(processBlock));
    

}

/*
    This function takes a string corresponding to the waveshaping function
    to be used. It then sets the functionToUse lambda in the waveshaper.
 */
void ChuginatorAudioProcessor::setFunctionToUse(int gainStageNum, std::string func)
{
    if(gainStageNum == 1)
    {
        gainStage1.setWaveshapeFunc(func);
        waveshapeFunctionCurrent1 = func;
    }
    else if(gainStageNum == 2)
    {
        gainStage2.setWaveshapeFunc(func);
        waveshapeFunctionCurrent2 = func;
    }
    else if(gainStageNum == 3)
    {
        gainStage3.setWaveshapeFunc(func);
        waveshapeFunctionCurrent3 = func;
    }
    return;
}


std::string ChuginatorAudioProcessor::getParamIntToString(int numOfDistType)
{
    switch(numOfDistType)
    {
        case 1:
            return "Amp1";
            break;
        case 2:
            return "Amp2";
            break;
        case 3:
            return "Amp3";
            break;
        case 4:
            return "Tanh";
            break;
            
        case 5:
            return "Atan";
            break;
        case 6:
            return "HalfRect";
            break;
        
        default:
            return "Amp1";
            break;
    }
}


std::string ChuginatorAudioProcessor::getWaveshapeFuncParam(int gainStageNum)
{
    if(gainStageNum == 1)
    {
        auto waveshapeInitFunction1 = treeState.getRawParameterValue("TYPE1");
        return getParamIntToString((int) * waveshapeInitFunction1);
    }
    else if(gainStageNum == 2)
    {
        auto waveshapeInitFunction2 = treeState.getRawParameterValue("TYPE2");
        return getParamIntToString((int) * waveshapeInitFunction2);
    }
    else if(gainStageNum == 3)
    {
        auto waveshapeInitFunction3 = treeState.getRawParameterValue("TYPE3");
        return getParamIntToString((int) * waveshapeInitFunction3);
    }
    else
    {
        return "Amp1";
    }
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
    treeState.state.appendChild(variableTree, nullptr);
    juce::MemoryOutputStream stream(destData, false);
    treeState.state.writeToStream(stream);
}

void ChuginatorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
    variableTree = tree.getChildWithName("Variables");

    if(tree.isValid())
    {
        treeState.state = tree;
        
        savedFile = juce::File(variableTree.getProperty("file1"));
        root = juce::File(variableTree.getProperty("root"));
        
        irLoader.loadImpulseResponse(savedFile, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChuginatorAudioProcessor();
}
