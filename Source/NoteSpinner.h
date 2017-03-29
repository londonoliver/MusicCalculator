//
//  NoteSpinner.h
//  MusicCalculator
//
//  Created by London Oliver on 2/19/17.
//
//

#ifndef NoteSpinner_h
#define NoteSpinner_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "Spinner.h"

class NoteSpinner : public Component, private LabelListener
{
public:
    int width;
    int height;
    
    Font font;
    
    Spinner s1;
    Spinner s2;
    
    Label ed;
    
    int s1Width;
    int s2Width;
    
    NoteSpinner();
    ~NoteSpinner();
    
    
    void setTextColour (Colour colour);
    int getNote();
    void setNote (int note);
    int getOctave();
    void setOctave (int octave);
    void setFontHeight (float fontHeight);
    String toString();
    void fitBounds();
    void setSpinnersText (String val, NotificationType notification);
    void attachListener (Label::Listener *listener);
    void detachListener (Label::Listener *listener);
    void resized() override;
private:
    void mouseDoubleClick (const MouseEvent &e) override;
    void setSpinnersVisible (bool visible);
    void editorHidden (Label *label, TextEditor &editor) override;
    void labelTextChanged (Label *labelThatHasChanged) override;
    void editorShown (Label *, TextEditor &) override;
    bool isNumber (String val);
    int noteIndex (String val);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteSpinner)
};

#endif /* NoteSpinner_h */
