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
    //
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
    //
    
    
    MusicCalculatorAudioProcessorEditor (MusicCalculatorAudioProcessor&);
    ~MusicCalculatorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MusicCalculatorAudioProcessor& processor;

    int width, height;
    
    void timerCallback() override;
    void setConversion();
    void labelTextChanged (Label *label) override;
    
    void buttonClicked (Button *) override;
    
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
