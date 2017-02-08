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
    startTimer (100);
    
    
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
    
    
    
    
    addAndMakeVisible(bpmLabel);
    addAndMakeVisible(table);
    addAndMakeVisible(syncButton);
    addAndMakeVisible(alert);

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
    alert.setBounds(getWidth()/2, getHeight()/2, 150, 50);
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
        double bpm = bpmLabel.getTextValue().getValue();
        double ms = bpmToMs(bpm);
        for (int i = 0; i < table.getNumRows(); i++ )
        {
            table.setText(2, i, String(ms));
            ms = ms/2;
        }
    }
}

void MusicCalculatorAudioProcessorEditor::buttonClicked(juce::Button *button)
{
    if(syncButton.getToggleState())
    {
        // Sync on
        
        if (hostHasTempoInformation())
            bpmLabel.setEnabled(false);
        else
        {
            alert.doIt();
            syncButton.setToggleState(false, dontSendNotification);
        }
    }
    else if(!syncButton.getToggleState())
    {
        // Sync off
        
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
