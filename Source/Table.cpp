//
//  TableComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/5/17.
//
//
#include "Table.h"
#include <iostream>

using namespace std;


Table::Table()   : font (14.0f)
{
    
    
    width = 200;
    height = 300;
    
    header = new CustomTableHeader();
    header->setTable(this);
    table.setHeader(header);
    
    numTempoRows = 8;
    numNoteRows = 1;
    numHertzRows = 1;
    
    
    table.getHeader().addColumn(columnOneName, 1, width/2);
    table.getHeader().addColumn(columnTwoName, 2, width/2);
    
    addAndMakeVisible (table);
    table.setModel (this);
    
    setTableType();
    
    table.setRowHeight (25);
}




int Table::getNumRows()
{
    return  (display)   ?
    
    (display->displayType == Display::DisplayType::TEMPO)   ?   numTempoRows
    
    :
    
    ((display->displayType == Display::DisplayType::NOTE)   ?   numNoteRows
     
     :   numHertzRows)
    
    :
    
    0;
}

void Table::setNumRows (int i)
{

}



void Table::paintRowBackground (Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected)
{
    if (rowNumber % 2)
        g.fillAll (Colour (0xffeeeeee));
}




void Table::paintCell (Graphics& g, int rowNumber, int columnId,
                       int width, int height, bool /*rowIsSelected*/)
{
}




void Table::sortOrderChanged (int newSortColumnId, bool isForwards)
{
}




Component* Table::refreshComponentForCell (int rowNumber, int columnId, bool /*isRowSelected*/,
                                           Component* existingComponentToUpdate)
{
    EditableTextCustomComponent* textLabel = static_cast<EditableTextCustomComponent*> (existingComponentToUpdate);
    
    if (textLabel == nullptr)
        textLabel = new EditableTextCustomComponent (*this);
    
    if (columnId == 1 && display->displayType == Display::DisplayType::TEMPO)
        textLabel->removeChildComponent (textLabel->button);
    else
    {
        textLabel->addAndMakeVisible (textLabel->button);
        textLabel->button->setVisible (false);
    }
    
    
    textLabel->label.setText (
                       
                       (display)    ?
                       
                       (display->displayType == Display::DisplayType::TEMPO)   ?   setTempoTable (rowNumber, columnId)
                       
                       :
                       
                       ((display->displayType == Display::DisplayType::NOTE)   ?   setNoteTable (rowNumber, columnId)
                        
                        :   setHertzTable (rowNumber, columnId))
                       
                       :
                       
                       "", sendNotification
                       );
    
    return textLabel;
}




int Table::getColumnAutoSizeWidth (int columnId)
{
    return width/2;
}




String Table::getText (const int columnNumber, const int rowNumber) const
{
    return "";
}




void Table::setText (const int columnNumber, const int rowNumber, const String& newText)
{
    table.updateContent();
}




void Table::setDisplay (Display *display)
{
    this->display = display;
}



double Table::getTempo()
{
    return (display) ? display->getTempo() : 0;
}




int Table::getNote()
{
    return (display) ? display->getNote() : 0;
}




int Table::getOctave()
{
    return (display) ? display->getOctave() : 0;
}




double Table::noteToHz(int note, int octave)
{
    note -= 9;
    octave -= 4;
    return semitoneShift(440, (float)note + (float)(octave * 12));
}




double Table::semitoneShift(double value, double amount)
{
    return value / pow (2, amount / -12);
}




double Table::getWholeNoteMs()
{
    return (1000.0 / (getTempo() / 60.0)) * 4.0 *
    ((delayType == DelayType::DOTTED) ? (3.0 / 2.0) :
     ((delayType == DelayType::TRIPLET) ? (2.0 / 3.0) : 1));
}




double Table::getWholeNoteHz()
{
    return (getTempo() / 60.0) / 4.0 /
    ((delayType == DelayType::DOTTED) ? (3.0 / 2.0) :
     ((delayType == DelayType::TRIPLET) ? (2.0 / 3.0) : 1));
}




String Table::setTempoTable (int rowNumber, int columnId)
{
    return  (columnId == 1)     ?   "1/"                                            +
    String (pow (2, rowNumber))                     +
    
    ((delayType == DelayType::DOTTED)   ?   "."
     
     :
     
     ((delayType == DelayType::TRIPLET)  ?   "T"
      
      :   ""))
    
    :
    
    ((columnId == 2)    ?   (tempoConversion == TempoConversion::MS)    ?   String (getWholeNoteMs() / pow (2, rowNumber))
     
     :   String (getWholeNoteHz() * pow (2, rowNumber))
     
     :   "");
}




String Table::setNoteTable (int rowNumber, int columnId)
{
    return  (columnId == 1)     ?   String (noteToHz (getNote(), getOctave()))
    
    :   "";
}




