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

    // Dial
    g.setColour(juce::Colour::fromRGB(240, 220, 200)); // warm beige
    g.fillEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    // Base angle
    float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    float innerRadius = radius * 0.6f;
    float outerRadius = radius;

    // Indicator
    juce::Line<float> line(
        centerX + innerRadius * std::cos(angle - juce::MathConstants<float>::halfPi),
        centerY + innerRadius * std::sin(angle - juce::MathConstants<float>::halfPi),
        centerX + outerRadius * std::cos(angle - juce::MathConstants<float>::halfPi),
        centerY + outerRadius * std::sin(angle - juce::MathConstants<float>::halfPi)
    );

    g.setColour(juce::Colour::fromRGB(0, 160, 140));
    g.drawLine(line, 12.0f); 
}
