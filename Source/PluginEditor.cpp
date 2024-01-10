/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChuginatorAudioProcessorEditor::ChuginatorAudioProcessorEditor (ChuginatorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), //genericAudioProcessorEditor(p),
        presetPanel(p.getPresetManager())
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 520);
    
    //addAndMakeVisible(genericAudioProcessorEditor);
    addAndMakeVisible(presetPanel);
    
    addAndMakeVisible(buttonBoost);
    addAndMakeVisible(labelBoostButton);
    buttonBoost.setToggleable(true);
    labelBoostButton.setText("Boost", juce::dontSendNotification);
    
    addAndMakeVisible(buttonIROnOff);
    buttonIROnOff.setToggleable(true);
    
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("Load IR");
    loadButton.onClick = [this]()
    {
        fileLoader();
    };
    irName.setText(audioProcessor.savedFile.getFileName(), juce::dontSendNotification);
    
    addAndMakeVisible(irName);
    
    /*=====================================================================*/
    //INPUT
    /*addAndMakeVisible(sliderInputGain);
    addAndMakeVisible(labelInputGain);
    addAndMakeVisible(labelInputGainVal);
    
    //Slider
    setSliderPropertiesRotary(&sliderInputGain);
    sliderInputGain.setLookAndFeel(&lookAndFeel);
    sliderInputGain.setSkewFactor(5.0f);
    
    //Label
    labelInputGain.setText("Input(dB)", juce::dontSendNotification);
    labelInputGain.setLookAndFeel(&lookAndFeel);
    
    sliderInputGain.onValueChange = [this]()
    {
        labelInputGainVal.setText(juce::String((int)sliderInputGain.getValue()), juce::dontSendNotification);
    };
    //Label val
    labelInputGainVal.setText(juce::String((int)sliderInputGain.getValue()), juce::dontSendNotification);
    labelInputGainVal.setJustificationType(juce::Justification::centred);
    labelInputGainVal.setLookAndFeel(&lookAndFeel);
    */
    /*=====================================================================*/
    //PREEQ
    /*addAndMakeVisible(sliderPreEQ);
    addAndMakeVisible(labelPreEQ);
    addAndMakeVisible(labelPreEQVal);
    
    //Slider
    setSliderPropertiesRotary(&sliderPreEQ);
    sliderPreEQ.setLookAndFeel(&lookAndFeel);
    //Label
    labelPreEQ.setText("PreEQ", juce::dontSendNotification);
    labelPreEQ.setLookAndFeel(&lookAndFeel);
    
    sliderPreEQ.onValueChange = [this]()
    {
        labelPreEQVal.setText(juce::String(sliderPreEQ.getValue()), juce::dontSendNotification);
    };
    //Label val
    labelPreEQVal.setText(juce::String(sliderPreEQ.getValue()), juce::dontSendNotification);
    labelPreEQVal.setJustificationType(juce::Justification::centred);
    labelPreEQVal.setLookAndFeel(&lookAndFeel);*/

    /*=====================================================================*/
    //OUTPUT
    /*addAndMakeVisible(sliderOutputGain);
    addAndMakeVisible(labelOutputGain);
    addAndMakeVisible(labelOutputGainVal);
    
    //Slider
    setSliderPropertiesRotary(&sliderOutputGain);
    sliderOutputGain.setLookAndFeel(&lookAndFeel);
    sliderOutputGain.setSkewFactor(0.1f);
    
    //Label
    labelOutputGain.setText("Output(dB)", juce::dontSendNotification);
    labelOutputGain.setLookAndFeel(&lookAndFeel);
    
    sliderOutputGain.onValueChange = [this]()
    {
        labelOutputGainVal.setText(juce::String((int)sliderOutputGain.getValue()), juce::dontSendNotification);
    };
    //Label val
    labelOutputGainVal.setText(juce::String((int)sliderOutputGain.getValue()), juce::dontSendNotification);
    labelOutputGainVal.setJustificationType(juce::Justification::centred);
    labelOutputGainVal.setLookAndFeel(&lookAndFeel);*/
    
    addAndMakeVisible(row1GUI);
    
    /*=====================================================================*/
    //PREGAIN1
    addAndMakeVisible(sliderPreGain1);
    addAndMakeVisible(labelPreGain1);
    addAndMakeVisible(labelPreGain1Val);
    
    //Slider
    setSliderPropertiesRotary(&sliderPreGain1);
    sliderPreGain1.setLookAndFeel(&lookAndFeel);
    //Label
    labelPreGain1.setText("Gain1", juce::dontSendNotification);
    labelPreGain1.setLookAndFeel(&lookAndFeel);
    
    //Value readout setup
    sliderPreGain1.onValueChange = [this]()
    {
        labelPreGain1Val.setText(juce::String((int)sliderPreGain1.getValue()), juce::dontSendNotification);
    };
    //Label val
    labelPreGain1Val.setText(juce::String((int)sliderPreGain1.getValue()), juce::dontSendNotification);
    labelPreGain1Val.setJustificationType(juce::Justification::centred);
    labelPreGain1Val.setLookAndFeel(&lookAndFeel);
    
    addAndMakeVisible(buttonGain1);
    addAndMakeVisible(waveshapeType1);
    buttonGain1.setToggleable(true);
    
    //Menu
    labelWaveshapeType1.attachToComponent(&waveshapeType1, false);
    labelWaveshapeType1.setColour(juce::Label::textColourId, juce::Colours::white);
    labelWaveshapeType1.setText("Dist Type", juce::dontSendNotification);
    labelWaveshapeType1.setLookAndFeel(&lookAndFeel);
    
    waveshapeType1.addItem("Amp1", 1);
    waveshapeType1.addItem("Amp2", 2);
    waveshapeType1.addItem("Amp3", 3);
    waveshapeType1.addItem("Tanh", 4);
    waveshapeType1.addItem("Atan", 5);
    waveshapeType1.addItem("HardClip", 6);
    waveshapeType1.addItem("Screamer", 7);

    waveshapeType1.onChange = [this]{
                modeMenuChanged(1);
    };
    waveshapeType1.setLookAndFeel(&lookAndFeel);
    
    //MIX1
    addAndMakeVisible(sliderMix1);
    addAndMakeVisible(labelMix1);
    addAndMakeVisible(labelMix1Val);
    
    setSliderPropertiesRotary(&sliderMix1);
    sliderMix1.setLookAndFeel(&lookAndFeel);
    labelMix1.setText("Mix1", juce::dontSendNotification);
    labelMix1.setLookAndFeel(&lookAndFeel);
    
    sliderMix1.onValueChange = [this]()
    {
        labelMix1Val.setText(juce::String(sliderMix1.getValue()), juce::dontSendNotification);
    };
    
    labelMix1Val.setText(juce::String(sliderMix1.getValue()), juce::dontSendNotification);
    labelMix1Val.setJustificationType(juce::Justification::centred);
    labelMix1Val.setLookAndFeel(&lookAndFeel);
    
    /*=====================================================================*/
    //PREGAIN2
    addAndMakeVisible(sliderPreGain2);
    addAndMakeVisible(labelPreGain2);
    addAndMakeVisible(labelPreGain2Val);
    
    setSliderPropertiesRotary(&sliderPreGain2);
    sliderPreGain2.setLookAndFeel(&lookAndFeel);
    labelPreGain2.setText("Gain2", juce::dontSendNotification);
    labelPreGain2.setLookAndFeel(&lookAndFeel);
    
    sliderPreGain2.onValueChange = [this]()
    {
        labelPreGain2Val.setText(juce::String((int)sliderPreGain2.getValue()), juce::dontSendNotification);
    };
    
    labelPreGain2Val.setText(juce::String((int)sliderPreGain2.getValue()), juce::dontSendNotification);
    labelPreGain2Val.setJustificationType(juce::Justification::centred);
    labelPreGain2Val.setLookAndFeel(&lookAndFeel);
    
    addAndMakeVisible(buttonGain2);
    addAndMakeVisible(waveshapeType2);
    
    buttonGain2.setToggleable(true);
    
    labelWaveshapeType2.attachToComponent(&waveshapeType2, false);
    labelWaveshapeType2.setColour(juce::Label::textColourId, juce::Colours::white);
    labelWaveshapeType2.setText("Dist Type", juce::dontSendNotification);
    labelWaveshapeType2.setLookAndFeel(&lookAndFeel);
    
    waveshapeType2.addItem("Amp1", 1);
    waveshapeType2.addItem("Amp2", 2);
    waveshapeType2.addItem("Amp3", 3);
    waveshapeType2.addItem("Tanh", 4);
    waveshapeType2.addItem("Atan", 5);
    waveshapeType2.addItem("HardClip", 6);
    waveshapeType2.addItem("Screamer", 7);
    
    waveshapeType2.onChange = [this]{
                modeMenuChanged(2);
    };
    
    waveshapeType2.setLookAndFeel(&lookAndFeel);
    
    //MIX2
    addAndMakeVisible(sliderMix2);
    addAndMakeVisible(labelMix2);
    addAndMakeVisible(labelMix2Val);
    
    setSliderPropertiesRotary(&sliderMix2);
    sliderMix2.setLookAndFeel(&lookAndFeel);
    labelMix2.setText("Mix2", juce::dontSendNotification);
    labelMix2.setLookAndFeel(&lookAndFeel);
    
    sliderMix2.onValueChange = [this]()
    {
        labelMix2Val.setText(juce::String(sliderMix2.getValue()), juce::dontSendNotification);
    };
    
    labelMix2Val.setText(juce::String(sliderMix2.getValue()), juce::dontSendNotification);
    labelMix2Val.setJustificationType(juce::Justification::centred);
    labelMix2Val.setLookAndFeel(&lookAndFeel);
    
    /*=====================================================================*/
    //PREGAIN3
    addAndMakeVisible(sliderPreGain3);
    addAndMakeVisible(labelPreGain3);
    addAndMakeVisible(labelPreGain3Val);

    setSliderPropertiesRotary(&sliderPreGain3);
    sliderPreGain3.setLookAndFeel(&lookAndFeel);
    labelPreGain3.setText("Gain3", juce::dontSendNotification);
    labelPreGain3.setLookAndFeel(&lookAndFeel);
    
    sliderPreGain3.onValueChange = [this]()
    {
        labelPreGain3Val.setText(juce::String((int)sliderPreGain3.getValue()), juce::dontSendNotification);
    };
    
    labelPreGain3Val.setText(juce::String((int)sliderPreGain3.getValue()), juce::dontSendNotification);
    labelPreGain3Val.setJustificationType(juce::Justification::centred);
    labelPreGain3Val.setLookAndFeel(&lookAndFeel);
    
    addAndMakeVisible(buttonGain3);
    addAndMakeVisible(waveshapeType3);
    
    buttonGain3.setToggleable(true);
    
    labelWaveshapeType3.attachToComponent(&waveshapeType3, false);
    labelWaveshapeType3.setColour(juce::Label::textColourId, juce::Colours::white);
    labelWaveshapeType3.setText("Dist Type", juce::dontSendNotification);
    labelWaveshapeType3.setLookAndFeel(&lookAndFeel);
    
    waveshapeType3.addItem("Amp1", 1);
    waveshapeType3.addItem("Amp2", 2);
    waveshapeType3.addItem("Amp3", 3);
    waveshapeType3.addItem("Tanh", 4);
    waveshapeType3.addItem("Atan", 5);
    waveshapeType3.addItem("HardClip", 6);
    waveshapeType3.addItem("Screamer", 7);
    
    waveshapeType3.onChange = [this]{
                modeMenuChanged(3);
    };
    waveshapeType3.setLookAndFeel(&lookAndFeel);
    
    //MIX3
    addAndMakeVisible(sliderMix3);
    addAndMakeVisible(labelMix3);
    addAndMakeVisible(labelMix3Val);
    
    setSliderPropertiesRotary(&sliderMix3);
    sliderMix3.setLookAndFeel(&lookAndFeel);
    labelMix3.setText("Mix3", juce::dontSendNotification);
    labelMix3.setLookAndFeel(&lookAndFeel);
    
    sliderMix3.onValueChange = [this]()
    {
        labelMix3Val.setText(juce::String(sliderMix3.getValue()), juce::dontSendNotification);
    };
    
    labelMix3Val.setText(juce::String(sliderMix3.getValue()), juce::dontSendNotification);
    labelMix3Val.setJustificationType(juce::Justification::centred);
    labelMix3Val.setLookAndFeel(&lookAndFeel);
    
    /*=====================================================================*/
    //EQ
    //Low
    addAndMakeVisible(sliderFilterLowGain);
    addAndMakeVisible(labelFilterLowGain);
    addAndMakeVisible(labelFilterLowGainVal);
    
    setSliderPropertiesRotary(&sliderFilterLowGain);
    sliderFilterLowGain.setLookAndFeel(&lookAndFeel);
    labelFilterLowGain.setText("Low", juce::dontSendNotification);
    labelFilterLowGain.setLookAndFeel(&lookAndFeel);
    
    sliderFilterLowGain.onValueChange = [this]()
    {
        labelFilterLowGainVal.setText(juce::String(sliderFilterLowGain.getValue()), juce::dontSendNotification);
    };
    
    labelFilterLowGainVal.setText(juce::String(sliderFilterLowGain.getValue()), juce::dontSendNotification);
    labelFilterLowGainVal.setJustificationType(juce::Justification::centred);
    labelFilterLowGainVal.setLookAndFeel(&lookAndFeel);
    
    //Mid
    addAndMakeVisible(sliderFilterMidGain);
    addAndMakeVisible(labelFilterMidGain);
    addAndMakeVisible(labelFilterMidGainVal);
    
    setSliderPropertiesRotary(&sliderFilterMidGain);
    sliderFilterMidGain.setLookAndFeel(&lookAndFeel);
    labelFilterMidGain.setText("Mid", juce::dontSendNotification);
    labelFilterMidGain.setLookAndFeel(&lookAndFeel);
    
    sliderFilterMidGain.onValueChange = [this]()
    {
        labelFilterMidGainVal.setText(juce::String(sliderFilterMidGain.getValue()), juce::dontSendNotification);
    };
    
    labelFilterMidGainVal.setText(juce::String(sliderFilterMidGain.getValue()), juce::dontSendNotification);
    labelFilterMidGainVal.setJustificationType(juce::Justification::centred);
    labelFilterMidGainVal.setLookAndFeel(&lookAndFeel);
    
    //High
    addAndMakeVisible(sliderFilterHighGain);
    addAndMakeVisible(labelFilterHighGain);
    addAndMakeVisible(labelFilterHighGainVal);
    
    setSliderPropertiesRotary(&sliderFilterHighGain);
    sliderFilterHighGain.setLookAndFeel(&lookAndFeel);
    labelFilterHighGain.setText("High", juce::dontSendNotification);
    labelFilterHighGain.setLookAndFeel(&lookAndFeel);
    
    sliderFilterHighGain.onValueChange = [this]()
    {
        labelFilterHighGainVal.setText(juce::String(sliderFilterHighGain.getValue()), juce::dontSendNotification);
    };
    
    labelFilterHighGainVal.setText(juce::String(sliderFilterHighGain.getValue()), juce::dontSendNotification);
    labelFilterHighGainVal.setJustificationType(juce::Justification::centred);
    labelFilterHighGainVal.setLookAndFeel(&lookAndFeel);
    
    //Noise Gate
    //Threshold
    /*addAndMakeVisible(sliderNoiseGateThresh);
    addAndMakeVisible(labelNoiseGateThresh);
    addAndMakeVisible(labelNoiseGateThreshVal);
    
    setSliderPropertiesRotary(&sliderNoiseGateThresh);
    sliderNoiseGateThresh.setLookAndFeel(&lookAndFeel);
    labelNoiseGateThresh.setText("Thr", juce::dontSendNotification);
    labelNoiseGateThresh.setLookAndFeel(&lookAndFeel);
    
    sliderNoiseGateThresh.onValueChange = [this]()
    {
        labelNoiseGateThreshVal.setText(juce::String(sliderNoiseGateThresh.getValue()), juce::dontSendNotification);
    };
    
    labelNoiseGateThreshVal.setText(juce::String(sliderNoiseGateThresh.getValue()), juce::dontSendNotification);
    labelNoiseGateThreshVal.setLookAndFeel(&lookAndFeel);*/
    
    addAndMakeVisible(noiseGateGUI);
    
    
    makeSliderAttachments();
}

