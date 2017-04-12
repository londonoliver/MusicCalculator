/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 Entypo pictograms by Daniel Bruce — www.entypo.com
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace std;


//==============================================================================
MusicCalculatorAudioProcessorEditor::MusicCalculatorAudioProcessorEditor (MusicCalculatorAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    initialWidth = 280;
    initialHeight = initialWidth;
    
    setResizable(true, true);
    setResizeLimits(initialWidth, initialHeight, 3 * initialWidth, 3 * initialHeight);
    setSize (initialWidth, initialHeight);
    getConstrainer()->setFixedAspectRatio ( (double) initialWidth / (double) initialHeight );
    setConstrainer(this);
    
    
    addAndMakeVisible (container);
    {
        toggleLabel.setText("Conversion Type:", dontSendNotification);
        toggleLabel.setBorderSize (BorderSize<int> (0));
        container.addAndMakeVisible (toggleLabel);
        
        tempoToggle.setButtonText("Tempo");
        tempoToggle.setRadioGroupId (1);
        tempoToggle.addListener (this);
        tempoToggle.setToggleState (processor.mode, dontSendNotification);
        tempoToggle.setWantsKeyboardFocus (false);
        tempoToggle.setLookAndFeel (this);
        container.addAndMakeVisible (tempoToggle);
        
        noteToggle.setButtonText("Note");
        noteToggle.setRadioGroupId (1);
        noteToggle.addListener (this);
        noteToggle.setToggleState (!processor.mode, dontSendNotification);
        noteToggle.setWantsKeyboardFocus (false);
        noteToggle.setLookAndFeel (this);
        container.addAndMakeVisible (noteToggle);
    }
    {
        displayLabel.setBorderSize (BorderSize<int> (0));
        displayLabel.setJustificationType (Justification::centred);
        container.addAndMakeVisible (displayLabel);
        
        tempoSpinner.attachListener (this);
        tempoSpinner.setSpinnersText (processor.tempo, dontSendNotification);
        container.addChildComponent (tempoSpinner);
        
        noteSpinner.attachListener (this);
        noteSpinner.setSpinnersText (processor.note, dontSendNotification);
        container.addChildComponent (noteSpinner);
    }
    {
        tempoSyncButton.setToggleText ("HOST", "OFF");
        tempoSyncButton.addListener (this);
        tempoSyncButton.setToggleState (processor.tempoSync, dontSendNotification);
        container.addChildComponent (tempoSyncButton);
        
        tempoFraction.attachListener (this);
        tempoFraction.setFraction (processor.numerator, processor.denominator);
        container.addChildComponent (tempoFraction);
        
        tempoUnitsButton.setToggleText ("Hz", "ms");
        tempoUnitsButton.addListener (this);
        tempoUnitsButton.setToggleState (processor.units, dontSendNotification);
        container.addChildComponent (tempoUnitsButton);
        
        midiSyncButton.setToggleText ("MIDI", "OFF");
        midiSyncButton.addListener (this);
        midiSyncButton.setToggleState (processor.midiSync, dontSendNotification);
        container.addChildComponent (midiSyncButton);
        
        tempoSyncLabel.setText ("Sync", dontSendNotification);
        tempoSyncLabel.setJustificationType (Justification::centred);
        tempoSyncLabel.setBorderSize (BorderSize<int> (0));
        container.addChildComponent (tempoSyncLabel);
        
        tempoFractionLabel.setText ("Fraction", dontSendNotification);
        tempoFractionLabel.setJustificationType (Justification::centred);
        tempoFractionLabel.setBorderSize (BorderSize<int> (0));
        container.addChildComponent (tempoFractionLabel);
        
        tempoUnitsLabel.setText ("Units", dontSendNotification);
        tempoUnitsLabel.setJustificationType (Justification::centred);
        tempoUnitsLabel.setBorderSize (BorderSize<int> (0));
        container.addChildComponent (tempoUnitsLabel);
        
        midiSyncLabel.setText ("Sync", dontSendNotification);
        midiSyncLabel.setJustificationType (Justification::centred);
        midiSyncLabel.setBorderSize (BorderSize<int> (0));
        container.addChildComponent (midiSyncLabel);
    }
    {
        conversionLabel.setText ("Conversion", dontSendNotification);
        conversionLabel.setBorderSize (BorderSize<int> (0));
        conversionLabel.setJustificationType (Justification::centred);
        container.addAndMakeVisible (conversionLabel);
        
        conversionValueLabel.setBorderSize (BorderSize<int> (0));
        conversionValueLabel.setJustificationType (Justification::centred);
        container.addAndMakeVisible (conversionValueLabel);
        
        copy.setButtonText ("Copy");
        copy.setName ("Copy");
        copy.addListener (this);
        copy.setLookAndFeel (this);
        container.addAndMakeVisible (copy);
        
        container.addChildComponent (check);
    }
    
    lastInputIndex = 0;
    setMidiInput (0);
    keyboardState.addListener (this);
    startTimer (100);
    
    setConversion();
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
    copy.removeListener (this);
    keyboardState.removeListener(this);
}

