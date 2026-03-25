/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SlackerChorusAudioProcessorEditor::SlackerChorusAudioProcessorEditor (SlackerChorusAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
	rateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "RATE", rateSlider);
	depthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DEPTH", depthSlider);
	mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", mixSlider);

	addAndMakeVisible(rateSlider);
    addAndMakeVisible(depthSlider);
    addAndMakeVisible(mixSlider);

    setSize (600, 400);
}

SlackerChorusAudioProcessorEditor::~SlackerChorusAudioProcessorEditor()
{
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
	rateSlider.setBounds(10, 10, getWidth() - 20, 20);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