ChuginatorAudioProcessorEditor::~ChuginatorAudioProcessorEditor()
{
}

void ChuginatorAudioProcessorEditor::sliderValueChanged(juce::Slider *slider, juce::Label *label)
{

}


void ChuginatorAudioProcessorEditor::fileLoader()
{
    fileChooser = std::make_unique<juce::FileChooser>("Choose file", audioProcessor.root, "*");
    
    
    const auto fileChooserFlags = juce::FileBrowserComponent::openMode |
                                  juce::FileBrowserComponent::canSelectFiles |
                                  juce::FileBrowserComponent::canSelectDirectories;
    
    fileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
    {
        juce::File result (chooser.getResult());
        
        if(result.getFileExtension() == ".wav" | result.getFileExtension() == ".mp3")
        {
            audioProcessor.savedFile = result;
            audioProcessor.root = result.getParentDirectory().getFullPathName();
            
            audioProcessor.IRFilePathTree.setProperty("file1", result.getFullPathName(), nullptr);
            audioProcessor.IRFilePathTree.setProperty("root", result.getParentDirectory().getFullPathName(), nullptr);
            
            
            audioProcessor.irLoader.reset();
            audioProcessor.irLoader.loadImpulseResponse(audioProcessor.savedFile, juce::dsp::Convolution::Stereo::yes,
                                                        juce::dsp::Convolution::Trim::yes, 0);
            irName.setText(result.getFileName(), juce::dontSendNotification);
            //irName.setText(audioProcessor.savedFile.getFileName(), juce::dontSendNotification);

        }
    });
}