//==============================================================================
void MusicCalculatorAudioProcessorEditor::paint (Graphics& g)
{
    //Colour displayColour = Colour (51, 52 ,51);
    Colour displayColour = Colour (82, 87, 88);
    Colour skinColour = Colour (82, 87, 88);
    Colour skinTextColour = Colour (242, 242, 242);
    Colour displayTextColour = Colour (255, 255, 255);
    Colour brighter = skinColour.brighter();
    Colour darker = skinColour.darker();
    
    g.fillAll(Colours::black);
    
    // set colours
    toggleLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    displayLabel.setColour(Label::ColourIds::textColourId, skinTextColour);
    tempoSyncLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    tempoFractionLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    tempoUnitsLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    midiSyncLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    conversionLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    conversionValueLabel.setColour (Label::ColourIds::textColourId, displayTextColour);
    tempoToggle.setColour(ToggleButton::ColourIds::textColourId, skinTextColour);
    noteToggle.setColour(ToggleButton::ColourIds::textColourId, skinTextColour);
    tempoSpinner.setTextColour (displayTextColour);
    noteSpinner.setTextColour (displayTextColour);
    tempoFraction.setColour (skinTextColour);
    tempoSyncButton.setColour (skinTextColour);
    tempoUnitsButton.setColour (skinTextColour);
    copy.setColour (TextButton::ColourIds::textColourOffId, skinTextColour);
    check.setColour (skinTextColour);
    midiSyncButton.setColour (skinTextColour);
    
    Rectangle<int> r (container.getX(), container.getY(), container.getWidth(), container.getHeight());
    int cornerSize = 0.02 * getWidth();
    int lineThickness = getHeight() / initialHeight;
    
    // background
    g.setColour(skinColour);
    g.fillRoundedRectangle(r.toFloat(), cornerSize);
    
    // toggle
    Path outline;
    outline.addRoundedRectangle (r.getX(), r.getY(), r.getWidth(), p1.getY() - r.getY(), cornerSize, cornerSize, true, true, false, false);
    g.setGradientFill (ColourGradient (skinColour.brighter(0.5f), r.getX(), r.getY(), skinColour.brighter(0.1f), r.getX(), p1.getY(), false));
    g.fillPath (outline);
    
    // display
    Rectangle<int> r1 (r.getX(), p1.getY(), r.getWidth(), p2.getY() - p1.getY());
    g.setColour(displayColour);
    //g.setGradientFill (ColourGradient (skinColour.brighter(0.5f), r1.getX(), p1.getY(), skinColour.brighter(0.05f), r1.getX(), p2.getY(), false));
    g.fillRect(r1);
    
    int reduce = lineThickness * 2;
    r1.reduce(reduce/2, reduce/2);
    g.setColour(displayColour.brighter());
    g.setGradientFill (ColourGradient (displayColour.brighter(), r1.getX(), r1.getY(), displayColour.darker(), r1.getX(), p2.getY(), false));
    //g.drawRoundedRectangle(r1.toFloat(), 0.0f, reduce);
    
    
    // buttons
    g.setGradientFill (ColourGradient (skinColour.brighter(0.5f), r.getX(), p2.getY(), skinColour.brighter(0.05f), r.getX(), p5.getY(), false));
    g.fillRect(r.getX(), p2.getY(), r.getWidth(), p5.getY() - p2.getY());
    
    // conversion
    outline.clear();
    outline.addRoundedRectangle (r.getX(), p5.getY(), r.getWidth(), r.getY() + r.getHeight() - p5.getY(), cornerSize, cornerSize, false, false, true, true);
    g.setGradientFill (ColourGradient (skinColour.brighter(0.5f), r.getX(), p5.getY(), skinColour.brighter(0.05f), r.getX(), r.getHeight(), false));
    g.fillPath (outline);
    
    // bevel lines
    g.setColour (darker);
    g.fillRect(r.getX(), p1.getY() - lineThickness, r.getWidth(), lineThickness);
    g.fillRect(r.getX(), p5.getY() - lineThickness, r.getWidth(), lineThickness);
    g.setColour (brighter);
    g.fillRect(r.getX(), p2.getY(), r.getWidth(), lineThickness);
    g.fillRect(r.getX(), p5.getY(), r.getWidth(), lineThickness);
    
    g.setColour(Colours::coral);
    g.fillRect(r.getX(), p2.getY() - lineThickness, r.getWidth(), lineThickness);
    g.setColour(Colours::coral);
    g.fillRect(r.getX(), p1.getY(), r.getWidth(), lineThickness);
    
    
    if (tempoToggle.getToggleState())
    {
        g.setColour (darker);
        g.fillRect (p3.getX() - lineThickness, p2.getY(), lineThickness, p5.getY() - p2.getY());
        g.fillRect (p4.getX() - lineThickness, p2.getY(), lineThickness, p5.getY() - p2.getY());
        g.setColour (brighter);
        g.fillRect (p3.getX(), p2.getY(), lineThickness, p5.getY() - p2.getY());
        g.fillRect (p4.getX(), p2.getY(), lineThickness, p5.getY() - p2.getY());
        
        // fraction line
        int fractionLineWidth = tempoFraction.numerator.getFont().getStringWidth ("128");
        g.setColour (skinTextColour);
        g.fillRect (tempoFraction.getX() + (tempoFraction.getWidth() - fractionLineWidth)/2 + r.getX(), tempoFraction.getY() + (tempoFraction.getHeight())/2 + r.getY() - lineThickness, fractionLineWidth, lineThickness);
    }
    g.setColour(brighter.brighter());
    g.drawRoundedRectangle(r.toFloat(), cornerSize, lineThickness);
}

