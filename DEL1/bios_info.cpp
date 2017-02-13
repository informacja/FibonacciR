/*
	+-------------------------------------------------------------------------------+
	|																				|
	|	File: 				bios_info												|
	|						=================================================		|
	|	Dev Platform:		WinXP SP2 2.3GHZ 2GB RAM								|
	|	Dev Environment: 	Visual Studio.NET 2005 									|
	|	Target:				Windows Server 2003 R2 (x86,x64)						|
	|	Purpose:			Display and support functions for table type 0x00		|
	|						=================================================		|
	+-------------------------------------------------------------------------------+

*/

#include "stdafx.h"
#include "windows.h"
//#include "smbios_tables.h"
#include "bios_info.h"
#include "smbios_p.h"
#include <VCL.H>


extern bool use_file;
//extern void p(_TCHAR *, ...);
//extern bool return_next_table_of_type(supported_tables,void*,int*,bool);
//extern void get_string_resource_for_id(int, unsigned char *, _TCHAR *);

void pe(String msg, ...)
{

unique_ptr<ofstream> a(new ofstream);



	va_list argList;
	va_start(argList, msg);


	(*a).open("Wyniki.txt", ios::out | ios::app);

		*a << &msg << "  ||  " << argList

		<< "\n";

		(*a).close();

//		vwprintf(msg, argList);
	//}
	va_end(argList);
}


