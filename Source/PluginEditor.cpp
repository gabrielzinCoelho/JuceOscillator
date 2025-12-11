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
    setSize(720, 360);
    setLookAndFeel(&customLF);

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
    // FREQUÊNCIA (knob)
    frequencySlider.setSliderStyle(juce::Slider::Rotary);
    frequencySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    frequencySlider.setLookAndFeel(&customLF);
    customLF.setFrequencySlider(&frequencySlider);
    addAndMakeVisible(frequencySlider);

    freqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FREQ", frequencySlider);

    // --- 3. CONFIGURAR GANHO (VOLUME) ---
    gainSlider.setSliderStyle(juce::Slider::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    gainSlider.setLookAndFeel(&customLF);
    addAndMakeVisible(gainSlider);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAIN", gainSlider);

    // --- 4. CONFIGURAR PAN ---
    panSlider.setSliderStyle(juce::Slider::Rotary);
    panSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    panSlider.setLookAndFeel(&customLF);
    customLF.setPanSlider(&panSlider);
    addAndMakeVisible(panSlider);

    panAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "PAN", panSlider);

    // --- RÓTULOS (LABELS) ---
    addAndMakeVisible(waveLabel); waveLabel.setText("TIPO DE ONDA", juce::dontSendNotification);
    waveLabel.attachToComponent(&waveTypeBox, false);
    waveLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(freqLabel); freqLabel.setText("FREQUENCIA (Hz)", juce::dontSendNotification);
    freqLabel.attachToComponent(&frequencySlider, false);
    freqLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(gainLabel); gainLabel.setText("VOLUME", juce::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, false);
    gainLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(panLabel); panLabel.setText("PAN (ESQ/DIR)", juce::dontSendNotification);
    panLabel.attachToComponent(&panSlider, false);
    panLabel.setJustificationType(juce::Justification::centred);
}

OsciladorSimplesAudioProcessorEditor::~OsciladorSimplesAudioProcessorEditor() 
{
    frequencySlider.setLookAndFeel(nullptr);
    panSlider.setLookAndFeel(nullptr);
    setLookAndFeel(nullptr);
}

// ==============================================================================
// PINTAR O FUNDO
// ==============================================================================
void OsciladorSimplesAudioProcessorEditor::paint(juce::Graphics& g)
{
    background = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    // Fundo cinza escuro estilo "rack"!
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);

    g.setColour(juce::Colours::grey);
    g.setFont(14.0f);
}

// ==============================================================================
// ORGANIZAR OS BOTÕES NA TELA
// ==============================================================================
void OsciladorSimplesAudioProcessorEditor::resized()
{
    // Define a posição exata (X, Y, Largura, Altura)

    waveTypeBox.setBounds(30, 110, 150, 30);

    frequencySlider.setBounds(570, 110, 110, 110);

    gainSlider.setBounds(68, 170, 80, 160);

    panSlider.setBounds(570, 240, 110, 110);
}
