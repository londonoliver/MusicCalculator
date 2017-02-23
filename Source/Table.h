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

class Table   :    public Component, public TableListBoxModel, public LookAndFeel_V3
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
    
private:
    class EditableTextCustomComponent  : public Label
    {
    public:
        EditableTextCustomComponent (Table& td);
        
        void mouseDown (const MouseEvent& event) override;
        void textWasEdited() override;
        void setRowAndColumn (const int newRow, const int newColumn);
        void editorShown (TextEditor *editor) override;
    private:
        Table& owner;
        int row, columnId;
        TextEditor editor;
    };
        
    class CustomTableHeader : public TableHeaderComponent, private Button::Listener
    {
    public:
        CustomTableHeader();
        
        void paint (Graphics& g) override;
        void resized() override;
        void setTable (Table* t);
    private:
        SafePointer<Table> table;
        TextButton b1, b2;
        
        void buttonClicked (Button *button) override;
        
    };
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Table)

public:
    SafePointer<Display> display;
    SafePointer<CustomTableHeader> header;
};

#endif /* Table_h */
