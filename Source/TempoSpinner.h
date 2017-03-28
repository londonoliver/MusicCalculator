//
//  TempoSpinner.h
//  MusicCalculator
//
//  Created by London Oliver on 2/18/17.
//
//

#ifndef TempoSpinner_h
#define TempoSpinner_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "Spinner.h"

class TempoSpinner : public Component, private Label::Listener, private LookAndFeel_V3
{
public:
    int width;
    int height;
    
    Font font;
    String f;
    
    Spinner s1;
    Spinner s2;
    Spinner s3;
    Spinner s4;
    Spinner s5;
    Spinner s6;
    
    Label ed;
    
    int s1Width;
    int s2Width;
    int s3Width;
    int s4Width;
    int s5Width;
    int s6Width;
    
    Colour highlightColour;
    
    TempoSpinner();
    ~TempoSpinner();
    
    void setBackgroundColour (Colour colour);
    void setTextColour (Colour colour);
    void setFontHeight (float fontHeight);
    String toString();
    double getValue();
    void fitBounds();
    void setSpinnersText (String val, NotificationType notification);
    void attachListener(Label::Listener *listener);
    void detachListener(Label::Listener *listener);
    void resized() override;
private:
    void mouseDoubleClick (const MouseEvent &e) override;
    void setSpinnersVisible (bool visible);
    void editorHidden (Label *label, TextEditor &editor) override;
    void labelTextChanged (Label *labelThatHasChanged) override;
    void editorShown (Label *, TextEditor &) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TempoSpinner)
};



#endif /* TempoSpinner_h */
