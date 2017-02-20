//
//  TableComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/5/17.
//
//
#ifndef Table_hpp
#define Table_hpp
#include "../JuceLibraryCode/JuceHeader.h"
#include "TempoSpinner.h"
#include <iostream>
#endif

using namespace std;

//==============================================================================
/**
 This class shows how to implement a TableListBoxModel to show in a TableListBox.
 */
class Table   :    public Component, public TableListBoxModel, public LookAndFeel_V3
{
public:
    enum class DelayType {NORMAL, DOTTED, TRIPLET};
    enum class TempoConversion {MS, HZ};
    
    DelayType delayType;
    TempoConversion tempoConversion;
    
    int width;
    int height;
    
    TableListBox table;     // the table component itself
    Font font;
    String columnOneName = "Note", columnTwoName = "Ms";
    
    int numRows;            // The number of rows of data we've got
    int numCols;
    
    int noteType;       // State of the note column: 1 = whole, 2 = dotted, 3 = triplet
    bool Hz = false;    // if true, then column two will show hz, if false it will show ms
    
    Table()   : font (14.0f)
    {
        width = 200;
        height = 300;
        
        header = new CustomTableHeader();
        header->setTable(this);
        table.setHeader(header);
        
        numRows = 8;
        
        
        // Create our table component and add it to this component..
        addAndMakeVisible (table);
        table.setModel (this);
        
        table.getHeader().addColumn("Note", 1, width/2);
        table.getHeader().addColumn("Ms", 2, width/2);
        
        noteType = 1;
        Hz = false;
    }
    
    // This is overloaded from TableListBoxModel, and must return the total number of rows in our table
    int getNumRows() override
    {
        return numRows;
    }
    
    // This is overloaded from TableListBoxModel, and should fill in the background of the whole row
    void paintRowBackground (Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected) override
    {
        if (rowNumber % 2)
            g.fillAll (Colour (0xffeeeeee));
    }
    
    // This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom
    // components.
    void paintCell (Graphics& g, int rowNumber, int columnId,
                    int width, int height, bool /*rowIsSelected*/) override
    {
    }
    
    // This is overloaded from TableListBoxModel, and tells us that the user has clicked a table header
    // to change the sort order.
    void sortOrderChanged (int newSortColumnId, bool isForwards) override
    {
    }
    
    // This is overloaded from TableListBoxModel, and must update any custom components that we're using
    Component* refreshComponentForCell (int rowNumber, int columnId, bool /*isRowSelected*/,
                                        Component* existingComponentToUpdate) override
    {
        // The other columns are editable text columns, for which we use the custom Label component
        EditableTextCustomComponent* textLabel = static_cast<EditableTextCustomComponent*> (existingComponentToUpdate);
        
        // same as above...
        if (textLabel == nullptr)
            textLabel = new EditableTextCustomComponent (*this);
        
        if (columnId == 2)
        {
            textLabel->setEditable(true);
        }
        //tempoConversion = TempoConversion::HZ;
        //delayType = DelayType::TRIPLET;
        textLabel->setText(setTempoTable(rowNumber, columnId), sendNotification);
        //cout << "rowNumber = " << rowNumber << " columnId = " << columnId << endl;
        
        return textLabel;
    }
    
    // This is overloaded from TableListBoxModel, and should choose the best width for the specified
    // column.
    int getColumnAutoSizeWidth (int columnId) override
    {
        return width/2;
    }
    
    // A couple of quick methods to set and get cell values when the user changes them
    String getText (const int columnNumber, const int rowNumber) const
    {
        return "";
    }
    
    void setText (const int columnNumber, const int rowNumber, const String& newText)
    {
        table.updateContent();
    }
    
    void setTempoSpinner (TempoSpinner *ts)
    {
        tempoSpinner = ts;
    }
    
    double getBPM()
    {
        return (tempoSpinner) ? tempoSpinner->getValue() : 0;
    }
    
