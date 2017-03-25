//
//  Container.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/21/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "Display.cpp"
#include "ButtonPanel.cpp"
#include "OutputPanel.cpp"
#include "ModeButtons.cpp"

class Container : public Component, public LabelListener, public ButtonListener
{
public:
    Display d;
    ButtonPanel p;
    OutputPanel o;
    ModeButtons m;
    
    Container()
    {
        addAndMakeVisible (d);
        addAndMakeVisible (p);
        addAndMakeVisible (o);
        addAndMakeVisible (m);
        
        d.ts.attachListener (this);
        d.ns.attachListener (this);
        p.f.attachListener (this);
        p.s.addListener (this);
        p.u.addListener (this);
        m.b1->addListener (this);
        m.b2->addListener (this);
    }
    
    ~Container()
    {
        d.ts.detachListener (this);
        d.ns.detachListener (this);
        p.f.detachListener (this);
        p.s.removeListener (this);
        p.u.removeListener (this);
        m.b1->removeListener (this);
        m.b2->removeListener (this);
    }
    
    void resized() override
    {
        int margin = (1.0/10.0) * getHeight();
        m.setBounds(0, 0, 60, 30);
        d.setBounds(0, m.getY() + m.getHeight() + margin/2, getWidth(), getHeight()/5);
        p.setBounds(0, d.getY() + d.getHeight() + margin, getWidth(), getHeight()/5);
        o.setBounds(0, p.getY() + p.getHeight() + margin, getWidth(), getHeight()/5);
    }
    
private:
    void setConversion()
    {
        double bpm = d.ts.getValue();
        double bpm_ms = (1000.0 / (bpm / 60.0)) * 4.0 * p.f.getFraction();
        double bpm_hz = (bpm / 60.0) / 4.0 / p.f.getFraction();
        
        int note = d.ns.getNote() - 9;
        int octave = d.ns.getOctave() - 4;
        double concertA = 440.0;
        double note_hz = concertA / pow (2.0, ((float) note + (float) (octave * 12.0)) / -12.0);
        
        o.c.label.setText ((m.b1->getToggleState()) ? (p.u.getToggleState() ? String (bpm_hz) : String (bpm_ms)) : String (note_hz), dontSendNotification);
        o.c.units.setText ((m.b1->getToggleState()) ? (p.u.getToggleState() ? "Hz": "Ms") : "Hz", dontSendNotification);\
        o.c.resized();
    }
    
    
    void labelTextChanged (Label *label) override
    {
        setConversion();
    }
    
    void buttonClicked (Button *b) override
    {
        setConversion();
        d.ts.setVisible (m.b1->getToggleState());
        d.ns.setVisible (m.b2->getToggleState());
        d.l.setText ((m.b1->getToggleState()) ? "Tempo" : "Note", dontSendNotification);
        d.resized();
        p.s.setVisible (m.b1->getToggleState());
        p.f.setVisible (m.b1->getToggleState());
        p.u.setVisible (m.b1->getToggleState());
        p.l2.setVisible (m.b1->getToggleState());
        p.l3.setVisible (m.b1->getToggleState());
        p.m.setVisible (m.b2->getToggleState());
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Container)
};
