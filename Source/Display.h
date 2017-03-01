//
//  Display.h
//  MusicCalculator
//
//  Created by London Oliver on 2/20/17.
//
//

#ifndef Display_h
#define Display_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "Spinner.h"

class Display : public Component, public LabelListener
{
public:
    enum class DisplayType {TEMPO, NOTE, HERTZ};
    
    DisplayType displayType;
    
    int width;
    int height;
    
    Font font;
    
    Spinner t1;
    Spinner t2;
    Spinner t3;
    Spinner t4;
    Spinner t5;
    Spinner t6;
    
    Spinner n1;
    Spinner n2;
    
    Spinner h1;
    Spinner h2;
    Spinner h3;
    Spinner h4;
    
    Label ed;
    
    int t1Width;
    int t2Width;
    int t3Width;
    int t4Width;
    int t5Width;
    int t6Width;
    
    int n1Width;
    int n2Width;
    
    int h1Width;
    int h2Width;
    int h3Width;
    int h4Width;
    
    bool tempoSync;
    bool midiSync;
    
    Display();
    
    String toString(DisplayType displayType);
    double getTempo();
    void setTempo (double tempo);
    int getNote();
    int getOctave();
    double getHertz();
    void setDisplay (String val, DisplayType displayType);
    void attachListener(Label::Listener *listener);
    void removeListeners(Label::Listener *listener);
    void setDisplayType (DisplayType displayType);
    int noteIndex (String val);
    void setSpinnersEnabled (bool enabled);
    void setTempoSync (bool sync);
    void setMidiSync (bool sync);
    void resized();
private:
    void fitBounds();
    void mouseDoubleClick (const MouseEvent &e);
    void setSpinnersVisible (bool visible);
    void editorHidden (Label *label, TextEditor &editor);
    void labelTextChanged (Label *labelThatHasChanged);
    void editorShown (Label *, TextEditor &);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Display)
};

#endif /* Display_h */
