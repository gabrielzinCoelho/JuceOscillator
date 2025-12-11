/*
  ==============================================================================
    PluginProcessor.cpp - O Cérebro do Plugin --- É basicamente a "main" do puglin
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

// ==============================================================================
// 1. AQUI CRIAMOS OS BOTÕES NA MEMÓRIA
// ==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout OsciladorSimplesAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Tipo de Onda (0 a 3)
    params.push_back(std::make_unique<juce::AudioParameterInt>("WAVE", "Wave Type", 0, 3, 0));

    // Frequência (20Hz a 20kHz)
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FREQ", "Frequency",
        juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.25f), 440.0f));

    // Ganho (0 a 1)
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", 0.0f, 1.0f, 0.5f));

    // Pan (-1 a 1)
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PAN", "Pan", -1.0f, 1.0f, 0.0f));

    return { params.begin(), params.end() };
}

// ==============================================================================
// 2. O CONSTRUTOR (Inicialização)
// ==============================================================================
OsciladorSimplesAudioProcessor::OsciladorSimplesAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    // LIGA O SISTEMA DE PARÂMETROS
    apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
}

OsciladorSimplesAudioProcessor::~OsciladorSimplesAudioProcessor()
{
}

// ==============================================================================
// 3. PREPARAR O ÁUDIO
// ==============================================================================
void OsciladorSimplesAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Avisa o oscilador sobre a taxa de amostragem
    meuOscilador.setSampleRate(sampleRate);
}

void OsciladorSimplesAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OsciladorSimplesAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    return true;
#endif
}
#endif

// ==============================================================================
// 4. PROCESSAR O ÁUDIO (O LOOP PRINCIPAL)
// ==============================================================================
void OsciladorSimplesAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Limpa o buffer
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // --- LER OS BOTÕES ---
    int waveType = (int)*apvts.getRawParameterValue("WAVE");
    float frequency = *apvts.getRawParameterValue("FREQ");
    float gain = *apvts.getRawParameterValue("GAIN");
    float pan = *apvts.getRawParameterValue("PAN");

    // --- ATUALIZAR OSCILADOR ---
    meuOscilador.setWaveType(waveType);
    meuOscilador.setFrequency(frequency);

    auto* leftChannel = buffer.getWritePointer(0);
    auto* rightChannel = (totalNumOutputChannels > 1) ? buffer.getWritePointer(1) : nullptr;

    // --- GERAR SOM ---
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        float rawSample = meuOscilador.getNextSample();

        // Aplica Volume
        rawSample *= gain;

        // Aplica Pan
        float leftGain = (1.0f - pan) * 0.5f;
        float rightGain = (1.0f + pan) * 0.5f;

        leftChannel[sample] = rawSample * (leftGain * 2.0f);

        if (rightChannel != nullptr)
        {
            rightChannel[sample] = rawSample * (rightGain * 2.0f);
        }
    }
}

// ==============================================================================
// FUNÇÕES PADRÃO -- Não modifiquei muito(Tharlon)
// ==============================================================================
bool OsciladorSimplesAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* OsciladorSimplesAudioProcessor::createEditor()
{
    return new OsciladorSimplesAudioProcessorEditor(*this);
}

void OsciladorSimplesAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {}
void OsciladorSimplesAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {}

const juce::String OsciladorSimplesAudioProcessor::getName() const { return JucePlugin_Name; }
bool OsciladorSimplesAudioProcessor::acceptsMidi() const { return false; }
bool OsciladorSimplesAudioProcessor::producesMidi() const { return false; }
bool OsciladorSimplesAudioProcessor::isMidiEffect() const { return false; }
double OsciladorSimplesAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int OsciladorSimplesAudioProcessor::getNumPrograms() { return 1; }
int OsciladorSimplesAudioProcessor::getCurrentProgram() { return 0; }
void OsciladorSimplesAudioProcessor::setCurrentProgram(int index) {}
const juce::String OsciladorSimplesAudioProcessor::getProgramName(int index) { return {}; }
void OsciladorSimplesAudioProcessor::changeProgramName(int index, const juce::String& newName) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OsciladorSimplesAudioProcessor();
}
