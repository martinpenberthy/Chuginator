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
    
    //INPUT
    addAndMakeVisible(sliderInputGain);
    addAndMakeVisible(labelInputGain);
    
    setSliderProperties(&sliderInputGain);
    sliderInputGain.setLookAndFeel(&lookAndFeel);
    labelInputGain.setText("Input(dB)", juce::dontSendNotification);
    
    //PREEQ
    addAndMakeVisible(sliderPreEQ);
    addAndMakeVisible(labelPreEQ);
    
    setSliderProperties(&sliderPreEQ);
    sliderPreEQ.setLookAndFeel(&lookAndFeel);
    labelPreEQ.setText("PreEQ", juce::dontSendNotification);
    
    //OUTPUT
    addAndMakeVisible(sliderOutputGain);
    addAndMakeVisible(labelOutputGain);
    
    setSliderProperties(&sliderOutputGain);
    sliderOutputGain.setLookAndFeel(&lookAndFeel);
    labelOutputGain.setText("Output(dB)", juce::dontSendNotification);
    
    //PREGAIN1
    addAndMakeVisible(sliderPreGain1);
    addAndMakeVisible(labelPreGain1);
    addAndMakeVisible(buttonGain1);
    
    setSliderProperties(&sliderPreGain1);
    sliderPreGain1.setLookAndFeel(&lookAndFeel);
    labelPreGain1.setText("Gain1", juce::dontSendNotification);
    
    buttonGain1.setToggleable(true);
    //buttonGain1.onClick = [this] { updateToggleState (&maleButton); };
    
    //MIX1
    addAndMakeVisible(sliderMix1);
    addAndMakeVisible(labelMix1);
    
    setSliderProperties(&sliderMix1);
    sliderMix1.setLookAndFeel(&lookAndFeel);
    labelMix1.setText("Mix1", juce::dontSendNotification);
    
    
    //PREGAIN2
    addAndMakeVisible(sliderPreGain2);
    addAndMakeVisible(labelPreGain2);
    addAndMakeVisible(buttonGain2);
    
    setSliderProperties(&sliderPreGain2);
    sliderPreGain2.setLookAndFeel(&lookAndFeel);
    labelPreGain2.setText("Gain2", juce::dontSendNotification);
    
    buttonGain2.setToggleable(true);
    
    //MIX2
    addAndMakeVisible(sliderMix2);
    addAndMakeVisible(labelMix2);
    
    
    setSliderProperties(&sliderMix2);
    sliderMix2.setLookAndFeel(&lookAndFeel);
    labelMix2.setText("Mix2", juce::dontSendNotification);
    
    //PREGAIN3
    addAndMakeVisible(sliderPreGain3);
    addAndMakeVisible(labelPreGain3);
    addAndMakeVisible(buttonGain3);
    
    setSliderProperties(&sliderPreGain3);
    sliderPreGain3.setLookAndFeel(&lookAndFeel);
    labelPreGain3.setText("Gain3", juce::dontSendNotification);
    
    buttonGain3.setToggleable(true);
    
    //MIX3
    addAndMakeVisible(sliderMix3);
    addAndMakeVisible(labelMix3);
    
    setSliderProperties(&sliderMix3);
    sliderMix3.setLookAndFeel(&lookAndFeel);
    labelMix3.setText("Mix3", juce::dontSendNotification);
    
    //EQ
    addAndMakeVisible(sliderFilterLowGain);
    addAndMakeVisible(labelFilterLowGain);
    
    setSliderProperties(&sliderFilterLowGain);
    sliderFilterLowGain.setLookAndFeel(&lookAndFeel);
    labelFilterLowGain.setText("Low", juce::dontSendNotification);
    
    addAndMakeVisible(sliderFilterMidGain);
    addAndMakeVisible(labelFilterMidGain);
    
    setSliderProperties(&sliderFilterMidGain);
    sliderFilterMidGain.setLookAndFeel(&lookAndFeel);
    labelFilterMidGain.setText("Mid", juce::dontSendNotification);
    
    addAndMakeVisible(sliderFilterHighGain);
    addAndMakeVisible(labelFilterHighGain);
    
    setSliderProperties(&sliderFilterHighGain);
    sliderFilterHighGain.setLookAndFeel(&lookAndFeel);
    labelFilterHighGain.setText("High", juce::dontSendNotification);
    
    makeSliderAttachments();
}

ChuginatorAudioProcessorEditor::~ChuginatorAudioProcessorEditor()
{
}

/*void ChuginatorAudioProcessorEditor::updateToggleState (juce::Button* button)
{
    audioProcessor.gain1OnOff = button->getToggleState();
}*/

