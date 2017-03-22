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
#include "Container.cpp"



//==============================================================================
/**
*/
class MusicCalculatorAudioProcessorEditor : public AudioProcessorEditor,
                                            private Timer,
                                            private MidiInputCallback,
                                            private MidiKeyboardStateListener,
                                            private LookAndFeel_V3,
                                            private ComponentBoundsConstrainer
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

    int width, height;
    
    int note, octave;
    
    void timerCallback() override;


    Container c;
    
    void drawCornerResizer (Graphics& g, int w, int h, bool /*isMouseOver*/, bool /*isMouseDragging*/) override;
    
    
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
