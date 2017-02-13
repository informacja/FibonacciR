//---------------------------------------------------------------------------

#ifndef PictureH
#define PictureH

#include <String>
#include <math.h>
#include <iomanip.h>
#include <fstream.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <shellapi.h>
#include <winbase.h>
#include <stdio.h>     	// for FILE, fopen, fstat, fileno, fread and fclose
#include <sys\stat.h>  	// for fstat and the stat struct
//#include <Math.hpp> 	// for Min
#include <memory>     	// for STL auto_ptr class
#include <psapi.h>  	// Wprogramie.cpp
#include "adCpuUsage.hpp"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <filectrl.hpp>
#include <tlhelp32.h>        // procesy
#include <jpeg.hpp>
#include <pngimage.hpp>
#include <pnglang.hpp>
#include <ScreenTips.hpp>
#include <clipbrd.hpp>
#include <Vcl.DBCtrls.hpp> // database

//---------------------------------------------------------------------------
//   namespace Grp  {
class Picture {
//  public:
	TImage *image;
	TDBImage *imgd;
	char MinQuality;
	char Clipboard;

public:

	String FileName;

	Picture();
	Picture(TImage* image_to_conversion);
	~Picture();

/*
	+--------------------Manual-for-Screen-func---------------------------------+
	|																			|																		|
	|	Inputs:		String	path     											|
	|				char quality               Warning: BMP no lossless         |
	|							     											|
	|	Returns:	Information for user 										|
	|                                                                           |
	|	Notes: 		You can use func GetQualityJPEG\PNG() to convert from %     |
	|   ______________________________________________________________________  |
	|                                                                           |
	|	Examples: 	(how give inputs)											|
	|                                                                           |
	|	cout << object.ScreenPNG( path, quality );                              |
	|                                                                           |																			|
	|    path 	  = "C:\\"      (standard)                                      |
	|				"" 			(save to current folder where is app)           |
	|                                                                           |
	|	 quality  = 90 (Any number from 0 to 100)                               |
	|                                                                           |
	|	                                                                        |
	+---------------------------------------------------------------------------+
*/

	String ScreenBMP(String path_where_save_if_NULL_save_to_clipboard = "",     // "" current dir
													  String FileName = 0); 	// NULL or "" use defalut name (constructor)

	String ScreenPNG(String path_where_save_if_NULL_save_to_clipboard = "",
									char Quality_90 = 90, String FileName = 0);

	String ScreenJPG(String path_where_save_if_NULL_save_to_clipboard = "",
									char Quality_90 = 90, String FileName = 0);

	String ConvertToBMP(String Path_save = "", String Name = 0, TImage *img_0 = NULL); 	 // you can load Image in construtor and skip there

	String ConvertToPNG(String Path_save = "", String Name = 0,
						char Quality_90 = 90, TImage *img_0 = NULL);

	String ConvertToJPG(String Path_save = "", String Name = 0,
						char Quality_90 = 90, TImage *img_0 = NULL);

	void SetDefFileName(String LocalName_FiboScreen = "FiboScreen");

	void SetMinQuality(char MinimalQuality_30 = 30);

	unsigned GetQualityJPG(unsigned* Value_in_percent_90 = (unsigned*) 90);
	unsigned GetQualityPNG(unsigned Value_in_percent_90 = 90);

	void SaveToClipboard( bool save_1 = true );

private:

	void ValidateImputs(String *FileName, TImage *Image = 0);                                      // sprawdz poprawnoœæ


};

//	   }
#endif
