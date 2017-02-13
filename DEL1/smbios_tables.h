//General
#ifndef smbios_tablesH
#define smbios_tablesH
////////////////////////////////////////////////////////////////
#define MAX_DATA 0xFA00 //64K
#define MAX_STRING 0x3E8 //1K
#define MAX_STRING_TABLE 0x19 //25
#define MAX_CONTAINED_ELEMENTS 0xFF //255
#define MAX_CONTAINED_RECORD 0xFF //255
#define SMALL_STRING 0x64 //100
#define BIGGER_STRING 0xFF //255

//enum
////////////////////////////////////////////////////////////////
enum supported_tables
{
	bios_info = 0x00,
	sys_info = 0x01,
	enclosure = 0x03,
	processor = 0x04,
	cache = 0x07,
	slots = 0x09,
	phys_mem_array = 0x10,
	mem_dev = 0x11,
	mem_array_map_addr = 0x13,
	sys_boot_info = 0x20
};
//Mask 
///////////////////////////////////////////////////////////////
#define BIOS_INFORMATION 0x01
#define SYSTEM_INFORMATION 0x02
#define SYSTEM_ENCLOSURE 0x04
#define PROCESSOR_INFORMATION 0x08
#define CACHE_INFORMATION 0x10
#define SYSTEM_SLOTS 0x20
#define PHYSICAL_MEMORY_ARRAY 0x40
#define MEMORY_DEVICE 0x80
#define MEMORY_ARRAY_MAPPED_ADDRESS 0x100
#define SYSTEM_BOOT_INFORMATION 0x200
//(Note we are only supporting the required tables required by all BIOS mfgs.  Other vendor specific tables are available.  See spec.)

// Generic Structures
////////////////////////////////////////////////////////////////
struct raw_smbios_data
{
    unsigned char	smbios_major_version;
    unsigned char	smbios_minor_version;
    unsigned int	length;
    unsigned char	smbios_table_data[MAX_DATA];
};

struct required
{
	unsigned char type; //Type of table (spec allows 0 - 127)
	unsigned char length; //Length of formatted area, starting at type (does not include any string tables)
	unsigned short handle; //Unique handle for this structure for later recall
};

#endif
