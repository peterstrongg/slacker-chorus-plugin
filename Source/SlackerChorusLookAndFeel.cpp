/*
  ==============================================================================

    SlackerChorusLookAndFeel.cpp
    Created: 27 Mar 2026 1:43:32pm
    Author:  peter

  ==============================================================================
*/

#include "SlackerChorusLookAndFeel.h"

void SlackerChorusLookAndFeel::drawRotarySlider(
    juce::Graphics& g, int x, int y, int width, int height,
    float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
    juce::Slider& slider)
{
    auto radius = juce::jmin(width, height) / 2.0f - 10.0f;
    auto centerX = x + width * 0.5f;
    auto centerY = y + height * 0.5f;

    g.setColour(juce::Colour::fromRGB(180, 240, 180));
    g.fillEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
    
    // Shadow
    g.setColour(juce::Colour::fromRGBA(0, 0, 0, 40));
    g.fillEllipse(centerX - radius + 2, centerY - radius + 2, radius * 2, radius * 2);

    // Indicator line
    float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    juce::Line<float> line(centerX, centerY,
        centerX + radius * 0.8f * std::cos(angle - juce::MathConstants<float>::halfPi),
        centerY + radius * 0.8f * std::sin(angle - juce::MathConstants<float>::halfPi));

    g.setColour(juce::Colour::fromRGB(10, 60, 10));
    g.drawLine(line, 4.0f);
}
