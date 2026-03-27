/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "RotaryDialLookAndFeel.h"

#define DIAL_WIDTH 100
#define DIAL_HEIGHT 100

//==============================================================================
SlackerChorusAudioProcessorEditor::SlackerChorusAudioProcessorEditor (SlackerChorusAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
	rateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "RATE", rateSlider);
    depthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DEPTH", depthSlider);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", depthSlider);

    juce::Image earthImage = juce::ImageFileFormat::loadFrom(BinaryData::earth_png, BinaryData::earth_pngSize);

    rateLookAndFeel = std::make_unique<SlackerChorusLookAndFeel>();
    depthLookAndFeel = std::make_unique<RotaryDialLookAndFeel>(earthImage);
    
    rateSlider.setLookAndFeel(rateLookAndFeel.get());
    rateSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    depthSlider.setLookAndFeel(depthLookAndFeel.get());
    depthSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    depthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    addAndMakeVisible(rateSlider);
    addAndMakeVisible(depthSlider);

    setSize (600, 400);
}

SlackerChorusAudioProcessorEditor::~SlackerChorusAudioProcessorEditor()
{
	rateSlider.setLookAndFeel(nullptr);
    depthSlider.setLookAndFeel(nullptr);
}

//==============================================================================
void SlackerChorusAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Slacker Chorus", getLocalBounds(), juce::Justification::centred, 1);
}

void SlackerChorusAudioProcessorEditor::resized()
{
	
    rateSlider.setBounds(50, 50, DIAL_WIDTH, DIAL_HEIGHT);
    depthSlider.setBounds(250, 50, DIAL_WIDTH, DIAL_HEIGHT);
    
    //depthSlider.setBounds(10, 40, getWidth() - 20, 20);
	//mixSlider.setBounds(10, 70, getWidth() - 20, 20);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
