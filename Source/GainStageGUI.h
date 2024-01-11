/*
  ==============================================================================

    GainStageGUI.h
    Created: 10 Jan 2024 3:29:04pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GainStageGUI  : public juce::Component
{
public:
    GainStageGUI()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        
        //PREGAIN1
        addAndMakeVisible(sliderPreGain);
        addAndMakeVisible(labelPreGain);
        addAndMakeVisible(labelPreGainVal);
        
        //Slider
        setSliderPropertiesRotary(&sliderPreGain);
        sliderPreGain.setLookAndFeel(&lookAndFeel);
        //Label
        labelPreGain.setText("Gain", juce::dontSendNotification);
        labelPreGain.setLookAndFeel(&lookAndFeel);
        
        //Value readout setup
        sliderPreGain.onValueChange = [this]()
        {
            labelPreGainVal.setText(juce::String((int)sliderPreGain.getValue()), juce::dontSendNotification);
        };
        //Label val
        labelPreGainVal.setText(juce::String((int)sliderPreGain.getValue()), juce::dontSendNotification);
        labelPreGainVal.setJustificationType(juce::Justification::centred);
        labelPreGainVal.setLookAndFeel(&lookAndFeel);
        
        addAndMakeVisible(buttonGain);
        addAndMakeVisible(waveshapeType);
        buttonGain.setToggleable(true);
        
        //Menu
        //labelWaveshapeType.attachToComponent(&waveshapeType, false);
        labelWaveshapeType.setColour(juce::Label::textColourId, juce::Colours::white);
        labelWaveshapeType.setText("Dist Type", juce::dontSendNotification);
        labelWaveshapeType.setLookAndFeel(&lookAndFeel);

        
        waveshapeType.addItem("Amp1", 1);
        waveshapeType.addItem("Amp2", 2);
        waveshapeType.addItem("Amp3", 3);
        waveshapeType.addItem("Tanh", 4);
        waveshapeType.addItem("Atan", 5);
        waveshapeType.addItem("HardClip", 6);
        waveshapeType.addItem("Screamer", 7);

        
        /*waveshapeType.onChange = [this]{
                    modeMenuChanged(1);
        };*/
        waveshapeType.setLookAndFeel(&lookAndFeel);
        waveshapeType.setJustificationType(juce::Justification::centred);
        
        
        //MIX1
        addAndMakeVisible(sliderMix);
        addAndMakeVisible(labelMix);
        addAndMakeVisible(labelMixVal);
        
        setSliderPropertiesRotary(&sliderMix);
        sliderMix.setLookAndFeel(&lookAndFeel);
        labelMix.setText("Mix", juce::dontSendNotification);
        labelMix.setLookAndFeel(&lookAndFeel);
        
        sliderMix.onValueChange = [this]()
        {
            labelMixVal.setText(juce::String(sliderMix.getValue()), juce::dontSendNotification);
        };
        
        labelMixVal.setText(juce::String(sliderMix.getValue()), juce::dontSendNotification);
        labelMixVal.setJustificationType(juce::Justification::centred);
        labelMixVal.setLookAndFeel(&lookAndFeel);

    }

    ~GainStageGUI() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */
/*
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (juce::Colours::white);
        g.setFont (14.0f);
        g.drawText ("GainStageGUI", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
 */
        
        g.setColour(juce::Colours::white);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        
        const auto container = getLocalBounds();
        auto boundsTop = container;
        boundsTop = boundsTop.removeFromTop(container.proportionOfHeight(0.2f));
        auto boundsBottom = container;
        boundsBottom = boundsBottom.removeFromBottom(container.proportionOfHeight(0.8f));
        
        
        //Toggle
        //labelWaveshapeType.setBounds(bounds);
        buttonGain.setBounds(boundsTop.removeFromLeft(boundsTop.proportionOfWidth(0.3f)));
        waveshapeType.setBounds(boundsTop);
        
        
        //Gain
        /*sliderPreGain.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.5f)).removeFromBottom(container.proportionOfHeight(0.7f)));
        //labelPreGain.setBounds(bounds.removeFromBottom(container.proportionOfHeight(0.1f)));
        labelPreGainVal.setBounds(bounds.removeFromBottom(container.proportionOfHeight(0.1f)));
        
        
        //Mix
        sliderMix.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.5f)).removeFromBottom(container.proportionOfHeight(0.7f)));
        //labelMix.setBounds(sliderMix.getX(), sliderMix.getY() - 15, 76, 38);
        labelMixVal.setBounds(bounds.removeFromBottom(container.proportionOfHeight(0.1f)));
*/
    }
    
    
    void setSliderPropertiesRotary(juce::Slider *sliderToSet)
    {

        sliderToSet->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        sliderToSet->setTextBoxStyle(juce::Slider::NoTextBox, false, 76, 38);
        sliderToSet->setDoubleClickReturnValue(true, 0.0f);
    }
    

    
    juce::Label labelWaveshapeType;//Label for menu
    juce::ComboBox waveshapeType; //Menu selecting waveshaping function
    
    juce::Slider sliderPreGain;
    juce::Label labelPreGain;
    juce::Label labelPreGainVal;
    
    juce::Slider sliderMix;
    juce::Label labelMix;
    juce::Label labelMixVal;

    juce::ToggleButton buttonGain;
private:

    myLookAndFeel lookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainStageGUI)
};
