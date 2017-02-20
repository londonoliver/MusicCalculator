//
//  Display.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/19/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "Spinner.h"
#include <regex>

using namespace std;

class Display : public Component, public LabelListener
{
    
    
    
public:
    
    
    
    enum class DisplayType {TEMPO, NOTE, HERTZ};
    
    DisplayType displayType;
    
    int width;
    int height;
    
    Font font;
    
    Spinner t1;
    Spinner t2;
    Spinner t3;
    Spinner t4;
    Spinner t5;
    Spinner t6;
    
    Spinner n1;
    Spinner n2;
    
    Spinner h1;
    Spinner h2;
    Spinner h3;
    Spinner h4;
    
    Label ed;
    
    int t1Width;
    int t2Width;
    int t3Width;
    int t4Width;
    int t5Width;
    int t6Width;
    
    int n1Width;
    int n2Width;
    
    int h1Width;
    int h2Width;
    int h3Width;
    int h4Width;
    
    
    
    
    Display() : t1 {Spinner::SpinnerType::NUMBER, 5, 990},
                t2 {Spinner::SpinnerType::PERIOD, 0, 0},
                t3 {Spinner::SpinnerType::NUMBER, 0, 9},
                t4 {Spinner::SpinnerType::NUMBER, 0, 9},
                t5 {Spinner::SpinnerType::NUMBER, 0, 9},
                t6 {Spinner::SpinnerType::NUMBER, 0, 9},
    
                n1 {Spinner::SpinnerType::NOTE, 0, 11},
                n2 {Spinner::SpinnerType::NUMBER, 0, 8},
    
