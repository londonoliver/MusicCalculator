#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>

using namespace std;


class MainContentComponent  : public Component,
private MidiInputCallback,
private MidiKeyboardStateListener,
private Timer
{
public:
    MainContentComponent()
    : lastInputIndex (0)
    {
        setMidiInput (0);
        keyboardState.addListener (this);
        startTimer(100);
    }
    
    ~MainContentComponent()
    {
        keyboardState.removeListener (this);
        deviceManager.removeMidiInputCallback (MidiInput::getDevices()[midiInputList.getSelectedItemIndex()], this);
    }
    
private:
    /** Starts listening to a MIDI input device, enabling it if necessary. */
    void setMidiInput (int index)
    {
        const StringArray list (MidiInput::getDevices());
        
        deviceManager.removeMidiInputCallback (list[lastInputIndex], this);
        
        const String newInput (list[index]);
        
        if (! deviceManager.isMidiInputEnabled (newInput))
            deviceManager.setMidiInputEnabled (newInput, true);
        
        deviceManager.addMidiInputCallback (newInput, this);
        midiInputList.setSelectedId (index + 1, dontSendNotification);
        
        lastInputIndex = index;
    }
    
    // These methods handle callbacks from the midi device + on-screen keyboard..
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override
    {
        keyboardState.processNextMidiEvent (message);
    }
    
    void handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override
    {
        cout << "note " << midiNoteNumber << " on" << endl;
    }
    
    void handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override
    {
    }
    
    void timerCallback() override
    {
        setMidiInput(0);
    }
    
    //==============================================================================
    AudioDeviceManager deviceManager;           // [1]
    ComboBox midiInputList;                     // [2]
    Label midiInputListLabel;
    int lastInputIndex;                         // [3]
    
    MidiKeyboardState keyboardState;            // [5]
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent);
};


#endif  // MAINCOMPONENT_H_INCLUDED
