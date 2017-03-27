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
    setSize (300, 350);
    
    {
        tempoToggle.setButtonText("Tempo");
        tempoToggle.setRadioGroupId (1);
        tempoToggle.addListener (this);
        addAndMakeVisible (tempoToggle);
        
        noteToggle.setButtonText("Note");
        noteToggle.setRadioGroupId (1);
        noteToggle.addListener (this);
        addAndMakeVisible (noteToggle);
    }
    {
        tempoSpinner.attachListener (this);
        addChildComponent (tempoSpinner);
        
        noteSpinner.attachListener (this);
        addChildComponent (noteSpinner);
        
        displayLabel.setEditable (false);
        displayLabel.setBorderSize (BorderSize<int> (0));
        addAndMakeVisible (displayLabel);
    }
    {
        tempoSyncButton.setToggleText ("HOST", "OFF");
        tempoSyncButton.addListener (this);
        addChildComponent (tempoSyncButton);
        
        tempoFraction.attachListener (this);
        addChildComponent (tempoFraction);
        
        tempoUnitsButton.setToggleText ("HZ", "MS");
        tempoUnitsButton.addListener (this);
        addChildComponent (tempoUnitsButton);
        
        midiSyncButton.setToggleText ("MIDI", "OFF");
        midiSyncButton.addListener (this);
        addChildComponent (midiSyncButton);
        
        tempoSyncLabel.setText ("Sync", dontSendNotification);
        tempoSyncLabel.setJustificationType (Justification::centred);
        tempoSyncLabel.setBorderSize (BorderSize<int> (0));
        addChildComponent (tempoSyncLabel);
        
        tempoFractionLabel.setText ("Fraction", dontSendNotification);
        tempoFractionLabel.setJustificationType (Justification::centred);
        tempoFractionLabel.setBorderSize (BorderSize<int> (0));
        addChildComponent (tempoFractionLabel);
        
        tempoUnitsLabel.setText ("Units", dontSendNotification);
        tempoUnitsLabel.setJustificationType (Justification::centred);
        tempoUnitsLabel.setBorderSize (BorderSize<int> (0));
        addChildComponent (tempoUnitsLabel);
        
        midiSyncLabel.setText ("Sync", dontSendNotification);
        midiSyncLabel.setJustificationType (Justification::centred);
        midiSyncLabel.setBorderSize (BorderSize<int> (0));
        addChildComponent (midiSyncLabel);
    }
    {
        conversionLabel.setText ("Conversion", dontSendNotification);
        conversionLabel.setBorderSize (BorderSize<int> (0));
        addAndMakeVisible (conversionLabel);
        
        conversionValueLabel.setBorderSize (BorderSize<int> (0));
        addAndMakeVisible (conversionValueLabel);
        
        conversionUnitsLabel.setBorderSize (BorderSize<int> (0));
        addAndMakeVisible (conversionUnitsLabel);
        
        copy.setButtonText ("Copy");
        addAndMakeVisible (copy);
    }
    
    lastInputIndex = 0;
    setMidiInput (0);
    keyboardState.addListener (this);
    startTimer (100);
}

MusicCalculatorAudioProcessorEditor::~MusicCalculatorAudioProcessorEditor()
{
    tempoToggle.removeListener (this);
    noteToggle.removeListener (this);
    tempoSpinner.detachListener (this);
    noteSpinner.detachListener (this);
    tempoSyncButton.removeListener (this);
    tempoFraction.detachListener (this);
    tempoUnitsButton.removeListener (this);
    midiSyncButton.removeListener (this);
    keyboardState.removeListener(this);
}

//==============================================================================
void MusicCalculatorAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::red);
    g.setColour (Colours::black);
    g.setFont (15.0f);
}

