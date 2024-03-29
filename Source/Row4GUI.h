/*
  ==============================================================================

    Row4GUI.h
    Created: 12 Jan 2024 3:38:57pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Row4GUI  : public juce::Component
{
public:
    Row4GUI()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        
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
        
        
        addAndMakeVisible(buttonBoost);
        addAndMakeVisible(labelBoostButton);
        buttonBoost.setToggleable(true);
        labelBoostButton.setText("Boost", juce::dontSendNotification);
        
        addAndMakeVisible(buttonIROnOff);
        addAndMakeVisible(labelIR);
        labelIR.setText("IR", juce::dontSendNotification);
        buttonIROnOff.setToggleable(true);
        

    }

    ~Row4GUI() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

       /* g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (juce::Colours::white);
        g.setFont (14.0f);
        g.drawText ("Row4GUI", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text*/
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        const auto container = getLocalBounds();
        auto bounds = container;
        int sliderMargin = 18;
        
        sliderNoiseGateThresh.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.33)).reduced(sliderMargin));
        labelNoiseGateThresh.setBounds(sliderNoiseGateThresh.getX() + 45, sliderNoiseGateThresh.getY() - sliderMargin, 76, 38);
        labelNoiseGateThreshVal.setBounds(sliderNoiseGateThresh.getX() + 45, sliderNoiseGateThresh.getY() + 80, 40, 30);
        
        buttonBoost.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.33)));
        labelBoostButton.setBounds(buttonBoost.getX(), buttonBoost.getY(), 78, 38);
        
        buttonIROnOff.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.33)));
        labelIR.setBounds(buttonIROnOff.getX(), buttonIROnOff.getY(), 78, 38);
    }

    void setSliderPropertiesRotary(juce::Slider *sliderToSet)
    {

        sliderToSet->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        sliderToSet->setTextBoxStyle(juce::Slider::NoTextBox, false, 76, 38);
        sliderToSet->setDoubleClickReturnValue(true, 0.0f);
    }
    
    
    //NoiseGateGUI noiseGateGUI;
    
    //Noise Gate
    juce::Slider sliderNoiseGateThresh;
    juce::Label labelNoiseGateThresh;
    juce::Label labelNoiseGateThreshVal;
    
    //Boost
    juce::ToggleButton buttonBoost;
    juce::Label labelBoostButton;
    
    //IR on/off
    juce::ToggleButton buttonIROnOff;
    juce::Label labelIR;

private:
    myLookAndFeel lookAndFeel;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Row4GUI)
};
