/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MusicCalculatorAudioProcessorEditor::MusicCalculatorAudioProcessorEditor (MusicCalculatorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    startTimer (100);
    
    
    bpm = processor.getBpm();
    bpmLabel.setText(String::String(bpm), dontSendNotification);
    bpmLabel.setEditable(false, true, true);
    bpmLabel.setColour(Label::outlineColourId, Colour(0,0,0));
    
    
    
    
    
    addAndMakeVisible(bpmLabel);
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
    bpmLabel.setBounds(40, 30, 100, 100);
}

void MusicCalculatorAudioProcessorEditor::timerCallback()
{
    bpm = processor.getBpm();
    repaint();
}
