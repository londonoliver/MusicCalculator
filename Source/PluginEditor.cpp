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
    cout << "processor tempo = " << *processor.getTempo() << endl;
    if (hostHasTempoInformation())
        display.setDisplay (String (*processor.getTempo()), Display::DisplayType::TEMPO);
    else
        display.setDisplay("120", Display::DisplayType::TEMPO);
    
    display.setDisplay (Spinner::getNote(processor.getNote()) + String (processor.getOctave()), Display::DisplayType::NOTE);
    display.setDisplayType (processor.getDisplayType());
    table.delayType = processor.getDelayType();
    table.tempoConversion = processor.getTempoConversion();
    table.setTableType();
    
    width = 300;
    height = 350; //300
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (width, height);
    
    syncButton.setButtonText("Sync");
    syncButton.setClickingTogglesState(true);
    syncButton.addListener(this);
    syncButton.setToggleState(processor.getSync(), sendNotification);
    syncButton.changeWidthToFitText();
    
    
    display.attachListener(this);
    
    comboBox.addItem("Tempo", 1);
    comboBox.addItem("Note", 2);
    comboBox.addListener(this);
    comboBox.setWantsKeyboardFocus (false);
    comboBox.setLookAndFeel (this);
    
    addAndMakeVisible(syncButton);
    //addAndMakeVisible(midiButton);
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
    keyboardState.removeListener(this);
    comboBox.removeListener(this);
    midiButton.removeListener(this);
    syncButton.removeListener(this);
    display.removeListeners (this);
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
    
    //midiButton.setBounds(width - 50, height - 50, 25, 25);
    alert.setBounds((getWidth() - alert.getWidth())/2,
                    (getHeight() - alert.getHeight())/2,
                    alert.getWidth(), alert.getHeight());
    display.setBounds((width - display.width)/2, 25, display.width, display.height);
    comboBox.setBounds(display.getX() + display.width + 0, display.getY() + display.height - 25, 25, 25);
    table.setBounds((width - table.width)/2, display.getY() + display.height + 25, table.width, table.height);
    //syncButton.setBounds(width - table.width - 40, comboBox.getY(), 40, 25);
    
    
    
    processor.setDelayType(table.delayType);
    processor.setTempoConversion(table.tempoConversion);
}

void MusicCalculatorAudioProcessorEditor::timerCallback()
{
    setMidiInput(0);
    if (display.displayType == Display::DisplayType::NOTE)
        display.setDisplay (Spinner::getNote (note) + String (octave), Display::DisplayType::NOTE);
    if(syncButton.getToggleState())
    {
        // Sync on
        if (hostHasTempoInformation())
        {
            double *bpm = processor.getTempo();
            if (display.displayType == Display::DisplayType::TEMPO)
                display.setDisplay(String (*bpm), Display::DisplayType::TEMPO);
            
        }
    }
    else if(!syncButton.getToggleState())
    {
        // Sync off
    }
}

void MusicCalculatorAudioProcessorEditor::labelTextChanged(Label *labelThatHasChanged)
{
    note = display.getNote();
    octave = display.getOctave();
    
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
        
        if (processor.setSync (true))
        {
            display.setTempoSync (true);
            startTimer (100);
        }
        else
        {
            //alert.flash();
            syncButton.setToggleState(false, dontSendNotification);
        }
    }
    else if(!syncButton.getToggleState())
    {
        // Sync off
        
        processor.setSync(false);
        if (Timer::isTimerRunning())
            stopTimer();
        
        display.setTempoSync (false);
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
    }
}

void MusicCalculatorAudioProcessorEditor::handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/)
{
}

void MusicCalculatorAudioProcessorEditor::comboBoxChanged(juce::ComboBox *combo)
{
    int i = combo->getSelectedId();
    display.setDisplayType((i == 1) ? Display::DisplayType::TEMPO : Display::DisplayType::NOTE);
    table.setTableType();
    processor.setDisplayType(display.displayType);
}

void MusicCalculatorAudioProcessorEditor::drawComboBox (Graphics& g, int width, int height, const bool /*isButtonDown*/, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box)
{
    g.fillAll (box.findColour (ComboBox::backgroundColourId));
    
    const Colour buttonColour (box.findColour (ComboBox::buttonColourId));
    
    if (box.isEnabled() && box.hasKeyboardFocus (false))
    {
        g.setColour (buttonColour);
        g.drawRect (0, 0, width, height, 2);
    }
    else
    {
        g.setColour (box.findColour (ComboBox::outlineColourId));
        //g.drawRect (0, 0, width, height);
    }
    
    const float arrowX = 0.3f;
    const float arrowH = 0.2f;
    
    Path p;
    p.addTriangle (buttonX + buttonW * 0.5f,            buttonY + buttonH * (0.45f - arrowH),
                   buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.45f,
                   buttonX + buttonW * arrowX,          buttonY + buttonH * 0.45f);
    
    p.addTriangle (buttonX + buttonW * 0.5f,            buttonY + buttonH * (0.55f + arrowH),
                   buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.55f,
                   buttonX + buttonW * arrowX,          buttonY + buttonH * 0.55f);
    
    g.setColour (box.findColour (ComboBox::arrowColourId).withMultipliedAlpha (box.isEnabled() ? 1.0f : 0.3f));
    g.fillPath (p);
}
