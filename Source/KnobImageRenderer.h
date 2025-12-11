/*
  ==============================================================================
    KnobImageRenderer.h
    Classe utilitária para renderização de controles knobs usando imagens
    rotacionadas baseadas em valores de frequência
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <map>

class KnobImageRenderer
{
public:
    KnobImageRenderer()
    {
        initializeImageMap();
    }

    /**
     * Converte um valor de frequência (20Hz - 20.000Hz) para uma porcentagem (0-100%)
     * Usa escala logarítmica para melhor representação da percepção humana
     */
    static float frequencyToPercentage(float frequency)
    {
        // Limita a frequência ao intervalo válido
        frequency = juce::jlimit(20.0f, 20000.0f, frequency);
        
        // Calcula a porcentagem usando escala logarítmica
        const float minLog = std::log10(20.0f);
        const float maxLog = std::log10(20000.0f);
        const float currentLog = std::log10(frequency);
        
        float percentage = ((currentLog - minLog) / (maxLog - minLog)) * 100.0f;
        
        return juce::jlimit(0.0f, 100.0f, percentage);
    }

    /**
     * Converte uma porcentagem (0-100%) para valor de frequência (20Hz - 20.000Hz)
     * Usa escala logarítmica inversa
     */
    static float percentageToFrequency(float percentage)
    {
        percentage = juce::jlimit(0.0f, 100.0f, percentage);
        
        const float minLog = std::log10(20.0f);
        const float maxLog = std::log10(20000.0f);
        
        float logValue = minLog + (percentage / 100.0f) * (maxLog - minLog);
        float frequency = std::pow(10.0f, logValue);
        
        return juce::jlimit(20.0f, 20000.0f, frequency);
    }

    /**
     * Retorna o path da imagem que melhor se aproxima do ângulo de rotação
     * baseado no valor de frequência
     */
    juce::String getImagePathForFrequency(float frequency) const
    {
        float percentage = frequencyToPercentage(frequency);
        return getImagePathForPercentage(percentage);
    }

    /**
     * Retorna o path da imagem baseado na porcentagem (0-100%)
     * Seleciona a imagem mais próxima disponível no mapa
     */
    juce::String getImagePathForPercentage(float percentage) const
    {
        percentage = juce::jlimit(0.0f, 100.0f, percentage);
        
        // Encontra a porcentagem mais próxima no mapa
        int closestKey = 0;
        float minDifference = 100.0f;
        
        for (const auto& pair : imageMap)
        {
            float difference = std::abs(pair.first - percentage);
            if (difference < minDifference)
            {
                minDifference = difference;
                closestKey = pair.first;
            }
        }
        
        return imageMap.at(closestKey);
    }

    /**
     * Retorna o path da imagem baseado em um valor normalizado (0.0 - 1.0)
     */
    juce::String getImagePathForNormalizedValue(float normalizedValue) const
    {
        normalizedValue = juce::jlimit(0.0f, 1.0f, normalizedValue);
        float percentage = normalizedValue * 100.0f;
        return getImagePathForPercentage(percentage);
    }

    /**
     * Define um path customizado para uma porcentagem específica
     */
    void setImagePath(int percentage, const juce::String& path)
    {
        if (percentage >= 0 && percentage <= 100)
        {
            imageMap[percentage] = path;
        }
    }

    /**
     * Retorna o mapa completo de imagens
     */
    const std::map<int, juce::String>& getImageMap() const
    {
        return imageMap;
    }

    /**
     * Define o diretório base onde as imagens estão armazenadas
     */
    void setBaseDirectory(const juce::String& directory)
    {
        baseDirectory = directory;
        initializeImageMap();
    }

    /**
     * Carrega e retorna a imagem JUCE para uma frequência específica
     */
    juce::Image loadImageForFrequency(float frequency) const
    {
        juce::String imagePath = getImagePathForFrequency(frequency);
        juce::File imageFile(imagePath);
        
        if (imageFile.existsAsFile())
        {
            return juce::ImageFileFormat::loadFrom(imageFile);
        }
        
        return juce::Image();
    }

private:
    std::map<int, juce::String> imageMap;
    juce::String baseDirectory = "Resources/Images/Knobs/";

    /**
     * Inicializa o mapa de imagens com 11 posições (0%, 10%, 20%, ..., 100%)
     */
    void initializeImageMap()
    {
        imageMap.clear();
        
        imageMap[0]   = baseDirectory + "knob_000.png";
        imageMap[10]  = baseDirectory + "knob_010.png";
        imageMap[20]  = baseDirectory + "knob_020.png";
        imageMap[30]  = baseDirectory + "knob_030.png";
        imageMap[40]  = baseDirectory + "knob_040.png";
        imageMap[50]  = baseDirectory + "knob_050.png";
        imageMap[60]  = baseDirectory + "knob_060.png";
        imageMap[70]  = baseDirectory + "knob_070.png";
        imageMap[80]  = baseDirectory + "knob_080.png";
        imageMap[90]  = baseDirectory + "knob_090.png";
        imageMap[100] = baseDirectory + "knob_100.png";
    }
};
