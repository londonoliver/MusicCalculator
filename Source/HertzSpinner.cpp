//
//  HertzSpinner.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/16/17.
//
//

#ifndef HertzSpinner_hpp
#define HertzSpinner_hpp
#include "../JuceLibraryCode/JuceHeader.h"
#include "Spinner.cpp"
#include <iostream>
#include <regex>
#endif



using namespace std;

class NoteSpinner : public Component, private LabelListener
{
    int width;
    int height;
    
    Font font;
    
    Spinner s1 {Spinner::SpinnerType::NUMBER, 0, 11};
};
