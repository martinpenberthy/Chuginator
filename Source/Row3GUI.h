/*
  ==============================================================================

    Row3GUI.h
    Created: 12 Jan 2024 10:29:39am
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "myLookAndFeel.h"

//==============================================================================
/*
*/
class Row3GUI  : public juce::Component
{
public:
    Row3GUI()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
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
        
    }

    ~Row3GUI() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        /*g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (juce::Colours::white);
        g.setFont (14.0f);
        g.drawText ("Row3GUI", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text*/
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }
    
    
    void setSliderPropertiesRotary(juce::Slider *sliderToSet)
    {
        sliderToSet->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        sliderToSet->setTextBoxStyle(juce::Slider::NoTextBox, false, 76, 38);
        sliderToSet->setDoubleClickReturnValue(true, 0.0f);
    }
    
    //Filters
    juce::Slider sliderFilterHighGain;
    juce::Label labelFilterHighGain;
    juce::Label labelFilterHighGainVal;
    
    juce::Slider sliderFilterMidGain;
    juce::Label labelFilterMidGain;
    juce::Label labelFilterMidGainVal;

    
    juce::Slider sliderFilterLowGain;
    juce::Label labelFilterLowGain;
    juce::Label labelFilterLowGainVal;

private:
    myLookAndFeel lookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Row3GUI)
};
