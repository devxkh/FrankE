//// BFG license goes here
//
//
//#include <cmath>
//#include <fstream>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//using std::cerr;
//using std::cout;
//using std::cin;
//using std::endl;
//using std::exception;
//using std::ifstream;
//using std::ios;
//using std::max;
//using std::min;
//using std::string;
//using std::vector;
//
//#include <ft2build.h>
//#include FT_FREETYPE_H
//
////#include "tclap/CmdLine.h"
////using namespace TCLAP;
//
//#include "BFGBitmap.h"
//#include "BFGColor.h"
//#include "BFGDataStream.h"
//#include "BFGException.h"
//using namespace BFG;
//
//
//void exit (const string& message)
//{
//    cerr << message << endl;
//    exit(1);
//}
//
//
//string readFile (const string& fileName)
//{
//    FILE* testFile = fopen(fileName.data(), "r");
//    if (!testFile) { exit("Alphabet file '"+fileName+"' does not exist!"); }
//    fclose(testFile);
//    
//    ifstream file;
//    file.open(fileName.data());
//    
//    file.seekg (0, ios::end);
//    int length = file.tellg();
//    char* buffer = new char [length];
//    
//    file.seekg(0, ios::beg);
//    file.read(buffer, length);
//    file.close();
//    
//    string contents = buffer;
//    delete[] buffer;
//    return contents;
//}
//
//
//int main (int argc, char** argv)
//{
//	// Define all possible arguments
//	//UnlabeledValueArg<string> argFontFile (
//	//	"fontfile",
//	//	"The input font file (.ttf or .otf).",
//	//	true, "Font.ttf",
//	//	"string");
//	//ValueArg<string> argDataFormat (
//	//	"f", "format",
//	//	"The type of data file to produce.  Options: none, quickgui.",
//	//	false, "none",
//	//	"string");
//	//ValueArg<string> argAlphabet (
//	//	"a", "alphabet",
//	//	"A custom alphabet file.",
//	//	false, "",
//	//	"string");
//	//ValueArg<uint> argFontSize (
//	//	"s", "size",
//	//	"The font size to use (roughly pixel height).",
//	//	false, 128,
//	//	"uint");
//	//ValueArg<string> argColor (
//	//	"c", "color",
//	//	"The RGB color of the bitmap.  Values are from 0 to 1.",
//	//	false, "1 1 1",
//	//	"RGB(0-1)");
//	//ValueArg<float> argOutlineWidth (
//	//	"o", "outlinewidth",
//	//	"The pixel width of the outline.  0 for no outline.",
//	//	false, 0,
//	//	"float");
//	//ValueArg<string> argOutlineColor (
//	//	"C", "outlinecolor",
//	//	"The RGB color of the outline.  Values are from 0 to 1.",
//	//	false, "1 1 1",
//	//	"RGB(0-1)");
//	//ValueArg<float> argOutlineIntensity (
//	//	"i", "outlineintensity",
//	//	"The intensity of the outline.  Must be greater than 0.",
//	//	false, 2,
//	//	"float");
//	//ValueArg<float> argTargetSize (
//	//	"t", "texturesize",
//	//	"The created target texture size.  Must be greater than 0. Defaults to 512",
//	//	false, 512,
//	//	"uint");
//
//	//// Define command line to initiate a multi font output (for gorilla)
//	//// All the args must be there (Ex: fontgen -f gorilla -t 512)
//	//CmdLine multiCmd("Initiate a multi font gen in the same output", ' ', "1.0");
//	//multiCmd.add(argDataFormat);
//	//multiCmd.add(argTargetSize);
//
//	//// Define command line arguments for a full single argument line
//	//CmdLine fullCmd("Generates QuickGUI/gorilla bitmap fonts from TrueType fonts.", ' ', "1.0");
//	//fullCmd.add(argFontFile);
//	//fullCmd.add(argDataFormat);
//	//fullCmd.add(argAlphabet);
//	//fullCmd.add(argFontSize);
//	//fullCmd.add(argColor);
//	//fullCmd.add(argOutlineWidth);
//	//fullCmd.add(argOutlineColor);
//	//fullCmd.add(argOutlineIntensity);
//	//fullCmd.add(argTargetSize);
//
//	//// Define command line arguments for a full multi-font instance argument line
//	//CmdLine instanceCmd("Generates multi-font instance command", ' ', "1.0");
//	//instanceCmd.add(argFontFile);
//	//instanceCmd.add(argAlphabet);
//	//instanceCmd.add(argFontSize);
//	//instanceCmd.add(argColor);
//	//instanceCmd.add(argOutlineWidth);
//	//instanceCmd.add(argOutlineColor);
//	//instanceCmd.add(argOutlineIntensity);
//
//	// Default alphabet to be used
//	/*
//	string defAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\
//                abcdefghijklmnopqrstuvwxyz\
//                1234567890!@#$%^&*()[]{}<>\
//                -=_+,.:;?'\"/|\\`~";
//	*/
//	string defAlphabet = 
//		"!\"#$%&'()*+,-./0123456789:;<=>?@\
//		ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`\
//        abcdefghijklmnopqrstuvwxyz{|}~";
//
//	// variables keeping parsed arguments. Arguments that are vectors
//	// are those who can be used for multi-font output
//	vector<string> alphabetList;
//    vector<string> fontFileList;
//    vector<uint> fontSizeList;
//    vector<Color> colorList;
//	vector<Color> outlineColorList;
//    vector<float> outlineWidthList;
//    vector<float> outlineIntensityList;
//
//	string fileName;
//	uint fileSize;
//	DataStream* dataStream = NULL;
//    string dataFormat;
//    string bitmapFile;
//    string quickguiFile;
//
//	// Parse for multifont init command line
//	bool bMultifont = false;
//	if (argc == 5)
//	{
//		// Possible multifont initialization command line
//		bMultifont = true;
//		try
//		{
//			multiCmd.parse(argc, argv);
//			// Got a multi command initialization, parse options
//			// "-f"
//			dataFormat = argDataFormat.getValue();
//			if (dataFormat == "none")
//				dataStream = new NullDataStream();
//			else if (dataFormat == "quickgui")
//				dataStream = new QuickGUIDataFile();
//			else if (dataFormat == "gorilla")
//				dataStream = new GorillaDataFile();
//			else
//				exit("Invalid data format '"+dataFormat+"'!");
//			bitmapFile = fileName + ".png";
//			// "-t"
//			fileSize = (uint)argTargetSize.getValue();
//		}
//		catch (TCLAP::ArgException &e)
//		{
//			// Not an error, just indicating this command line is not
//			// to initiate multi-font output
//			bMultifont = false;
//		}
//	}
//
//	if (!bMultifont)
//	{
//		// Not generating multiple fonts, expect full command line
//		fullCmd.parse(argc, argv);
//
//		// <fontfile>
//		string s = argFontFile.getValue();
//		fontFileList.push_back(s);
//		fileName = s.substr(s.find_last_of("/")+1, -1);
//		fileName = fileName.substr(0, fileName.find_last_of("."));
//		bitmapFile = fileName + ".png";
//		quickguiFile = fileName + ".fontdata";
//		// "-a"
//		if (argAlphabet.getValue() != "")
//			alphabetList.push_back(readFile(argAlphabet.getValue()));
//		else
//			alphabetList.push_back(defAlphabet);
//		// "-f"
//		dataFormat = argDataFormat.getValue();
//		if (dataFormat == "none")
//			dataStream = new NullDataStream();
//		else if (dataFormat == "quickgui")
//			dataStream = new QuickGUIDataFile();
//		else if (dataFormat == "gorilla")
//			dataStream = new GorillaDataFile();
//		else
//			exit("Invalid data format '"+dataFormat+"'!");
//		// "-s"
//		fontSizeList.push_back(argFontSize.getValue());
//		// "-c"
//		try { colorList.push_back(argColor.getValue()); }
//		catch (exception) { exit("Color is not a proper RGB color!"); }
//		// "-C"
//		try { outlineColorList.push_back(argOutlineColor.getValue()); }
//		catch (exception) { exit("Outline color is not a proper RGB color!"); }
//		// "-o"
//		outlineWidthList.push_back(argOutlineWidth.getValue());
//		// "-i"
//		float f = argOutlineIntensity.getValue();
//		outlineIntensityList.push_back(f);
//		if (f <= 0)
//			exit("Outline intensity must be greater than 0!");
//		// "-t"
//		fileSize = (uint)argTargetSize.getValue();
//	}
//	else
//	{
//		// Generating multiple fonts, read each instance until
//		// the user enter empty one
//		int nb = 1;
//		size_t inLen;
//		char instanceInputCommand[1024];
//		cout<<endl;
//		cout<<"Enter each font attribute set one at a time. Enter empty line to finish." << endl;
//		cout<<"Ex: -o 2 -i 3 -c \"0 0 1\" -C \"1 0 1\" -s 18 segoepr.ttf" << endl << endl;
//		do
//		{
//			// Request next command line from user
//			cout<<"Enter command #" << nb++ << " : ";
//			cin.getline(instanceInputCommand, 1024);
//			inLen = strlen(instanceInputCommand);
//			
//			if (inLen > 0)
//			{
//				// Split the input string in argument for command line parsing by tclap
//				std::vector<string> argList;
//				argList.push_back(argv[0]);
//				string sArg;
//				bool bInString = false;
//				size_t idx = 0;
//				while(idx < inLen)
//				{
//					if (instanceInputCommand[idx] == ' ' && !bInString)
//					{
//						if (!sArg.empty())
//						{
//							argList.push_back(sArg);
//							sArg.clear();
//						}
//					}
//					else if (instanceInputCommand[idx] == '"')
//						bInString = !bInString;
//					else
//						sArg += instanceInputCommand[idx];
//					idx++;
//				}
//				if (!sArg.empty())
//					argList.push_back(sArg);
//
//				// Parse command line
//				instanceCmd.reset();
//				instanceCmd.parse(argList);
//
//				// Gather parsed arguments
//				// <fontfile>
//				string s = argFontFile.getValue();
//				fontFileList.push_back(s);
//				fileName = s.substr(s.find_last_of("/")+1, -1);
//				fileName = fileName.substr(0, fileName.find_last_of("."));
//				bitmapFile = fileName + ".png";
//				quickguiFile = fileName + ".fontdata";
//				// "-a"
//				if (argAlphabet.getValue() != "")
//					alphabetList.push_back(readFile(argAlphabet.getValue()));
//				else
//					alphabetList.push_back(defAlphabet);
//				// "-s"
//				fontSizeList.push_back(argFontSize.getValue());
//				// "-c"
//				try { colorList.push_back(argColor.getValue()); }
//				catch (exception) { exit("Color is not a proper RGB color!"); }
//				// "-C"
//				try { outlineColorList.push_back(argOutlineColor.getValue()); }
//				catch (exception) { exit("Outline color is not a proper RGB color!"); }
//				// "-o"
//				outlineWidthList.push_back(argOutlineWidth.getValue());
//				// "-i"
//				float f = argOutlineIntensity.getValue();
//				outlineIntensityList.push_back(f);
//				if (f <= 0)
//					exit("Outline intensity must be greater than 0!");
//
//			}
//		}
//		while(inLen > 0);
//	}
//    
//    
//    // Configure bitmap
//    Bitmap bitmap;
//    bitmap.setFileName(bitmapFile);
//	bitmap.setFileSize(fileSize);
//	bitmap.AllocateBinPack();
//	bitmap.attachDataStream(dataStream);
//
//	// Open data stream
//    dataStream->open(&bitmap);
//
//	// Generate all fonts
//	for(int i=0; i<fontSizeList.size(); ++i)
//	{
//		bitmap.setAlphabet(alphabetList[i]);
//		bitmap.setFontFile(fontFileList[i]);
//		bitmap.setFontSize(fontSizeList[i]);
//		bitmap.setColor(colorList[i]);
//		bitmap.setOutlineColor(outlineColorList[i]);
//		bitmap.setOutlineIntensity(outlineIntensityList[i]);
//		bitmap.setOutlineWidth(outlineWidthList[i]);
//
//		// Generate and save bitmap
//		try
//		{
//			bitmap.generate();
//		}
//		catch (const exception& e) { exit(e.what()); }
//	}
//    
//	// Close data stream
//    dataStream->close();
//
//	// Save the packed output bitmap file
//	bitmap.save();
//
//    // Exit
//    delete dataStream;
//    return 0;
//}