void MusicCalculatorAudioProcessorEditor::resized()
{
    Rectangle<int> r = getLocalBounds();
    container.setBounds (r);
    
    int width = container.getWidth();
    int height = container.getHeight();
    
    int togglePanelHeight = (0.4 / 4.0) * height;
    int panelHeight = (1.2 / 4.0) * height;
    int margin = togglePanelHeight / 4;
    
    int panel1Height = (0.4 / 4.0) * height;
    int panel2Height = (1.1 / 4.0) * height;
    int panel3Height = (1.1 / 4.0) * height;
    int panel4Height = (1.4 / 4.0) * height;
    
    Rectangle<int> panel1 (0, 0, width, panel1Height);
    Rectangle<int> panel2 (0, panel1.getY() + panel1.getHeight(), width, panel2Height);
    Rectangle<int> panel3 (0, panel2.getY() + panel2.getHeight(), width, panel3Height);
    Rectangle<int> panel4 (0, panel3.getY() + panel3.getHeight(), width, panel4Height);


    
    /*     __________________________
     *    |                          |  <- panel1
     * p1 X--------------------------|
     *    |                          |
     *    |                          |  <- panel2
     *    |        p3       p4       |
     * p2 X--------X--------X--------|
     *    |        |        |        |
     *    |        |        |        |  <- panel3
     *    |        |        |        |
     * p5 X--------------------------|
     *    |                          |
     *    |                          |  <- panel4
     *    |                          |
     *     --------------------------
     */
     
    
    p1.setY (panel1.getY() + panel1.getHeight());
    p2.setY (panel3.getY());
    p3.setX ((1.0 / 3.0) * width);
    p4.setX ((2.0 / 3.0) * width);
    p5.setY (panel4.getY());
    
    // toggle
    {
        Rectangle<int> r (panel1);
        r.reduce(margin, margin);
        toggleLabel.setFont(Font(r.getHeight()));
        toggleLabel.setBounds(r.getX() + margin, r.getY(), toggleLabel.getFont().getStringWidth(toggleLabel.getText()), r.getHeight());
        tempoToggle.setBounds (toggleLabel.getX() + toggleLabel.getWidth() + margin/2, r.getY(), (r.getWidth() - toggleLabel.getWidth())/2.25, r.getHeight());
        noteToggle.setBounds (tempoToggle.getX() + tempoToggle.getWidth(), r.getY(), (r.getWidth() - toggleLabel.getWidth())/2.25, r.getHeight());
    }
    // display
    {
        /*             panel2
         *   __________________________
         *  |            r1            |
         *  |--------------------------|
         *  |            r2            |
         *  |                          |
         *   --------------------------
         */
        
        Rectangle<int> r (panel2);
        Rectangle<int> r1 (r.getX(), r.getY(), width, (1.0 / 3.0) * r.getHeight());
        Rectangle<int> r2 (r.getX(), r1.getY() + r1.getHeight(), width, r.getHeight() - r1.getHeight());
        
        r1.reduce(margin, margin);
        r2.reduce(margin, margin);
        
        // r1
        displayLabel.setFont (Font (r1.getHeight()));
        displayLabel.setBounds (r1.getX(), r1.getY(), r1.getWidth(), r1.getHeight());
        
        // r2
        tempoSpinner.setFontHeight (r2.getHeight());
        tempoSpinner.setBounds (r2.getX(), r2.getY(), r2.getWidth(), r2.getHeight());
    
        noteSpinner.setFontHeight (r2.getHeight());
        noteSpinner.setBounds (r2.getX(), r2.getY(), r2.getWidth(), r2.getHeight());
    }
    // buttons
    {
        /*               panel3
         *     --------------------------
         *    |   r1   |   r2   |   r3   |
         *    |--------|--------|--------|
         *    |   r4   |   r5   |   r6   |
         *    |        |        |        |
         *     --------------------------
         */
        
        Rectangle<int> r (panel3);
        Rectangle<int> r1 (r.getX(), r.getY(), (1.0 / 3.0) * r.getWidth(), (1.0 / 3.0) * r.getHeight());
        Rectangle<int> r2 (p3.getX(), r1.getY(), (1.0 / 3.0) * r.getWidth(), r1.getHeight());
        Rectangle<int> r3 (p4.getX(), r1.getY(), (1.0 / 3.0) * r.getWidth(), r1.getHeight());
        Rectangle<int> r4 (r.getX(), r1.getY() + r1.getHeight(), r1.getWidth(), r.getHeight() - r1.getHeight());
        Rectangle<int> r5 (p3.getX(), r4.getY(), r2.getWidth(), r4.getHeight());
        Rectangle<int> r6 (p4.getX(), r4.getY(), r3.getWidth(), r4.getHeight());
        
        r1.reduce (margin, margin);
        r2.reduce (margin, margin);
        r3.reduce (margin, margin);
        r4.reduce (margin, margin);
        r5.reduce (margin, margin);
        r6.reduce (margin, margin);
        
        r4.reduce(margin * 2, 0);
        r5.reduce(margin * 2, 0);
        r6.reduce(margin * 2, 0);
        
        // r1
        tempoSyncLabel.setFont (Font (r1.getHeight()));
        tempoSyncLabel.setBounds (r1.getX(), r1.getY(), r1.getWidth(), r1.getHeight());
        
        // r2
        tempoFractionLabel.setFont (Font (r2.getHeight()));
        tempoFractionLabel.setBounds (r2.getX(), r2.getY(), r2.getWidth(), r2.getHeight());
        
        midiSyncLabel.setFont (Font (r2.getHeight()));
        midiSyncLabel.setBounds (r2.getX(), r2.getY(), r2.getWidth(), r2.getHeight());
        
        // r3
        tempoUnitsLabel.setFont (Font (r3.getHeight()));
        tempoUnitsLabel.setBounds (r3.getX(), r3.getY(), r3.getWidth(), r3.getHeight());
        
        // r4
        tempoSyncButton.setBounds (r4.getX(), r4.getY(), r5.getWidth(), r4.getHeight());
        
        // r5
        tempoFraction.setBounds (r5.getX(), r5.getY(), r5.getWidth(), r5.getHeight());
        
        midiSyncButton.setBounds (r5.getX(), r5.getY(), r5.getWidth(), r5.getHeight());
        
        // r6
        tempoUnitsButton.setBounds (r6.getX(), r6.getY(), r5.getWidth(), r6.getHeight());
    }
    // conversion
    {
        /*             panel4
         *   __________________________
         *  |            r1            |
         *  |--------------------------|
         *  |            r2            |
         *  |--------------------------|
         *  |            r3            |
         *   --------------------------
         */
        
        Rectangle<int> r (panel4);
        Rectangle<int> r1 (r.getX(), r.getY(), r.getWidth(), (1.0 / 3.0) * r.getHeight());
        Rectangle<int> r2 (r.getX(), r1.getY() + r1.getHeight(), r.getWidth(), (1.0 / 3.0) * r.getHeight());
        Rectangle<int> r3 (r.getX(), r2.getY() + r2.getHeight(), r.getWidth(), (1.0 / 3.0) * r.getHeight());
        
        r1.reduce(margin, margin);
        r2.reduce(0.0, margin/2);
        r2.reduce(r.getWidth()/2.75, 0);
        r3.reduce(margin, margin);
        
        // r1
        conversionLabel.setFont (tempoSyncLabel.getFont());
        conversionLabel.setBounds (r1.getX(), r1.getY(), r1.getWidth(), r1.getHeight());
        
        // r2
        copy.setBounds (r2.getX(), r2.getY(), r2.getWidth(), r2.getHeight());
        check.setBounds (copy.getX() + copy.getWidth() * 1.25, copy.getY(), r2.getHeight(), r2.getHeight());
        
        // r3
        conversionValueLabel.setFont (Font (r3.getHeight()));
        conversionValueLabel.setBounds (r3.getX(), r3.getY(), r3.getWidth(), r3.getHeight());
    }
    
    p1.setY (p1.getY() + r.getY());
    p2.setY (p2.getY() + r.getY());
    p3.setX (p3.getX() + r.getX());
    p4.setX (p4.getX() + r.getX());
    p5.setY (p5.getY() + r.getY());
    
    repaint();
}

