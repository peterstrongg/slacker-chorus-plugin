#include "RotaryDialLookAndFeel.h"

void RotaryDialLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPosProportional, float rotaryStartAngle,
    float rotaryEndAngle, juce::Slider& slider)
{
    if (!dialImage.isValid())
        return;

    float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    float centerX = x + width * 0.5f;
    float centerY = y + height * 0.5f;

    g.addTransform(juce::AffineTransform::rotation(angle, centerX, centerY));

    g.drawImageWithin(dialImage, x, y, width, height, juce::RectanglePlacement::centred);
}