void ChuginatorAudioProcessorEditor::makeSliderAttachments()
{
    sliderAttachmentInputGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "INPUTGAIN", row1GUI.sliderInputGain);
    
    sliderAttachmentPreEQ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "PREEQ", row1GUI.sliderPreEQ);
    
    sliderAttachmentPreGain1 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "PREGAIN1", sliderPreGain1);
    sliderAttachmentMix1 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "MIX1", sliderMix1);
    buttonAttachmentGain1OnOff = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "GAIN1ONOFF", buttonGain1);
    comboAttachmentWaveshapeType1 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, "TYPE1", waveshapeType1);
    
    
    sliderAttachmentPreGain2 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "PREGAIN2", sliderPreGain2);
    sliderAttachmentMix2 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "MIX2", sliderMix2);
    buttonAttachmentGain2OnOff = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "GAIN2ONOFF", buttonGain2);
    comboAttachmentWaveshapeType2 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, "TYPE2", waveshapeType2);

    
    
    sliderAttachmentPreGain3 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "PREGAIN3", sliderPreGain3);
    sliderAttachmentMix3 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "MIX3", sliderMix3);
    buttonAttachmentGain3OnOff = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "GAIN3ONOFF", buttonGain3);
    comboAttachmentWaveshapeType3 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, "TYPE3", waveshapeType3);

    
    //EQ
    sliderAttachmentFilterLowGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "LOW", sliderFilterLowGain);
    sliderAttachmentFilterMidGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "MID", sliderFilterMidGain);
    
    sliderAttachmentFilterHighGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "HIGH", sliderFilterHighGain);
    
    //NOISE GATE
    sliderAttachmentNoiseGateThresh = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "THRESHOLDNG", noiseGateGUI.sliderNoiseGateThresh);

    
    buttonAttachmentBoost = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "BOOSTONOFF", buttonBoost);
    buttonAttachmentIROnOff = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "IRONOFF", buttonIROnOff);
    
    sliderAttachmentOutputGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "OUTPUTGAIN", row1GUI.sliderOutputGain);
}