void ChuginatorAudioProcessorEditor::makeSliderAttachments()
{
    sliderAttachmentInputGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "INPUTGAIN", sliderInputGain);
    
    sliderAttachmentPreEQ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "PREEQ", sliderPreEQ);
    
    sliderAttachmentPreGain1 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "PREGAIN1", sliderPreGain1);
    sliderAttachmentMix1 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "MIX1", sliderMix1);
    buttonAttachmentGain1OnOff = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "GAIN1ONOFF", buttonGain1);
    
    sliderAttachmentPreGain2 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "PREGAIN2", sliderPreGain2);
    sliderAttachmentMix2 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "MIX2", sliderMix2);
    buttonAttachmentGain2OnOff = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "GAIN2ONOFF", buttonGain2);
    
    sliderAttachmentPreGain3 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "PREGAIN3", sliderPreGain3);
    sliderAttachmentMix3 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "MIX3", sliderMix3);
    buttonAttachmentGain3OnOff = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "GAIN3ONOFF", buttonGain3);
    
    //EQ
    sliderAttachmentFilterLowGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "LOW", sliderFilterLowGain);
    sliderAttachmentFilterMidGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "MID", sliderFilterMidGain);
    
    sliderAttachmentFilterHighGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "HIGH", sliderFilterHighGain);
    
    
    sliderAttachmentOutputGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "OUTPUTGAIN", sliderOutputGain);
}

void ChuginatorAudioProcessorEditor::setSliderProperties(juce::Slider *sliderToSet)
{
    
    sliderToSet->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderToSet->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 76, 38);
    sliderToSet->setDoubleClickReturnValue(true, 0.0f);
}


//==============================================================================
void ChuginatorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

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
    
    
    //ROW1
    sliderInputGain.setBounds(leftOffset, topOffset, knobSizeLarge, knobSizeLarge);
    labelInputGain.setBounds(sliderInputGain.getX(), sliderInputGain.getY() - 15, 76, 38);
    
    sliderPreEQ.setBounds((getWidth() / 2) - 60, topOffset, knobSizeLarge, knobSizeLarge);
    labelPreEQ.setBounds(sliderPreEQ.getX(), sliderPreEQ.getY() - 15, 76, 38);
    
    sliderOutputGain.setBounds(getWidth() - (leftOffset + knobSizeLarge), topOffset, knobSizeLarge, knobSizeLarge);
    labelOutputGain.setBounds(sliderOutputGain.getX(), sliderOutputGain.getY() - 15, 76, 38);
    
    //ROW2
    

    //Gain
    sliderPreGain1.setBounds(leftOffset - 15, topOffset + knobSizeLarge + 40, knobSizeMedium, knobSizeMedium);
    labelPreGain1.setBounds(sliderPreGain1.getX() + labelXOffset, sliderPreGain1.getY() - 15, 76, 38);
    
    //Toggle
    buttonGain1.setBounds(sliderPreGain1.getX() + 15, sliderPreGain1.getY() - 25, 20, 20);
    
    //Mix
    sliderMix1.setBounds(sliderPreGain1.getX() + (knobSizeMedium / 2) + 15, sliderPreGain1.getY(), knobSizeMedium, knobSizeMedium);
    labelMix1.setBounds(sliderMix1.getX() + labelXOffset, sliderMix1.getY() - 15, 76, 38);
    
    //Gain
    sliderPreGain2.setBounds(sliderPreEQ.getX() - 15, topOffset + knobSizeLarge + 40, knobSizeMedium, knobSizeMedium);
    labelPreGain2.setBounds(sliderPreGain2.getX() + labelXOffset, sliderPreGain2.getY() - 15, 76, 38);
    
    //Toggle
    buttonGain2.setBounds(sliderPreGain2.getX() + 15, sliderPreGain2.getY() - 25, 20, 20);
    
    //Mix
    sliderMix2.setBounds(sliderPreGain2.getX() + (knobSizeMedium / 2) + 15, sliderPreGain2.getY(), knobSizeMedium, knobSizeMedium);
    labelMix2.setBounds(sliderMix2.getX() + labelXOffset, sliderMix2.getY() - 15, 76, 38);
    
    
    sliderPreGain3.setBounds(sliderOutputGain.getX() - 15, topOffset + knobSizeLarge + 40, knobSizeMedium, knobSizeMedium);
    labelPreGain3.setBounds(sliderPreGain3.getX() + labelXOffset, sliderPreGain3.getY() - 15, 76, 38);
    
    //Toggle
    buttonGain3.setBounds(sliderPreGain3.getX() + 15, sliderPreGain3.getY() - 25, 20, 20);
    
    sliderMix3.setBounds(sliderPreGain3.getX() + (knobSizeMedium / 2) + 15, sliderPreGain3.getY(), knobSizeMedium, knobSizeMedium);
    labelMix3.setBounds(sliderMix3.getX() + labelXOffset, sliderMix3.getY() - 15, 76, 38);
    
    
    //ROW3
    sliderFilterLowGain.setBounds(sliderInputGain.getX(), sliderMix1.getY() + (knobSizeLarge - 15), knobSizeLarge, knobSizeLarge);
    labelFilterLowGain.setBounds(sliderFilterLowGain.getX(), sliderFilterLowGain.getY() - 15, 76, 38);
    
    sliderFilterMidGain.setBounds(sliderPreEQ.getX(), sliderMix2.getY() + (knobSizeLarge - 15), knobSizeLarge, knobSizeLarge);
    labelFilterMidGain.setBounds(sliderFilterMidGain.getX(), sliderFilterMidGain.getY() - 15, 76, 38);
    
    sliderFilterHighGain.setBounds(sliderOutputGain.getX(), sliderMix3.getY() + (knobSizeLarge - 15), knobSizeLarge, knobSizeLarge);
    labelFilterHighGain.setBounds(sliderFilterHighGain.getX(), sliderFilterHighGain.getY() - 15, 76, 38);
    
}
