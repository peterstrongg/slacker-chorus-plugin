#include "RotaryDialLookAndFeel.h"

void RotaryDialLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPosProportional, float rotaryStartAngle,
    float rotaryEndAngle, juce::Slider& slider)
{
    if (!dialImage.isValid())
        return;

    // Compute rotation angle based on slider position
    float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    // Center of the slider
    float centerX = x + width * 0.5f;
    float centerY = y + height * 0.5f;

    // Save graphics state so rotation doesn't affect other drawings
    g.addTransform(juce::AffineTransform::rotation(angle, centerX, centerY));

    // Draw the image centered in the slider bounds
    g.drawImageWithin(dialImage, x, y, width, height, juce::RectanglePlacement::centred);

    // Optional: restore transform (JUCE automatically does this per paint call)
}