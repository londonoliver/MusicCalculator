//
//  ToggleTextButton.h
//  MusicCalculator
//
//  Created by London Oliver on 3/31/17.
//
//

#ifndef ToggleTextButton_h
#define ToggleTextButton_h

#include "../JuceLibraryCode/JuceHeader.h"

class ToggleTextButton : public TextButton, private LookAndFeel_V3
{
public:
    String toggleOnText, toggleOffText;
    
    ToggleTextButton();
    
    void setToggleText (String toggleOnText, String toggleOffText);
    void setColour (Colour colour);
    
private:
    void drawButtonText (Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/) override;
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override;
    Font getTextButtonFont (TextButton&, int buttonHeight) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToggleTextButton)
};

#endif /* ToggleTextButton_h */
