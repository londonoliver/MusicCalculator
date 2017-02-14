//
//  TableComponent.cpp
//  MusicCalculator
//
//  Created by London Oliver on 2/5/17.
//
//

#include "../JuceLibraryCode/JuceHeader.h"
#include "LabelComponent.hpp"
#include <iostream>

using namespace std;

//==============================================================================
/**
 This class shows how to implement a TableListBoxModel to show in a TableListBox.
 */
class TableComponent   :    public Component,
                            public TableListBoxModel,
                            public LookAndFeel_V3
{
public:
    TableComponent()   : font (14.0f)
    {
        
        header = new CustomTableHeader();
        header->setTableComponent(this);
        table.setHeader(header);
        
        // Load some data from an embedded XML file..
        loadData();
        
        // Create our table component and add it to this component..
        addAndMakeVisible (table);
        table.setModel (this);
        
        // give it a border
        table.setColour (ListBox::outlineColourId, Colours::grey);
        table.setOutlineThickness (1);
        
        // Add some columns to the table header, based on the column list in our database..
        forEachXmlChildElement (*columnList, columnXml)
        {
            table.getHeader().addColumn (columnXml->getStringAttribute ("name"),
                                         columnXml->getIntAttribute ("columnId"),
                                         86,
                                         30, 100,
                                         TableHeaderComponent::visible);
        }
        
        // un-comment this line to have a go of stretch-to-fit mode
        //table.getHeader().setStretchToFitActive (true);
        
        table.setMultipleSelectionEnabled (true);
        
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
        //if (rowIsSelected)
            //g.fillAll (Colours::lightblue);
        if (rowNumber % 2)
            g.fillAll (Colour (0xffeeeeee));
    }
    
    // This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom
    // components.
    void paintCell (Graphics& g, int rowNumber, int columnId,
                    int width, int height, bool /*rowIsSelected*/) override
    {
        g.setColour (Colours::black);
        g.setFont (font);
        
        if (const XmlElement* rowElement = dataList->getChildElement (rowNumber))
        {
            const String text (rowElement->getStringAttribute (getAttributeNameForColumnId (columnId)));
            
            g.drawText (text, 2, 0, width - 4, height, Justification::centredLeft, true);
        }
        
        g.setColour (Colours::black.withAlpha (0.2f));
        g.fillRect (width - 1, 0, 1, height);
    }
    
    // This is overloaded from TableListBoxModel, and tells us that the user has clicked a table header
    // to change the sort order.
    void sortOrderChanged (int newSortColumnId, bool isForwards) override
    {
        String s;
        
        if (newSortColumnId == 0)
            return;
        else if (newSortColumnId == 1)
        {
            if (noteType == 1)
                noteType = 2;
            else if (noteType == 2)
                noteType = 3;
            else
                noteType = 1;
            
            columnOneName = (noteType == 1) ? "Note (Whole)" : ((noteType == 2) ? "Note (Dotted)" : "Note (Triplet)");
            
        }
        else if (newSortColumnId == 2)
        {
            Hz = !Hz;
            columnTwoName = (Hz) ? "Hz" : "Ms";
        }
        repaint();
        setMilliseconds();
        
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
        
        textLabel->setRowAndColumn (rowNumber, columnId);
        return textLabel;
    }
    
    // This is overloaded from TableListBoxModel, and should choose the best width for the specified
    // column.
    int getColumnAutoSizeWidth (int columnId) override
    {
        int widest = 32;
        
        // find the widest bit of text in this column..
        for (int i = getNumRows(); --i >= 0;)
        {
            if (const XmlElement* rowElement = dataList->getChildElement (i))
            {
                const String text (rowElement->getStringAttribute (getAttributeNameForColumnId (columnId)));
                
                widest = jmax (widest, font.getStringWidth (text));
            }
        }
        
        return widest + 8;
    }
    
    // A couple of quick methods to set and get cell values when the user changes them
    String getText (const int columnNumber, const int rowNumber) const
    {
        return dataList->getChildElement (rowNumber)->getStringAttribute ( getAttributeNameForColumnId(columnNumber));
    }
    
    void setText (const int columnNumber, const int rowNumber, const String& newText)
    {
        const String& columnName = table.getHeader().getColumnName (columnNumber);
        dataList->getChildElement (rowNumber)->setAttribute (columnName, newText);
        table.updateContent();
    }
    
    int getNoteType ()
    {
        return noteType;
    }
    
    void setNoteType (int i)
    {
        noteType = i;
    }
    
    bool getHz ()
    {
        return Hz;
    }
    
    void setHz (bool b)
    {
        Hz = b;
    }
    
    void setLabelComponent(LabelComponent* l)
    {
        labelComponent = l;
    }
    
    void setMilliseconds()
    {
        double bpm = labelComponent->getTextValue().getValue();
        double ms = 1000.0 / (bpm / 60.0); // ms for whole quarter note
        double hz = bpm /60.0;             // hz for whole quarter note
        double value = (Hz) ? hz : ms;
        int noteType = getNoteType();
        int noteDenominator = 4, noteNumerator = 1;
        String s = "";
        switch (noteType) {
            case 1:     // whole note
            {
                break;
            }
            case 2:     // dotted note
            {
                value = value * (3.0/2.0);
                s = ".";
                break;
            }
            case 3:     // triplet note
            {
                value = value * (2.0/3.0);
                s = "T";
                break;
            }
            default:
                break;
        } // end switch
        
        for (int i = 0; i < table.getNumRows(); i++ )
        {
            setText(1, i, String(noteNumerator) + "/" + String(noteDenominator) + s);
            setText(2, i, String(value));
            if (Hz)
                value = value*2.0;
            else
                value = value/2.0;
            noteDenominator = noteDenominator * 2;
        }
    }
    
    TableListBox* getTable()
    {
        return &table;
    }
    
    //==============================================================================
    void resized() override
    {
        // position our table with a gap around its edge
        table.setBoundsInset (BorderSize<int> (8));
    }
    
protected:
    SafePointer<LabelComponent> labelComponent;
    
private:
    TableListBox table;     // the table component itself
    Font font;
    String columnOneName = "Note (Whole)", columnTwoName = "Ms";
    
    
    ScopedPointer<XmlElement> demoData;   // This is the XML document loaded from the embedded file "demo table data.xml"
    XmlElement* columnList; // A pointer to the sub-node of demoData that contains the list of columns
    XmlElement* dataList;   // A pointer to the sub-node of demoData that contains the list of data rows
    int numRows;            // The number of rows of data we've got
    
    int noteType;       // State of the note column: 1 = whole, 2 = dotted, 3 = triplet
    bool Hz = false;    // if true, then column two will show hz, if false it will show ms
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //==============================================================================
    // This is a custom Label component, which we use for the table's editable text columns.
    class EditableTextCustomComponent  : public Label
    {
    public:
        EditableTextCustomComponent (TableComponent& td)  : owner (td)
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
            owner.setText (columnId, row, getText());
        }
        
        // Our demo code will call this when we may need to update our contents
        void setRowAndColumn (const int newRow, const int newColumn)
        {
            row = newRow;
            columnId = newColumn;
            setText (owner.getText(columnId, row), dontSendNotification);
        }
        
        void editorShown (TextEditor *editor) override
        {
            editor->setReadOnly(true);
            editor->setCaretVisible(false);
        }
        
    private:
        TableComponent& owner;
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
        
        
        void setTableComponent(TableComponent* t)
        {
            table = t;
        }
    private:
        SafePointer<TableComponent> table;
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
    
    
    
    
    
    //==============================================================================
    // this loads the embedded database XML file into memory
    void loadData()
    {
        demoData = XmlDocument::parse (BinaryData::delay_times_data_xml);
        
        dataList   = demoData->getChildByName ("DATA");
        columnList = demoData->getChildByName ("COLUMNS");
        
        numRows = dataList->getNumChildElements();
    }
    
    // (a utility method to search our XML for the attribute that matches a column ID)
    String getAttributeNameForColumnId (const int columnId) const
    {
        forEachXmlChildElement (*columnList, columnXml)
        {
            if (columnXml->getIntAttribute ("columnId") == columnId)
                return columnXml->getStringAttribute ("name");
        }
        
        return String();
    }
            
    SafePointer<CustomTableHeader> header; // move this up higher when you make a .h file
            
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TableComponent)
};
