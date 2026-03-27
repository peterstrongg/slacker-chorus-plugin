/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "RotaryDialLookAndFeel.h"
#include "SlackerChorusLookAndFeel.h"


//==============================================================================
/**
*/
class SlackerChorusAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SlackerChorusAudioProcessorEditor (SlackerChorusAudioProcessor&);
    ~SlackerChorusAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SlackerChorusAudioProcessor& audioProcessor;

    juce::Slider rateSlider;
	juce::Slider depthSlider;
    juce::Slider mixSlider;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;

    std::unique_ptr<SlackerChorusLookAndFeel> rateLookAndFeel;
    std::unique_ptr<RotaryDialLookAndFeel> depthLookAndFeel;
    std::unique_ptr<RotaryDialLookAndFeel> mixLookAndFeel;

	std::unique_ptr<SlackerChorusLookAndFeel> customLookAndFeel;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SlackerChorusAudioProcessorEditor)
};
