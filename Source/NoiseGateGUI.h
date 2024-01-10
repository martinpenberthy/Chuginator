/*
  ==============================================================================

    NoiseGateGUI.h
    Created: 10 Jan 2024 12:03:10pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once
#include "myLookAndFeel.h"

class NoiseGateGUI : public juce::Component
{
public:
    juce::Slider sliderNoiseGateThresh;
    juce::Label labelNoiseGateThresh;
    juce::Label labelNoiseGateThreshVal;
    myLookAndFeel lookAndFeel;
    
    void setSliderPropertiesRotary(juce::Slider *sliderToSet)
    {

        sliderToSet->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        sliderToSet->setTextBoxStyle(juce::Slider::NoTextBox, false, 76, 38);
        sliderToSet->setDoubleClickReturnValue(true, 0.0f);
    }
    
    NoiseGateGUI()
    {
        addAndMakeVisible(sliderNoiseGateThresh);
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
        labelNoiseGateThreshVal.setLookAndFeel(&lookAndFeel);
        
    }
    
    ~NoiseGateGUI()
    {
        
    }

    void resized() override
    {
        const auto container = getLocalBounds();
        auto bounds = container;
        sliderNoiseGateThresh.setBounds(getWidth() / 2, getHeight() / 2, 100, 100);
    }
    


private:
    
};