                h1 {Spinner::SpinnerType::NUMBER, 0, 20000},
                h2 {Spinner::SpinnerType::PERIOD, 0, 0},
                h3 {Spinner::SpinnerType::NUMBER, 0, 9},
                h4 {Spinner::SpinnerType::NUMBER, 0, 9}
    {
        font = Font ("Roboto", 50, Font::plain);
        
        t1.setText (120);
        t2.Label::setText (".", sendNotification);
        t3.setText (0);
        t4.setText (0);
        t5.setText (0);
        t6.setText (0);
        
        n1.setText (0);
        n2.setText (3);
        
        h1.setText (440);
        h2.Label::setText (".", sendNotification);
        h3.setText (0);
        h4.setText (0);
        
        fitBounds();
        
        addAndMakeVisible (t1);
        addAndMakeVisible (t2);
        addAndMakeVisible (t3);
        addAndMakeVisible (t4);
        addAndMakeVisible (t5);
        addAndMakeVisible (t6);
        
        addAndMakeVisible (n1);
        addAndMakeVisible (n2);
        
        addAndMakeVisible (h1);
        addAndMakeVisible (h2);
        addAndMakeVisible (h3);
        addAndMakeVisible (h4);
        
        attachListener (this);
        
        setType (DisplayType::TEMPO);
        
        setSpinnersVisible (true);
        
        ed.setFont (font);
        ed.setBorderSize (BorderSize<int> (0));
        addAndMakeVisible (ed);
        ed.setVisible (false);
        ed.addListener(this);
    }
    
    
    
    
    String toString()
    {
        return  (displayType == DisplayType::TEMPO)     ?       t1.getTextValue().toString() +
                                                                "." +
                                                                t3.getTextValue().toString() +
                                                                t4.getTextValue().toString() +
                                                                t5.getTextValue().toString() +
                                                                t6.getTextValue().toString()
        
                                                        :
        
                ((displayType == DisplayType::NOTE)     ?       n1.getTextValue().toString() +
                                                                n2.getTextValue().toString()
                   
                                                        :
        
                                                                h1.getTextValue().toString() +
                                                                "." +
                                                                h3.getTextValue().toString() +
                                                                h4.getTextValue().toString());
    }
    
    
    
    
    double getTempo()
    {
        return  (double) t1.getTextValue().getValue()           +
                (double) t3.getTextValue().getValue() * 0.1     +
                (double) t4.getTextValue().getValue() * 0.01    +
                (double) t5.getTextValue().getValue() * 0.001   +
                (double) t6.getTextValue().getValue() * 0.0001;
    }
    
    
    
    
    void fitBounds()
    {
        t1Width = font.getStringWidth (t1.getTextValue().toString());
        t2Width = font.getStringWidth (t2.getTextValue().toString());
        t3Width = font.getStringWidth (t3.getTextValue().toString());
        t4Width = font.getStringWidth (t4.getTextValue().toString());
        t5Width = font.getStringWidth (t5.getTextValue().toString());
        t6Width = font.getStringWidth (t6.getTextValue().toString());
        
        n1Width = font.getStringWidth (n1.getTextValue().toString());
        n2Width = font.getStringWidth (n2.getTextValue().toString());
        
        h1Width = font.getStringWidth (h1.getTextValue().toString());
        h2Width = font.getStringWidth (h2.getTextValue().toString());
        h3Width = font.getStringWidth (h3.getTextValue().toString());
        h4Width = font.getStringWidth (h4.getTextValue().toString());
        
        height = font.getHeight();
        width = (displayType == DisplayType::TEMPO)     ?       t1Width +
                                                                t2Width +
                                                                t3Width +
                                                                t4Width +
                                                                t5Width +
                                                                t6Width
        
                                                        :
        
                ((displayType == DisplayType::NOTE)     ?       n1Width +
                                                                n2Width
                 
                                                        :
                 
                                                                h1Width +
                                                                h2Width +
                                                                h3Width +
                                                                h4Width);
        
        setBounds       (0                                                  , 0,    width,      height);
        
        t1.setBounds    (0                                                  , 0,    t1Width,    height);
        t2.setBounds    (t1Width                                            , 0,    t2Width,    height);
        t3.setBounds    (t1Width + t2Width                                  , 0,    t3Width,    height);
        t4.setBounds    (t1Width + t2Width + t3Width                        , 0,    t4Width,    height);
        t5.setBounds    (t1Width + t2Width + t3Width + t4Width              , 0,    t5Width,    height);
        t6.setBounds    (t1Width + t2Width + t3Width + t4Width + t5Width    , 0,    t6Width,    height);
        
        n1.setBounds    (0                                                  , 0,    n1Width,    height);
        n2.setBounds    (n1Width                                            , 0,    n2Width,    height);
        
        h1.setBounds    (0                                                  , 0,    h1Width,    height);
        h2.setBounds    (h1Width                                            , 0,    h2Width,    height);
        h3.setBounds    (h1Width + h2Width                                  , 0,    h3Width,    height);
        h4.setBounds    (h1Width + h2Width + h3Width                        , 0,    h4Width,    height);
        
        ed.setBounds    (0                                                  , 0,    width,      height);
    }
    
    
    
    
    void setDisplay (String val)
    {
            int len = val.length();
            
            int i = 0;
        
            if (displayType == DisplayType::TEMPO)
            {
                    while (i < len && val[i] != '.') i++;
                    
                    int i1 = stoi (val.substring (0, i).toStdString());
                    
                    if (i1 >= t1.min)
                    {
                        t1.setText (i1);
                        t3.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
                        t4.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
                        t5.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
                        t6.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
                    }
            }
            else if (displayType == DisplayType::NOTE)
            {
                    String str1;
                    String str2;
                    
                    str2 = val.substring(len - 1, len);

                    if (regex_match (str2.toStdString(), regex ("^[0-8]$")))
                    {
                        str1 = val.substring(0, len - 1);
                        if (noteIndex(str1) != -1)
                        {
                            n1.setText(noteIndex (str1));
                            n2.setText (stoi (str2.toStdString()));
                        }
                    }
                    else
                    {
                        str1 = val.substring(0, len);
                        if (noteIndex (str1) != -1)
                            n1.setText(noteIndex (str1));
                    }
            }
            else
            {
                    while (i < len && val[i] != '.') i++;

                    h1.setText ((i != 0) ? stoi (val.substring (0, i).toStdString()) : 0);
                    h3.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
                    h4.setText ((++i < len) ? stoi (val.substring (i, i + 1).toStdString()) : 0);
            }

    }
    
    
    
    
    void attachListener(Label::Listener *listener)
    {
        t1.addListener (listener);
        t2.addListener (listener);
        t3.addListener (listener);
        t4.addListener (listener);
        t5.addListener (listener);
        t6.addListener (listener);
        
        n1.addListener (listener);
        n2.addListener (listener);
        
        h1.addListener (listener);
        h2.addListener (listener);
        h3.addListener (listener);
        h4.addListener (listener);
    }
    
    
    
    
    void setType (DisplayType displayType)
    {
        this->displayType = displayType;
        
        setSpinnersVisible (true);
        
        resized();
    }
    
    
    
    
    void resized()
    {
        fitBounds();
        
        if (getParentComponent())
            getParentComponent()->resized();
    }
    
    
    
    
private:
    
    
    
