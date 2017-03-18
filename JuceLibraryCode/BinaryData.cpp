/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== metronome.svg ==================
static const unsigned char temp_binary_data_0[] =
"<svg fill=\"#000000\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" version=\"1.1\" x=\"0px\" y=\"0px\" viewBox=\"0 0 100 100\" enable-background=\"new 0 0 100 100\" xml:space=\"preserve\"><path fill=\"#000000\" d="
"\"M86.945,10.635c-0.863-0.494-1.964-0.19-2.455,0.673l-8.31,14.591l-2.891-1.745l-1.769,9.447l0.205,0.123  l-1.303,2.286L63.111,6.819c-0.25-1-1.299-1.819-2.33-1.819H37.608c-1.031,0-2.082,0.818-2.334,1.818L13.454,93.182  c-0.253,1,0.385,1.818,1.416,1.81"
"8h68.459c1.031,0,1.67-0.818,1.42-1.818L71.69,41.061l3.117-5.475l0.152,0.092l7.559-5.951  l-3.257-1.966l8.355-14.67C88.11,12.226,87.81,11.127,86.945,10.635z M71.58,70.625H54.855l12.946-22.737l5.197,20.789  C73.25,69.678,72.61,70.625,71.58,70.625z M50."
"714,70.625H26.57c-1.031,0-1.669-0.994-1.416-1.994L39.59,11.5  c0.253-1,1.303-1.812,2.334-1.812h14.431c1.032,0,2.081,0.725,2.331,1.725l7.854,31.421L50.714,70.625z\"/></svg>";

const char* metronome_svg = (const char*) temp_binary_data_0;

//================== note.svg ==================
static const unsigned char temp_binary_data_1[] =
"<svg fill=\"#000000\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" version=\"1.1\" x=\"0px\" y=\"0px\" viewBox=\"0 0 80 80\" enable-background=\"new 0 0 80 80\" xml:space=\"preserve\"><g><g><path fill=\"#000000\" "
"d=\"M45.8,49.6c1.4,2.7-1,6.7-5.2,8.9c-4.3,2.2-8.9,1.9-10.3-0.8c-1.4-2.7,0.7-7.3,5.2-8.9    C40.3,47.2,44.4,47,45.8,49.6z\"/></g><g><rect x=\"44\" y=\"18\" fill=\"#000000\" width=\"2\" height=\"32\"/></g></g></svg>";

const char* note_svg = (const char*) temp_binary_data_1;

//================== clipboard.svg ==================
static const unsigned char temp_binary_data_2[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"
"<!-- Generator: Adobe Illustrator 18.1.0, SVG Export Plug-In . SVG Version: 6.00 Build 0)  -->\r\n"
"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\r\n"
"<svg version=\"1.1\" id=\"Clipboard\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\r\n"
"\t viewBox=\"0 0 20 20\" enable-background=\"new 0 0 20 20\" xml:space=\"preserve\">\r\n"
"<path d=\"M15.6,2l-1.2,3H5.6l-1.2-3C3.629,2,3,2.629,3,3.4V18.6c0,0.77,0.629,1.4,1.399,1.4h11.2c0.77,0,1.4-0.631,1.4-1.4V3.4\r\n"
"\tC17,2.629,16.369,2,15.6,2z M13.6,4l0.9-2h-2.181L11.6,0h-3.2L7.68,2H5.5l0.899,2H13.6z\"/>\r\n"
"</svg>\r\n";

const char* clipboard_svg = (const char*) temp_binary_data_2;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x7332ec57:  numBytes = 899; return metronome_svg;
        case 0x5e435497:  numBytes = 431; return note_svg;
        case 0x0dd4103b:  numBytes = 666; return clipboard_svg;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "metronome_svg",
    "note_svg",
    "clipboard_svg"
};

}