void ChuginatorAudioProcessorEditor::setSliderPropertiesRotary(juce::Slider *sliderToSet)
{

    sliderToSet->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderToSet->setTextBoxStyle(juce::Slider::NoTextBox, false, 76, 38);
    sliderToSet->setDoubleClickReturnValue(true, 0.0f);
}

void ChuginatorAudioProcessorEditor::setSliderPropertiesVertical(juce::Slider *sliderToSet)
{

    sliderToSet->setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sliderToSet->setTextBoxStyle(juce::Slider::NoTextBox, false, 76, 38);
    sliderToSet->setDoubleClickReturnValue(true, 0.0f);
    //sliderToSet->setNumDecimalPlacesToDisplay(4);
}

void ChuginatorAudioProcessorEditor::modeMenuChanged(int gainStageNum)
{
    if(gainStageNum == 1)
    {
        //Set the string in the audio processor with the function to use
        switch (waveshapeType1.getSelectedId())
        {
            case 1://Amp1
                audioProcessor.waveshapeFunction1 = "Amp1";
                break;
                
            case 2://Amp2
                audioProcessor.waveshapeFunction1 = "Amp2";
                break;
                
            case 3://Amp3
                audioProcessor.waveshapeFunction1 = "Amp3";
                break;
                
            case 4://Tanh
                audioProcessor.waveshapeFunction1 = "Tanh";
                break;
                
            case 5://Atan
                audioProcessor.waveshapeFunction1 = "Atan";

                break;
                
            case 6://HardClip
                audioProcessor.waveshapeFunction1 = "HardClip";
                break;
            
            case 7:
                audioProcessor.waveshapeFunction1 = "Screamer";
                break;

            default:
                audioProcessor.waveshapeFunction1 = "Amp1";
                break;
        }
    }
    else if(gainStageNum == 2)
    {
        //Set the string in the audio processor with the function to use
        switch (waveshapeType2.getSelectedId())
        {
            case 1://Amp1
                audioProcessor.waveshapeFunction2 = "Amp1";
                break;
                
            case 2://Amp2
                audioProcessor.waveshapeFunction2 = "Amp2";
                break;
                
            case 3://Amp3
                audioProcessor.waveshapeFunction2 = "Amp3";
                break;
                
            case 4://Tanh
                audioProcessor.waveshapeFunction2 = "Tanh";
                break;
                
            case 5://Atan
                audioProcessor.waveshapeFunction2 = "Atan";

                break;
                
            case 6://HardClip
                audioProcessor.waveshapeFunction2 = "HardClip";
                break;
                
            case 7:
                audioProcessor.waveshapeFunction2 = "Screamer";
                break;
                
            default:
                audioProcessor.waveshapeFunction2 = "Amp1";
                break;
        }
    }
    else if(gainStageNum == 3)
    {
        //Set the string in the audio processor with the function to use
        switch (waveshapeType3.getSelectedId())
        {
            case 1://Amp1
                audioProcessor.waveshapeFunction3 = "Amp1";
                break;
                
            case 2://Amp2
                audioProcessor.waveshapeFunction3 = "Amp2";
                break;
                
            case 3://Amp3
                audioProcessor.waveshapeFunction3 = "Amp3";
                break;
                
            case 4://Tanh
                audioProcessor.waveshapeFunction3 = "Tanh";
                break;
                
            case 5://Atan
                audioProcessor.waveshapeFunction3 = "Atan";
                break;
                
            case 6://HardClip
                audioProcessor.waveshapeFunction3 = "HardClip";
                break;
                
            case 7:
                audioProcessor.waveshapeFunction3 = "Screamer";
                break;
                
            default:
                audioProcessor.waveshapeFunction3 = "Amp1";
                break;
        }
    }
    
    
    
}

