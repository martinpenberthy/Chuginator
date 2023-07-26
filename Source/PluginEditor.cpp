/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChuginatorAudioProcessorEditor::ChuginatorAudioProcessorEditor (ChuginatorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 520);
    
    lookAndFeel.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black.withAlpha(0.0f));
    lookAndFeel.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::whitesmoke.withAlpha(0.25f));
    lookAndFeel.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::black.withAlpha(0.25f));
    lookAndFeel.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.25f));
    lookAndFeel.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("Load IR");
    loadButton.onClick = [this]()
    {
        fileLoader();
    };
    irName.setText(audioProcessor.savedFile.getFileName(), juce::dontSendNotification);
    
    addAndMakeVisible(irName);

    /*audioProcessor.distTypeList = {
        "Amp1",
        "Amp2",
        "Amp3",
        "Tanh",
        "Atan",
        "HalfRect"
    };*/
    
    //INPUT
    addAndMakeVisible(sliderInputGain);
    addAndMakeVisible(labelInputGain);
    
    setSliderPropertiesRotary(&sliderInputGain);
    sliderInputGain.setLookAndFeel(&lookAndFeel);
    labelInputGain.setText("Input(dB)", juce::dontSendNotification);
    
    //PREEQ
    addAndMakeVisible(sliderPreEQ);
    addAndMakeVisible(labelPreEQ);
    
    setSliderPropertiesRotary(&sliderPreEQ);
    sliderPreEQ.setLookAndFeel(&lookAndFeel);
    labelPreEQ.setText("PreEQ", juce::dontSendNotification);
    
    //OUTPUT
    addAndMakeVisible(sliderOutputGain);
    addAndMakeVisible(labelOutputGain);
    
    setSliderPropertiesRotary(&sliderOutputGain);
    sliderOutputGain.setLookAndFeel(&lookAndFeel);
    labelOutputGain.setText("Output(dB)", juce::dontSendNotification);
    
    //PREGAIN1
    addAndMakeVisible(sliderPreGain1);
    addAndMakeVisible(labelPreGain1);
    addAndMakeVisible(buttonGain1);
    addAndMakeVisible(waveshapeType1);
    
    setSliderPropertiesRotary(&sliderPreGain1);
    sliderPreGain1.setLookAndFeel(&lookAndFeel);
    labelPreGain1.setText("Gain1", juce::dontSendNotification);
    
    buttonGain1.setToggleable(true);
    
    labelWaveshapeType1.attachToComponent(&waveshapeType1, false);
    labelWaveshapeType1.setColour(juce::Label::textColourId, juce::Colours::white);
    labelWaveshapeType1.setText("Dist Type", juce::dontSendNotification);
        
    waveshapeType1.addItem("Amp1", 1);
    waveshapeType1.addItem("Amp2", 2);
    waveshapeType1.addItem("Amp3", 3);
    waveshapeType1.addItem("Tanh", 4);
    waveshapeType1.addItem("Atan", 5);
    waveshapeType1.addItem("HalfRect", 6);
    
    waveshapeType1.onChange = [this]{
                modeMenuChanged(1);
    };
    
    
    //MIX1
    addAndMakeVisible(sliderMix1);
    addAndMakeVisible(labelMix1);
    
    setSliderPropertiesRotary(&sliderMix1);
    sliderMix1.setLookAndFeel(&lookAndFeel);
    labelMix1.setText("Mix1", juce::dontSendNotification);
    
    
    //PREGAIN2
    addAndMakeVisible(sliderPreGain2);
    addAndMakeVisible(labelPreGain2);
    addAndMakeVisible(buttonGain2);
    addAndMakeVisible(waveshapeType2);
    
    setSliderPropertiesRotary(&sliderPreGain2);
    sliderPreGain2.setLookAndFeel(&lookAndFeel);
    labelPreGain2.setText("Gain2", juce::dontSendNotification);
    
    buttonGain2.setToggleable(true);
    
    labelWaveshapeType2.attachToComponent(&waveshapeType1, false);
    labelWaveshapeType2.setColour(juce::Label::textColourId, juce::Colours::white);
    labelWaveshapeType2.setText("Dist Type", juce::dontSendNotification);
        
    waveshapeType2.addItem("Amp1", 1);
    waveshapeType2.addItem("Amp2", 2);
    waveshapeType2.addItem("Amp3", 3);
    waveshapeType2.addItem("Tanh", 4);
    waveshapeType2.addItem("Atan", 5);
    waveshapeType2.addItem("HalfRect", 6);
    
    waveshapeType2.onChange = [this]{
                modeMenuChanged(2);
    };
    
    //MIX2
    addAndMakeVisible(sliderMix2);
    addAndMakeVisible(labelMix2);
    
    
    setSliderPropertiesRotary(&sliderMix2);
    sliderMix2.setLookAndFeel(&lookAndFeel);
    labelMix2.setText("Mix2", juce::dontSendNotification);
    
    //PREGAIN3
    addAndMakeVisible(sliderPreGain3);
    addAndMakeVisible(labelPreGain3);
    addAndMakeVisible(buttonGain3);
    addAndMakeVisible(waveshapeType3);
    
    setSliderPropertiesRotary(&sliderPreGain3);
    sliderPreGain3.setLookAndFeel(&lookAndFeel);
    labelPreGain3.setText("Gain3", juce::dontSendNotification);
    
    buttonGain3.setToggleable(true);
    
    labelWaveshapeType3.attachToComponent(&waveshapeType3, false);
    labelWaveshapeType3.setColour(juce::Label::textColourId, juce::Colours::white);
    labelWaveshapeType3.setText("Dist Type", juce::dontSendNotification);
        
    waveshapeType3.addItem("Amp1", 1);
    waveshapeType3.addItem("Amp2", 2);
    waveshapeType3.addItem("Amp3", 3);
    waveshapeType3.addItem("Tanh", 4);
    waveshapeType3.addItem("Atan", 5);
    waveshapeType3.addItem("HalfRect", 6);
    
    waveshapeType3.onChange = [this]{
                modeMenuChanged(3);
    };
    
    
    
    //MIX3
    addAndMakeVisible(sliderMix3);
    addAndMakeVisible(labelMix3);
    
    setSliderPropertiesRotary(&sliderMix3);
    sliderMix3.setLookAndFeel(&lookAndFeel);
    labelMix3.setText("Mix3", juce::dontSendNotification);
    
    //EQ
    addAndMakeVisible(sliderFilterLowGain);
    addAndMakeVisible(labelFilterLowGain);
    
    setSliderPropertiesRotary(&sliderFilterLowGain);
    sliderFilterLowGain.setLookAndFeel(&lookAndFeel);
    labelFilterLowGain.setText("Low", juce::dontSendNotification);
    
    addAndMakeVisible(sliderFilterMidGain);
    addAndMakeVisible(labelFilterMidGain);
    
    setSliderPropertiesRotary(&sliderFilterMidGain);
    sliderFilterMidGain.setLookAndFeel(&lookAndFeel);
    labelFilterMidGain.setText("Mid", juce::dontSendNotification);
    
    addAndMakeVisible(sliderFilterHighGain);
    addAndMakeVisible(labelFilterHighGain);
    
    setSliderPropertiesRotary(&sliderFilterHighGain);
    sliderFilterHighGain.setLookAndFeel(&lookAndFeel);
    labelFilterHighGain.setText("High", juce::dontSendNotification);
    
    
    //Noise Gate
    //Threshold
    addAndMakeVisible(sliderNoiseGateThresh);
    addAndMakeVisible(labelNoiseGateThresh);
    
    setSliderPropertiesVertical(&sliderNoiseGateThresh);
    sliderNoiseGateThresh.setLookAndFeel(&lookAndFeel);
    labelNoiseGateThresh.setText("Thr", juce::dontSendNotification);

    
    //Ratio
    addAndMakeVisible(sliderNoiseGateRatio);
    addAndMakeVisible(labelNoiseGateRatio);
    
    setSliderPropertiesVertical(&sliderNoiseGateRatio);
    sliderNoiseGateRatio.setLookAndFeel(&lookAndFeel);
    labelNoiseGateRatio.setText("Ratio", juce::dontSendNotification);
    
    //Attack
    addAndMakeVisible(sliderNoiseGateAttack);
    addAndMakeVisible(labelNoiseGateAttack);
    
    setSliderPropertiesVertical(&sliderNoiseGateAttack);
    sliderNoiseGateAttack.setLookAndFeel(&lookAndFeel);
    labelNoiseGateAttack.setText("A", juce::dontSendNotification);
    
    //Release
    addAndMakeVisible(sliderNoiseGateRelease);
    addAndMakeVisible(labelNoiseGateRelease);
    
    setSliderPropertiesVertical(&sliderNoiseGateRelease);
    sliderNoiseGateRelease.setLookAndFeel(&lookAndFeel);
    labelNoiseGateRelease.setText("R", juce::dontSendNotification);
    
    
    
    makeSliderAttachments();
}

