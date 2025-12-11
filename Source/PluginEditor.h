/*
  ==============================================================================

  É a "biblioteca" do PluginEditor, essecial pra versão cpp funcionar.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class OsciladorSimplesAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    OsciladorSimplesAudioProcessorEditor (OsciladorSimplesAudioProcessor&);
    ~OsciladorSimplesAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // Esta referência é fornecida como uma maneira rápida para o seu editor acessar o objeto processor que o criou.
    OsciladorSimplesAudioProcessor& audioProcessor;

    // Attachments:
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> panAttachment;

    //Controles e labels:
    juce::ComboBox waveTypeBox;
    juce::Slider frequencySlider;
    juce::Slider gainSlider;
    juce::Slider panSlider;
    juce::Label waveLabel, freqLabel, gainLabel, panLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OsciladorSimplesAudioProcessorEditor)
};
