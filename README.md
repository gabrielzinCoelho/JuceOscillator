# 🎵 Oscilador Simples - Plugin VST3

Um plugin de áudio VST3 desenvolvido em C++ utilizando o framework JUCE. Este oscilador modular serve tanto como gerador de teste de áudio quanto como base para um sintetizador completo.

## 📋 Sobre o Projeto

Este projeto implementa um oscilador de áudio digital com controles essenciais para geração e manipulação de ondas sonoras. Ideal para aprendizado de síntese de áudio, teste de equipamentos e desenvolvimento de sintetizadores.

## ✨ Funcionalidades

### 1. 🎼 Seletor de Tipo de Onda (Waveform Select)

Permite escolher a "cor" ou timbre do som gerado através de diferentes formas de onda.

**Controle Visual:** Menu dropdown (ComboBox) ou knob rotativo com 4 posições

**Opções Disponíveis:**
- **Senoide (Sine):** Som puro e suave, ideal para sub-graves e tons fundamentais
- **Dente de Serra (Sawtooth):** Som rasgado e brilhante, perfeito para cordas sintéticas e leads
- **Quadrada (Square):** Som "oco" característico de videogames clássicos, ótimo para baixos
- **Triângulo (Triangle):** Meio termo entre senoide e dente de serra, som mais suave

### 2. 🎚️ Controle de Frequência (Frequency)

Permite ajustar manualmente a frequência do oscilador. Como este plugin não processa MIDI por enquanto, a frequência é controlada diretamente.

**Controle Visual:** Knob grande ou slider horizontal

**Faixa de Operação:** 20 Hz (grave profundo) até 20.000 Hz (agudo extremo)

### 3. 🔊 Volume Geral (Master Gain)

Controla o nível de saída do oscilador. Osciladores digitais geram sinais em amplitude máxima (0 dB), sendo necessário atenuação para uso prático.

**Controle Visual:** Knob pequeno ou fader vertical

**Faixa de Operação:** -∞ dB (mudo) até 0 dB (volume máximo)

### 4. ◀️▶️ Panorâmica (Pan)

Controla o posicionamento do som no campo estéreo, permitindo direcionar o áudio para os canais esquerdo ou direito.

**Controle Visual:** Knob centralizado

**Faixa de Operação:** -100% (totalmente à esquerda) até +100% (totalmente à direita)

## 🛠️ Tecnologias Utilizadas

- **Linguagem:** C++
- **Framework:** JUCE (plataforma para desenvolvimento de plugins de áudio)
- **Formato:** VST3 (Virtual Studio Technology)

## 📦 Estrutura do Projeto

```
JuceOscillator/
├── Source/
│   ├── Oscillator.h          # Implementação do motor do oscilador
│   ├── PluginProcessor.cpp   # Processamento de áudio
│   ├── PluginProcessor.h     # Declarações do processador
│   ├── PluginEditor.cpp      # Interface gráfica
│   └── PluginEditor.h        # Declarações da interface
├── OsciladorSimples.jucer    # Arquivo de projeto JUCE
└── README.md                 # Este arquivo
```

## 🚀 Como Usar

1. Abra o arquivo `.jucer` no Projucer (JUCE)
2. Configure o ambiente de desenvolvimento (Visual Studio, Xcode, etc.)
3. Compile o projeto
4. O plugin VST3 será gerado na pasta de saída
5. Copie o plugin para a pasta de plugins do seu DAW
6. Carregue o plugin em uma faixa de áudio no seu DAW

## 🎯 Casos de Uso

- **Geração de tom de teste** para calibração de equipamentos de áudio
- **Base para sintetizadores** mais complexos
- **Aprendizado** de síntese sonora e processamento de áudio digital
- **Efeitos sonoros** para jogos e multimídia
- **Sound design** e experimentação sonora

## 📝 Licença

Consulte o arquivo LICENSE para mais informações.

## 🤝 Autores
Tharlon Eduardo, Gabriel Coelho Costa, Isac Gonçalves Cunha, Otávio Sbampato
