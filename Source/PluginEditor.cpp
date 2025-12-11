/*
  ==============================================================================
    PluginEditor.cpp - A Interface Visual 
  ==============================================================================
*/
#include <memory>
#include "PluginProcessor.h"
#include "PluginEditor.h"

// ==============================================================================
// CONSTRUTOR: ONDE MONTAMOS A TELA
// ==============================================================================
OsciladorSimplesAudioProcessorEditor::OsciladorSimplesAudioProcessorEditor(OsciladorSimplesAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Tamanho da janela
    setSize(500, 350);

    // --- 1. CONFIGURAR MENU DE ONDA ---
    waveTypeBox.addItem("Senoide (Sine)", 1);
    waveTypeBox.addItem("Dente de Serra (Saw)", 2);
    waveTypeBox.addItem("Quadrada (Square)", 3);
    waveTypeBox.addItem("Triangulo (Triangle)", 4);
    waveTypeBox.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(waveTypeBox);

    // A Cola: Liga o Menu ao parâmetro "WAVE" do processador
    waveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "WAVE", waveTypeBox);

    // --- 2. CONFIGURAR FREQUÊNCIA ---
    frequencySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(frequencySlider);

    freqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FREQ", frequencySlider);

    // --- 3. CONFIGURAR GANHO (VOLUME) ---
    gainSlider.setSliderStyle(juce::Slider::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(gainSlider);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAIN", gainSlider);

    // --- 4. CONFIGURAR PAN ---
    panSlider.setSliderStyle(juce::Slider::Rotary);
    panSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(panSlider);

    panAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "PAN", panSlider);

    // --- RÓTULOS (LABELS) ---
    addAndMakeVisible(waveLabel); waveLabel.setText("Tipo de Onda", juce::dontSendNotification);
    waveLabel.attachToComponent(&waveTypeBox, false);
    waveLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(freqLabel); freqLabel.setText("Frequencia (Hz)", juce::dontSendNotification);
    freqLabel.attachToComponent(&frequencySlider, false);
    freqLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(gainLabel); gainLabel.setText("Volume", juce::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, false);
    gainLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(panLabel); panLabel.setText("Pan (Esq/Dir)", juce::dontSendNotification);
    panLabel.attachToComponent(&panSlider, false);
    panLabel.setJustificationType(juce::Justification::centred);
}

OsciladorSimplesAudioProcessorEditor::~OsciladorSimplesAudioProcessorEditor()
{
}

// ==============================================================================
// PINTAR O FUNDO
// ==============================================================================
void OsciladorSimplesAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Fundo cinza escuro estilo "rack"!
    g.fillAll(juce::Colours::darkgrey.darker(0.2f));

    g.setColour(juce::Colours::white);
    g.setFont(30.0f);
    g.drawFittedText("OSCILADOR HUMILDE", getLocalBounds().removeFromTop(50), juce::Justification::centred, 1);

    g.setColour(juce::Colours::grey);
    g.setFont(14.0f);
    g.drawFittedText("v1.0 - Feito no Visual Studio", getLocalBounds().removeFromBottom(30), juce::Justification::centred, 1);
}

// ==============================================================================
// ORGANIZAR OS BOTÕES NA TELA
// ==============================================================================
void OsciladorSimplesAudioProcessorEditor::resized()
{
    // Define a posição exata (X, Y, Largura, Altura)

    waveTypeBox.setBounds(50, 80, 150, 30);

    frequencySlider.setBounds(250, 80, 250, 250);

    gainSlider.setBounds(50, 150, 60, 150);

    panSlider.setBounds(130, 200, 80, 80);
}
