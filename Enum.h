#ifndef EnumH
#define EnumH

//---------------------------------------------------------------------------   // Klasy.cpp

enum stream_name_tag
	{
		SRT_SAME = 0,
		STR_BEGINING,
		STR_POSTFIX,
		STR_NEW_NAME
	};

enum stream_path_tag {

		PATH_CURR = 0,
//		PATH_DESKTOP,         // access denied
		PATH_USER

	 };

enum stream_logfile_tag {

		LOG_DESKTOP = 0,
		LOG_HERE,
		LOG_OTHER

	 };

enum icons {

	ICO_EMPTY = 0,                                                              // DO USTAWIENIA GDY BÊD¥ IKONY
	ICO_ZONE_ID,
	ICO_ADATA

	};



//---------------------------------------------------------------------------
#endif
