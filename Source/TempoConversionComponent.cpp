//
//  TempoConversionComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/1/17.
//
//  https://thenounproject.com/bravebros/collection/music/?i=104862
//  https://thenounproject.com/search/?q=metronome&i=28820
//

#include "TempoConversionComponent.h"

TempoConversionComponent::TempoConversionComponent()
{
    width = 200;
    height = 400;
    
    sync.addListener (this);
    sync.setName ("sync");
    sync.setButtonText ("Sync");

    
    b1.setLookAndFeel (this);
    b2.setLookAndFeel (this);
    sync.setLookAndFeel(this);
    
    b1.addListener (this);
    b2.addListener (this);
    
    b1.setName ("b1");
    b2.setName ("b2");
    
    b1.setButtonText ("Note");
    b2.setButtonText ("Ms");
    
    addAndMakeVisible (tempoSpinner);
    //addAndMakeVisible (syncComponent);
    addAndMakeVisible (b1);
    addAndMakeVisible (b2);
    
    c11.removeChildComponent (c11.button);
    c12.removeChildComponent (c12.button);
    c13.removeChildComponent (c13.button);
    c14.removeChildComponent (c14.button);
    c15.removeChildComponent (c15.button);
    c16.removeChildComponent (c16.button);
    c17.removeChildComponent (c17.button);
    c18.removeChildComponent (c18.button);
    
    c12.setBackgroundColor (Colour (0xffeeeeee));
    c14.setBackgroundColor (Colour (0xffeeeeee));
    c16.setBackgroundColor (Colour (0xffeeeeee));
    c18.setBackgroundColor (Colour (0xffeeeeee));
    
    c22.setBackgroundColor (Colour (0xffeeeeee));
    c24.setBackgroundColor (Colour (0xffeeeeee));
    c26.setBackgroundColor (Colour (0xffeeeeee));
    c28.setBackgroundColor (Colour (0xffeeeeee));
    
    setTableText();
    
    addAndMakeVisible(c11);
    addAndMakeVisible(c12);
    addAndMakeVisible(c13);
    addAndMakeVisible(c14);
    addAndMakeVisible(c15);
    addAndMakeVisible(c16);
    addAndMakeVisible(c17);
    addAndMakeVisible(c18);
    
    addAndMakeVisible(c21);
    addAndMakeVisible(c22);
    addAndMakeVisible(c23);
    addAndMakeVisible(c24);
    addAndMakeVisible(c25);
    addAndMakeVisible(c26);
    addAndMakeVisible(c27);
    addAndMakeVisible(c28);
    
    resized();
}

TempoConversionComponent::~TempoConversionComponent()
{
    b1.removeListener (this);
    b2.removeListener (this);
}

void TempoConversionComponent::paint (Graphics &g)
{
    g.fillAll (bgColour);
}

void TempoConversionComponent::resized()
{
    width = getWidth();
    height = getHeight();
    
    int margin = (0.025 * height);
    
    setTableText();
    
    float fontHeight = 0.15f * (float) height;
    int tableWidth = width;
    int buttonHeight = 0.1 * height;
    
    //syncComponent.setBounds(0, 0, width, buttonHeight);
    
    
    tempoSpinner.setFontHeight (fontHeight);
    tempoSpinner.setBounds ((width - tempoSpinner.width)/2, margin, tempoSpinner.width, tempoSpinner.height);
    
    int c1Width = floor(tableWidth/2.0);
    int c2Width = ceil(tableWidth/2.0);
    
    b1.setBounds (0, tempoSpinner.getY() + tempoSpinner.getHeight() + margin, c1Width, buttonHeight);
    b2.setBounds (width/2, b1.getY(), c2Width, buttonHeight);
    b2.setButtonText ((col2_Mode == ColumnTwoMode::MS) ? "Ms" : "Hz");
    
    int cellHeight = (height - (b1.getY() + buttonHeight))/8.0;
    
    c11.setBounds (0, b1.getY() + buttonHeight, c1Width, cellHeight);
    c12.setBounds (0, c11.getY() + cellHeight, c1Width, cellHeight);
    c13.setBounds (0, c12.getY() + cellHeight, c1Width, cellHeight);
    c14.setBounds (0, c13.getY() + cellHeight, c1Width, cellHeight);
    c15.setBounds (0, c14.getY() + cellHeight, c1Width, cellHeight);
    c16.setBounds (0, c15.getY() + cellHeight, c1Width, cellHeight);
    c17.setBounds (0, c16.getY() + cellHeight, c1Width, cellHeight);
    c18.setBounds (0, c17.getY() + cellHeight, c1Width, cellHeight);
    
    c21.setBounds (width/2, b2.getY() + buttonHeight, c2Width, cellHeight);
    c22.setBounds (width/2, c21.getY() + cellHeight, c2Width, cellHeight);
    c23.setBounds (width/2, c22.getY() + cellHeight, c2Width, cellHeight);
    c24.setBounds (width/2, c23.getY() + cellHeight, c2Width, cellHeight);
    c25.setBounds (width/2, c24.getY() + cellHeight, c2Width, cellHeight);
    c26.setBounds (width/2, c25.getY() + cellHeight, c2Width, cellHeight);
    c27.setBounds (width/2, c26.getY() + cellHeight, c2Width, cellHeight);
    c28.setBounds (width/2, c27.getY() + cellHeight, c2Width, cellHeight);
}

