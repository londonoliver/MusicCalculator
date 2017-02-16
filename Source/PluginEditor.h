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
#include "LabelComponent.hpp"
#include "TableComponent.cpp"
#include "AlertCompnent.cpp"
#include "MainComponent.cpp"
#include "Display.cpp"


//==============================================================================
/**
*/
class MusicCalculatorAudioProcessorEditor : public AudioProcessorEditor,
                                            private Timer,
                                            private LabelListener,
                                            private ButtonListener,
                                            private TableHeaderComponent::Listener,
                                            private MidiInputCallback,
                                            private MidiKeyboardStateListener
{
public:
    MusicCalculatorAudioProcessorEditor (MusicCalculatorAudioProcessor&);
    ~MusicCalculatorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MusicCalculatorAudioProcessor& processor;
    
    int note, octave;
    
    int width, height;
    
    bool sync;
    
    LabelComponent bpmLabel;
    void labelTextChanged (Label *labelThatHasChanged) override;
    
    void timerCallback() override;
    double bpmToMs (double bpm);
    double noteToHz (int note, int octave);
    double semitoneShift (double value, double amount);
    
    
    TableComponent table;
    
    TextButton syncButton;
    void buttonClicked (Button *button) override;
    
    double bpm;
    
    bool hostHasTempoInformation();
    
    AlertComponent alert;
    
    Label noteToHzLabel;
    
    Display display;
    
    LabelComponent noteLabel;
    LabelComponent octaveLabel;
    
    void tableColumnsChanged (TableHeaderComponent *tableHeader) override;
    void tableColumnsResized (TableHeaderComponent *tableHeader) override;
    void tableSortOrderChanged (TableHeaderComponent *tableHeader) override;
    void tableColumnDraggingChanged (TableHeaderComponent *tableHeader, int columnIdNowBeingDragged) override;
    
    
    void setMidiInput (int index);
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
    void handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override;
    
    
    
    //==============================================================================
    AudioDeviceManager deviceManager;           // [1]
    ComboBox midiInputList;                     // [2]
    Label midiInputListLabel;
    int lastInputIndex;                         // [3]
    
    MidiKeyboardState keyboardState;            // [5]
    
    //==============================================================================
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicCalculatorAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