//==============================================================================
void ChuginatorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    juce::Rectangle<int> area (0, 0, getWidth(), getHeight());
    juce::ColourGradient bgGradient = juce::ColourGradient(juce::Colours::navy, 0, 0, juce::Colours::grey, getWidth(), getHeight(), false);
    g.setGradientFill(bgGradient);
    g.fillRect (area);
}

void ChuginatorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    int leftOffset = 40;
    int topOffset = 30;
    int labelXOffset = 25;
    
    int knobSizeLarge = 85;
    int knobSizeMedium = 60;
    
    int menuWidth = 80;
    int menuHeight = 15;
    
    int smallLabelWidth = 40;
    int smallLabelHeight = 20;
    
    int row4XOffset =  getWidth() / 4;
    int row4YOffset = getHeight() / 4;
            
    const auto container = getLocalBounds();
    auto bounds = container;
    int sliderMargin = 18;
    
    //ROW1
   /* sliderInputGain.setBounds(leftOffset, topOffset, knobSizeLarge, knobSizeLarge);
    labelInputGain.setBounds(sliderInputGain.getX(), sliderInputGain.getY() - 15, 76, 38);
    labelInputGainVal.setBounds(sliderInputGain.getX() + 5, sliderInputGain.getY() + 70, 76, 38);*/
    /*sliderInputGain.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.33f)).removeFromTop(container.proportionOfHeight(0.25f)).reduced(sliderMargin));
    labelInputGain.setBounds(sliderInputGain.getX(), sliderInputGain.getY() - sliderMargin, 76, 38);
    labelInputGainVal.setBounds(sliderInputGain.getX(), sliderInputGain.getY() + (sliderMargin * 4), 76, 38);
    
    
    //sliderPreEQ.setBounds((getWidth() / 2) - 40, topOffset, knobSizeLarge, knobSizeLarge);
    sliderPreEQ.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.33f)).removeFromTop(container.proportionOfHeight(0.25f)).reduced(sliderMargin));
    labelPreEQ.setBounds(sliderPreEQ.getX(), sliderPreEQ.getY() - sliderMargin, 76, 38);
    labelPreEQVal.setBounds(sliderPreEQ.getX(), sliderPreEQ.getY() + (sliderMargin * 4), 76, 38);

    
    //sliderOutputGain.setBounds(getWidth() - (leftOffset + knobSizeLarge), topOffset, knobSizeLarge, knobSizeLarge);
    sliderOutputGain.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.33f)).removeFromTop(container.proportionOfHeight(0.25f)).reduced(sliderMargin));
    labelOutputGain.setBounds(sliderOutputGain.getX(), sliderOutputGain.getY() - 15, 76, 38);
    labelOutputGainVal.setBounds(sliderOutputGain.getX() + 5, sliderOutputGain.getY() + 70, 76, 38);

    */
    
    row1GUI.setBounds(bounds.removeFromTop(container.proportionOfHeight(0.25f)));
    
    
    //ROW2
    /*=====================================================================*/
    //GAIN1
    //Gain
    sliderPreGain1.setBounds(leftOffset - 10, topOffset + knobSizeLarge + 55, knobSizeMedium, knobSizeMedium);
    labelPreGain1.setBounds(sliderPreGain1.getX(), sliderPreGain1.getY() - 15, 76, 38);
    labelPreGain1Val.setBounds(sliderPreGain1.getX() - 7, sliderPreGain1.getY() + 50, 76, 38);
    
    //Toggle
    buttonGain1.setBounds(sliderPreGain1.getX() + 15, sliderPreGain1.getY() - 25, 20, 20);
    waveshapeType1.setBounds(buttonGain1.getX() + 25, buttonGain1.getY(), menuWidth, menuHeight);
    //labelWaveshapeType1.setBounds(waveshapeType1.getX(), waveshapeType1.getY() - 25, 50, 25);
    
    //Mix
    sliderMix1.setBounds(sliderPreGain1.getX() + (knobSizeMedium / 2) + 25, sliderPreGain1.getY(), knobSizeMedium, knobSizeMedium);
    labelMix1.setBounds(sliderMix1.getX(), sliderMix1.getY() - 15, 76, 38);
    labelMix1Val.setBounds(sliderMix1.getX() - 7, sliderMix1.getY() + 50, 76, 38);

    
    /*=====================================================================*/
    //GAIN2
    //Gain
    sliderPreGain2.setBounds(row1GUI.sliderPreEQ.getX() - 10, topOffset + knobSizeLarge + 55, knobSizeMedium, knobSizeMedium);
    labelPreGain2.setBounds(sliderPreGain2.getX(), sliderPreGain2.getY() - 15, 76, 38);
    labelPreGain2Val.setBounds(sliderPreGain2.getX() - 7, sliderPreGain2.getY() + 50, 76, 38);

    
    //Toggle
    buttonGain2.setBounds(sliderPreGain2.getX() + 15, sliderPreGain2.getY() - 25, 20, 20);
    waveshapeType2.setBounds(buttonGain2.getX() + 25, buttonGain2.getY(), menuWidth, menuHeight);
    
    //Mix
    sliderMix2.setBounds(sliderPreGain2.getX() + (knobSizeMedium / 2) + 25, sliderPreGain2.getY(), knobSizeMedium, knobSizeMedium);
    labelMix2.setBounds(sliderMix2.getX(), sliderMix2.getY() - 15, 76, 38);
    labelMix2Val.setBounds(sliderMix2.getX() - 7, sliderMix2.getY() + 50, 76, 38);

    
    /*=====================================================================*/
    //GAIN3
    //Gain
    sliderPreGain3.setBounds(row1GUI.sliderOutputGain.getX() - 10, topOffset + knobSizeLarge + 55, knobSizeMedium, knobSizeMedium);
    labelPreGain3.setBounds(sliderPreGain3.getX(), sliderPreGain3.getY() - 15, 76, 38);
    labelPreGain3Val.setBounds(sliderPreGain3.getX() - 7, sliderPreGain3.getY() + 50, 76, 38);

    //Toggle
    buttonGain3.setBounds(sliderPreGain3.getX() + 15, sliderPreGain3.getY() - 25, 20, 20);
    waveshapeType3.setBounds(buttonGain3.getX() + 25, buttonGain3.getY(), menuWidth, menuHeight);

    //Mix
    sliderMix3.setBounds(sliderPreGain3.getX() + (knobSizeMedium / 2) + 25, sliderPreGain3.getY(), knobSizeMedium, knobSizeMedium);
    labelMix3.setBounds(sliderMix3.getX(), sliderMix3.getY() - 15, 76, 38);
    labelMix3Val.setBounds(sliderMix3.getX() - 7, sliderMix3.getY() + 50, 76, 38);

    /*=====================================================================*/
    //ROW3
    sliderFilterLowGain.setBounds(row1GUI.sliderInputGain.getX(), sliderMix1.getY() + (knobSizeLarge), knobSizeLarge, knobSizeLarge);
    labelFilterLowGain.setBounds(sliderFilterLowGain.getX(), sliderFilterLowGain.getY() - 15, 76, 38);
    labelFilterLowGainVal.setBounds(sliderFilterLowGain.getX() + 5, sliderFilterLowGain.getY() + 70, 76, 38);
    
    sliderFilterMidGain.setBounds(row1GUI.sliderPreEQ.getX(), sliderMix2.getY() + (knobSizeLarge), knobSizeLarge, knobSizeLarge);
    labelFilterMidGain.setBounds(sliderFilterMidGain.getX(), sliderFilterMidGain.getY() - 15, 76, 38);
    labelFilterMidGainVal.setBounds(sliderFilterMidGain.getX() + 5, sliderFilterMidGain.getY() + 70, 76, 38);
    
    
    sliderFilterHighGain.setBounds(row1GUI.sliderOutputGain.getX(), sliderMix3.getY() + (knobSizeLarge), knobSizeLarge, knobSizeLarge);
    labelFilterHighGain.setBounds(sliderFilterHighGain.getX(), sliderFilterHighGain.getY() - 15, 76, 38);
    labelFilterHighGainVal.setBounds(sliderFilterHighGain.getX() + 5, sliderFilterHighGain.getY() + 70, 76, 38);

    
    
    /*=====================================================================*/
    //ROW4
    //Noise Gate
    /*sliderNoiseGateThresh.setBounds(leftOffset - 20, getHeight() - 110, knobSizeLarge, knobSizeLarge);
    labelNoiseGateThresh.setBounds(sliderNoiseGateThresh.getX(), sliderNoiseGateThresh.getY() - 20, smallLabelWidth, smallLabelHeight);
    labelNoiseGateThreshVal.setBounds(sliderNoiseGateThresh.getX(), sliderNoiseGateThresh.getY() + 65, 40, 38);*/
    //noiseGateGUI.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.33f)).removeFromBottom(container.proportionOfHeight(0.25f)));
    noiseGateGUI.setBounds(getWidth() / 2, getHeight() / 2, 100, 100);
    
    
    loadButton.setBounds(row4XOffset * 3, getHeight() - 100, 75, 25);
    irName.setBounds(loadButton.getX(), loadButton.getY() + 25, 150, 25);
    
    
    buttonBoost.setBounds((getWidth() / 2) + 50, getHeight() - 50, 30, 30);
    labelBoostButton.setBounds(buttonBoost.getX(), buttonBoost.getY() - 30, 50, 20);
    buttonIROnOff.setBounds(irName.getX(), getHeight() - 50, 30, 30);

    //genericAudioProcessorEditor.setBounds(getLocalBounds()
     //     .withSizeKeepingCentre(getLocalBounds().proportionOfWidth(0.9f), getLocalBounds().proportionOfHeight(0.5f)));
      
    //presetPanel.setBounds(getLocalBounds().removeFromTop(proportionOfHeight(0.05f)));
}
