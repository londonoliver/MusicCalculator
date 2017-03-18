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
    
    bgColour = Colours::white;
    
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
    g.fillAll (bgColour.withAlpha(0.0f));
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
    button->setVisible (false);
    fadeout = true;
    Desktop::getInstance().getAnimator().animateComponent (&copied, Rectangle<int> (0, 0, getWidth(), getHeight()), 0.7f, 250, true, 1.0, 1.0);
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
    label.setBorderSize (BorderSize<int> (0));
    button->setBounds (getWidth() - buttonHeight, (rowHeight - buttonHeight)/2, buttonHeight, buttonHeight);
    label.setBounds ((0.025 * getWidth()), (getHeight() - label.getFont().getHeight())/2, button->getX(), label.getFont().getHeight());
}


void CustomTableCell::mouseEnter (const MouseEvent &event)
{
    if (! Desktop::getInstance().getAnimator().isAnimating(&copied) )
        button->setVisible (true);
}


void CustomTableCell::mouseExit (const MouseEvent &event)
{
    button->setVisible (false);
}


void CustomTableCell::mouseDown (const MouseEvent& event)
{
    label.mouseDown (event);
}
