/*
	+-------------------------------------------------------------------------------+
    |																				|
	|	File: 				SMBIOS_P.CPP											|
	|						=================================================		|
	|	Dev Platform:		WinXP SP2 2.3GHZ 2GB RAM								|
	|	Dev Environment: 	Visual Studio.NET 2005 									|
	|	Target:				Windows Server 2003 R2 (x86,x64)						|
	|	Purpose:			This is the main user interface--a command line			|
	|						argument driven console.  The purpose is to parse 		|
	|						and report raw bios tables.								|
	|						=================================================		|
	|   Limitations:		Based on SMB Reference Specification 2.6A Prelim		|
	|						Only the following table types are supported:			|
	|						0x00, 0x01, 0x03, 0x04, 0x07, 0x09, 0x10, 0x11,			|
	|						0x13, 0x20.												|
	|	Dev Summary->																|
	|   Revision:	Who:	When:   	What:										|
    |   =========== ======= ===========	=========================================	|
    |   01.00.00	WJF		01/21/08	Original Creation							|
	|																				|
    +-------------------------------------------------------------------------------+
         
*/

//includes
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "windows.h"
#include "wbemidl.h"
#include "smbios_tables.h"
#include "bios_info.h"
#include <memory>
#include <fstream.h>

//#include "cache.h"
//#include "enclosure.h"
//#include "mem_array_map.h"
//#include "mem_dev.h"
//#include "phys_mem_array.h"
//#include "processor.h"
//#include "slots.h"
//#include "sys_boot_info.h"
//#include "sys_info.h"

//defines
//////////////////////////////////////////////////////////////////////////
#define VERSION _T("01.00.00")

//global variables
//////////////////////////////////////////////////////////////////////////
bool use_file = false;
_TCHAR output_file_name[0xff];
unsigned char mask=1;
raw_smbios_data global_buffer;

//function prototypes
//////////////////////////////////////////////////////////////////////////
bool parse_command_line(int, _TCHAR* argv[]);
bool init_raw_smbios_data();
bool log(_TCHAR*);
bool return_next_table_of_type(supported_tables,void*,int*,bool);
int get_formatted_section_length(int);
int get_unformatted_section_length(int);
void p(_TCHAR *, ...);
void cls();
void get_string_resource_for_id(int, unsigned char *, _TCHAR *);
void add_the_directory(_TCHAR*);
bool log_an_entry_to_disk (_TCHAR*, _TCHAR*);

/*
	+---------------------------------------------------------------------------+
	|																			|
	|	main																	|
	|	=====																	|
	|																			|
	|	Inputs:		int argc													|
	|				_TCHAR* argv[]												|
	|																			|
	|	Returns:	int															|
	|																			|
	|	Notes:		Application entry point.									|
	+---------------------------------------------------------------------------+															
*/       /*
int _tmain(int argc, _TCHAR* argv[])
{
	bool good_command_line=true;

	if (argc>1) 
	{
		good_command_line=parse_command_line(argc,argv);
	}

	p(_T("BIOS Peek Utility (v) %s\n"),VERSION);
	p(_T("=======================================\n"));
	p(_T("By William J Francis\n"));
	p(_T("w.j.francis@tx.rr.com\n\n"));
	
	if (good_command_line)
	{
		if (!init_raw_smbios_data())
		{
			p(_T("Failed to initialize raw smb bios data.\n\n"));
		}
		else
		{
			show_bios_information();
			show_system_information();
			show_system_enclosure();
			show_processor_information();
			show_cache_information();
			show_system_slots();
			show_physical_memory_array();
			show_memory_device();
			show_memory_array_mapped_address();
			show_system_boot_information();
		}
	}

	if (!use_file)
	{
		p(_T("Press <ENTER> to exit"));
		getchar();
	}

	if (!good_command_line) 
		return -1;
	else
		return 0;
}
			   */
/*
	+---------------------------------------------------------------------------+
	|																			|
	|	parse_command_line														|
	|	==============================											|
	|																			|
	|	Inputs:		int arg_count												|
	|				_TCHAR* args[]												|
	|																			|
	|	Returns:	bool														|
	|																			|
	|	Notes:		Used to parse the command line.  Presently, this just		|
	|				means determining whether the output goes to the console	|
	|				or a file.													|
	+---------------------------------------------------------------------------+															
*/
bool parse_command_line(int arg_count, _TCHAR* args[])
{
	for (int i=1; i<arg_count; i++)
	{
		if (_wcsicmp(args[i],_T("-f"))==0)
		{
			if (++i > arg_count-1)
			{
				p(_T("You failed to specify a valid file name for the '-f' option.\n\n"));
				return false;
			}
			else
			{
//				wcscpy_s(output_file_name,_TRUNCATE,args[i]);
				use_file=true;
			}
		}
		else
		{
			p(_T("Unknown command line specified.\n"));
			p(_T("Currently supported command line:\n"));
			p(_T("memdevp -[options]\n"));
			p(_T("where supported options are:\n"));
			p(_T("-f filename\n"));
			p(_T("example: memdevp -f c:\\tmp\\ramlog.txt\n\n"));
			return false;
		}
	}
	return true;
}

