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
    
    // updateToggleState (juce::Button* button)

    
private:
    
    juce::LookAndFeel_V4 lookAndFeel;
    
    juce::Slider sliderInputGain;
    juce::Label labelInputGain;
    
    juce::Slider sliderPreEQ;//PreEQ slider
    juce::Label labelPreEQ; //PreEQ label
    
    //Gain1
    juce::Slider sliderPreGain1;
    juce::Label labelPreGain1;
    
    juce::Slider sliderMix1;
    juce::Label labelMix1;
    
    juce::ToggleButton buttonGain1; 
    
    //Gain2
    juce::Slider sliderPreGain2;
    juce::Label labelPreGain2;
    
    juce::Slider sliderMix2;
    juce::Label labelMix2;
    
    juce::ToggleButton buttonGain2;

    
    //Gain3
    juce::Slider sliderPreGain3;
    juce::Label labelPreGain3;
    
    juce::Slider sliderMix3;
    juce::Label labelMix3;
    
    juce::ToggleButton buttonGain3;

    
    
    //Filters
    juce::Slider sliderFilterHighGain;
    juce::Label labelFilterHighGain;
    
    juce::Slider sliderFilterMidGain;
    juce::Label labelFilterMidGain;
    
    juce::Slider sliderFilterLowGain;
    juce::Label labelFilterLowGain;
    
    
    
    juce::Slider sliderOutputGain;
    juce::Label labelOutputGain;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentInputGain;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentPreEQ;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentPreGain1;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentMix1;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> buttonAttachmentGain1OnOff;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentPreGain2;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentMix2;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> buttonAttachmentGain2OnOff;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentPreGain3;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentMix3;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> buttonAttachmentGain3OnOff;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentFilterHighGain;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentFilterMidGain;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentFilterLowGain;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentOutputGain;


    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChuginatorAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChuginatorAudioProcessorEditor)
};
