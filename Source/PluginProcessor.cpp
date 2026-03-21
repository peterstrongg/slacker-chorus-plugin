/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SlackerChorusAudioProcessor::SlackerChorusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
}

SlackerChorusAudioProcessor::~SlackerChorusAudioProcessor()
{
}

//==============================================================================
const juce::String SlackerChorusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SlackerChorusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SlackerChorusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SlackerChorusAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SlackerChorusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SlackerChorusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SlackerChorusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SlackerChorusAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SlackerChorusAudioProcessor::getProgramName (int index)
{
    return {};
}

void SlackerChorusAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SlackerChorusAudioProcessor::prepareToPlay (double sr, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    sampleRate = sr;

    delayLine.reset();

	delayLine.prepare({ 
        sampleRate, 
        static_cast<juce::uint32> (samplesPerBlock), 
        static_cast<juce::uint32> (getTotalNumOutputChannels())}
    );
}

void SlackerChorusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SlackerChorusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SlackerChorusAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // =========================
    // PARAMETERS
    // =========================
    const float baseDelayMs = 20.0f;
    const float depthMs = 5.0f;
    const float mix = 0.5f;

    const float lfoIncrement =
        (2.0f * juce::MathConstants<float>::pi * lfoRate) / sampleRate;

    // We will compute ONE averaged delay per block (important fix)
    float blockLfoSum = 0.0f;
    int totalSamples = buffer.getNumSamples();

    // =========================
    // PROCESS AUDIO
    // =========================
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        lfoPhase = std::fmod(lfoPhase, juce::MathConstants<float>::twoPi);

        for (int sample = 0; sample < totalSamples; ++sample)
        {
            float input = channelData[sample];

            // ---- LFO ----
            float lfoValue = std::sin(lfoPhase);
            lfoPhase += lfoIncrement;

            blockLfoSum += lfoValue;

            float delayedSignal = delayLine.popSample(channel);
            delayLine.pushSample(channel, input);

            channelData[sample] =
                (input * (1.0f - mix)) + (delayedSignal * mix);
        }

        // =========================
        // UPDATE DELAY ONCE PER BLOCK
        // =========================
        float avgLfo = blockLfoSum / (float)totalSamples;
        blockLfoSum = 0.0f;

        float delayMs = baseDelayMs + (avgLfo * depthMs);
        float delaySamples = (delayMs / 1000.0f) * sampleRate;

        delayLine.setDelay(delaySamples);
    }
}

//==============================================================================
bool SlackerChorusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SlackerChorusAudioProcessor::createEditor()
{
    return new SlackerChorusAudioProcessorEditor (*this);
}

//==============================================================================
void SlackerChorusAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SlackerChorusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout SlackerChorusAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "RATE", "Rate",
        juce::NormalisableRange<float>(0.05f, 5.0f, 0.01f, 0.5f),
        0.3f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "DEPTH", "Depth",
        juce::NormalisableRange<float>(1.0f, 10.0f, 0.1f),
        4.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "MIX", "Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f),
        0.4f));

    return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SlackerChorusAudioProcessor();
}