void TempoConversionComponent::setTableText()
{
    int rowNumber = 0;
    
    String mode = (col1_Mode == ColumnOneMode::DOTTED) ? "."
        : ((col1_Mode == ColumnOneMode::TRIPLET) ? "T"
           : "");
    
    c11.label.setText ("1/" + String (pow (2, rowNumber++)) + mode, sendNotification);
    c12.label.setText ("1/" + String (pow (2, rowNumber++)) + mode, sendNotification);
    c13.label.setText ("1/" + String (pow (2, rowNumber++)) + mode, sendNotification);
    c14.label.setText ("1/" + String (pow (2, rowNumber++)) + mode, sendNotification);
    c15.label.setText ("1/" + String (pow (2, rowNumber++)) + mode, sendNotification);
    c16.label.setText ("1/" + String (pow (2, rowNumber++)) + mode, sendNotification);
    c17.label.setText ("1/" + String (pow (2, rowNumber++)) + mode, sendNotification);
    c18.label.setText ("1/" + String (pow (2, rowNumber++)) + mode, sendNotification);
    
    double bpm = tempoSpinner.getValue();
    
    double multiplier = (col1_Mode == ColumnOneMode::DOTTED) ? (3.0 / 2.0) :
    ((col1_Mode == ColumnOneMode::TRIPLET) ? (2.0 / 3.0) : 1);
    
    double wholeNoteMs = (1000.0 / (bpm / 60.0)) * 4.0 * multiplier;
    
    double wholeNoteHz = (bpm / 60.0) / 4.0 / multiplier;
    
    double wholeNote = (col2_Mode == ColumnTwoMode::MS) ? wholeNoteMs : wholeNoteHz;
    
    rowNumber = 0;
    
    int exponent = (col2_Mode == ColumnTwoMode::MS) ? -1.0 : 1.0;
    
    c21.label.setText (String (wholeNote * pow (pow (2, rowNumber++), exponent)), sendNotification);
    c22.label.setText (String (wholeNote * pow (pow (2, rowNumber++), exponent)), sendNotification);
    c23.label.setText (String (wholeNote * pow (pow (2, rowNumber++), exponent)), sendNotification);
    c24.label.setText (String (wholeNote * pow (pow (2, rowNumber++), exponent)), sendNotification);
    c25.label.setText (String (wholeNote * pow (pow (2, rowNumber++), exponent)), sendNotification);
    c26.label.setText (String (wholeNote * pow (pow (2, rowNumber++), exponent)), sendNotification);
    c27.label.setText (String (wholeNote * pow (pow (2, rowNumber++), exponent)), sendNotification);
    c28.label.setText (String (wholeNote * pow (pow (2, rowNumber++), exponent)), sendNotification);
}

Font TempoConversionComponent::getTextButtonFont (TextButton &, int buttonHeight)
{
    return Font (0.6f * (float) buttonHeight);
}

void TempoConversionComponent::buttonClicked (Button *button)
{
    if (button->getName() == b1.getName())
        col1_Mode = (col1_Mode == ColumnOneMode::NORMAL) ? ColumnOneMode::DOTTED
            : ((col1_Mode == ColumnOneMode::DOTTED) ? ColumnOneMode::TRIPLET
               : ColumnOneMode::NORMAL);
    else if (button->getName() == b2.getName())
        col2_Mode = (col2_Mode == ColumnTwoMode::MS) ? ColumnTwoMode::HZ : ColumnTwoMode::MS;
    
    resized();
}

void TempoConversionComponent::drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown)
{
    Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                       .withMultipliedAlpha (1.0f));
    
    if (isButtonDown || isMouseOverButton)
        baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);
    
    const bool flatOnLeft   = button.isConnectedOnLeft();
    const bool flatOnRight  = button.isConnectedOnRight();
    const bool flatOnTop    = button.isConnectedOnTop();
    const bool flatOnBottom = button.isConnectedOnBottom();
    
    const float width  = button.getWidth() - 1.0f;
    const float height = button.getHeight() - 1.0f;
    
    if (width > 0 && height > 0)
    {
        const float cornerSize = 4.0f;
        
        Path outline;
        outline.addRoundedRectangle (0.5f, 0.5f, width, height, cornerSize, cornerSize,
                                      (flatOnLeft  || flatOnTop),
                                      (flatOnRight || flatOnTop),
                                      (flatOnLeft  || flatOnBottom),
                                      (flatOnRight || flatOnBottom));
        

        g.setColour (baseColour.withAlpha(0.0f));
        g.fillPath (outline);

        g.setColour (Colour (baseColour));
        g.strokePath (outline, PathStrokeType (1.0f));
        
    }
}
