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
    
    width = 400;
    height = 300;
    note = 0;
    octave = 3;
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (width, height);
    
    bpmLabel.setFormattedText(*processor.getBpm(), sendNotification);
    //bpmLabel.setEditable(false, true, true);
    bpmLabel.setColour(Label::outlineColourId, Colour(0,0,0));
    bpmLabel.addListener(this);
    bpmLabel.setName("bpmLabel");
    
    
    syncButton.setButtonText("Sync");
    syncButton.setClickingTogglesState(true);
    syncButton.addListener(this);
    syncButton.setToggleState(processor.getSync(), sendNotification);
    
    table.setName("table");
    table.setLabelComponent(&bpmLabel);
    table.getTable()->getHeader().addListener(this);
    table.setNoteType(processor.getNoteType());
    table.setHz(processor.getHz());
    
    noteToHzLabel.setColour(Label::outlineColourId, Colour(0,0,0));
    
    noteLabel.setLabelType(LabelComponent::LabelType::NOTENAME);
    noteLabel.setName("noteLabel");
    noteLabel.addListener(this);
    octaveLabel.setLabelType(LabelComponent::LabelType::NOTENUMBER);
    octaveLabel.setName("octaveLabel");
    octaveLabel.addListener(this);
    
    comboBox.addItem("Tempo", 1);
    comboBox.addItem("Note", 2);
    comboBox.addItem("Hertz", 3);
    comboBox.addListener(this);
    
    addAndMakeVisible(bpmLabel);
    //addAndMakeVisible(table);
    addAndMakeVisible(syncButton);
    addAndMakeVisible(alert);
    addAndMakeVisible(noteToHzLabel);
    alert.setVisible(false);
    addAndMakeVisible(octaveLabel);
    table.setMilliseconds();
    addAndMakeVisible(noteLabel);
    //addAndMakeVisible(tempoSpinner);
    //addAndMakeVisible(noteSpinner);
    //addAndMakeVisible(hertzSpinner);
    //addAndMakeVisible(newTable);
    addAndMakeVisible(display);
    addAndMakeVisible(comboBox);
    
    //newTable.setTempoSpinner (&tempoSpinner);
    
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
    //g.drawLine((float)width/2, 0, (float)width/2, height);
}

void MusicCalculatorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    Font f = bpmLabel.getFont();
    //bpmLabel.setBounds((width - 200)/2, 20, 200, f.getHeight());
    table.setBounds((width - 200)/2, 40 + f.getHeight(), 200, height - (60 + f.getHeight()));
    /*syncButton.setBounds(200, 20, 50, 50);
    alert.setBounds((getWidth() - alert.getWidth())/2,
                    (getHeight() - alert.getHeight())/2,
                    alert.getWidth(), alert.getHeight());*/
    //noteLabel.setBounds(width/2 - 51, 20, 50, noteLabel.getFont().getHeight());
    //octaveLabel.setBounds(width/2 + 1, 20, 50, octaveLabel.getFont().getHeight());
    //noteToHzLabel.setBounds(100, 100, 50, 50);
    //tempoSpinner.Component::setBounds((width - tempoSpinner.width)/2, 20, tempoSpinner.width, tempoSpinner.height);
    //noteSpinner.Component::setBounds((width - noteSpinner.width)/2, 20, noteSpinner.width, noteSpinner.height);
    //hertzSpinner.Component::setBounds((width - hertzSpinner.width)/2, 20, hertzSpinner.width, hertzSpinner.height);
    //newTable.setBounds((width - table.width)/2, tempoSpinner.height + 40, table.width, table.height);
    display.setBounds((width - display.width)/2, 20, display.width, display.height);
    comboBox.setBounds(20, 100, 100, 100);
}

void MusicCalculatorAudioProcessorEditor::timerCallback()
{
    setMidiInput(0);
    if(syncButton.getToggleState())
    {
        // Sync on
        if (hostHasTempoInformation())
        {
            double *bpm = processor.getBpm();
            bpmLabel.setFormattedText(*bpm, sendNotification);
        }
    }
    else if(!syncButton.getToggleState())
    {
        // Sync off
    }
}

double MusicCalculatorAudioProcessorEditor::bpmToMs(double bpm)
{
    return 1000.0 / (bpm / 60.0);
}

void MusicCalculatorAudioProcessorEditor::labelTextChanged(Label *labelThatHasChanged)
{
    String s =  labelThatHasChanged->getName();
    if(s == bpmLabel.getName())
    {
        processor.setBpm(bpmLabel.getTextValue().getValue());
        table.setMilliseconds();
    }
    else if (s == noteLabel.getName() || s == octaveLabel.getName())
    {
        note = noteLabel.getNote();
        octave = octaveLabel.getOctave();
        noteToHzLabel.setText(String(noteToHz(note, octave)), sendNotification);
    }
}

void MusicCalculatorAudioProcessorEditor::buttonClicked(juce::Button *button)
{
    if(syncButton.getToggleState())
    {
        // Sync on
        
       if (processor.setSync(true))
       {
           bpmLabel.setEnabled(false);
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
        bpmLabel.setEnabled(true);
    }
}

bool MusicCalculatorAudioProcessorEditor::hostHasTempoInformation()
{
    double *d = processor.getBpm();
    if (*d >= 5.0 && *d <= 990.0)
        return true;
    else
        return false;
}

double MusicCalculatorAudioProcessorEditor::noteToHz(int note, int octave)
{
    note -= 9;
    octave -= 4;
    return semitoneShift(440, (float)note + (float)(octave * 12));
}

double MusicCalculatorAudioProcessorEditor::semitoneShift(double value, double amount)
{
    return value / pow(2, amount / -12);
}


void MusicCalculatorAudioProcessorEditor::tableColumnsChanged (TableHeaderComponent *tableHeader)
{
    processor.setNoteType(table.getNoteType());
    processor.setHz(table.getHz());
}

void MusicCalculatorAudioProcessorEditor::tableColumnsResized (TableHeaderComponent *tableHeader) {}
void MusicCalculatorAudioProcessorEditor::tableSortOrderChanged (TableHeaderComponent *tableHeader) {}
void MusicCalculatorAudioProcessorEditor::tableColumnDraggingChanged (TableHeaderComponent *tableHeader, int columnIdNowBeingDragged) {}

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
    }
}

void MusicCalculatorAudioProcessorEditor::handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/)
{
}

void MusicCalculatorAudioProcessorEditor::comboBoxChanged(juce::ComboBox *combo)
{
    int i = combo->getSelectedId();
    display.setType((i == 1) ? Display::DisplayType::TEMPO : ((i == 2) ? Display::DisplayType::NOTE : Display::DisplayType::HERTZ));
}
