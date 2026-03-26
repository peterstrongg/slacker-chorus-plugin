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
    RotaryDialLookAndFeel() 
    {
        dialImage = juce::ImageFileFormat::loadFrom(BinaryData::earth_png, BinaryData::earth_pngSize);
        jassert(dialImage.isValid());
		// dialImage.multiplyAllAlphas(1.0f); // Ensure the image is treated as premultiplied alpha
    };

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
    
 
private:
    juce::Image dialImage; 
};
