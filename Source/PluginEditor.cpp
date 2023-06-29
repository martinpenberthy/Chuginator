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
    
    
    addAndMakeVisible(sliderInputGain);
    addAndMakeVisible(labelInputGain);
    
    setSliderProperties(&sliderInputGain);
    sliderInputGain.setLookAndFeel(&lookAndFeel);
    labelInputGain.setText("InputGain(dB)", juce::dontSendNotification);
    
    addAndMakeVisible(sliderPreEQ);
    addAndMakeVisible(labelPreEQ);
    
    setSliderProperties(&sliderPreEQ);
    sliderPreEQ.setLookAndFeel(&lookAndFeel);
    labelPreEQ.setText("PreEQ", juce::dontSendNotification);
    
    
    addAndMakeVisible(sliderOutputGain);
    addAndMakeVisible(labelOutputGain);
    
    setSliderProperties(&sliderOutputGain);
    sliderOutputGain.setLookAndFeel(&lookAndFeel);
    labelOutputGain.setText("OutputGain(dB)", juce::dontSendNotification);
    
    makeSliderAttachments();
}

ChuginatorAudioProcessorEditor::~ChuginatorAudioProcessorEditor()
{
}

void ChuginatorAudioProcessorEditor::makeSliderAttachments()
{
    sliderAttachmentInputGain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "INPUTGAIN", sliderInputGain);
    
    sliderAttachmentPreEQ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "PREEQ", sliderPreEQ);
    
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
    
    int leftOffest = 60;
    int topOffset = 30;
    int knobSize = 125;
    
    sliderInputGain.setBounds(leftOffest, topOffset, knobSize, knobSize);
    labelInputGain.setBounds(sliderInputGain.getX(), sliderInputGain.getY() - 15, 76, 38);
    
    sliderPreEQ.setBounds((getWidth() / 2) - 60, topOffset, knobSize, knobSize);
    labelPreEQ.setBounds(sliderPreEQ.getX(), sliderPreEQ.getY() - 15, 76, 38);
    
    sliderOutputGain.setBounds(getWidth() - leftOffest, topOffset, knobSize, knobSize);
    labelOutputGain.setBounds(sliderOutputGain.getX(), sliderOutputGain.getY() - 15, 76, 38);
}
