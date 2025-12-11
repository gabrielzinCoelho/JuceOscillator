#pragma once
#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel()
    {
        // === IMAGENS ===
        knobImage = juce::ImageCache::getFromMemory(BinaryData::knob_slider_png, BinaryData::knob_slider_pngSize);
        knobBase = juce::ImageCache::getFromMemory(BinaryData::knob_base_png, BinaryData::knob_base_pngSize);

        sliderBg = juce::ImageCache::getFromMemory(BinaryData::slider_base_png, BinaryData::slider_base_pngSize);
        sliderHandle = juce::ImageCache::getFromMemory(BinaryData::slider_lid_png, BinaryData::slider_lid_pngSize);

        // === FONTE ORBORN.TTF ===
        loadCustomFont();
    }

    // =======================================
    //   FUNÇÃO QUE REALMENTE CARREGA A FONTE
    // =======================================
    void loadCustomFont()
    {
        // Certifique-se de que Orborn.ttf foi adicionado ao Binary Resources no Projucer
        const void* fontData = static_cast<const void*>(BinaryData::Organix_otf);
        size_t fontSize = (size_t)BinaryData::Organix_otfSize;

        // createSystemTypefaceFor retorna juce::Typeface::Ptr
        juce::Typeface::Ptr tf = juce::Typeface::createSystemTypefaceFor(fontData, fontSize);

        orbornTypeface = tf;

        // gera um juce::Font a partir do typeface e escolhe a altura padrão (18)
        defaultFont = juce::Font(orbornTypeface).withHeight(12.0f);
    }

    // =============== FONTE EM LABELS, MENUS, ETC ===============
    juce::Font getLabelFont(juce::Label&) override
    {
        return defaultFont;
    }

    juce::Font getComboBoxFont(juce::ComboBox&) override
    {
        return defaultFont;
    }

    juce::Font getTextButtonFont(juce::TextButton&, int height) override
    {
        return defaultFont.withHeight((float)height * 0.55f);
    }

    juce::Font getPopupMenuFont() override
    {
        return defaultFont;
    }

    // ======================
    //  KNOBS (Rotary Slider)
    // ======================
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, juce::Slider& slider) override
    {
        juce::Image pointerImg = knobImage;   
        juce::Image baseImg = knobBase;    

        const float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

        int targetSize = juce::jmin(width, height);

        juce::Rectangle<float> bounds{
            x + (width - targetSize) * 0.5f,
            y + (height - targetSize) * 0.5f,
            (float)targetSize,
            (float)targetSize
        };

        // --- 1) BASE (fixa) ---
        g.drawImage(baseImg,
            bounds.getX(), bounds.getY(),
            bounds.getWidth(), bounds.getHeight(),
            0, 0,
            baseImg.getWidth(), baseImg.getHeight()
        );

        // --- 2) PONTEIRO (rotaciona + desloca) ---

        float cx = pointerImg.getWidth() * 0.5f;
        float cy = pointerImg.getHeight() * 0.5f;

        // Ajustes finos de posição
        const float offsetX = 0.0f;   
        const float offsetY = -0.01f; 

        juce::AffineTransform transform =
            juce::AffineTransform::rotation(angle, cx, cy)
            .followedBy(juce::AffineTransform::scale(
                (float)targetSize / pointerImg.getWidth(),
                (float)targetSize / pointerImg.getHeight()))
            .followedBy(juce::AffineTransform::translation(
                bounds.getX() + offsetX,
                bounds.getY() + offsetY
            ));

        g.drawImageTransformed(pointerImg, transform, false);
    }


    // Identifica qual knob é qual
    void setFrequencySlider(juce::Slider* s) { freqSliderPtr = s; }
    void setPanSlider(juce::Slider* s) { panSliderPtr = s; }

    // ======================
    //  SLIDER VERTICAL (GAIN)
    // ======================
    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        // ==========================
        // 1) BASE (FUNDO DO SLIDER)
        // ==========================

        const float baseWidthFactor = 0.55f;
        const float baseWidth = width * baseWidthFactor;

        const float baseX = x + (width - baseWidth) * 0.5f;
        const float baseY = y;

        g.drawImage(
            sliderBg,
            baseX, baseY,
            baseWidth, height,
            0, 0,
            sliderBg.getWidth(),
            sliderBg.getHeight()
        );

        // ==========================
        // 2) HANDLE (PEGADOR)
        // ==========================

        const float handleWidth = baseWidth * 0.50f;

        const float handleScale = handleWidth / sliderHandle.getWidth();
        const float handleHeight = sliderHandle.getHeight() * handleScale;

        const float handleX = x + (width - handleWidth) * 0.5f;

        // === Limite vertical do handle (80%) ===
        const float maxHandleHeight = height * 0.75f;
        float limitedHandleHeight = handleHeight;

        if (limitedHandleHeight > maxHandleHeight)
            limitedHandleHeight = maxHandleHeight;

        float handleY = sliderPos - (limitedHandleHeight * 0.5f);

        if (handleY < y)
            handleY = y;

        if (handleY > y + height - limitedHandleHeight)
            handleY = y + height - limitedHandleHeight;

        g.drawImage(
            sliderHandle,
            handleX,
            handleY,
            handleWidth,
            limitedHandleHeight,
            0, 0,
            sliderHandle.getWidth(),
            sliderHandle.getHeight()
        );
    }


private:
    juce::Image knobImage, knobBase;
    juce::Image sliderBg, sliderHandle;

    juce::Font defaultFont;
    juce::Typeface::Ptr orbornTypeface; 

    juce::Slider* freqSliderPtr = nullptr;
    juce::Slider* panSliderPtr = nullptr;
};
