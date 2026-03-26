/*
  ==============================================================================

    RotaryDialLookAndFeel.h
    Created: 25 Mar 2026 10:39:30pm
    Author:  peter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <BinaryData.h>

class RotaryDialLookAndFeel : public juce::LookAndFeel_V4
{
public:
    RotaryDialLookAndFeel(juce::Image img) : dialImage(img)
    {
        jassert(dialImage.isValid());
    };

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
    
 
private:
    juce::Image dialImage; 
};