String Table::setHertzTable (int rowNumber, int columnId)
{
    return  "";
}



void Table::setTableType ()
{
    table.updateContent();
    
    if (display)
    {
        if (display->displayType == Display::DisplayType::TEMPO)
        {
            table.getHeader().setColumnVisible(1, true);
            table.getHeader().setColumnVisible(2, true);
            
            table.getHeader().setColumnWidth(1, width/2);
            table.getHeader().setColumnWidth(2, width/2);
            
            columnOneName = (delayType == DelayType::NORMAL)    ?   "Note"
            :
            ((delayType == DelayType::DOTTED)   ?   "Note"
             :   "Note");
            
            columnTwoName = (tempoConversion == TempoConversion::MS)    ?   "Ms"
            :   "Hz";
        }
        else if (display->displayType == Display::DisplayType::NOTE)
        {
            table.getHeader().setColumnVisible(1, true);
            table.getHeader().setColumnVisible(2, false);
            
            table.getHeader().setColumnWidth(1, width);
            
            columnOneName = "Hz";
            
            
        }
        else
        {
            table.getHeader().setColumnVisible(1, true);
            table.getHeader().setColumnVisible(2, false);
            
            table.getHeader().setColumnWidth(1, width);
        }
    }
    table.getHeader().resized();
}




void Table::setMilliseconds()
{
}




TableListBox* Table::getTable()
{
    return &table;
}




void Table::resized()
{
    header->setBounds(0, 0, width, 40);
    
    table.setBounds (0, header->getY(), width, height);
    table.setBoundsInset (BorderSize<int> (0));
    
    if (getParentComponent())
        getParentComponent()->resized();
}






//====================================================================
/*
 *  EditableCustomTextComponent
 */
//====================================================================



Table::EditableTextCustomComponent::EditableTextCustomComponent (Table& td)  : owner (td)
{
    button = new DrawableButton ("Button 1", DrawableButton::ImageFitted);
    
    ScopedPointer<XmlElement> svg (XmlDocument::parse(BinaryData::clipboard_svg));
    ScopedPointer<Drawable> normal;
    ScopedPointer<Drawable> over;
    ScopedPointer<Drawable> down;
    
    if (svg != nullptr)
    {
        normal = Drawable::createFromSVG (*svg);
        normal->replaceColour(Colours::black, Colours::grey);
        
        over = Drawable::createFromSVG (*svg);
        over->replaceColour(Colours::black, Colours::grey.darker());
        
        down = Drawable::createFromSVG (*svg);
        down->replaceColour(Colours::black, Colours::grey.darker().darker());
        
        button->setImages(normal, over, down);
    }
    
    
    
    label.setEditable (false);
    label.setColour (Label::textColourId, Colours::black);
    
    copied.setEditable (false);
    copied.setColour (Label::backgroundColourId, Colours::black.withAlpha(0.0f));
    copied.setText ("Copied", dontSendNotification);
    copied.setJustificationType (Justification::centredLeft);
    
    addAndMakeVisible (label);
    addAndMakeVisible (button);
    addAndMakeVisible (copied);
    
    copied.setVisible (false);
    
    button->setVisible (false);
    button->addListener (this);
    
    addMouseListener(this, true);
    
    Desktop::getInstance().getAnimator().addChangeListener (this);
    
}

Table::EditableTextCustomComponent::~EditableTextCustomComponent()
{
    removeMouseListener (this);
    button->removeListener (this);
    Desktop::getInstance().getAnimator().removeChangeListener (this);
}


void paint()
{
}

void Table::EditableTextCustomComponent::buttonClicked (Button *button)
{
    label.showEditor();
    label.getCurrentTextEditor()->selectAll();
    label.getCurrentTextEditor()->copyToClipboard();
    label.hideEditor (false);
    
    label.setVisible (false);
    
    copied.setBounds(-getWidth(), 0, getWidth(), getHeight());
    copied.setVisible (true);
    button->setVisible (false);
    fadeout = true;
    Desktop::getInstance().getAnimator().animateComponent (&copied, Rectangle<int> (0, 0, getWidth(), getHeight()), 0.7f, 250, true, 1.0, 1.0);
}

void Table::EditableTextCustomComponent::changeListenerCallback (ChangeBroadcaster *source)
{
    if (source == &Desktop::getInstance().getAnimator())
    {
        if ( ! Desktop::getInstance().getAnimator().isAnimating(&copied) )
        {
            Desktop::getInstance().getAnimator().fadeOut (&copied, 1000);
            fadeout = !fadeout;
            
            if (fadeout)
            {
                label.setVisible (true);
                fadeout = !fadeout;
            }
        }
    }
}


void Table::EditableTextCustomComponent::resized()
{
    label.setBoundsInset (BorderSize<int> (0));
    label.setBounds (0, (getHeight() - label.getFont().getHeight())/2, 100, label.getFont().getHeight());
    button->setBounds (getWidth() - 25, (getHeight() - 20)/2, 20, 20);
}


