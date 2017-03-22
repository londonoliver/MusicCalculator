/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 Entypo pictograms by Daniel Bruce — www.entypo.com
 
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
    setSize(300, 350);
    
    addAndMakeVisible(c);
    
    lastInputIndex = 0;
    setMidiInput (0);
    keyboardState.addListener (this);
    startTimer(100);
}

MusicCalculatorAudioProcessorEditor::~MusicCalculatorAudioProcessorEditor()
{
    keyboardState.removeListener(this);
}

//==============================================================================
void MusicCalculatorAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::red);
    ColourGradient gradient (Colour (188, 188, 188), 0.0f, 0.0f, Colour (143, 143, 143), 0.0f, getHeight(), false);
    //ColourGradient gradient (Colour (73, 85, 98), 0.0f, 0.0f, Colour (41, 50, 60), 0.0f, getHeight(), false);
    //ColourGradient gradient (Colour (65, 67, 69), 0.0f, 0.0f, Colour (35, 37, 38), 0.0f, getHeight(), false);
    //ColourGradient gradient (Colour (251, 128, 38), 0.0f, 0.0f, Colour (253, 198, 72), 0.0f, getHeight(), false);
    //ColourGradient gradient (Colour (213, 61, 251), 0.0f, 0.0f, Colour (147, 67, 234), 0.0f, getHeight(), false);
    g.setGradientFill(gradient);
    //g.fillRect(getLocalBounds());
    g.setColour (Colours::black);
    g.setFont (15.0f);
}

void MusicCalculatorAudioProcessorEditor::resized()
{
    width = getWidth();
    height = getHeight();
    
    c.setBounds(0, 0, width, height);
}

void MusicCalculatorAudioProcessorEditor::timerCallback()
{
    setMidiInput(0);
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

void MusicCalculatorAudioProcessorEditor::drawCornerResizer (Graphics& g, int w, int h, bool /*isMouseOver*/, bool /*isMouseDragging*/)
{
}
