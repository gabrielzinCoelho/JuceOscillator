/*
  ==============================================================================
    KnobImageRenderer_Example.cpp
    Exemplos de uso da classe KnobImageRenderer
  ==============================================================================
*/

#include "KnobImageRenderer.h"

/*
  EXEMPLO 1: Uso básico - obter path da imagem para uma frequência
  
  KnobImageRenderer renderer;
  
  // Para 20 Hz (frequência mínima) - retorna "Resources/Images/Knobs/knob_000.png"
  juce::String path1 = renderer.getImagePathForFrequency(20.0f);
  
  // Para 200 Hz (frequência média-baixa) - retorna imagem próxima a ~30%
  juce::String path2 = renderer.getImagePathForFrequency(200.0f);
  
  // Para 2000 Hz (frequência média) - retorna imagem próxima a ~50%
  juce::String path3 = renderer.getImagePathForFrequency(2000.0f);
  
  // Para 20.000 Hz (frequência máxima) - retorna "Resources/Images/Knobs/knob_100.png"
  juce::String path4 = renderer.getImagePathForFrequency(20000.0f);
*/

/*
  EXEMPLO 2: Uso com valor normalizado (0.0 a 1.0)
  
  KnobImageRenderer renderer;
  
  // Para valor normalizado 0.0 (0%) - retorna "Resources/Images/Knobs/knob_000.png"
  juce::String path1 = renderer.getImagePathForNormalizedValue(0.0f);
  
  // Para valor normalizado 0.5 (50%) - retorna "Resources/Images/Knobs/knob_050.png"
  juce::String path2 = renderer.getImagePathForNormalizedValue(0.5f);
  
  // Para valor normalizado 1.0 (100%) - retorna "Resources/Images/Knobs/knob_100.png"
  juce::String path3 = renderer.getImagePathForNormalizedValue(1.0f);
*/

/*
  EXEMPLO 3: Converter entre frequência e porcentagem
  
  // Frequência para porcentagem
  float percentage = KnobImageRenderer::frequencyToPercentage(1000.0f);
  DBG("1000 Hz = " + juce::String(percentage, 2) + "%");
  
  // Porcentagem para frequência
  float frequency = KnobImageRenderer::percentageToFrequency(50.0f);
  DBG("50% = " + juce::String(frequency, 2) + " Hz");
*/

/*
  EXEMPLO 4: Customizar paths de imagem
  
  KnobImageRenderer renderer;
  
  // Alterar o diretório base
  renderer.setBaseDirectory("Assets/UI/Knobs/");
  
  // Ou definir path individual
  renderer.setImagePath(0, "Assets/UI/Knobs/custom_min.png");
  renderer.setImagePath(100, "Assets/UI/Knobs/custom_max.png");
*/

/*
  EXEMPLO 5: Carregar imagem diretamente
  
  KnobImageRenderer renderer;
  
  // Carrega a imagem JUCE para uma frequência específica
  juce::Image knobImage = renderer.loadImageForFrequency(440.0f); // Lá central
  
  if (knobImage.isValid())
  {
      // Desenhar a imagem em um componente
      g.drawImage(knobImage, bounds);
  }
*/

/*
  EXEMPLO 6: Integração com Slider/Knob em PluginEditor
  
  class MyKnobComponent : public juce::Component
  {
  public:
      MyKnobComponent()
      {
          frequencySlider.setRange(20.0, 20000.0, 0.01);
          frequencySlider.setValue(440.0);
          frequencySlider.setSkewFactorFromMidPoint(1000.0); // Escala logarítmica
          frequencySlider.onValueChange = [this]()
          {
              updateKnobImage();
          };
          
          addAndMakeVisible(frequencySlider);
          updateKnobImage();
      }
      
      void paint(juce::Graphics& g) override
      {
          if (currentKnobImage.isValid())
          {
              g.drawImage(currentKnobImage, getLocalBounds().toFloat());
          }
      }
      
  private:
      void updateKnobImage()
      {
          float frequency = frequencySlider.getValue();
          currentKnobImage = renderer.loadImageForFrequency(frequency);
          repaint();
      }
      
      juce::Slider frequencySlider;
      KnobImageRenderer renderer;
      juce::Image currentKnobImage;
  };
*/

/*
  EXEMPLO 7: Uso com LookAndFeel customizado
  
  class CustomKnobLookAndFeel : public juce::LookAndFeel_V4
  {
  public:
      void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                           juce::Slider& slider) override
      {
          // Obter frequência do slider
          float frequency = slider.getValue();
          
          // Obter imagem correspondente
          juce::Image knobImage = renderer.loadImageForFrequency(frequency);
          
          if (knobImage.isValid())
          {
              // Desenhar a imagem do knob
              juce::Rectangle<int> bounds(x, y, width, height);
              g.drawImage(knobImage, bounds.toFloat());
          }
          else
          {
              // Fallback para desenho padrão se imagem não existir
              LookAndFeel_V4::drawRotarySlider(g, x, y, width, height,
                                              sliderPos, rotaryStartAngle,
                                              rotaryEndAngle, slider);
          }
      }
      
  private:
      KnobImageRenderer renderer;
  };
*/

/*
  TABELA DE REFERÊNCIA: Mapeamento Frequência -> Porcentagem (escala logarítmica)
  
  Frequência (Hz)  |  Porcentagem (%)  |  Imagem mais próxima
  -------------------------------------------------------------
  20               |  0%               |  knob_000.png
  40               |  10%              |  knob_010.png
  80               |  20%              |  knob_020.png
  160              |  30%              |  knob_030.png
  320              |  40%              |  knob_040.png
  630              |  50%              |  knob_050.png
  1260             |  60%              |  knob_060.png
  2500             |  70%              |  knob_070.png
  5000             |  80%              |  knob_080.png
  10000            |  90%              |  knob_090.png
  20000            |  100%             |  knob_100.png
*/
