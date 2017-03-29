//
//  Fraction.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/18/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "Spinner.h"

using namespace std;

class Fraction : public Component, public LabelListener, public TextEditorListener
{
public:
    Spinner numerator, denominator;
    Label numEd, denEd;
    Colour colour;
    
    Fraction() :    numerator {Spinner::SpinnerType::ARRAY, Array<int> {1, 2, 3, 4, 5, 6, 7, 8} },
                    denominator {Spinner::SpinnerType::ARRAY, Array<int> {1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192} }
    {
        numerator.setText(0, dontSendNotification);
        numerator.setEditable (false, true, true);
        numerator.setName ("numerator");
        addAndMakeVisible (numerator);
        
        denominator.setText(3, dontSendNotification);
        denominator.setEditable (false, true, true);
        denominator.setName ("denominator");
        addAndMakeVisible (denominator);
        
        numEd.setName ("numEd");
        numEd.addListener (this);
        numEd.setColour (TextEditor::ColourIds::focusedOutlineColourId, Colours::white.withAlpha(0.0f));
        numEd.setColour (TextEditor::ColourIds::highlightColourId, Colours::white.withAlpha(0.5f));
        addChildComponent (numEd);
        
        denEd.setName ("denEd");
        denEd.addListener (this);
        denEd.setColour (TextEditor::ColourIds::focusedOutlineColourId, Colours::white.withAlpha(0.0f));
        denEd.setColour (TextEditor::ColourIds::highlightColourId, Colours::white.withAlpha(0.5f));
        addChildComponent (denEd);
        
        colour = Colours::black;
    }
    
    ~Fraction()
    {
        numEd.removeListener (this);
        denEd.removeListener (this);
    }
    
    void paint (Graphics &g) override
    {
        g.fillAll (Colours::white.withAlpha (0.0f));
        g.setColour (colour);
        int lineWidth = numerator.getFont().getStringWidth("128");
        int lineThickness = getHeight()/42;
        //g.drawHorizontalLine(getHeight()/2, (getWidth() - lineWidth)/2, (getWidth() + lineWidth)/2);
        g.fillRect((getWidth() - lineWidth)/2, (getHeight() - lineThickness)/2, lineWidth, lineThickness);
    }
    
    void resized() override
    {
        numerator.setFont (Font (getHeight()/2.0f));
        denominator.setFont (Font (getHeight()/2.0f));
        numEd.setFont (Font (getHeight()/2.0f));
        denEd.setFont (Font (getHeight()/2.0f));
        
        int width = getWidth();
        int height = getHeight();
        int numWidth = numerator.getFont().getStringWidth(numerator.getText()) * 1.1;
        int numHeight = height/2;
        int denWidth = denominator.getFont().getStringWidth(denominator.getText()) * 1.1;
        int denHeight = height/2;
        numerator.setBounds((width - numWidth)/2, 0, numWidth, numHeight);
        denominator.setBounds((width - denWidth)/2, numHeight, denWidth, denHeight);
        if (numEd.isBeingEdited())
        {
            int edWidth = numEd.getCurrentTextEditor()->getFont().getStringWidth(numEd.getCurrentTextEditor()->getText()) * 1.1;
            numEd.setBounds((width - edWidth)/2, 0, edWidth, numHeight);
        }
        else
        {
            numEd.setBounds((width - numWidth)/2, 0, numWidth, numHeight);
        }
        if (denEd.isBeingEdited())
        {
            int edWidth = denEd.getCurrentTextEditor()->getFont().getStringWidth(denEd.getCurrentTextEditor()->getText()) * 1.1;
            denEd.setBounds((width - edWidth)/2, numHeight, edWidth, denHeight);
        }
        else
        {
            denEd.setBounds((width - denWidth)/2, numHeight, denWidth, denHeight);
        }
    }
    
    void setColour (Colour c)
    {
        this->colour = c;
        
        numerator.setColour (Label::ColourIds::textColourId, colour);
        
        denominator.setColour (Label::ColourIds::textColourId, colour);
        
        numEd.setColour (Label::ColourIds::textWhenEditingColourId, colour);
        numEd.setColour (CaretComponent::ColourIds::caretColourId, colour);
        
        denEd.setColour (Label::ColourIds::textWhenEditingColourId, colour);
        denEd.setColour (CaretComponent::ColourIds::caretColourId, colour);
    }
    
    void attachListener (LabelListener *l)
    {
        numerator.addListener (l);
        denominator.addListener (l);
    }
    
    void detachListener (LabelListener *l)
    {
        numerator.removeListener (l);
        denominator.removeListener (l);
    }
    
    int getNumerator()      {   return numerator.getTextValue().getValue();     }
    int getDenominator()    {   return denominator.getTextValue().getValue();   }
    
    void setFraction (int numerator, int denominator)
    {
        this->numerator.setText (this->numerator.arr.indexOf (numerator), dontSendNotification);
        this->denominator.setText (this->denominator.arr.indexOf (denominator), dontSendNotification);
    }
    
    double getFraction()
    {
        return (double) numerator.getTextValue().getValue() / (double) denominator.getTextValue().getValue();
    }
    
    void mouseDoubleClick (const MouseEvent &e) override
    {
        if (e.originalComponent->getName() == numerator.getName())
        {
            numerator.setVisible (false);
            
            numEd.setVisible (true);
            numEd.setText(numerator.getText(), dontSendNotification);
            numEd.showEditor();
        }
        else if (e.originalComponent->getName() == denominator.getName())
        {
            denominator.setVisible (false);
            
            denEd.setVisible (true);
            denEd.setText(denominator.getText(), dontSendNotification);
            denEd.showEditor();
        }
    }
    
    void editorHidden (Label *label, TextEditor &editor) override
    {
        if (editor.getName() == numEd.getName())
        {
            numEd.setVisible (false);
            
            numerator.setVisible(true);
            
            int val = numerator.arr.indexOf(int (numEd.getTextValue().getValue()));
            if (val != -1)
                numerator.setText(val, sendNotification);
        }
        else
        {
            denEd.setVisible (false);
            
            denominator.setVisible(true);
            
            int val = denominator.arr.indexOf(int (denEd.getTextValue().getValue()));
            if (val != -1)
                denominator.setText(val, sendNotification);
        }
        
        editor.removeListener (this);
    }
    
    void textEditorTextChanged (TextEditor &ed) override
    {
        resized();
    }
    
    void editorShown (Label *, TextEditor &ed) override
    {
        ed.addListener (this);
        ed.setBorder (BorderSize<int> (0));
        ed.setInputRestrictions (3);
    }
    
    void labelTextChanged (Label *labelThatHasChanged) override
    {
        resized();
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fraction)
};
