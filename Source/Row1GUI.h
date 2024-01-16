/*
  ==============================================================================

    Row1GUI.h
    Created: 10 Jan 2024 2:32:46pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "myLookAndFeel.h"

//==============================================================================
/*
 Contains GUI components for inputGain, PreEQ and outputGain
*/
class Row1GUI  : public juce::Component
{
public:
    Row1GUI()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        /*=====================================================================*/
        //INPUT
        addAndMakeVisible(sliderInputGain);
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
        
        /*=====================================================================*/
        //PREEQ
        addAndMakeVisible(sliderPreEQ);
        addAndMakeVisible(labelPreEQ);
        addAndMakeVisible(labelPreEQVal);
        
        //Slider
        setSliderPropertiesRotary(&sliderPreEQ);
        sliderPreEQ.setLookAndFeel(&lookAndFeel);
        //Label
        labelPreEQ.setText("Pres", juce::dontSendNotification);
        labelPreEQ.setLookAndFeel(&lookAndFeel);
        
        sliderPreEQ.onValueChange = [this]()
        {
            labelPreEQVal.setText(juce::String(sliderPreEQ.getValue()), juce::dontSendNotification);
        };
        //Label val
        labelPreEQVal.setText(juce::String(sliderPreEQ.getValue()), juce::dontSendNotification);
        labelPreEQVal.setJustificationType(juce::Justification::centred);
        labelPreEQVal.setLookAndFeel(&lookAndFeel);

        /*=====================================================================*/
        //DEPTH
        addAndMakeVisible(sliderDepth);
        addAndMakeVisible(labelDepth);
        addAndMakeVisible(labelDepthVal);
        
        //Slider
        setSliderPropertiesRotary(&sliderDepth);
        sliderDepth.setLookAndFeel(&lookAndFeel);
        
        //Label
        labelDepth.setText("Depth", juce::dontSendNotification);
        labelDepth.setLookAndFeel(&lookAndFeel);
        
        sliderDepth.onValueChange = [this]()
        {
            labelDepthVal.setText(juce::String(sliderDepth.getValue()), juce::dontSendNotification);
        };
        
        //Label val
        labelDepthVal.setText(juce::String(sliderDepth.getValue()), juce::dontSendNotification);
        labelDepthVal.setJustificationType(juce::Justification::centred);
        labelDepthVal.setLookAndFeel(&lookAndFeel);
        
        
        /*=====================================================================*/
        //OUTPUT
        addAndMakeVisible(sliderOutputGain);
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
        labelOutputGainVal.setLookAndFeel(&lookAndFeel);
    }

    ~Row1GUI() override
    {
    }

    void paint (juce::Graphics& g) override
    {

    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        
        const auto container = getLocalBounds();
        auto bounds = container;
        int sliderMargin = 18;
        
        sliderInputGain.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.25f)).reduced(sliderMargin));
        labelInputGain.setBounds(sliderInputGain.getX(), sliderInputGain.getY() - sliderMargin, 76, 38);
        labelInputGainVal.setBounds(sliderInputGain.getX(), sliderInputGain.getY() + (sliderMargin * 4), 76, 38);
        
        
        sliderDepth.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.25f)).reduced(sliderMargin));
        labelDepth.setBounds(sliderDepth.getX(), sliderDepth.getY() - 15, 76, 38);
        labelDepthVal.setBounds(sliderDepth.getX() + 5, sliderDepth.getY() + 70, 76, 38);
        
        //sliderPreEQ.setBounds((getWidth() / 2) - 40, topOffset, knobSizeLarge, knobSizeLarge);
        sliderPreEQ.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.25f)).reduced(sliderMargin));
        labelPreEQ.setBounds(sliderPreEQ.getX(), sliderPreEQ.getY() - sliderMargin, 76, 38);
        labelPreEQVal.setBounds(sliderPreEQ.getX(), sliderPreEQ.getY() + (sliderMargin * 4), 76, 38);
        
        
        //sliderOutputGain.setBounds(getWidth() - (leftOffset + knobSizeLarge), topOffset, knobSizeLarge, knobSizeLarge);
        sliderOutputGain.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.25f)).reduced(sliderMargin));
        labelOutputGain.setBounds(sliderOutputGain.getX(), sliderOutputGain.getY() - 15, 76, 38);
        labelOutputGainVal.setBounds(sliderOutputGain.getX() + 5, sliderOutputGain.getY() + 70, 76, 38);
    }

    
    void setSliderPropertiesRotary(juce::Slider *sliderToSet)
    {
        sliderToSet->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        sliderToSet->setTextBoxStyle(juce::Slider::NoTextBox, false, 76, 38);
        sliderToSet->setDoubleClickReturnValue(true, 0.0f);
    }
    
    
    juce::Slider sliderInputGain;
    juce::Label labelInputGain;
    juce::Label labelInputGainVal;
    
    juce::Slider sliderDepth;
    juce::Label labelDepth;
    juce::Label labelDepthVal;
    
    juce::Slider sliderPreEQ;//PreEQ slider
    juce::Label labelPreEQ; //PreEQ label
    juce::Label labelPreEQVal;
    
    juce::Slider sliderOutputGain;
    juce::Label labelOutputGain;
    juce::Label labelOutputGainVal;
private:
    myLookAndFeel lookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Row1GUI)
};