    double getWholeNoteMs()
    {
        return (1000.0 / (getBPM() / 60.0)) * 4.0 *
                ((delayType == DelayType::DOTTED) ? (3.0 / 2.0) :
                 ((delayType == DelayType::TRIPLET) ? (2.0 / 3.0) : 1));
    }
    
    double getWholeNoteHz()
    {
        return (getBPM() / 60.0) / 4.0 /
        ((delayType == DelayType::DOTTED) ? (3.0 / 2.0) :
         ((delayType == DelayType::TRIPLET) ? (2.0 / 3.0) : 1));
    }
    
    String setTempoTable (int rowNumber, int columnId)
    {
        if (columnId == 1)
            return "1/" + String (pow (2, rowNumber))
            + ((delayType == DelayType::DOTTED) ? "." :
               ((delayType == DelayType::TRIPLET) ? "T" : ""));
        else
            return (tempoConversion == TempoConversion::MS) ?
                    String (getWholeNoteMs() / pow (2, rowNumber)) :
                    String (getWholeNoteHz() * pow (2, rowNumber));
    }
    
    void setMilliseconds()
    {
    }
    
    TableListBox* getTable()
    {
        return &table;
    }
    
    //==============================================================================
    void resized() override
    {
        // position our table with a gap around its edge
        table.setBounds (0, 0, width, height);
        table.setBoundsInset (BorderSize<int> (0));
    }
    
protected:
    SafePointer<TempoSpinner> tempoSpinner;
    
private:
    
    //==============================================================================
    // This is a custom Label component, which we use for the table's editable text columns.
    class EditableTextCustomComponent  : public Label
    {
    public:
        EditableTextCustomComponent (Table& td)  : owner (td)
        {
            // double click to edit the label text; single click handled below
            setEditable (false);
            setColour (textColourId, Colours::black);
        }
        
        void mouseDown (const MouseEvent& event) override
        {
            // single click on the label should simply select the row
            
            Label::mouseDown (event);
        }
        
        void textWasEdited() override
        {
            //owner.setText (columnId, row, getText());
        }
        
        // Our demo code will call this when we may need to update our contents
        void setRowAndColumn (const int newRow, const int newColumn)
        {
        }
        
        void editorShown (TextEditor *editor) override
        {
            editor->setReadOnly(true);
            editor->setCaretVisible(false);
        }
        
    private:
        Table& owner;
        int row, columnId;
        TextEditor editor;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    //==============================================================================
    // This is a custom TableHeader component, which we use for the table's header.
    class CustomTableHeader : public TableHeaderComponent, private Button::Listener
    {
    public:
        CustomTableHeader()
        {
            addAndMakeVisible(b1);
            addAndMakeVisible(b2);
            b1.setName("b1");
            b2.setName("b2");
            b1.addListener(this);
            b2.addListener(this);
        }
        
        SafePointer<TextButton> getButton (int i)
        {
            if (i == 1)
                return &b1;
            else
                return &b2;
        }
        
        
        void paint (Graphics& g) override
        {
        }
        
        void resized() override
        {
            if (table)
            {
                b1.setButtonText(table->columnOneName);
                b2.setButtonText(table->columnTwoName);
            }
            b1.setBounds(0, 0, getColumnWidth(1), getHeight());
            b2.setBounds(getColumnWidth(1), 0, getColumnWidth(2), getHeight());
        }
        
        
        void setTable(Table* t)
        {
            table = t;
        }
    private:
        SafePointer<Table> table;
        TextButton b1, b2;
        
        void buttonClicked (Button *button) override
        {
            if (table)
            {
                if (button->getName() == "b1")
                {
                    table->sortOrderChanged(1, true);
                    b1.setButtonText(table->columnOneName);
                }
                else if (button->getName() == "b2")
                {
                    table->sortOrderChanged(2, true);
                    b2.setButtonText(table->columnTwoName);
                }
            }
        }
    };
    
    SafePointer<CustomTableHeader> header; // move this up higher when you make a .h file
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Table)
};
