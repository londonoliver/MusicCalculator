//
//  ToggleTextButtonn.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/16/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"

class ToggleTextButton : public Component, private LookAndFeel_V3
{
public:
    TextButton b;
    String toggleOnText, toggleOffText;
    
    ToggleTextButton()
    {
        addAndMakeVisible(b);
        b.setClickingTogglesState(true);
        b.setLookAndFeel (this);
    }
    
    void setToggleText (String toggleOnText, String toggleOffText)
    {
        this->toggleOnText = toggleOnText;
        this->toggleOffText = toggleOffText;
        repaint();
    }
    
    void resized() override
    {
        b.setBounds(0, 0, getWidth(), getHeight());
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToggleTextButton)
};