ChuginatorAudioProcessorEditor::~ChuginatorAudioProcessorEditor()
{
}

/*void ChuginatorAudioProcessorEditor::updateToggleState (juce::Button* button)
{
    audioProcessor.gain1OnOff = button->getToggleState();
}*/

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
            
            audioProcessor.variableTree.setProperty("file1", result.getFullPathName(), nullptr);
            audioProcessor.variableTree.setProperty("root", result.getParentDirectory().getFullPathName(), nullptr);
            
            
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
    sliderAttachmentInputGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "INPUTGAIN", sliderInputGain);
    
    sliderAttachmentPreEQ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "PREEQ", sliderPreEQ);
    
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
    sliderAttachmentNoiseGateThresh = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "THRESHOLD", sliderNoiseGateThresh);
    sliderAttachmentNoiseGateRatio = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "RATIO", sliderNoiseGateRatio);
    sliderAttachmentNoiseGateAttack = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "ATTACK", sliderNoiseGateAttack);
    sliderAttachmentNoiseGateRelease = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "RELEASE", sliderNoiseGateRelease);
    
    
    
    sliderAttachmentOutputGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "OUTPUTGAIN", sliderOutputGain);
}

void ChuginatorAudioProcessorEditor::setSliderPropertiesRotary(juce::Slider *sliderToSet)
{

    sliderToSet->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderToSet->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 76, 38);
    sliderToSet->setDoubleClickReturnValue(true, 0.0f);
}

