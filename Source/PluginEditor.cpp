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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    bpm = 120;
    
    bpmLabel.setFormattedText(bpm, sendNotification);
    bpmLabel.setEditable(false, true, true);
    bpmLabel.setColour(Label::outlineColourId, Colour(0,0,0));
    bpmLabel.addListener(this);
    bpmLabel.setName("bpmLabel");
    
    msLabel.setText(String(bpmToMs(bpm)), sendNotification);
    msLabel.setColour(Label::outlineColourId, Colour(0,0,0));
    
    
    syncButton.setButtonText("Sync");
    syncButton.setClickingTogglesState(true);
    syncButton.addListener(this);
    
    table.addChangeListener(this);
    table.setName("table");
    
    
    addAndMakeVisible(bpmLabel);
    addAndMakeVisible(table);
    addAndMakeVisible(syncButton);
    addAndMakeVisible(alert);
    alert.setVisible(false);
    
    setMilliseconds(false);

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
    Font f = bpmLabel.getFont();
    bpmLabel.setBounds(30, 20, f.getStringWidth("120.000"), f.getHeight());
    table.setBounds(30, 70, 200, 200);
    syncButton.setBounds(200, 20, 50, 50);
    alert.setBounds((getWidth() - alert.getWidth())/2,
                    (getHeight() - alert.getHeight())/2,
                    alert.getWidth(), alert.getHeight());
}

void MusicCalculatorAudioProcessorEditor::timerCallback()
{
    //v.setValue(i + 1);
    if(syncButton.getToggleState())
    {
        // Sync on
        if (hostHasTempoInformation())
        {
            double bpm = processor.getBpm();
            bpmLabel.setFormattedText(bpm, sendNotification);
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
        setMilliseconds(false);
    }
}

// Sets the millisecond value given the current bpm. If change is true then this will also
// change the note value from whole to dotted to triplet etc.
void MusicCalculatorAudioProcessorEditor::setMilliseconds(bool change)
{
    double bpm = bpmLabel.getTextValue().getValue();
    double ms = 1000.0 / (bpm / 60.0); // ms for whole quarter note
    int noteType = table.getNoteType();
    int noteDenominator, noteNumerator;
    
    if (change)
    {
        switch (noteType) {
            case 1:
                noteType = 2;
                table.setNoteType(2);
                break;
            case 2:
                noteType = 3;
                table.setNoteType(3);
                break;
            case 3:
                noteType = 1;
                table.setNoteType(1);
                break;
            default:
                break;
        }
    }
    
    switch (noteType) {
        case 1:     // whole note
        {
            noteNumerator = 1;
            noteDenominator = 4;
            break;
        }
        case 2:     // dotted note
        {
            ms = ms * (3.0/2.0);
            noteNumerator = 3;
            noteDenominator = 8;
            break;
        }
        case 3:     // triplet note
        {
            ms = ms * (2.0/3.0);
            noteNumerator = 1;
            noteDenominator = 6;
            break;
        }
        default:
            break;
    } // end switch
    
    for (int i = 0; i < table.getNumRows(); i++ )
    {
        table.setText(1, i, String(noteNumerator) + "/" + String(noteDenominator));
        table.setText(2, i, String(ms));
        ms = ms/2.0;
        noteDenominator = noteDenominator * 2;
    }
}

void MusicCalculatorAudioProcessorEditor::buttonClicked(juce::Button *button)
{
    if(syncButton.getToggleState())
    {
        // Sync on
        
        startTimer (100);
        
        if (hostHasTempoInformation())
            bpmLabel.setEnabled(false);
        else
        {
            alert.flash();
            
            
            syncButton.setToggleState(false, dontSendNotification);
        }
    }
    else if(!syncButton.getToggleState())
    {
        // Sync off
        
        stopTimer();
        
        bpmLabel.setEnabled(true);
    }
}

bool MusicCalculatorAudioProcessorEditor::hostHasTempoInformation()
{
    double d = processor.getBpm();
    if (d >= 5.0 && d <= 990.0)
        return true;
    else
        return false;
}

void MusicCalculatorAudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    setMilliseconds(true);
}