/*
	+---------------------------------------------------------------------------+
	|																			|
	|	init_raw_smbios_data													|
	|	==============================											|
	|																			|
	|	Inputs:		void														|
	|																			|
	|	Returns:	bool														|
	|																			|
	|	Notes:		This function uses wbem to load our global buffer with		|
	|				the raw dump of the smbios data which the OS pulls on start	|
	|				up.  This data will not change without a reboot of the		|
	|				computer.  This technique is used in lieu of the API call	|
	|				
	+---------------------------------------------------------------------------+															
*/
bool init_raw_smbios_data()
{
	//zero raw dat memory
	memset(global_buffer.smbios_table_data,0,MAX_DATA);

	bool ret = false;
	HRESULT h_result;

    // Initialize COM.
    h_result =  CoInitializeEx(0, COINIT_MULTITHREADED); 
    if (h_result<0)
    {
        return false;              // Program has failed.
    }

    // Obtain the initial locator to Windows Management
    // on a particular host computer.
    
	IWbemLocator* p_locator = 0;

    h_result = CoCreateInstance(
        CLSID_WbemLocator,             
        0, 
        CLSCTX_INPROC_SERVER, 
        IID_IWbemLocator, (LPVOID *) &p_locator);
 
    if (h_result<0)
    {
        CoUninitialize();
        return false;       // Program has failed.
    }

    IWbemServices* p_service = 0;

    // Connect to the root\cimv2 namespace with the
    // current user and obtain pointer pSvc
    // to make IWbemServices calls.

    h_result = p_locator->ConnectServer(
        _T("ROOT\\WMI"),		 // WMI namespace
        NULL,                    // User name
        NULL,                    // User password
        0,                       // Locale
        NULL,                    // Security flags                 
        0,                       // Authority       
        0,                       // Context object
        &p_service                 // IWbemServices proxy
    );                              
    
    if (h_result<0)
    {
        p_locator->Release();     
        CoUninitialize();
        return false;                // Program has failed.
    }

    // Set the IWbemServices proxy so that impersonation
    // of the user (client) occurs.
    h_result = CoSetProxyBlanket(
       p_service,                      // the proxy to set
       RPC_C_AUTHN_WINNT,            // authentication service
       RPC_C_AUTHZ_NONE,             // authorization service
       NULL,                         // Server principal name
       RPC_C_AUTHN_LEVEL_CALL,       // authentication level
       RPC_C_IMP_LEVEL_IMPERSONATE,  // impersonation level
       NULL,                         // client identity 
       EOAC_NONE                     // proxy capabilities     
    );

    if (h_result<0)
    {
        p_service->Release();
        p_locator->Release();     
        CoUninitialize();
        return false;               // Program has failed.
    }

    IEnumWbemClassObject* p_enumerator = NULL;
    h_result = p_service->CreateInstanceEnum( _T("MSSMBios_RawSMBiosTables"), 0, NULL, &p_enumerator);
    
    if (h_result<0)
    {
        p_service->Release();
        p_locator->Release();     
        CoUninitialize();
        return false;               // Program has failed.
    }
    else
    { 
        do
        {
            IWbemClassObject* p_instance = NULL;
            ULONG dw_count = NULL;

            h_result = p_enumerator->Next(
                WBEM_INFINITE,
                1,
                &p_instance,
                &dw_count);      
			if(h_result>=0)
			{
				VARIANT variant_bios_data;
				VariantInit(&variant_bios_data);
				CIMTYPE type;

				h_result = p_instance->Get(_T("SmbiosMajorVersion"),0,&variant_bios_data,&type,NULL);
				if(h_result <0)
				{
					VariantClear(&variant_bios_data);
				}
				else
				{
					global_buffer.smbios_major_version = (unsigned char)variant_bios_data.iVal;
					VariantInit(&variant_bios_data);
					h_result = p_instance->Get(_T("SmbiosMinorVersion"),0,&variant_bios_data,&type,NULL);
					if(h_result<0)
					{
						VariantClear(&variant_bios_data);
					}
					else
					{
						global_buffer.smbios_minor_version = (unsigned char)variant_bios_data.iVal;
						VariantInit(&variant_bios_data);
						h_result = p_instance->Get(_T("SMBiosData"),0,&variant_bios_data,&type,NULL);
						if(h_result>=0)
						{
							if ( ( VT_UI1 | VT_ARRAY  ) != variant_bios_data.vt )
							{
							}
							else
							{
								SAFEARRAY* p_array = NULL;
								p_array = V_ARRAY(&variant_bios_data);
								unsigned char* p_data = (unsigned char *)p_array->pvData;

								global_buffer.length = p_array->rgsabound[0].cElements;
								if (global_buffer.length >= MAX_DATA) 
								{
									p(_T("Return global_buffer would overflow.  Abort initialization of raw SMBIOS data.\n"));
									p_service->Release();
									p_locator->Release();     
									CoUninitialize();
									return false;
								}
								memcpy(global_buffer.smbios_table_data,p_data,global_buffer.length);
							}
						}
						VariantClear(&variant_bios_data);
					}
				}
				break;
			}
    
        } while (h_result == WBEM_S_NO_ERROR);
    }
	
    p_service->Release();
    p_locator->Release();     
    CoUninitialize();

	return true;
}