void MusicCalculatorAudioProcessorEditor::buttonClicked (Button *button)
{
    if (button->getName() == copy.getName())
    {
        SystemClipboard::copyTextToClipboard(setConversion());

        check.setVisible (true);
        check.setAlpha (1.0f);
        Desktop::getInstance().getAnimator().fadeOut (&check, 500);
    }
    else
    {
        setConversion();
    }
}

void MusicCalculatorAudioProcessorEditor::labelTextChanged (Label *) {  setConversion();    }

String MusicCalculatorAudioProcessorEditor::setConversion()
{
    double bpm = tempoSpinner.getValue();
    double bpm_ms = (1000.0 / (bpm / 60.0)) * 4.0 * tempoFraction.getFraction();
    double bpm_hz = (bpm / 60.0) / 4.0 / tempoFraction.getFraction();
    
    note = noteSpinner.getNote() - 9;
    octave = noteSpinner.getOctave() - 4;
    double concertA = 440.0;
    double note_hz = concertA / pow (2.0, ((float) note + (float) (octave * 12.0)) / -12.0);
    
    String conversion = (tempoToggle.getToggleState()) ? ((tempoUnitsButton.getToggleState()) ? String (bpm_hz) : String (bpm_ms)) : String (note_hz);
    String units = (tempoToggle.getToggleState()) ? (tempoUnitsButton.getToggleState() ? " Hz": " ms") : " Hz";
    
    conversionValueLabel.setText (String (conversion) + units, dontSendNotification);
    
    processor.mode = tempoToggle.getToggleState();
    processor.tempo = tempoSpinner.toString();
    processor.tempoSync = tempoSyncButton.getToggleState();
    processor.numerator = tempoFraction.getNumerator();
    processor.denominator = tempoFraction.getDenominator();
    processor.units = tempoUnitsButton.getToggleState();
    processor.note = noteSpinner.toString();
    processor.midiSync = midiSyncButton.getToggleState();
    
    {
        tempoSpinner.setVisible (tempoToggle.getToggleState());
        tempoSpinner.setEnabled ( ! tempoSyncButton.getToggleState() );
        noteSpinner.setVisible (noteToggle.getToggleState());
        displayLabel.setText((tempoToggle.getToggleState()) ? "Tempo" : "Note", dontSendNotification);
        noteSpinner.setEnabled ( ! midiSyncButton.getToggleState() );
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
    
    return conversion;
}

void MusicCalculatorAudioProcessorEditor::timerCallback()
{
    tempoSyncButton.setEnabled (processor.isTempoInformationAvailable());
    midiSyncButton.setEnabled( ! MidiInput::getDevices().isEmpty() );
    
    if (tempoToggle.getToggleState() && tempoSyncButton.getToggleState())
        tempoSpinner.setSpinnersText (String (processor.tempo), sendNotification);
    else if (noteToggle.getToggleState() && midiSyncButton.getToggleState())
    {
        setMidiInput(0);
        if (midiSyncButton.getToggleState())
            noteSpinner.setSpinnersText (Spinner::getNote (note) + String(octave), sendNotification);
    }
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
        note = midiNoteNumber % 12;
        octave = midiNoteNumber / 12 + (3 - 5);  // octave = midiNoteNumber / 12 + (middleC - 5)
        
        /* Dont set notespinner text from here - this is in another thread and requires a thread lock
         * which can cause plugin to lock up if there are too many noteOn events at one time.
         *
         * Instead, set class variables note and octave and then set notespinner text from timerCallback() method
         */
    }
}

