/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ChuginatorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ChuginatorAudioProcessorEditor (ChuginatorAudioProcessor&);
    ~ChuginatorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void setSliderProperties(juce::Slider *sliderToSet);
    void makeSliderAttachments();
    
    
private:
    
    juce::LookAndFeel_V4 lookAndFeel;
    
    juce::Slider sliderInputGain;
    juce::Label labelInputGain;
    
    juce::Slider sliderPreEQ;//PreEQ slider
    juce::Label labelPreEQ; //PreEQ label
    
    juce::Slider sliderPreGain1;
    juce::Label labelPreGain1;
    
    juce::Slider sliderOutputGain;
    juce::Label labelOutputGain;
    
    juce::Slider sliderMix1;
    juce::Label labelMix1;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentInputGain;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentPreEQ;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentPreGain1;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentMix1;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentOutputGain;


    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChuginatorAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChuginatorAudioProcessorEditor)
};
