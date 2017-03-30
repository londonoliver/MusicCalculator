/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "TempoSpinner.h"
#include "NoteSpinner.h"
#include "Fraction.cpp"
#include "ToggleTextButton.cpp"
#include "Checkmark.cpp"



//==============================================================================
/**
*/
class MusicCalculatorAudioProcessorEditor : public AudioProcessorEditor,
                                            private Timer,
                                            private MidiInputCallback,
                                            private MidiKeyboardStateListener,
                                            private LookAndFeel_V3,
                                            private ComponentBoundsConstrainer,
                                            private ButtonListener,
                                            private LabelListener
{
public:
    
    Component container;
    //
    Label toggleLabel;
    ToggleButton tempoToggle, noteToggle;
    //
    //
    TempoSpinner tempoSpinner;
    NoteSpinner noteSpinner;
    Label displayLabel;
    //
    //
    Fraction tempoFraction;
    ToggleTextButton tempoSyncButton;
    ToggleTextButton tempoUnitsButton;
    ToggleTextButton midiSyncButton;
    Label tempoSyncLabel;
    Label tempoFractionLabel;
    Label tempoUnitsLabel;
    Label midiSyncLabel;
    //
    //
    Label conversionLabel;
    Label conversionValueLabel;
    Label conversionUnitsLabel;
    TextButton copy;
    Checkmark check;
    //
    
    Point<int> p1, p2, p3, p4, p5;
    
    MusicCalculatorAudioProcessorEditor (MusicCalculatorAudioProcessor&);
    ~MusicCalculatorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MusicCalculatorAudioProcessor& processor;
    
    void timerCallback() override;
    void setConversion();
    void labelTextChanged (Label *label) override;
    
    void buttonClicked (Button *) override;
    
    void drawButtonText (Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/) override;
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override;
    Font getTextButtonFont (TextButton&, int buttonHeight) override;
    void drawToggleButton (Graphics& g, ToggleButton& button, bool isMouseOverButton, bool isButtonDown) override;
    void drawTickBox (Graphics& g, Component& component, float x, float y, float w, float h,const bool ticked, const bool isEnabled, const bool isMouseOverButton, const bool isButtonDown) override;
    
    void setMidiInput (int index);
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
    void handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override;
    
    
    
    //==============================================================================
    AudioDeviceManager deviceManager;           // [1]
    int lastInputIndex;                         // [3]
    
    MidiKeyboardState keyboardState;            // [5]
    
    //==============================================================================
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicCalculatorAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