void MusicCalculatorAudioProcessorEditor::handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/)
{
}

void MusicCalculatorAudioProcessorEditor::drawButtonText (Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/)
{
    Font font (getTextButtonFont (button, button.getHeight()));
    g.setFont (font);
    g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                    : TextButton::textColourOffId)
                 .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
    
    const int yIndent = jmin (4, button.proportionOfHeight (0.3f));
    const int cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;
    
    const int fontHeight = roundToInt (font.getHeight() * 0.6f);
    const int leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
    const int rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
    const int textWidth = button.getWidth() - leftIndent - rightIndent;
    
    if (textWidth > 0)
        g.drawFittedText (button.getButtonText(),
                          leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2,
                          Justification::centred, 2);
    
}

void MusicCalculatorAudioProcessorEditor::drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                           bool isMouseOverButton, bool isButtonDown)
{
    Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                       .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));
    
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
                                     ! (flatOnLeft  || flatOnTop),
                                     ! (flatOnRight || flatOnTop),
                                     ! (flatOnLeft  || flatOnBottom),
                                     ! (flatOnRight || flatOnBottom));
        
        const float mainBrightness = baseColour.getBrightness();
        const float mainAlpha = baseColour.getFloatAlpha();
        
        if (isButtonDown || isMouseOverButton)
        {
            g.setColour ((isButtonDown) ? Colours::white.withAlpha (0.4f) : Colours::white.withAlpha (0.2f));
            g.fillPath (outline);
        }
        
        g.setColour (Colours::white.withAlpha (0.4f * mainAlpha * mainBrightness * mainBrightness));
        g.strokePath (outline, PathStrokeType (1.0f), AffineTransform::translation (0.0f, 1.0f)
                      .scaled (1.0f, (height - 1.6f) / height));
        
        g.setColour (Colours::black.withAlpha (0.4f * mainAlpha));
        g.strokePath (outline, PathStrokeType (1.0f));
    }
}

