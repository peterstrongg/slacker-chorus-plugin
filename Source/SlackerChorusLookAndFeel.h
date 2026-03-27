/*
  ==============================================================================

    SlackerChorusLookAndFeel.h
    Created: 27 Mar 2026 1:43:46pm
    Author:  peter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SlackerChorusLookAndFeel : public juce::LookAndFeel_V4
{
public:
    SlackerChorusLookAndFeel() {}
	~SlackerChorusLookAndFeel() override {}

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
};