/*
	+---------------------------------------------------------------------------+
	|																			|
	|	get_formatted_section_length											|
	|	==============================											|
	|																			|
	|	Inputs:		int index													|
	|																			|
	|	Returns:	int	length													|
	|																			|
	|	Notes:		Returns the length of the formatted section of a table		|
	|				beginning at the specified index within the					|
	|				global buffer.												|
	+---------------------------------------------------------------------------+															
*/
int get_formatted_section_length(int index)
{
	int type = global_buffer.smbios_table_data[index];
	if (( type <0) || (type > 127)) return 0; //error
	int length = (int)global_buffer.smbios_table_data[index+1];
	return length;
}

/*
	+---------------------------------------------------------------------------+
	|																			|
	|	get_unformatted_section_length											|
	|	==============================											|
	|																			|
	|	Inputs:		int index													|
	|																			|
	|	Returns:	int	length													|
	|																			|
	|	Notes:		Returns the length of the unformatted section of a table	|
	|				(string table) beginning at the specified index within the	|
	|				global buffer.												|
	+---------------------------------------------------------------------------+															
*/
int get_unformatted_section_length(int index)
{
	int start_point=index;
	int unformatted_section_length=(int)global_buffer.smbios_table_data[index+1];
	index+=unformatted_section_length;
	while (index < MAX_DATA-1)
	{
		if ((global_buffer.smbios_table_data[index]==0) && (global_buffer.smbios_table_data[index+1]==0))
		{
			return index-unformatted_section_length+2-start_point;
		}
		index++;
	}
	return 0;
}
/*
	+---------------------------------------------------------------------------+
	|																			|
	|	return_next_table_of_type												|
	|	==========================												|
	|																			|
	|	Inputs:		supported_tables table_type_to_find							|
	|				void* p_return_buffer										|
	|				int* return_buffer_length									|
	|				bool reset													|
	|																			|
	|	Returns:	bool														|
	|																			|
	|	Notes:		Use this method to copy a complete table of the specifed	|
	|				type into a local buffer.  The method uses the global		|
	|				buffer which contains all tables and starts the search at	|
	|				the current index position (wherever the last search left	|
	|				off) unless the reset flag is set.							|
	+---------------------------------------------------------------------------+															
*/
bool return_next_table_of_type(supported_tables table_type_to_find, void* p_return_buffer, int* return_buffer_length, bool reset)
{
	static int index;
	int formatted_section_length=0;
	int unformatted_section_length=0;
	int current_table_length=0;

	if (reset) index=0;

	while(true)
	{
		formatted_section_length = get_formatted_section_length(index);
		unformatted_section_length = get_unformatted_section_length(index);
		current_table_length = formatted_section_length+unformatted_section_length;
		
		//check the first 
		if (global_buffer.smbios_table_data[index]==table_type_to_find)
		{
			if (current_table_length < *return_buffer_length)
			{
				memcpy(p_return_buffer,&(global_buffer.smbios_table_data[index]),current_table_length);
				*return_buffer_length=current_table_length;
			}
			else
			{
				break;
				//indicates an error even though table was found...your buffer was too small
			}
			index+=current_table_length;
			return true;
		}
		
		index+=current_table_length;

		if (current_table_length==0) break;
	}
	*return_buffer_length=0;
	return false;
}