void Table::EditableTextCustomComponent::mouseEnter (const MouseEvent &event)
{
    if (! Desktop::getInstance().getAnimator().isAnimating(&copied) )
        button->setVisible (true);
}


void Table::EditableTextCustomComponent::mouseExit (const MouseEvent &event)
{
    button->setVisible (false);
}


void Table::EditableTextCustomComponent::mouseDown (const MouseEvent& event)
{
    label.mouseDown (event);
}





//====================================================================
/*
 *  CustomTableHeader
 */
//====================================================================







Table::CustomTableHeader::CustomTableHeader()
{
    addAndMakeVisible (b1);
    addAndMakeVisible (b2);
    b1.setName ("b1");
    b2.setName ("b2");
    b1.addListener (this);
    b2.addListener (this);
    b1.setConnectedEdges (1|2|4|8);
    b2.setConnectedEdges (1|2|4|8);
    b1.setColour(TextButton::ColourIds::buttonColourId, Colour (0xffeeeeee));
    b2.setColour(TextButton::ColourIds::buttonColourId, Colour (0xffeeeeee));
    setLookAndFeel (this);
}

Table::CustomTableHeader::~CustomTableHeader()
{
    b1.removeListener(this);
    b2.removeListener(this);
}

void Table::CustomTableHeader::paint (Graphics& g)
{
}


void Table::CustomTableHeader::resized()
{
    if (table)
    {
        b1.setButtonText (table->columnOneName);
        b2.setButtonText (table->columnTwoName);
        
        if (table->display)
        {
            if (table->display->displayType == Display::DisplayType::TEMPO)
            {
                b1.setEnabled (true);
            }
            else
            {
                b1.setEnabled (false);
            }
        }
    }
    
    b1.setBounds(0, 0, getColumnWidth(1), getHeight());
    b2.setBounds(getColumnWidth(1), 0, getColumnWidth(2), getHeight());
}


void Table::CustomTableHeader::setTable (Table* t)
{
    table = t;
}


void Table::CustomTableHeader::buttonClicked (Button *button)
{
    if (table && table->display->displayType == Display::DisplayType::TEMPO)
    {
        if (button->getName() == b1.getName())
        {
            table->delayType =  (table->delayType == DelayType::NORMAL)     ?   DelayType::DOTTED
            :
            ((table->delayType == DelayType::DOTTED)    ?   DelayType::TRIPLET
             :   DelayType::NORMAL);
            
            
            table->setTableType();
            
            b1.setButtonText(table->columnOneName);
            
            table->table.updateContent();
            
        }
        else if (button->getName() == b2.getName())
        {
            table->tempoConversion = (table->tempoConversion == TempoConversion::MS)    ?   TempoConversion::HZ
            :   TempoConversion::MS;
            
            
            table->setTableType();
            
            b2.setButtonText(table->columnTwoName);
            
            table->table.updateContent();
        }
        
        table->resized();
    }
}

void Table::CustomTableHeader::drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown)
{
    /*Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                       .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));*/
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
                                     ! (flatOnLeft  || flatOnTop),
                                     ! (flatOnRight || flatOnTop),
                                     ! (flatOnLeft  || flatOnBottom),
                                     ! (flatOnRight || flatOnBottom));
        
        drawButtonShape (g, outline, baseColour, height);
        
    }
}

void Table::CustomTableHeader::drawButtonShape (Graphics& g, const Path& outline, Colour baseColour, float height)
{
    //const float mainBrightness = baseColour.getBrightness();
    //const float mainAlpha = baseColour.getFloatAlpha();
    
    /*g.setGradientFill (ColourGradient (baseColour.brighter (0.2f), 0.0f, 0.0f,
                                       baseColour.darker (0.25f), 0.0f, height, false));*/
    g.setColour (baseColour);
    g.fillPath (outline);
    
    //g.setColour (Colours::white.withAlpha (0.4f * mainAlpha * mainBrightness * mainBrightness));
    /*g.strokePath (outline, PathStrokeType (1.0f), AffineTransform::translation (0.0f, 1.0f)
                  .scaled (1.0f, (height - 1.6f) / height));*/
    
    //g.setColour (Colours::black.withAlpha (0.4f * mainAlpha));
    g.setColour (Colour (baseColour));
    g.strokePath (outline, PathStrokeType (1.0f));
}

void Table::CustomTableHeader::drawButtonText (Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/)
{
    Font font (getTextButtonFont (button, button.getHeight()));
    g.setFont (font);
    //g.setFont (Font ("Roboto", 15, Font::plain));
    /*g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                    : TextButton::textColourOffId)
                 .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));*/
    g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                    : TextButton::textColourOffId)
                 .withMultipliedAlpha (1.0f));
    
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