void ChuginatorAudioProcessorEditor::setSliderPropertiesVertical(juce::Slider *sliderToSet)
{

    sliderToSet->setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sliderToSet->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 76, 38);
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
                
            case 6://HalfRect
                audioProcessor.waveshapeFunction1 = "HalfRect";
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
                
            case 6://HalfRect
                audioProcessor.waveshapeFunction2 = "HalfRect";
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
                
            case 6://HalfRect
                audioProcessor.waveshapeFunction3 = "HalfRect";
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
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //backgroundImage = juce::ImageCache::getFromMemory(BinaryData::AmpBackground1_png, BinaryData::AmpBackground1_pngSize);
    //g.drawImageWithin(backgroundImage, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
}

void ChuginatorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    int leftOffset = 40;
    int topOffset = 30;
    int labelXOffset = 25;
    int knobSizeLarge = 115;
    int knobSizeMedium = 100;
    int knobSizeSmall = 70;
    int menuWidth = 80;
    int menuHeight = 15;
    
    int smallLabelWidth = 40;
    int smallLabelHeight = 20;
    
    int row4XOffset =  getWidth() / 4;
    int row4YOffset = getHeight() / 4;
    
    //ROW1
    sliderInputGain.setBounds(leftOffset, topOffset, knobSizeLarge, knobSizeLarge);
    labelInputGain.setBounds(sliderInputGain.getX(), sliderInputGain.getY() - 15, 76, 38);
    
    sliderPreEQ.setBounds((getWidth() / 2) - 60, topOffset, knobSizeLarge, knobSizeLarge);
    labelPreEQ.setBounds(sliderPreEQ.getX(), sliderPreEQ.getY() - 15, 76, 38);
    
    sliderOutputGain.setBounds(getWidth() - (leftOffset + knobSizeLarge), topOffset, knobSizeLarge, knobSizeLarge);
    labelOutputGain.setBounds(sliderOutputGain.getX(), sliderOutputGain.getY() - 15, 76, 38);
    
    //ROW2
    /*=====================================================================*/
    //GAIN1
    //Gain
    sliderPreGain1.setBounds(leftOffset - 15, topOffset + knobSizeLarge + 40, knobSizeMedium, knobSizeMedium);
    labelPreGain1.setBounds(sliderPreGain1.getX() + labelXOffset, sliderPreGain1.getY() - 15, 76, 38);
    
    //Toggle
    buttonGain1.setBounds(sliderPreGain1.getX() + 15, sliderPreGain1.getY() - 25, 20, 20);
    waveshapeType1.setBounds(buttonGain1.getX() + 25, buttonGain1.getY(), menuWidth, menuHeight);
    //labelWaveshapeType1.setBounds(waveshapeType1.getX(), waveshapeType1.getY() - 25, 50, 25);
    
    //Mix
    sliderMix1.setBounds(sliderPreGain1.getX() + (knobSizeMedium / 2) + 15, sliderPreGain1.getY(), knobSizeMedium, knobSizeMedium);
    labelMix1.setBounds(sliderMix1.getX() + labelXOffset, sliderMix1.getY() - 15, 76, 38);
    
    
    /*=====================================================================*/
    //GAIN2
    //Gain
    sliderPreGain2.setBounds(sliderPreEQ.getX() - 15, topOffset + knobSizeLarge + 40, knobSizeMedium, knobSizeMedium);
    labelPreGain2.setBounds(sliderPreGain2.getX() + labelXOffset, sliderPreGain2.getY() - 15, 76, 38);
    
    //Toggle
    buttonGain2.setBounds(sliderPreGain2.getX() + 15, sliderPreGain2.getY() - 25, 20, 20);
    waveshapeType2.setBounds(buttonGain2.getX() + 25, buttonGain2.getY(), menuWidth, menuHeight);
    
    //Mix
    sliderMix2.setBounds(sliderPreGain2.getX() + (knobSizeMedium / 2) + 15, sliderPreGain2.getY(), knobSizeMedium, knobSizeMedium);
    labelMix2.setBounds(sliderMix2.getX() + labelXOffset, sliderMix2.getY() - 15, 76, 38);
    
    
    /*=====================================================================*/
    //GAIN3
    //Gain
    sliderPreGain3.setBounds(sliderOutputGain.getX() - 15, topOffset + knobSizeLarge + 40, knobSizeMedium, knobSizeMedium);
    labelPreGain3.setBounds(sliderPreGain3.getX() + labelXOffset, sliderPreGain3.getY() - 15, 76, 38);
    
    //Toggle
    buttonGain3.setBounds(sliderPreGain3.getX() + 15, sliderPreGain3.getY() - 25, 20, 20);
    waveshapeType3.setBounds(buttonGain3.getX() + 25, buttonGain3.getY(), menuWidth, menuHeight);

    //Mix
    sliderMix3.setBounds(sliderPreGain3.getX() + (knobSizeMedium / 2) + 15, sliderPreGain3.getY(), knobSizeMedium, knobSizeMedium);
    labelMix3.setBounds(sliderMix3.getX() + labelXOffset, sliderMix3.getY() - 15, 76, 38);
    
    /*=====================================================================*/
    //ROW3
    sliderFilterLowGain.setBounds(sliderInputGain.getX(), sliderMix1.getY() + (knobSizeLarge - 15), knobSizeLarge, knobSizeLarge);
    labelFilterLowGain.setBounds(sliderFilterLowGain.getX(), sliderFilterLowGain.getY() - 15, 76, 38);
    
    sliderFilterMidGain.setBounds(sliderPreEQ.getX(), sliderMix2.getY() + (knobSizeLarge - 15), knobSizeLarge, knobSizeLarge);
    labelFilterMidGain.setBounds(sliderFilterMidGain.getX(), sliderFilterMidGain.getY() - 15, 76, 38);
    
    sliderFilterHighGain.setBounds(sliderOutputGain.getX(), sliderMix3.getY() + (knobSizeLarge - 15), knobSizeLarge, knobSizeLarge);
    labelFilterHighGain.setBounds(sliderFilterHighGain.getX(), sliderFilterHighGain.getY() - 15, 76, 38);
    
    /*=====================================================================*/
    //ROW4
    //Noise Gate
    sliderNoiseGateThresh.setBounds(leftOffset - 20, getHeight() - 110, 50, 120);
    labelNoiseGateThresh.setBounds(sliderNoiseGateThresh.getX(), sliderNoiseGateThresh.getY() - 20, smallLabelWidth, smallLabelHeight);
    
    sliderNoiseGateRatio.setBounds(sliderNoiseGateThresh.getX() + 30, sliderNoiseGateThresh.getY(), 50, 120);
    labelNoiseGateRatio.setBounds(sliderNoiseGateRatio.getX(), sliderNoiseGateRatio.getY() - 20, smallLabelWidth, smallLabelHeight);
    
    sliderNoiseGateAttack.setBounds(sliderNoiseGateRatio.getX() + 30, sliderNoiseGateRatio.getY(), 50, 120);
    labelNoiseGateAttack.setBounds(sliderNoiseGateAttack.getX() + 10, sliderNoiseGateAttack.getY() - 20, smallLabelWidth, smallLabelHeight);
    
    sliderNoiseGateRelease.setBounds(sliderNoiseGateAttack.getX() + 30, sliderNoiseGateAttack.getY(), 50, 120);
    labelNoiseGateRelease.setBounds(sliderNoiseGateRelease.getX() + 10, sliderNoiseGateRelease.getY() - 20, smallLabelWidth, smallLabelHeight);
    
    loadButton.setBounds(row4XOffset * 3, getHeight() - 100, 75, 25);
    irName.setBounds(loadButton.getX(), loadButton.getY() + 25, 60, 25);
    
}
