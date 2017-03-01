/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== clipboard.svg ==================
static const unsigned char temp_binary_data_0[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"
"<!-- Generator: Adobe Illustrator 18.1.0, SVG Export Plug-In . SVG Version: 6.00 Build 0)  -->\r\n"
"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\r\n"
"<svg version=\"1.1\" id=\"Clipboard\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\r\n"
"\t viewBox=\"0 0 20 20\" enable-background=\"new 0 0 20 20\" xml:space=\"preserve\">\r\n"
"<path d=\"M15.6,2l-1.2,3H5.6l-1.2-3C3.629,2,3,2.629,3,3.4V18.6c0,0.77,0.629,1.4,1.399,1.4h11.2c0.77,0,1.4-0.631,1.4-1.4V3.4\r\n"
"\tC17,2.629,16.369,2,15.6,2z M13.6,4l0.9-2h-2.181L11.6,0h-3.2L7.68,2H5.5l0.899,2H13.6z\"/>\r\n"
"</svg>\r\n";

const char* clipboard_svg = (const char*) temp_binary_data_0;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x0dd4103b:  numBytes = 666; return clipboard_svg;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "clipboard_svg"
};

}
