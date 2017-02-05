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
    
    
    double bpm = processor.getBpm();
    bpmLabel.setText(DraggableLabel::format(bpm), sendNotification);
    bpmLabel.setEditable(false, true, true);
    bpmLabel.setColour(Label::outlineColourId, Colour(0,0,0));
    bpmLabel.addListener(this);
    
    
    msLabel.setText(String(bpmToMs(bpm)), sendNotification);
    msLabel.setColour(Label::outlineColourId, Colour(0,0,0));
    
    table.setOutlineThickness(1);
    table.getHeader().addColumn("note", 1, 50);
    table.getHeader().addColumn("ms", 2, 50);
    table.getHeader().setStretchToFitActive(true);
    
    
    
    addAndMakeVisible(bpmLabel);
    addAndMakeVisible(msLabel);
    addAndMakeVisible(table);
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
    bpmLabel.setBounds(40, 30, f.getStringWidth("120.000"), f.getHeight());
    msLabel.setBounds(40, 200, f.getStringWidth("111"), f.getHeight());
    table.setBounds(200, 100, 100, 100);
}

void MusicCalculatorAudioProcessorEditor::timerCallback()
{
    if(sync)
    {
        double bpm = processor.getBpm();
        bpmLabel.setText(DraggableLabel::format(bpm), sendNotification);
    }
}

double MusicCalculatorAudioProcessorEditor::bpmToMs(double bpm)
{
    return 1000.0 / (bpm / 60.0);
}

void MusicCalculatorAudioProcessorEditor::labelTextChanged(juce::Label *labelThatHasChanged)
{
    double bpm = bpmLabel.getTextValue().getValue();
    double ms = bpmToMs(bpm);
    msLabel.setText(String(ms), sendNotification);
}
