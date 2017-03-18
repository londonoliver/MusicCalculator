//
//  NoteConversionComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/3/17.
//
//

#include "NoteConversionComponent.h"

NoteConversionComponent::NoteConversionComponent()
{
    width = 200;
    height = 400;
    
    label.setText ("Hz", sendNotification);
    
    setTableText();
    
    //addAndMakeVisible (syncComponent);
    addAndMakeVisible (noteSpinner);
    addAndMakeVisible (label);
    addAndMakeVisible (c1);
    
    label.setColour (Label::ColourIds::backgroundColourId, Colour (0xffeeeeee));
    label.setJustificationType (Justification::centred);
    
    resized();
}

NoteConversionComponent::~NoteConversionComponent()
{
}

void NoteConversionComponent::resized()
{
    width = getWidth();
    height = getHeight();
    
    int margin = (0.025 * height);
    
    setTableText();
    
    float fontHeight = 0.142 * (float) height;
    int labelHeight = 0.1 * height;
    
    //syncComponent.setBounds(0, 0, width, labelHeight);
    
    noteSpinner.setFontHeight (fontHeight);
    noteSpinner.setBounds ((width - noteSpinner.width)/2, margin, noteSpinner.width, noteSpinner.height);
    
    label.setBounds (0, noteSpinner.getY() + noteSpinner.height + margin, width, labelHeight);
    
    int cellHeight = (height - (label.getY() + labelHeight))/8.0;
    
    c1.setBounds (0, label.getY() + labelHeight, width, cellHeight);
}

void NoteConversionComponent::setTableText()
{
    int note = noteSpinner.getNote() - 9;
    int octave = noteSpinner.getOctave() - 4;
    
    double hz = semitoneShift (440, (double) note + (double) (octave * 12));
    
    c1.label.setText (String (hz), sendNotification);
}

double NoteConversionComponent::semitoneShift (double value, double amount)
{
    return value / pow (2, amount / -12);
}