bool show_bios_information()
{
	bool result=false;
	unsigned char buf[MAX_DATA];
	unsigned char* p_buf = buf;
	int len=MAX_DATA;
	memset(buf,0,MAX_DATA);
	pe( ("BIOS_INFO_TYPE_0\n") );
//	AnsiString =  "BIOS_INFO_TYPE_0\n";
	//there is only ever one bios info table so...
	if (return_next_table_of_type(bios_info,&buf,&len,true))
	{
		//build the table up
		bios_info_type_0 t0;
		memset(&t0,0,sizeof(bios_info_type_0));
		memcpy(&t0.header,buf,4);
		get_string_resource_for_id(buf[0x04],p_buf,t0.vendor);
		get_string_resource_for_id(buf[0x05],p_buf,t0.bios_version);
		memcpy(&t0.start_addr_segment,&buf[0x06],2);
		get_string_resource_for_id(buf[0x08],p_buf,t0.bios_release_date);
		t0.bios_rom_size=buf[0x09];
		memcpy(&t0.bios_characteristics,&buf[0x0A],4);
		//determine optional bytes
		int number_of_optional_bytes=buf[0x01]-0x12;
		memcpy(&t0.bios_extension1,&buf[0x12],number_of_optional_bytes);
		//now display what we found out
			p( _T("vendor:%s\n"),t0.vendor)
			;
		p(_T(" vendor:%s\n"),t0.vendor);
		p(_T(" version string:%s\n"),t0.bios_version);
		p(_T(" start segment:0x%04x\n"),t0.start_addr_segment);
		p(_T(" release date:%s\n"),t0.bios_release_date);
		p(_T(" rom size:0x%02x\n"),t0.bios_rom_size);
		p(_T("  characterizations:\n"));
		if (t0.bios_characteristics & ISA_SUPPORTED) p(_T("    isa supported\n"));
		if (t0.bios_characteristics & MCS_SUPPORTED) p(_T("    mcs supported\n"));
		if (t0.bios_characteristics & ESIA_SUPPORTED) p(_T("    eisa supported\n"));
		if (t0.bios_characteristics & PCI_SUPPORTED) p(_T("    pci supported\n"));
		if (t0.bios_characteristics & PCMCIA_SUPPORTED) p(_T("    pccards supported\n"));
		if (t0.bios_characteristics & PNP_SUPPORTED) p(_T("    plug n play supported\n"));
		if (t0.bios_characteristics & APM_SUPPORTED) p(_T("    apm supported\n"));
		if (t0.bios_characteristics & BIOS_FLASHABLE) p(_T("    bios flash upgradable\n"));
		if (t0.bios_characteristics & BIOS_SHADOW_SUPPORTED) p(_T("    bios shadowing supported\n"));
		if (t0.bios_characteristics & VL_VESA_SUPPORTED) p(_T("    vl-vesa supported\n"));
		if (t0.bios_characteristics & ESCD_SUPPORTED) p(_T("    escd supported\n"));
		if (t0.bios_characteristics & CD_BOOT_SUPPORTED) p(_T("    cd boot supported\n"));
		if (t0.bios_characteristics & SELECT_BOOT_SUPPORTED) p(_T("    selectable boot device\n"));
		if (t0.bios_characteristics & BIOS_ROM_SOCKETED) p(_T("    socketed rom\n"));
		if (t0.bios_characteristics & PCCARD_BOOT_SUPPORTED) p(_T("    boot from pccard supported\n"));
		if (t0.bios_characteristics & EDD_SUPPORTED) p(_T("    edd supported\n"));
		if (t0.bios_characteristics & INT_13H_JAP_FLOPPY_NEC_SUPPORTED) p(_T("    japanese nec floppy supported\n"));
		if (t0.bios_characteristics & INT_13H_JAP_FLOPPY_TOSHIBA_SUPPORTED) p(_T("    japanese toshiba floppy supported\n"));
		if (t0.bios_characteristics & INT_13H_525_360KB_FLOPPY_SUPPORTED) p(_T("    5.25 360kb floppy supported\n"));
		if (t0.bios_characteristics & INT_13H_525_12MB_FLOPPY_SUPPORTED) p(_T("    5.25 1.2mb floppy supported\n"));
		if (t0.bios_characteristics & INT_13H_35_720KB_FLOPPY_SUPPORTED) p(_T("    3.5 720kb floppy supported\n"));
		if (t0.bios_characteristics & INT_13H_35_288MB_FLOPPY_SUPPORTED) p(_T("    3.5 2.88mb floppy supported\n"));
		if (t0.bios_characteristics & INT_5H_PRINT_SCREEN_SUPPORTED) p(_T("    print screen supported\n"));
		if (t0.bios_characteristics & INT_9H_842_KEYBD_SUPPORTED) p(_T("    8042 keyboard supported\n"));
		if (t0.bios_characteristics & INT_14H_SERIAL_SUPPORTED) p(_T("    serial service supported\n"));
		if (t0.bios_characteristics & INT_17H_PRINTER_SUPPORTED) p(_T("    print service supported\n"));
		if (t0.bios_characteristics & INT_10H_CGA_MONO_VIDEO_SUPPORTED) p(_T("    cga/mono video supported\n"));
		p(_T("  extensions:\n"));
		if (t0.bios_characteristics & NEC_PC_98) p(_T("    nec pc 98 supported\n"));
		if (t0.bios_extension1 & ACPI_SUPPORTED) p(_T("    acpi supported\n"));
		if (t0.bios_extension1 & USB_LEGACY_SUPPORTED) p(_T("    legacy usb supported\n"));
		if (t0.bios_extension1 & AGP_SUPPORTED) p(_T("    agp supported\n"));
		if (t0.bios_extension1 & I20_SUPPORTED) p(_T("    i2o supported\n"));
		if (t0.bios_extension1 & LS120_SUPPORTED) p(_T("    ls120 supported\n"));
		if (t0.bios_extension1 & ATAPI_ZIP_BOOT_SUPPORTED) p(_T("    boot from atapi zip disk supported\n"));
		if (t0.bios_extension1 & BOOT_1394_SUPPORTED) p(_T("    boot from ieee 1394 disk supported\n"));
		if (t0.bios_extension1 & SMART_BATTERY_SUPPORTED) p(_T("    smart battery supported\n"));
		if (t0.bios_extension2 & BIOS_BOOT_SPEC_SUPPORTED) p(_T("    bios boot specification supported\n"));
		if (t0.bios_extension2 & FUNC_KEY_INIT_NET_BOOT_SUPPORTED) p(_T("    function key initiated network boot supported\n"));
		if (t0.bios_extension2 & TARGET_CONTENT_DIST_SUPPORTED) p(_T("    third party target content distribution support\n"));
		p(_T(" system bios major release:0x%02x\n"),t0.sys_bios_major);
		p(_T(" system bios minor release:0x%02x\n"),t0.sys_bios_minor);
		p(_T(" embedded controller firmware major release:0x%02x\n"),t0.embedded_controller_fw_major);
		p(_T(" embedded controller firmware minor release:0x%02x\n"),t0.embedded_controller_fw_minor);
		p(_T("\n"));
		result = true;
	}
	else
	{
		p(_T(" An error occurred retrieving this data from the bios.  No information available.\n"));
		p(_T("\n"));
		result = false;
	}
	return result;
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
*/    /*
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
*/  /*
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
}             */
