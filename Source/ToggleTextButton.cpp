//
//  ToggleTextButtonn.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/16/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"

class ToggleTextButton : public TextButton, private LookAndFeel_V3
{
public:
    String toggleOnText, toggleOffText;
    
    ToggleTextButton()
    {
        setClickingTogglesState(true);
        setLookAndFeel (this);
    }
    
    void setToggleText (String toggleOnText, String toggleOffText)
    {
        this->toggleOnText = toggleOnText;
        this->toggleOffText = toggleOffText;
        repaint();
    }
    
private:
    void drawButtonText (Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/) override
    {
        Font font (getTextButtonFont (button, button.getHeight()));
        g.setFont (font);
        g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                        : TextButton::textColourOffId)
                     .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
        
        button.setButtonText((button.getToggleState()) ? toggleOnText : toggleOffText);
        
        const int yIndent = jmin (4, button.proportionOfHeight (0.3f));
        const int cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;
        
        const int fontHeight = roundToInt (font.getHeight() * 0.6f);
        const int leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
        const int rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
        const int textWidth = button.getWidth() - leftIndent - rightIndent;
        
        if (textWidth > 0)
            g.drawFittedText (button.getButtonText(),
                              leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2,
                              Justification::centred, 2);

    }
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                                               bool isMouseOverButton, bool isButtonDown) override
    {
        Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));
        
        if (isButtonDown || isMouseOverButton)
            baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);
        
        const bool flatOnLeft   = button.isConnectedOnLeft();
        const bool flatOnRight  = button.isConnectedOnRight();
        const bool flatOnTop    = button.isConnectedOnTop();
        const bool flatOnBottom = button.isConnectedOnBottom();
        
        const float width  = button.getWidth() - 1.0f;
        const float height = button.getHeight() - 1.0f;
        
        if (width > 0 && height > 0)
        {
            const float cornerSize = 4.0f;
            
            Path outline;
            outline.addRoundedRectangle (0.5f, 0.5f, width, height, cornerSize, cornerSize,
                                         ! (flatOnLeft  || flatOnTop),
                                         ! (flatOnRight || flatOnTop),
                                         ! (flatOnLeft  || flatOnBottom),
                                         ! (flatOnRight || flatOnBottom));
            
            if (isButtonDown || isMouseOverButton)
            {
                g.setColour ((isButtonDown) ? Colours::white.withAlpha (0.4f) : Colours::white.withAlpha (0.2f));
                g.fillPath (outline);
            }
            
            const float mainBrightness = baseColour.getBrightness();
            const float mainAlpha = baseColour.getFloatAlpha();
            
            g.setGradientFill (ColourGradient (baseColour.brighter (0.2f), 0.0f, 0.0f, baseColour.darker (0.25f), 0.0f, height, false));
            //g.fillPath (outline);
            
            g.setColour (Colours::white.withAlpha (0.4f * mainAlpha * mainBrightness * mainBrightness));
            g.strokePath (outline, PathStrokeType (1.0f), AffineTransform::translation (0.0f, 1.0f)
                          .scaled (1.0f, (height - 1.6f) / height));
            
            g.setColour (Colours::black.withAlpha (0.4f * mainAlpha));
            g.strokePath (outline, PathStrokeType (1.0f));
        }
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToggleTextButton)
};
