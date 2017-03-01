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
#include "AlertCompnent.cpp"
#include "Table.h"
#include "Display.h"



//==============================================================================
/**
*/
class MusicCalculatorAudioProcessorEditor : public AudioProcessorEditor,
                                            private Timer,
                                            private LabelListener,
                                            private ButtonListener,
                                            private MidiInputCallback,
                                            private MidiKeyboardStateListener,
                                            private ComboBox::Listener,
                                            private LookAndFeel_V3
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
    double tempo;
    
    int width, height;
    
    bool sync;
    
    
    void timerCallback() override;
    double bpmToMs (double bpm);
    double noteToHz (int note, int octave);
    double semitoneShift (double value, double amount);
    
    
    Table table;
    
    TextButton syncButton;
    TextButton midiButton;
    void buttonClicked (Button *button) override;
    
    double bpm;
    
    bool hostHasTempoInformation();
    
    AlertComponent alert;
    
    Display display;
    void labelTextChanged (Label *label) override;
    
    ComboBox comboBox;
    void comboBoxChanged(ComboBox *comboBox) override;

    
    void drawComboBox (Graphics& g, int width, int height, const bool /*isButtonDown*/, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box) override;
    
    
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
