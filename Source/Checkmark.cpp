//
//  Checkmark.cpp
//  MusicCalculator
//
//  Created by London Oliver on 3/28/17.
//
//

#include "Checkmark.h"

Checkmark::Checkmark()
{
}

void Checkmark::paint (Graphics &g)
{
    float w = getWidth();
    float h = getHeight() * 0.9;
    Path tick;
    tick.startNewSubPath (w/4, h/2);
    tick.lineTo (w/2, h);
    tick.lineTo (h, 0.0f);
    
    g.setColour (colour);
    g.strokePath (tick, PathStrokeType (w/10));
}

void Checkmark::setColour (Colour c)
{
    this->colour = c;
}
