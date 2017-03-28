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
    setSize (300, 350);
    
    {
        toggleLabel.setText("Conversion Type:", dontSendNotification);
        toggleLabel.setBorderSize (BorderSize<int> (0));
        addAndMakeVisible (toggleLabel);
        
        tempoToggle.setButtonText("Tempo");
        tempoToggle.setRadioGroupId (1);
        tempoToggle.addListener (this);
        tempoToggle.setToggleState (processor.mode, dontSendNotification);
        tempoToggle.setWantsKeyboardFocus (false);
        addAndMakeVisible (tempoToggle);
        
        noteToggle.setButtonText("Note");
        noteToggle.setRadioGroupId (1);
        noteToggle.addListener (this);
        noteToggle.setToggleState (!processor.mode, dontSendNotification);
        noteToggle.setWantsKeyboardFocus (false);
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
    }
    
    lastInputIndex = 0;
    setMidiInput (0);
    keyboardState.addListener (this);
    startTimer (100);
    
    setConversion();
    
    setResizable (true, true);
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
    g.fillAll (Colours::red);
    g.setColour (Colours::black);
    g.setFont (15.0f);
}

void MusicCalculatorAudioProcessorEditor::resized()
{
    width = getWidth();
    height = getHeight();
    
    int margin = (3.0 / 40.0) * height;
    int smallPanelHeight = (1.0 / 10.0) * height;
    int bigPanelHeight = (2.0 / 10.0) * height;
    
    {
        int toggleWidth = 0.2 * width;
        int toggleLabelWidth = toggleLabel.getFont().getStringWidth (toggleLabel.getText());
        toggleLabel.setBounds(toggleWidth/4, 0, toggleLabelWidth, smallPanelHeight);
        tempoToggle.setBounds (toggleLabel.getX() + toggleLabel.getWidth(), 0, toggleWidth, smallPanelHeight);
        noteToggle.setBounds (tempoToggle.getX() + tempoToggle.getWidth(), 0, toggleWidth, smallPanelHeight);
    }
    {
        int displayLabelHeight = (1.0 / 5.0) * bigPanelHeight;
        displayLabel.setFont (Font (displayLabelHeight));
        int displayLabelWidth =  displayLabel.getFont().getStringWidth(displayLabel.getText());
        
        displayLabel.setBounds ((width - displayLabelWidth)/2, smallPanelHeight + margin/2, displayLabelWidth, displayLabelHeight);
    
        int displayHeight = (3.0 / 5.0) * bigPanelHeight;
        
        tempoSpinner.setFontHeight ((float) displayHeight);
        tempoSpinner.setBounds ((width - tempoSpinner.width)/2, displayLabel.getY() + 2 * displayLabel.getHeight(), tempoSpinner.width, displayHeight);
        
        noteSpinner.setFontHeight ((float) displayHeight);
        noteSpinner.setBounds ((width - noteSpinner.width)/2, displayLabel.getY() + 2 * displayLabel.getHeight(), noteSpinner.width, displayHeight);
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