Font MusicCalculatorAudioProcessorEditor::getTextButtonFont (TextButton&, int buttonHeight)
{
    return Font (buttonHeight * 0.6f);
}

void MusicCalculatorAudioProcessorEditor::drawToggleButton (Graphics& g, ToggleButton& button,
                                       bool isMouseOverButton, bool isButtonDown)
{
    if (button.hasKeyboardFocus (true))
    {
        g.setColour (button.findColour (TextEditor::focusedOutlineColourId));
        g.drawRect (0, 0, button.getWidth(), button.getHeight());
    }
    
    float fontSize = button.getHeight();
    const float tickWidth = fontSize * 1.1f;
    
    drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
                 tickWidth, tickWidth,
                 button.getToggleState(),
                 button.isEnabled(),
                 isMouseOverButton,
                 isButtonDown);
    
    g.setColour (button.findColour (ToggleButton::textColourId));
    g.setFont (fontSize);
    
    if (! button.isEnabled())
        g.setOpacity (0.5f);
    
    const int textX = (int) tickWidth + 5;
    
    g.drawFittedText (button.getButtonText(),
                      textX, 0,
                      button.getWidth() - textX - 2, button.getHeight(),
                      Justification::centredLeft, 10);
}

void MusicCalculatorAudioProcessorEditor::drawTickBox (Graphics& g, Component& component,
                                  float x, float y, float w, float h,
                                  const bool ticked,
                                  const bool isEnabled,
                                  const bool isMouseOverButton,
                                  const bool isButtonDown)
{
    const float boxSize = w * 0.7f;
    
    const float sat = 1.3f;
    const Colour baseColour (component.findColour (TextButton::buttonColourId)
                             .withMultipliedAlpha (isEnabled ? 1.0f : 0.5f).withMultipliedSaturation (sat));
    
    if (isButtonDown)      baseColour.contrasting (0.2f);
    if (isMouseOverButton) baseColour.contrasting (0.1f);
    
    
    drawGlassSphere (g, x, y + (h - boxSize) * 0.5f, boxSize,
                     baseColour, isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.1f : 0.5f) : 0.3f);
    
    if (ticked)
    {
        Path tick;
        tick.startNewSubPath (1.5f, 3.0f);
        tick.lineTo (3.0f, 6.0f);
        tick.lineTo (6.0f, 0.0f);
        
        g.setColour (component.findColour (isEnabled ? ToggleButton::tickColourId
                                           : ToggleButton::tickDisabledColourId));
        
        const AffineTransform trans (AffineTransform::scale (w / 9.0f, h / 9.0f)
                                     .translated (x, y));
        
        g.strokePath (tick, PathStrokeType (h/8), trans);
    }
}
