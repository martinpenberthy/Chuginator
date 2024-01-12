/*
  ==============================================================================

    Row2GUI.h
    Created: 10 Jan 2024 3:29:30pm
    Author:  Martin Penberthy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GainStageGUI.h"
//==============================================================================
/*
*/
class Row2GUI  : public juce::Component
{
public:
    
    GainStageGUI gain1;
    GainStageGUI gain2;
    GainStageGUI gain3;
    Row2GUI()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        addAndMakeVisible(gain1);
        addAndMakeVisible(gain2);
        addAndMakeVisible(gain3);
        
    }

    ~Row2GUI() override
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
        g.drawText ("Row2GUI", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text*/
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        const auto container = getLocalBounds();
        auto bounds = container;
        
        
        gain1.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.3333f)));
        gain2.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.3333f)));
        gain3.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.3333f)));
    }

    
private:

    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Row2GUI)
};
