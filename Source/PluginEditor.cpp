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
    width = 300;
    height = 1.167 * width;
    
    setResizable(true, true);
    setResizeLimits(width, height, 3 * width, 3 * height);
    setSize (width, height);
    getConstrainer()->setFixedAspectRatio ( (double) width / (double) height );
    setConstrainer(this);
    
    {
        toggleLabel.setText("Conversion Type:", dontSendNotification);
        toggleLabel.setBorderSize (BorderSize<int> (0));
        addAndMakeVisible (toggleLabel);
        
        tempoToggle.setButtonText("Tempo");
        tempoToggle.setRadioGroupId (1);
        tempoToggle.addListener (this);
        tempoToggle.setToggleState (processor.mode, dontSendNotification);
        tempoToggle.setWantsKeyboardFocus (false);
        tempoToggle.setLookAndFeel (this);
        addAndMakeVisible (tempoToggle);
        
        noteToggle.setButtonText("Note");
        noteToggle.setRadioGroupId (1);
        noteToggle.addListener (this);
        noteToggle.setToggleState (!processor.mode, dontSendNotification);
        noteToggle.setWantsKeyboardFocus (false);
        noteToggle.setLookAndFeel (this);
        addAndMakeVisible (noteToggle);
    }
    {
        tempoSpinner.attachListener (this);
        tempoSpinner.setSpinnersText (processor.tempo, dontSendNotification);
        addChildComponent (tempoSpinner);
        
        noteSpinner.attachListener (this);
        noteSpinner.setSpinnersText (processor.note, dontSendNotification);
        addChildComponent (noteSpinner);
        
        displayLabel.setBorderSize (BorderSize<int> (0));
        addAndMakeVisible (displayLabel);
    }
    {
        tempoSyncButton.setToggleText ("HOST", "OFF");
        tempoSyncButton.addListener (this);
        tempoSyncButton.setToggleState (processor.tempoSync, dontSendNotification);
        addChildComponent (tempoSyncButton);
        
        tempoFraction.attachListener (this);
        tempoFraction.setFraction (processor.numerator, processor.denominator);
        addChildComponent (tempoFraction);
        
        tempoUnitsButton.setToggleText ("HZ", "MS");
        tempoUnitsButton.addListener (this);
        tempoUnitsButton.setToggleState (processor.units, dontSendNotification);
        addChildComponent (tempoUnitsButton);
        
        midiSyncButton.setToggleText ("MIDI", "OFF");
        midiSyncButton.addListener (this);
        midiSyncButton.setToggleState (processor.midiSync, dontSendNotification);
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
        copy.setName ("Copy");
        copy.addListener (this);
        copy.setLookAndFeel (this);
        addAndMakeVisible (copy);
        
        addChildComponent (check);
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
    Colour displayColour = Colours::maroon;
    Colour skinColour = Colour (82, 87, 88);
    Colour skinTextColour = Colour (242, 242, 242);
    Colour displayTextColour = Colour (254, 236, 220);
    Colour skinBrighter = Colours::white.withAlpha(0.2f);
    

    
    toggleLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    displayLabel.setColour(Label::ColourIds::textColourId, displayTextColour);
    tempoSyncLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    tempoFractionLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    tempoUnitsLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    midiSyncLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    conversionLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    conversionValueLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    conversionUnitsLabel.setColour (Label::ColourIds::textColourId, skinTextColour);
    
    tempoToggle.setColour(ToggleButton::ColourIds::textColourId, skinTextColour);
    //tempoToggle.setColour(ToggleButton::ColourIds::tickColourId, skinTextColour);
    noteToggle.setColour(ToggleButton::ColourIds::textColourId, skinTextColour);
    //noteToggle.setColour(ToggleButton::ColourIds::tickColourId, skinTextColour);
    tempoSpinner.setTextColour (displayTextColour);
    noteSpinner.setTextColour (displayTextColour);
    tempoFraction.setColour (skinTextColour);
    tempoSyncButton.setColour (skinTextColour);
    //tempoSyncButton.juce::Component::setColour (TextButton::ColourIds::buttonColourId, skinColour);
    tempoUnitsButton.setColour (skinTextColour);
    //tempoUnitsButton.juce::Component::setColour (TextButton::ColourIds::buttonColourId, skinColour);
    copy.setColour (TextButton::ColourIds::textColourOffId, skinTextColour);
    check.setColour (skinTextColour);
    midiSyncButton.setColour (skinTextColour);
    
    int lineHeight = height/350;
    
    int toggleEnd = toggleLabel.getY() + toggleLabel.getHeight() + width * 0.02;
    int margin = (3.0 / 40.0) * height;
    int buttonsBegin = tempoSpinner.getY() + tempoSpinner.getHeight() + margin/2;
    int conversionBegin = tempoSyncButton.getY() + tempoSyncButton.getHeight() + margin/2;
    
    int buttonWidth = (1.0 / 6.0) * width;
    int button1End = 2 * buttonWidth;
    int button2End = 4 * buttonWidth;
    
    g.setGradientFill(ColourGradient (skinColour.brighter(0.2f), 0.0f, 0, skinColour, 0.0f, height, false));
    g.fillRect(0, 0, width, height);
    
    // toggle fill
    g.setColour(skinColour);
    g.fillRect(0, 0, width, toggleEnd);
    
    // display fill
    g.setColour(displayColour);
    g.fillRect (0, toggleEnd, width, buttonsBegin - toggleEnd);
    
    // display glare
    g.setColour(Colours::white.withAlpha(0.1f));
    Rectangle<int> r (0, toggleEnd, width, (buttonsBegin - toggleEnd)/2);
    r.reduce(lineHeight * 2, lineHeight * 2);
    g.fillRoundedRectangle (r.toFloat(), lineHeight * 3);
    
    // buttons gradient fill
    g.setGradientFill(ColourGradient (skinColour.brighter(0.2f), 0.0f, buttonsBegin, skinColour, 0.0f, height - buttonsBegin, false));
    g.fillRect(0, buttonsBegin, width, conversionBegin - buttonsBegin);
    
    //conversion gradient fill
    g.setGradientFill(ColourGradient (skinColour.brighter(0.1f), 0.0f, conversionBegin, skinColour.darker(0.1f), 0.0f, height, false));
    g.fillRect(0, conversionBegin, width, height);
    
    // lines
    
    { // toggle
        g.setColour (skinColour.darker());
        g.fillRect (0, toggleEnd - lineHeight, width, lineHeight);
        
        g.setColour (displayColour.brighter());
        g.fillRect (0, toggleEnd, width, lineHeight);
    }
    {   // buttons top
        g.setColour (displayColour.darker());
        g.fillRect (0, buttonsBegin - lineHeight, width, lineHeight);
        
        g.setColour (skinBrighter);
        g.fillRect (lineHeight * 2, buttonsBegin, width - lineHeight * 2, lineHeight);
    }
    {   // buttons vertical
        if (tempoToggle.getToggleState())
        {
            g.setColour (skinColour.darker());
            g.fillRect (button1End, buttonsBegin, lineHeight, conversionBegin - buttonsBegin - lineHeight);
            g.fillRect (button2End , buttonsBegin, lineHeight, conversionBegin - buttonsBegin - lineHeight);
            
            g.setColour (skinBrighter);
            g.fillRect (button1End + lineHeight, buttonsBegin + lineHeight, lineHeight, conversionBegin - buttonsBegin -  2 * lineHeight);
            g.fillRect (button2End + lineHeight, buttonsBegin + lineHeight, lineHeight, conversionBegin - buttonsBegin - 2 * lineHeight);
        }
    }
    {   // conversion top
        g.setColour (skinColour.darker());
        g.fillRect(lineHeight, conversionBegin - lineHeight, width, lineHeight);
        
        g.setColour (skinBrighter);
        g.fillRect(lineHeight * 2, conversionBegin, width - lineHeight * 2, lineHeight);
    }
    {   // bottom
        g.setColour (skinColour.darker());
        g.fillRect(lineHeight, height - lineHeight, width, lineHeight);
    }
    {   // sides
        g.setColour(skinColour.darker());
        g.fillRect (0, 0, lineHeight, toggleEnd);
        g.fillRect (width - lineHeight, 0, lineHeight, toggleEnd);
        
        g.fillRect (0, buttonsBegin, lineHeight, height - buttonsBegin);
        g.fillRect (width - lineHeight, buttonsBegin, lineHeight, height - buttonsBegin);
        
        g.setColour (skinBrighter);
        //g.fillRect (lineHeight, buttonsBegin, lineHeight, height - buttonsBegin - lineHeight);
        //g.fillRect (lineHeight, 0, lineHeight, toggleEnd - lineHeight);
        
        
        
        g.setColour(displayColour.darker());
        g.fillRect(0, toggleEnd, lineHeight, buttonsBegin - toggleEnd);
        g.fillRect(width - lineHeight, toggleEnd, lineHeight, buttonsBegin - toggleEnd);
        
        g.setColour(displayColour.brighter());
        //g.fillRect(lineHeight, toggleEnd, lineHeight, buttonsBegin - toggleEnd - lineHeight);
        
    }
    

    
    
    
    g.setColour (Colours::black);
    g.setFont (15.0f);
}

