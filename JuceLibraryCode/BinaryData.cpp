/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== delay times data.xml ==================
static const unsigned char temp_binary_data_0[] =
"<DELAY_TIMES_DATA>\n"
"\t<COLUMNS>\n"
"\t\t<COLUMN columnId=\"1\" name=\"Note\" width=\"50\"/>\n"
"\t\t<COLUMN columnId=\"2\" name=\"Ms\" width=\"50\"/>\n"
"    </COLUMNS>\n"
"    <DATA>\n"
"        <ITEM Note=\"1/2\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/4\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/8\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/16\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/32\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/64\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/128\" Ms=\"-\" />\n"
"    </DATA>\n"
"</DELAY_TIMES_DATA>\n";

const char* delay_times_data_xml = (const char*) temp_binary_data_0;

//================== delay times data2.xml ==================
static const unsigned char temp_binary_data_1[] =
"<DELAY_TIMES_DATA>\n"
"    <COLUMNS>\n"
"        <COLUMN columnId=\"1\" name=\"Note\" width=\"50\"/>\n"
"        <COLUMN columnId=\"2\" name=\"Ms\" width=\"50\"/>\n"
"    </COLUMNS>\n"
"    <DATA>\n"
"        <ITEM Note=\"4/1\" Ms=\"-\" />\n"
"        <ITEM Note=\"3/1\" Ms=\"-\" />\n"
"        <ITEM Note=\"2/1\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/1\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/2\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/4\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/8\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/16\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/32\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/64\" Ms=\"-\" />\n"
"        <ITEM Note=\"1/128\" Ms=\"-\" />\n"
"    </DATA>\n"
"</DELAY_TIMES_DATA>\n";

const char* delay_times_data2_xml = (const char*) temp_binary_data_1;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x71dd2117:  numBytes = 432; return delay_times_data_xml;
        case 0xc741acab:  numBytes = 587; return delay_times_data2_xml;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "delay_times_data_xml",
    "delay_times_data2_xml"
};

}
