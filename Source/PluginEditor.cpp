/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;


//==============================================================================
MusicCalculatorAudioProcessorEditor::MusicCalculatorAudioProcessorEditor (MusicCalculatorAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    table.setDisplay (&display);
    
    display.setDisplay (String (*processor.getTempo()), Display::DisplayType::TEMPO);
    display.setDisplay (Spinner::getNote(processor.getNote()) + String (processor.getOctave()), Display::DisplayType::NOTE);
    display.setDisplayType (processor.getDisplayType());
    table.delayType = processor.getDelayType();
    table.tempoConversion = processor.getTempoConversion();
    table.setTableType();
    
    width = 400;
    height = 300;
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (width, height);
    
    syncButton.setButtonText("Sync");
    syncButton.setClickingTogglesState(true);
    syncButton.addListener(this);
    syncButton.setToggleState(processor.getSync(), sendNotification);
    
    display.attachListener(this);
    
    comboBox.addItem("Tempo", 1);
    comboBox.addItem("Note", 2);
    comboBox.addItem("Hertz", 3);
    comboBox.addListener(this);
    
    addAndMakeVisible(syncButton);
    addAndMakeVisible(table);
    addAndMakeVisible(display);
    addAndMakeVisible(comboBox);
    addAndMakeVisible(alert);
    alert.setVisible(false);
    
    
    
    
    lastInputIndex = 0;
    setMidiInput (0);
    keyboardState.addListener (this);
    startTimer(100);
}

MusicCalculatorAudioProcessorEditor::~MusicCalculatorAudioProcessorEditor()
{
}

//==============================================================================
void MusicCalculatorAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.setFont (15.0f);
}

void MusicCalculatorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    syncButton.setBounds(width - 50, 0, 50, 50);
    alert.setBounds((getWidth() - alert.getWidth())/2,
                    (getHeight() - alert.getHeight())/2,
                    alert.getWidth(), alert.getHeight());
    table.setBounds((width - table.width)/2, display.height + 40, table.width, table.height);
    display.setBounds((width - display.width)/2, 20, display.width, display.height);
    comboBox.setBounds (0, 0, 50, 50);
    
    cout << "table header height = " << table.table.getHeader().getHeight();
    
    processor.setDelayType(table.delayType);
    
    processor.setTempoConversion(table.tempoConversion);
}

void MusicCalculatorAudioProcessorEditor::timerCallback()
{
    setMidiInput(0);
    if(syncButton.getToggleState())
    {
        // Sync on
        if (hostHasTempoInformation())
        {
            double *bpm = processor.getTempo();

        }
    }
    else if(!syncButton.getToggleState())
    {
        // Sync off
    }
}

void MusicCalculatorAudioProcessorEditor::labelTextChanged(Label *labelThatHasChanged)
{
    processor.setTempo (table.getTempo());
    processor.setNote (display.getNote());
    processor.setOctave (display.getOctave());
    table.table.updateContent();
}

void MusicCalculatorAudioProcessorEditor::buttonClicked(juce::Button *button)
{
    if(syncButton.getToggleState())
    {
        // Sync on
        
       if (processor.setSync(true))
       {
           startTimer (100);
       }
       else
       {
           alert.flash();
           syncButton.setToggleState(false, dontSendNotification);
       }
    }
    else if(!syncButton.getToggleState())
    {
        // Sync off
        
        processor.setSync(false);
        if (Timer::isTimerRunning())
            stopTimer();
    }
}

bool MusicCalculatorAudioProcessorEditor::hostHasTempoInformation()
{
    double *d = processor.getTempo();
    if (*d >= 5.0 && *d <= 990.0)
        return true;
    else
        return false;
}

/** Starts listening to a MIDI input device, enabling it if necessary. */
void MusicCalculatorAudioProcessorEditor::setMidiInput (int index)
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
void MusicCalculatorAudioProcessorEditor::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
    keyboardState.processNextMidiEvent (message);
}

void MusicCalculatorAudioProcessorEditor::handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    if (isPositiveAndBelow (midiNoteNumber, (int) 128))
    {
        note = midiNoteNumber % 12;
        octave = midiNoteNumber / 12 + (3 - 5);  // octave = midiNoteNumber / 12 + (middleC - 5)
        
        if (display.displayType == Display::DisplayType::NOTE)
        display.setDisplay (Spinner::getNote (note) + String (octave), Display::DisplayType::NOTE);
    }
    cout << "note on" << endl;
}

void MusicCalculatorAudioProcessorEditor::handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/)
{
}

void MusicCalculatorAudioProcessorEditor::comboBoxChanged(juce::ComboBox *combo)
{
    int i = combo->getSelectedId();
    display.setDisplayType((i == 1) ? Display::DisplayType::TEMPO : ((i == 2) ? Display::DisplayType::NOTE : Display::DisplayType::HERTZ));
    table.setTableType();
    processor.setDisplayType(display.displayType);
}
