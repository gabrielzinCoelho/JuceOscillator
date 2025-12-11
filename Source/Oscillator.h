/*
  ==============================================================================

  É a "biblioteca/classe" do nosso oscilador simples, que gera formas de ondas básicas usando
  funções matemáticas, a maior parte já vem pronta em classes do próprio JUCE, parte vital do 
  modulo oscilador.

  ==============================================================================
*/
#pragma once
#include <cmath>               
#include <juce_audio_basics/juce_audio_basics.h>

class Oscillator
{
public:
    void setSampleRate(double sampleRate) {
        currentSampleRate = sampleRate;
        updateIncrement();
    }

    void setFrequency(float frequency) {
        frequencyInHz = frequency;
        updateIncrement();
    }

    void setWaveType(int type) {
        waveType = type;
    }

    float getNextSample() {
        float output = 0.0f;

        // Lógica da Onda
        if (waveType == 0)      // Senoide (Sine)
            output = std::sin(currentPhase * 2.0 * juce::MathConstants<double>::pi);
        else if (waveType == 1) // Serra (Sawtooth)
            output = (2.0f * currentPhase) - 1.0f;
        else if (waveType == 2) // Quadrada (Square)
            output = (currentPhase < 0.5f) ? 1.0f : -1.0f;
        else if (waveType == 3) // Triângulo (Triangle)
            output = (2.0f * std::abs(2.0f * currentPhase - 1.0f)) - 1.0f;

        // Avança o contador
        currentPhase += phaseIncrement;
        if (currentPhase >= 1.0) currentPhase -= 1.0;

        return output;
    }

private:
    void updateIncrement() {
        if (currentSampleRate > 0)
            phaseIncrement = frequencyInHz / currentSampleRate;
    }

    double currentSampleRate = 44100.0;
    double frequencyInHz = 440.0;
    double currentPhase = 0.0;
    double phaseIncrement = 0.0;
    int waveType = 0;
};