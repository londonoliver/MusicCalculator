//
//  CustomTableCell.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/3/17.
//
//

#include "CustomTableCell.h"

CustomTableCell::CustomTableCell()
{
    button = new DrawableButton ("Button 1", DrawableButton::ImageFitted);
    
    ScopedPointer<XmlElement> svg (XmlDocument::parse(BinaryData::clipboard_svg));
    ScopedPointer<Drawable> normal;
    ScopedPointer<Drawable> over;
    ScopedPointer<Drawable> down;
    
    if (svg != nullptr)
    {
        normal = Drawable::createFromSVG (*svg);
        normal->replaceColour(Colours::black, Colours::black);
        
        over = Drawable::createFromSVG (*svg);
        over->replaceColour(Colours::black, Colours::grey.darker());
        
        down = Drawable::createFromSVG (*svg);
        down->replaceColour(Colours::black, Colours::grey.darker().darker());
        
        button->setImages(normal, over, down);
    }
    
    
    
    label.setEditable (false);
    label.setColour (Label::textColourId, Colours::black);
    
    copied.setEditable (false);
    copied.setText ("Copied", dontSendNotification);
    copied.setJustificationType (Justification::centredLeft);
    
    tip.setButtonText ("Copy");
    
    addAndMakeVisible (label);
    //addChildComponent (button);
    addAndMakeVisible (copied);
    addAndMakeVisible (units);
    addAndMakeVisible (tip);
    
    label.setBorderSize (BorderSize<int> (0));
    units.setBorderSize (BorderSize<int> (0));
    copied.setBorderSize (BorderSize<int> (0));
    
    copied.setVisible (false);
    
    button->setVisible (false);
    button->addListener (this);
    tip.addListener (this);
    
    addMouseListener(this, true);
    
    Desktop::getInstance().getAnimator().addChangeListener (this);
    
    bgColour = Colours::white.withAlpha (0.0f);
    
}

CustomTableCell::~CustomTableCell()
{
    removeMouseListener (this);
    button->removeListener (this);
    Desktop::getInstance().getAnimator().removeChangeListener (this);
}
    
void CustomTableCell::setBackgroundColor (Colour colour)
{
    bgColour = colour;
    repaint();
}


void CustomTableCell::paint (Graphics &g)
{
    g.fillAll (bgColour);
}

void CustomTableCell::buttonClicked (Button *button)
{
    label.showEditor();
    label.getCurrentTextEditor()->selectAll();
    label.getCurrentTextEditor()->copyToClipboard();
    label.hideEditor (false);
    
    label.setVisible (false);
    
    copied.setBounds(-getWidth(), 0, getWidth(), getHeight());
    copied.setVisible (true);
    label.setVisible (false);
    fadeout = true;
    Desktop::getInstance().getAnimator().fadeIn(&label, 100);
}

void CustomTableCell::changeListenerCallback (ChangeBroadcaster *source)
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
                if (isMouseOver())
                    button->setVisible(true);
                fadeout = !fadeout;
            }
        }
    }
}


void CustomTableCell::resized()
{
    int rowHeight = getHeight();
    int fontHeight = 0.56f * rowHeight;
    int buttonHeight = 0.7 * rowHeight;
    Font font ("Roboto", fontHeight, Font::plain);
    label.setFont (font);
    copied.setFont (font);
    units.setFont (font);
    int labelWidth = label.getFont().getStringWidth(label.getText());
    int unitsWidth = units.getFont().getStringWidth(units.getText());
    int tabWidth = label.getFont().getStringWidth(" ");
    label.setBounds ((getWidth() - labelWidth - unitsWidth - tabWidth)/2, (getHeight() - fontHeight)/2, labelWidth, fontHeight);
    units.setBounds (label.getX() + labelWidth + tabWidth, (getHeight() - fontHeight)/2, unitsWidth, fontHeight);
    //button->setBounds (units.getX() + unitsWidth + tabWidth, (rowHeight - buttonHeight)/2, buttonHeight, buttonHeight);
    tip.setBounds(units.getX() + unitsWidth + tabWidth, (getHeight() - fontHeight)/2, 40, fontHeight);
}


void CustomTableCell::mouseEnter (const MouseEvent &event)
{
    if (! Desktop::getInstance().getAnimator().isAnimating(&copied) )
    {
        button->setVisible (true);
    }
}


void CustomTableCell::mouseExit (const MouseEvent &event)
{
    button->setVisible (false);
}


void CustomTableCell::mouseDown (const MouseEvent& event)
{
    label.mouseDown (event);
}