/*
	+---------------------------------------------------------------------------+
	|																			|
	|	p																		|
	|	==																		|
	|																			|
	|	Inputs:		_TCHAR*  msg												|
	|				_TCHAR* format												|
	|																			|
	|	Returns:	void														|
	|																			|
	|	Notes:		Displays the contents of msg formatted via the optional		|
	|				format string (printf style) so long as the disk log		|
	|				command line switch was not thrown.  Otherwise, the entry	|
	|				gets logged to the file specified on the command line.		|
	+---------------------------------------------------------------------------+															
*/
void p(_TCHAR *msg, ...)
{

unique_ptr<ofstream> a(new ofstream);



	va_list argList;
	va_start(argList, msg);


	(*a).open("Wyniki.txt", ios::out | ios::app);

		*a << msg << "  ||  " << argList

		<< "\n";

		(*a).close();

//		vwprintf(msg, argList);
	//}
	va_end(argList);
}

		/*
void p(String *msg, ...)
{

unique_ptr<ofstream> a(new ofstream);



	va_list argList;
	va_start(argList, msg);


	(*a).open("Wyniki.txt", ios::out | ios::app);

		*a << msg << "  ||  " << argList

		<< "\n";

		(*a).close();

//		vwprintf(msg, argList);
	//}
	va_end(argList);
}         */

/*
	+---------------------------------------------------------------------------+
	|																			|
	|	get_string_resource_for_id												|
	|	==========================												|
	|																			|
	|	Inputs:		int target_id												|
	|				unsigned char * in_buf										|
	|				_TCHAR * out_string											|
	|																			|
	|	Returns:	void														|
	|																			|
	|	Notes:		Takes an integer that identifies the string resource		|
	|				required from buffer.  This string resource is then copied	|
	|				into the out string buffer.									|
	+---------------------------------------------------------------------------+															
*/
void get_string_resource_for_id(int target_id, unsigned char * in_buf, _TCHAR * out_string)
{
	char array_of_string_entries[MAX_STRING_TABLE][MAX_STRING];
	int index = (int)*(in_buf+1);
	int id=0;
	int still_more_data = *(in_buf+index) + *(in_buf+index+1);
	while (still_more_data)
	{
		int start_of_this_string = index;
		while (*(in_buf+index)!=0)
		{
			index++;
		}
		int len = index - start_of_this_string;
		index++;
		if (len > 0)
		{
			memcpy(array_of_string_entries[id],in_buf+start_of_this_string,len+1);
		}
		id++;
		still_more_data = *(in_buf+index) + *(in_buf+index+1);
	}
	target_id-=1;
	if (target_id > id)
	{
		*(out_string)=NULL;
	}
	else
	{
		mbstowcs(out_string,array_of_string_entries[target_id],MAX_STRING*sizeof(_TCHAR));	
	}
}

/*
	+---------------------------------------------------------------------------+
	|																			|
	|	log_an_entry_to_disk												    |
	|	======================													|
	|																			|
	|	Inputs:		_TCHAR* oneLineOfText										|
	|				_TCHAR* fileName											|
	|																			|
	|	Returns:	bool														|
	|																			|
	|	Notes:		Write a single line to a file.  Inserts at the beginning	|
	|				and bumps everyone down one, lopping off any record that	|
	|				ends up past maxLine										|
	+---------------------------------------------------------------------------+															
*/
bool log_an_entry_to_disk (_TCHAR* what_to_log, _TCHAR* where_to_log)
{
	//Must create the directory
	add_the_directory(where_to_log);

	//open for append
	FILE* ofp = _wfopen(where_to_log,_T("a"));

	//write the new line to the start
	fputws(what_to_log,ofp);
	
	//Finally close our write handle
	fclose(ofp);

	return true;
}

/*
	+---------------------------------------------------------------------------+
	|																			|
	|	add_the_directory														|
	|	======================													|
	|																			|
	|	Inputs:		_TCHAR* fullyQualifiedFileName								|
	|																			|
	|	Returns:	void														|
	|																			|
	|	Notes:		Parses a fully qualified filename, such as:					|
	|				c:\windows\temp\ipmi\ipmi.log								|
	|				and recurses through the structure creating each folder		|
	|				as needed.													|
	+---------------------------------------------------------------------------+															
*/
void add_the_directory(_TCHAR* dir_plus_filename)
{
	int len = (int)wcslen(dir_plus_filename);
	_TCHAR buf[MAX_STRING];

	for (int i=0; i< len; i++)
	{
		//Doesn't hurt, we'll just try it
		if (dir_plus_filename[i]=='\\')
		{
			buf[i]=NULL;
			CreateDirectory(buf,0);
		}
		buf[i]=dir_plus_filename[i];
	}
}