void MusicCalculatorAudioProcessorEditor::resized()
{
    width = getWidth();
    height = getHeight();
    
    int margin = (3.0 / 40.0) * height;
    int smallPanelHeight = (1.0 / 20.0) * height;
    int bigPanelHeight = (2.0 / 10.0) * height;
    
    {
        int toggleWidth = 0.2 * width;
        int toggleMargin = width * 0.02;
        toggleLabel.setFont (Font (smallPanelHeight * 0.75f));
        int toggleLabelWidth = toggleLabel.getFont().getStringWidth (toggleLabel.getText());
        toggleLabel.setBounds(toggleMargin, toggleMargin, toggleLabelWidth, smallPanelHeight);
        tempoToggle.setBounds (toggleLabel.getX() + toggleLabel.getWidth(), toggleMargin, toggleWidth, smallPanelHeight);
        noteToggle.setBounds (tempoToggle.getX() + tempoToggle.getWidth(), toggleMargin, toggleWidth, smallPanelHeight);
    }
    {
        int displayLabelHeight = (1.0 / 5.0) * bigPanelHeight;
        displayLabel.setFont (Font (displayLabelHeight));
        int displayLabelWidth =  displayLabel.getFont().getStringWidth (displayLabel.getText());
        
        displayLabel.setBounds ((width - displayLabelWidth)/2, smallPanelHeight + margin, displayLabelWidth, displayLabelHeight);
    
        int displayHeight = (3.0 / 5.0) * bigPanelHeight;
        
        tempoSpinner.setFontHeight ((float) displayHeight);
        tempoSpinner.setBounds ((width - tempoSpinner.width)/2, displayLabel.getY() + 1.5 * displayLabel.getHeight(), tempoSpinner.width, displayHeight);
        
        noteSpinner.setFontHeight ((float) displayHeight);
        noteSpinner.setBounds ((width - noteSpinner.width)/2, displayLabel.getY() + 1.5 * displayLabel.getHeight(), noteSpinner.width, displayHeight);
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
        int conversionValueLabelHeight = (2.0 / 5.0) * bigPanelHeight;
        conversionLabel.setFont (Font (conversionLabelHeight));
        conversionValueLabel.setFont (Font (conversionValueLabelHeight));
        conversionUnitsLabel.setFont (Font (conversionValueLabelHeight));
        int conversionLabelWidth = conversionLabel.getFont().getStringWidth (conversionLabel.getText());
        int spaceWidth = conversionValueLabel.getFont().getStringWidth(" ");
        int conversionValueLabelWidth = conversionValueLabel.getFont().getStringWidth (conversionValueLabel.getText());
        int conversionUnitsLabelWidth = conversionValueLabel.getFont().getStringWidth (conversionUnitsLabel.getText());
        int copyWidth = conversionLabelWidth;
        int copyHeight = 2 * conversionLabelHeight;
        
        conversionLabel.setBounds ((width - conversionLabelWidth)/2, tempoSyncButton.getY() + tempoSyncButton.getHeight() + margin, conversionLabelWidth, conversionLabelHeight);
        
        copy.setBounds ((width - copyWidth)/2, conversionLabel.getY() + 2 * conversionLabel.getHeight(), copyWidth, copyHeight);
        
        check.setBounds (copy.getX() + copy.getWidth() + copyHeight/2, copy.getY(), copyHeight/1.5, copyHeight/1.5);
        
        conversionValueLabel.setBounds ((width - conversionValueLabelWidth - spaceWidth - conversionUnitsLabelWidth)/2, copy.getY() + 3 * conversionLabelHeight, conversionValueLabelWidth, conversionValueLabelHeight);
        
        conversionUnitsLabel.setBounds (conversionValueLabel.getX() + conversionValueLabelWidth + spaceWidth, copy.getY() + 3 * conversionLabelHeight, conversionUnitsLabelWidth, conversionValueLabelHeight);
    }
}

void MusicCalculatorAudioProcessorEditor::buttonClicked (Button *button)
{
    if (button->getName() == copy.getName())
    {
        conversionValueLabel.showEditor();
        conversionValueLabel.getCurrentTextEditor()->selectAll();
        conversionValueLabel.getCurrentTextEditor()->copyToClipboard();
        conversionValueLabel.hideEditor (false);

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
    repaint();
}

void MusicCalculatorAudioProcessorEditor::timerCallback()
{
    tempoSyncButton.setEnabled (processor.isTempoInformationAvailable());
    midiSyncButton.setEnabled( ! MidiInput::getDevices().isEmpty() );
    
    if (tempoToggle.getToggleState() && tempoSyncButton.getToggleState())
        tempoSpinner.setSpinnersText (String (processor.tempo), sendNotification);
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
        noteSpinner.setSpinnersText (Spinner::getNote (note) + String(octave), sendNotification);
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
    
    float fontSize = button.getHeight() * 0.75f;
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
