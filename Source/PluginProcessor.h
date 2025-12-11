/*
  ==============================================================================
    PluginProcessor.h ----- Aqui é onde você declara classes, inicializa bibliotecas externas, é basicamente
    a biblioteca que faz o PluginProcessor.cpp funcionar.
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Oscillator.h" // Incluindo nosso "motor"

//==============================================================================
class OsciladorSimplesAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    OsciladorSimplesAudioProcessor();
    ~OsciladorSimplesAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    // --- ADICIONADO: O SISTEMA DE PARÂMETROS (APVTS) --- Declaração de classe básica
    juce::AudioProcessorValueTreeState apvts;
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

private:
    // --- ADICIONADO: O MOTOR DO OSCILADOR --- Declaração de classe básica
    Oscillator meuOscilador;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OsciladorSimplesAudioProcessor)
};
