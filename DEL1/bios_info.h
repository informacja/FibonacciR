// BIOS Information (TYPE 0)
/////////////////////////////////////////////////////////////////
#ifndef bios_infoH
#define bios_infoH

#include "smbios_tables.h"

struct bios_info_type_0
{
	required header;
	_TCHAR vendor[MAX_STRING*sizeof(_TCHAR)];				//0x04 Bios Vendor's Name
	_TCHAR bios_version[MAX_STRING*sizeof(_TCHAR)];			//0x05 Free form version info
	unsigned short start_addr_segment;						//0x06 Segment location of bios starting address
	_TCHAR bios_release_date[MAX_STRING*sizeof(_TCHAR)];	//0x08 mm/dd/yy or mm/dd/yyyy
	unsigned char bios_rom_size;							//0x09 Size(n) where 64k*(n+1) is size of physical device device containing bios in bytes
	unsigned long bios_characteristics;						//0x0A See characteristics table (0.0) below
	unsigned char bios_extension1;							//0x12 Optional space reserved for extensions. (Length in offset 1 - 0x12) tables 0.1 and 0.2
	unsigned char bios_extension2;							//0x13 Optional space reserved for extensions. (Length in offset 1 - 0x12) tables 0.1 and 0.2
	unsigned char sys_bios_major;							//0x14 Major release for system bios (e.g. bios = 10.2, sys_bios_major = 0x0A)
	unsigned char sys_bios_minor;							//0x15 Minor release for system bios (e.g. bios = 10.2, sys_bios_minor = 0x02)
	unsigned char embedded_controller_fw_major;				//0x16 Major release for embedded firmware
	unsigned char embedded_controller_fw_minor;				//0x17 Minor release for embedded firmware
};

//Table 0.0 bios characteristics
#define RESERVED1 0x01 
#define RESERVED2 0x02 
#define UNKNOWN 0x04 
#define NOT_SUPPORTED8 0x08 
#define ISA_SUPPORTED 0x10 
#define MCS_SUPPORTED 0x20 
#define ESIA_SUPPORTED 0x40 
#define PCI_SUPPORTED 0x80 
#define PCMCIA_SUPPORTED 0x100
#define PNP_SUPPORTED 0x200 
#define APM_SUPPORTED 0x400
#define BIOS_FLASHABLE 0x800
#define BIOS_SHADOW_SUPPORTED 0x1000
#define VL_VESA_SUPPORTED 0x2000
#define ESCD_SUPPORTED 0x4000
#define CD_BOOT_SUPPORTED 0x8000 
#define SELECT_BOOT_SUPPORTED 0x10000
#define BIOS_ROM_SOCKETED 0x20000
#define PCCARD_BOOT_SUPPORTED 0x40000
#define EDD_SUPPORTED 0x80000
#define INT_13H_JAP_FLOPPY_NEC_SUPPORTED 0x100000
#define INT_13H_JAP_FLOPPY_TOSHIBA_SUPPORTED 0x200000
#define INT_13H_525_360KB_FLOPPY_SUPPORTED 0x400000
#define INT_13H_525_12MB_FLOPPY_SUPPORTED 0x800000
#define INT_13H_35_720KB_FLOPPY_SUPPORTED 0x1000000 
#define INT_13H_35_288MB_FLOPPY_SUPPORTED 0x2000000
#define INT_5H_PRINT_SCREEN_SUPPORTED 0x4000000
#define INT_9H_842_KEYBD_SUPPORTED 0x8000000
#define INT_14H_SERIAL_SUPPORTED 0x10000000 
#define INT_17H_PRINTER_SUPPORTED 0x20000000 
#define INT_10H_CGA_MONO_VIDEO_SUPPORTED 0x40000000 
#define NEC_PC_98 0x80000000

//table 0.1 BIOS characteristics extension byte 1
#define ACPI_SUPPORTED 0x01 
#define USB_LEGACY_SUPPORTED 0x02 
#define AGP_SUPPORTED 0x04 
#define I20_SUPPORTED 0x08 
#define LS120_SUPPORTED 0x10 
#define ATAPI_ZIP_BOOT_SUPPORTED 0x20
#define BOOT_1394_SUPPORTED 0x40 
#define SMART_BATTERY_SUPPORTED 0x80 

//table 0.2 BIOS characteristics extension byte 2
#define BIOS_BOOT_SPEC_SUPPORTED 0x01 
#define FUNC_KEY_INIT_NET_BOOT_SUPPORTED 0x02 
#define TARGET_CONTENT_DIST_SUPPORTED 0x04 

//prototypes
bool show_bios_information();

#endif
