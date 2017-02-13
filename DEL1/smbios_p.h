#ifndef smbios_pH
#define smbios_pH

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
void p(String *msg, ...);
void p(_TCHAR *, ...);
void cls();
void get_string_resource_for_id(int, unsigned char *, _TCHAR *);
void add_the_directory(_TCHAR*);
bool log_an_entry_to_disk (_TCHAR*, _TCHAR*);


#endif