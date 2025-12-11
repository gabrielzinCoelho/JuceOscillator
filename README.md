#Para um Oscilador "Modular" (que serve tanto como gerador de teste, quanto como coração de um possível sintetizador), precisamos de 4 controles essenciais.

##1. Seletor de Tipo de Onda (Waveform Select)
O usuário precisa escolher a "cor" do som.

Controle Visual: Um Menu (ComboBox) ou um Knob rotativo com 4 posições.

Opções:

Senoide (Sine): Som puro, suave (bom para sub-grave).

Dente de Serra (Sawtooth): Som rasgado, brilhante (bom para cordas/leads).

Quadrada (Square): Som "oco", videogame (bom para baixos).

Triângulo (Triangle): Meio termo entre Seno e Serra.

##2. Controle de Frequência (Frequency)
Já que esse plugin não vai receber notas de um teclado musical (MIDI) por enquanto, precisamos de um botão para "afinar" o oscilador manualmente.

Controle Visual: Um Knob grande ou Slider.

Faixa: De 20 Hz (grave profundo) a 20.000 Hz (agudo extremo).

##3. Volume Geral (Master Gain)
Osciladores digitais puros são matematicamente "perfeitos" e, por isso, muito altos (batem em 0dB). Precisamos de um controle para atenuar.

Controle Visual: Um Knob pequeno ou Fader vertical.

Faixa: De -Infinito (mudo) a 0 dB (volume máximo).

##4. Panorâmica (Pan) - O "Bônus"
Adiciona a capacidade de jogar o som para a esquerda ou direita

Controle Visual: Knob centralizado.

Faixa: Esquerda (-100%) a Direita (+100%).
