//
//  Table.h
//  MusicCalculator
//
//  Created by London Oliver on 2/21/17.
//
//

#ifndef Table_h
#define Table_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "Display.h"

class Table   :    public Component, public TableListBoxModel
{
public:
    enum class TableType {TEMPO, NOTE, HERTZ};
    enum class DelayType {NORMAL, DOTTED, TRIPLET};
    enum class TempoConversion {MS, HZ};
    
    TableType tableType;
    DelayType delayType;
    TempoConversion tempoConversion;
    
    int width;
    int height;
    
    TableListBox table;
    
    Font font;
    
    String columnOneName;
    String columnTwoName;
    
    int numTempoRows;
    int numNoteRows;
    int numHertzRows;
    
    Table();
    
    int getNumRows() override;
    void paintRowBackground (Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected) override;
    void paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool /*rowIsSelected*/) override;
    void sortOrderChanged (int newSortColumnId, bool isForwards) override;
    Component* refreshComponentForCell (int rowNumber, int columnId, bool /*isRowSelected*/, Component* existingComponentToUpdate) override;
    int getColumnAutoSizeWidth (int columnId) override;
    String getText (const int columnNumber, const int rowNumber) const;
    void setText (const int columnNumber, const int rowNumber, const String& newText);
    void setDisplay (Display *display);
    double getTempo();
    int getNote();
    int getOctave();
    double noteToHz(int note, int octave);
    double semitoneShift(double value, double amount);
    double getWholeNoteMs();
    double getWholeNoteHz();
    String setTempoTable (int rowNumber, int columnId);
    String setNoteTable (int rowNumber, int columnId);
    String setHertzTable (int rowNumber, int columnId);
    void setTableType();
    void setMilliseconds();
    TableListBox* getTable();
    void resized() override;
    
    void setNumRows (int i);
    int getNumColumns();
    void setNumColumns (int i);
    
    
private:
    
    class EditableTextCustomComponent  : public Component, public Button::Listener, public ChangeListener
    {
    public:
        Label label;
        Label copied;
        bool fadeout;
        ScopedPointer<DrawableButton> button;
        
        EditableTextCustomComponent (Table& td);
        ~EditableTextCustomComponent();
        
        void resized() override;
        void mouseDown (const MouseEvent& event) override;
        void mouseEnter (const MouseEvent &event) override;
        void mouseExit (const MouseEvent &event) override;
        void buttonClicked (Button *button) override;
        void changeListenerCallback (ChangeBroadcaster *source) override;
    private:
        Table& owner;
    };
        
    class CustomTableHeader : public TableHeaderComponent, private Button::Listener, public LookAndFeel_V3
    {
    public:
        CustomTableHeader();
        ~CustomTableHeader();
        
        TextButton b1, b2;
        void paint (Graphics& g) override;
        void resized() override;
        void setTable (Table* t);
    private:
        SafePointer<Table> table;

        void buttonClicked (Button *button) override;
        void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override;
        static void drawButtonShape (Graphics& g, const Path& outline, Colour baseColour, float height);
        void drawButtonText (Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/) override;
    };
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Table)

public:
    SafePointer<Display> display;
    SafePointer<CustomTableHeader> header;
};

#endif /* Table_h */
