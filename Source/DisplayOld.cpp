//
//  Display.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/19/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "TempoSpinner.h"
#include "NoteSpinner.h"
#include "HertzSpinner.h"

class DisplayOld : public Component, public Label::Listener
{
public:
    int width;
    int height;
    
    enum class DisplayType {TEMPO, NOTE, HERTZ};
    
    DisplayType type;
    
    TempoSpinner tempoSpinner;
    NoteSpinner noteSpinner;
    HertzSpinner hertzSpinner;
    
    DisplayOld()
    {
        tempoSpinner.attachListener (this);
        noteSpinner.attachListener (this);
        hertzSpinner.attachListener (this);
        
        addAndMakeVisible (tempoSpinner);
        addAndMakeVisible (noteSpinner);
        addAndMakeVisible (hertzSpinner);
        
        setType (DisplayType::TEMPO);
    }
    
    void fitBounds ()
    {
        width = (type == DisplayType::TEMPO) ? tempoSpinner.width :
                    ((type == DisplayType::NOTE) ? noteSpinner.width :
                     hertzSpinner.width);
        height = (type == DisplayType::TEMPO) ? tempoSpinner.height :
                    ((type == DisplayType::NOTE) ? noteSpinner.height :
                     hertzSpinner.height);
        
        setBounds(0, 0, width, height);
        
        tempoSpinner.setBounds(0, 0, tempoSpinner.width, tempoSpinner.height);
        noteSpinner.setBounds(0, 0, noteSpinner.width, noteSpinner.height);
        hertzSpinner.setBounds(0, 0, hertzSpinner.width, hertzSpinner.height);
    }
    
    void setType (DisplayType type)
    {
        this->type = type;
        
        tempoSpinner.setVisible ((this->type == DisplayType::TEMPO) ? true : false);
        noteSpinner.setVisible ((this->type == DisplayType::NOTE) ? true : false);
        hertzSpinner.setVisible ((this->type == DisplayType::HERTZ) ? true : false);
        
        resized();
    }
    
    void resized()
    {
        tempoSpinner.resized();
        noteSpinner.resized();
        hertzSpinner.resized();
        
        fitBounds();
        
        if (getParentComponent())
            getParentComponent()->resized();
    }
private:
    void labelTextChanged (Label *labelThatHasChanged)
    {
        resized();
    }
};
