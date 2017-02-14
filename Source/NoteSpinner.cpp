//
//  NoteSpinner.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/13/17.
//
//

#include "NoteSpinner.hpp"

NoteSpinner::NoteSpinner()
{
    addAndMakeVisible(l1);
    addAndMakeVisible(l2);
    setFont(Font("Roboto", 20, Font::plain));
    l1.setText("C", sendNotification);
    l2.setText("3", sendNotification);
    l1.setType(2);
    l2.setType(3);
}

void NoteSpinner::resized()
{
    int letterWidth = 60;
    l1.setBounds(0, 0, letterWidth, letterWidth);
    l2.setBounds(letterWidth, 0, letterWidth, letterWidth);
}

void NoteSpinner::setFont (Font font)
{
    f = font;
    l1.setFont(f);
    l2.setFont(f);
}

Font NoteSpinner::getFont()
{
    return f;
}