void MusicCalculatorAudioProcessorEditor::resized()
{
    width = getWidth();
    height = getHeight();
    
    //c.setBounds(0, 0, width, height);
    
    int margin = (3.0 / 40.0) * height;
    int smallPanelHeight = (1.0 / 10.0) * height;
    int bigPanelHeight = (2.0 / 10.0) * height;
    
    {
        int toggleWidth = 0.2 * width;
        tempoToggle.setBounds (0, 0, toggleWidth, smallPanelHeight);
        noteToggle.setBounds (toggleWidth, 0, toggleWidth, smallPanelHeight);
    }
    {
        int displayLabelHeight = (1.0 / 5.0) * bigPanelHeight;
        displayLabel.setFont(Font (displayLabelHeight));
        int displayLabelWidth =  displayLabel.getFont().getStringWidth(displayLabel.getText());
        
        displayLabel.setBounds ((width - displayLabelWidth)/2, smallPanelHeight + margin, displayLabelWidth, displayLabelHeight);
    
        int displayHeight = (3.0 / 5.0) * bigPanelHeight;
        
        tempoSpinner.setFontHeight((float) displayHeight);
        tempoSpinner.setBounds((width - tempoSpinner.width)/2, displayLabel.getY() + 2 * displayLabel.getHeight(), tempoSpinner.width, displayHeight);
        
        noteSpinner.setFontHeight((float) displayHeight);
        noteSpinner.setBounds((width - noteSpinner.width)/2, displayLabel.getY() + 2 * displayLabel.getHeight(), noteSpinner.width, displayHeight);
    }
    {
        int buttonLabelHeight = (1.0 / 5.0) * bigPanelHeight;
        int buttonHeight = (3.0 / 5.0) * bigPanelHeight;
        int buttonWidth = (1.0 / 6.0) * width;
        
        tempoSyncLabel.setFont (Font (buttonLabelHeight));
        tempoSyncLabel.setBounds (buttonWidth/2, tempoSpinner.getY() + tempoSpinner.getHeight() + margin, buttonWidth, buttonLabelHeight);
        
        tempoFractionLabel.setFont (Font (buttonLabelHeight));
        tempoFractionLabel.setBounds (tempoSyncLabel.getX() + 2 * buttonWidth, tempoSpinner.getY() + tempoSpinner.getHeight() + margin, buttonWidth, buttonLabelHeight);
        
        tempoUnitsLabel.setFont (Font (buttonLabelHeight));
        tempoUnitsLabel.setBounds (tempoFractionLabel.getX() + 2 * buttonWidth, tempoSpinner.getY() + tempoSpinner.getHeight() + margin, buttonWidth, buttonLabelHeight);
        
        midiSyncLabel.setFont (Font (buttonLabelHeight));
        midiSyncLabel.setBounds (tempoSyncLabel.getX() + 2 * buttonWidth, tempoSpinner.getY() + tempoSpinner.getHeight() + margin, buttonWidth, buttonLabelHeight);
        
        tempoSyncButton.setBounds (buttonWidth/2, tempoSyncLabel.getY() + 2 * buttonLabelHeight, buttonWidth, buttonHeight);
        
        tempoFraction.setBounds (tempoSyncButton.getX() + 2 * buttonWidth, tempoSyncLabel.getY() + 2 * buttonLabelHeight, buttonWidth, buttonHeight);
        
        tempoUnitsButton.setBounds (tempoFraction.getX() + 2 * buttonWidth, tempoSyncLabel.getY() + 2 * buttonLabelHeight, buttonWidth, buttonHeight);
        
        midiSyncButton.setBounds (tempoSyncButton.getX() + 2 * buttonWidth, tempoSyncLabel.getY() + 2 * buttonLabelHeight, buttonWidth, buttonHeight);
    }
    {
        int conversionLabelHeight = (1.0 / 5.0) * bigPanelHeight;
        int conversionValueLabelHeight = (3.0 / 5.0) * bigPanelHeight;
        conversionLabel.setFont (Font (conversionLabelHeight));
        conversionValueLabel.setFont (Font (conversionValueLabelHeight));
        conversionUnitsLabel.setFont (Font (conversionValueLabelHeight));
        int conversionLabelWidth = conversionLabel.getFont().getStringWidth (conversionLabel.getText());
        int spaceWidth = conversionValueLabel.getFont().getStringWidth(" ");
        int conversionValueLabelWidth = conversionValueLabel.getFont().getStringWidth (conversionValueLabel.getText());
        int conversionUnitsLabelWidth = conversionValueLabel.getFont().getStringWidth (conversionUnitsLabel.getText());
        
        conversionLabel.setBounds ((width - conversionLabelWidth)/2, tempoSyncButton.getY() + tempoSyncButton.getHeight() + margin, conversionLabelWidth, conversionLabelHeight);
        
        conversionValueLabel.setBounds ((width - conversionValueLabelWidth - spaceWidth - conversionUnitsLabelWidth)/2, conversionLabel.getY() + 2 * conversionLabelHeight, conversionValueLabelWidth, conversionValueLabelHeight);
        
        conversionUnitsLabel.setBounds (conversionValueLabel.getX() + conversionValueLabelWidth + spaceWidth, conversionLabel.getY() + 2 * conversionLabelHeight, conversionValueLabelWidth, conversionValueLabelHeight);
        
        //copy.setBounds (conversionUnitsLabel.getX() + conversionUnitsLabel.getWidth() + (width - (conversionUnitsLabel.getX() + conversionUnitsLabel.getWidth()))/2, conversionLabel.getY() + 2 * conversionLabelHeight, (width - (conversionUnitsLabel.getX() + conversionUnitsLabel.getWidth()))/2, conversionValueLabelHeight);
        
    }
}

