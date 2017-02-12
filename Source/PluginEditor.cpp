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
    
    bpmLabel.setFormattedText(*processor.getBpm(), sendNotification);
    bpmLabel.setEditable(false, true, true);
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
    
    addAndMakeVisible(bpmLabel);
    addAndMakeVisible(table);
    addAndMakeVisible(syncButton);
    addAndMakeVisible(alert);
    alert.setVisible(false);
    
    table.setMilliseconds();

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


void MusicCalculatorAudioProcessorEditor::tableColumnsChanged (TableHeaderComponent *tableHeader)
{
    processor.setNoteType(table.getNoteType());
    processor.setHz(table.getHz());
}

void MusicCalculatorAudioProcessorEditor::tableColumnsResized (TableHeaderComponent *tableHeader) {}
void MusicCalculatorAudioProcessorEditor::tableSortOrderChanged (TableHeaderComponent *tableHeader) {}
void MusicCalculatorAudioProcessorEditor::tableColumnDraggingChanged (TableHeaderComponent *tableHeader, int columnIdNowBeingDragged) {}