    void mouseDoubleClick (const MouseEvent &e)
    {
        setSpinnersVisible (false);
        
        ed.setVisible (true);
        
        ed.setText (toString(), sendNotification);
        
        ed.showEditor();
    }
    
    
    
    void setSpinnersVisible (bool visible)
    {
        t1.setVisible ((displayType == DisplayType::TEMPO)  ?   visible : false);
        t2.setVisible ((displayType == DisplayType::TEMPO)  ?   visible : false);
        t3.setVisible ((displayType == DisplayType::TEMPO)  ?   visible : false);
        t4.setVisible ((displayType == DisplayType::TEMPO)  ?   visible : false);
        t5.setVisible ((displayType == DisplayType::TEMPO)  ?   visible : false);
        t6.setVisible ((displayType == DisplayType::TEMPO)  ?   visible : false);
        
        n1.setVisible ((displayType == DisplayType::NOTE)   ?   visible : false);
        n2.setVisible ((displayType == DisplayType::NOTE)   ?   visible : false);
        
        h1.setVisible ((displayType == DisplayType::HERTZ)  ?   visible : false);
        h2.setVisible ((displayType == DisplayType::HERTZ)  ?   visible : false);
        h3.setVisible ((displayType == DisplayType::HERTZ)  ?   visible : false);
        h4.setVisible ((displayType == DisplayType::HERTZ)  ?   visible : false);
    }
    
    
    
    
    void editorHidden (Label *label, TextEditor &editor)
    {
        ed.setVisible (false);
        
        setSpinnersVisible (true);
        
        String val = ed.getTextValue().toString().trim();
        
        
        if (displayType == DisplayType::TEMPO)
        {
            if (regex_match (val.toStdString(), regex ("(\\d+)((\\.)(\\d*)?)?")))
                setDisplay (val);
        }
        else if (displayType == DisplayType::NOTE)
        {
            setDisplay (val);
        }
        else
        {
            if (regex_match (val.toStdString(), regex ("(\\d*)((\\.)(\\d*)?)?")))
                setDisplay (val);
        }
    }
    
    
    
    
    void labelTextChanged (Label *labelThatHasChanged)
    {
        resized();
    }
    
    
    
    
    void editorShown (Label *, TextEditor &)
    {
    }
    
    
    
    
    int noteIndex (String val)
    {
        if (val == "C" || val == "c")
            return 0;
        else if (val == "C#" || val == "c#" || val == "Db" || val == "db")
            return 1;
        else if (val == "D" || val == "d")
            return 2;
        else if (val == "D#" || val == "d#" || val == "Eb" || val == "eb")
            return 3;
        else if (val == "E" || val == "e" || val == "Fb" || val == "fb")
            return 4;
        else if (val == "F" || val == "f")
            return 5;
        else if (val == "F#" || val == "f#" || val == "Gb" || val == "gb")
            return 6;
        else if (val == "G" || val == "g")
            return 7;
        else if (val == "G#" || val == "g#" || val == "Ab" || val == "ab")
            return 8;
        else if (val == "A" || val == "a")
            return 9;
        else if (val == "A#" || val == "a#" || val == "Bb" || val == "bb")
            return 10;
        else if (val == "B" || val == "b" || val == "Cb" || val == "cb")
            return 11;
        else
            return -1;
    }
};