void MusicCalculatorAudioProcessorEditor::buttonClicked (Button *)
{
    setConversion();
    
    {
        tempoSpinner.setVisible (tempoToggle.getToggleState());
        tempoSpinner.setEnabled ( ! tempoSyncButton.getToggleState() );
        noteSpinner.setVisible (noteToggle.getToggleState());
        displayLabel.setText((tempoToggle.getToggleState()) ? "Tempo" : "Note", dontSendNotification);
    }
    {
        tempoSyncLabel.setVisible (tempoToggle.getToggleState());
        tempoFractionLabel.setVisible (tempoToggle.getToggleState());
        tempoUnitsLabel.setVisible (tempoToggle.getToggleState());
        midiSyncLabel.setVisible (noteToggle.getToggleState());
        
        tempoSyncButton.setVisible (tempoToggle.getToggleState());
        tempoFraction.setVisible (tempoToggle.getToggleState());
        tempoUnitsButton.setVisible (tempoToggle.getToggleState());
        midiSyncButton.setVisible (noteToggle.getToggleState());
    }
    
    resized();
}

void MusicCalculatorAudioProcessorEditor::labelTextChanged (Label *) {  setConversion();    }

void MusicCalculatorAudioProcessorEditor::setConversion()
{
    double bpm = tempoSpinner.getValue();
    double bpm_ms = (1000.0 / (bpm / 60.0)) * 4.0 * tempoFraction.getFraction();
    double bpm_hz = (bpm / 60.0) / 4.0 / tempoFraction.getFraction();
    
    int note = noteSpinner.getNote() - 9;
    int octave = noteSpinner.getOctave() - 4;
    double concertA = 440.0;
    double note_hz = concertA / pow (2.0, ((float) note + (float) (octave * 12.0)) / -12.0);
    
    conversionValueLabel.setText ((tempoToggle.getToggleState()) ? (tempoUnitsButton.getToggleState() ? String (bpm_hz) : String (bpm_ms)) : String (note_hz), dontSendNotification);
    conversionUnitsLabel.setText ((tempoToggle.getToggleState()) ? (tempoUnitsButton.getToggleState() ? "Hz": "Ms") : "Hz", dontSendNotification);
    
    processor.mode = tempoToggle.getToggleState();
    processor.tempo = tempoSpinner.toString();
    processor.tempoSync = tempoSyncButton.getToggleState();
    processor.numerator = tempoFraction.getNumerator();
    processor.denominator = tempoFraction.getDenominator();
    processor.units = tempoUnitsButton.getToggleState();
    processor.note = noteSpinner.toString();
    processor.midiSync = midiSyncButton.getToggleState();
    
    resized();
}

void MusicCalculatorAudioProcessorEditor::timerCallback()
{
    tempoSyncButton.setEnabled (processor.isTempoInformationAvailable());
    midiSyncButton.setEnabled( ! MidiInput::getDevices().isEmpty() );
    
    if (tempoToggle.getToggleState() && tempoSyncButton.getToggleState())
        tempoSpinner.setSpinnersText (String (processor.tempo));
    else if (noteToggle.getToggleState() && midiSyncButton.getToggleState())
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
    
    lastInputIndex = index;
}

// These methods handle callbacks from the midi device + on-screen keyboard..
void MusicCalculatorAudioProcessorEditor::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
    keyboardState.processNextMidiEvent (message);
}

void MusicCalculatorAudioProcessorEditor::handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    if (midiSyncButton.getToggleState() && isPositiveAndBelow (midiNoteNumber, 128))
    {
        int note = midiNoteNumber % 12;
        int octave = midiNoteNumber / 12 + (3 - 5);  // octave = midiNoteNumber / 12 + (middleC - 5)
        noteSpinner.setSpinnersText (Spinner::getNote (note) + String(octave));
    }
}

void MusicCalculatorAudioProcessorEditor::handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/)
{
}
