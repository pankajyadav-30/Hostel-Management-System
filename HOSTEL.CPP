
//REQUIRED CONSTANT DECLARATIONS
const int SINGLE	= 101;
const int DOUBLE	= 102;
const int SHADOW	= 103;
const int NO_SHADOW	= 104;
const int FRONT		= 105;
const int REAR		= 106;
const int TRUE		= 107;
const int FALSE		= 108;
const int YES		= 109;
const int NO		= 110;

//REQUIRED STANDARD LIBRARIES
#include <dir.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>

//REQUIRED STRUCTURE DEFINITIONS
struct member
{
	char name[ 50 ];
        char address[ 50 ];
        char phone[ 50 ];
        char qualification[ 50 ];
        char room_no[ 21 ];
        int  sex;
        int  day;
        int  month;
        int  year;
} temp_member;

struct expenses
{
	char  item[ 21 ];
        float price;
        int   day;
        int   month;
        int   year;
} temp_expenses;

struct bill
{
	float amount;
        char  contributor[ 50 ];
        int   day;
        int   month;
        int   year;
} temp_bill;

struct room
{
        char room_no[ 21 ];
        int  capacity;
        int  day;
        int  month;
        int  year;
} temp_room;

//REQUIRED GLOBAL VARIABLES
char expenses_file[ 50 ];

//REQUIRED FUNCTION PROTOTYPES

//FUNCTIONS FOR MANIPULATING MENU SYSTEM
void main_menu( void );
int  reports_menu( void );
int  sub_menu( int row );

//FUNCTIONS FOR DISPLAYING REPORTS
void members_report( void );
void expenses_report( void );
void bills_report( void );
void rooms_report( void );

//FUNCTIONS FOR COUNTING RECORDS
int count_member_records( void );
int count_expenses_records( void );
int count_bills_records( void );
int count_room_records( void );

//FUNCTIONS FOR FINDING RECORDS
int find_member_record( int record_no );
int find_expenses_record( int record_no );
int find_bills_record( int record_no );
int find_room_record( int record_no );

//FUNCTIONS FOR WRITING RECORDS
void write_member_record_to_file( void );
void write_expenses_record_to_file( void );
void write_bill_record_to_file( void );
void write_room_record_to_file( void );

//FUNCTIONS FOR REMOVING RECORDS
void remove_member_record( int recod_no );
void remove_expenses_record( int record_no );
void remove_bills_record( int record_no );
void remove_room_record( int record_no );

//FUNCTIONS FOR MODIFYING RECORDS
void modify_member_record( int record_no );
void modify_expenses_record( int record_no );
void modify_bills_record( int record_no );
void modify_room_record( int record_no );

//DATA TYPE CONVERSION FUNCTIONS
char * float_to_string( float value );
int    string_to_float( char * string , float * value );
int    string_to_int( char * string , int * value );

//FUNCTIONS FOR WRITING AND READING BACK SETTINGS
void write_settings_to_file( char * file_name );
void load_settings( void );

//DIALOG BOXES
void msgbox( char * title , char * message , int page );
int  yes_no( char * message );

int add_member_record_dialog_box( int load_values );
int add_expenses_record_dialog_box( int load_values );
int add_bill_record_dialog_box( int load_values );
int add_room_record_dialog_box( int load_values );

int read_member_record_dialog_box( int * record_no );
int read_expenses_record_dialog_box( int * record_no );
int read_bills_record_dialog_box( int * record_no );
int read_room_record_dialog_box( int * record_no );

void settings_dialog_box( void );
int  ask_filename_dialog_box( char  * file );

//FUNCTIONS FOR WRITING REPORTS TO FILES
void write_members_report_to_file( char * file );
void write_bills_report_to_file( char * file );
void write_expenses_report_to_file( char * file );
void write_rooms_report_to_file( char * file );

//COMMON FUNCTIONS
void draw_border( int x1 , int y1 , int x2 , int y2 , int type , int fore_ground_color , int back_ground_color , int shadow , int page );
void draw_line( int type , int row , int from , int to , int fore_ground_color , int back_ground_color , int page );
void fill_screen( int x1 , int y1 , int x2 , int y2 , int color , int page );
void display_string( char *string , int color , int back_ground_color , int hot_key_color , int column, int row , int shadow , int page );
void modified_display_string( char * string );
void goto_xy( int x , int y , int page );
void dos_shell( void );
int  does_room_number_exist( char * room_no );
int  count_members_in_the_room( char * room_no );
char * get_date_string( int day , int month , int year );

void copy_video_page( int from ,int to );
void change_active_video_page( int to );

int  find_color_attribute( int fore_ground_color , int back_ground_color );
int  is_filename_valid( char * filename );
int  is_chronological( date first, date second );

//FUNCTIONS FOR FINDING TOTAL AND BALANCE AMOUNTS
float find_balance_amount( void );
float find_total_amount( void );

//REQUIRED CLASS DEFINITIONS

// THE KEY CLASS ( TO READ KEY STROKES )

class key
{
private:
	int ascii_code;
	int scan_code;
public:
        key()
        {
		ascii_code = scan_code = 99;
        }

	void read_key_stroke( void );
	void set_values( int asc , int scan );
	void init( void );

	int get_ascii_code( void );
	int get_scan_code( void );
};

void key :: set_values( int asc , int scan )
{
	ascii_code = asc;
	scan_code  = scan;
}

void key :: init( void )
{
	ascii_code = scan_code = 99;
	fflush( stdin );
}

int key :: get_ascii_code( void )
{
	return ( ascii_code );
}

int key :: get_scan_code( void )
{
	return ( scan_code );
}

void key :: read_key_stroke( void )
{
	init();

	while( ! kbhit() );

	ascii_code = getch();

	if( ascii_code == 0 )
	{
		scan_code = getch();
	}
}

// THE TEXTBOX CLASS

class text_box
{
private:
	char text[ 50 ];

	int current_size;
	int current_position;

	int from;
	int length;
	int row;
	int skip;
        int page;

	key my_key;
public:
	text_box() {}
	text_box( int fr , int len , int ro , int page );
	void initialize( int fr , int len , int ro , int page );

	int  read( void );
	void draw_textbox( int color = 11 , int back_ground_color = 1 );

	void left_arrow( void );
	void right_arrow( void );

	void back_space( void );
	void del( void );

	void home( void );
	void end( void );
	void character( void );

	int  got_focus( void );
	void lost_focus( void );

	char * get_text( void );
	void set_text( char * string );
};

text_box :: text_box( int fr , int len , int ro , int page )
{
	initialize( fr , len , ro , page );
}

void text_box :: initialize( int fr , int len , int ro , int pag )
{
	length = len;
	current_position = 0;

	skip = 0;
	from = fr;
	row = ro;
        page = pag;

	current_size = 0;
	strcpy( text , "" );
}

int text_box :: got_focus( void )
{
	int result;

	if( current_size > length )
	{
		current_position = length - 1;
		skip = current_size - length + 1;
	}
	else
	{
		skip = 0;
		current_position = current_size;
	}

        _setcursortype( _NORMALCURSOR );
	result = read();
	lost_focus();

	return ( result );
}

void text_box :: lost_focus( void )
{
	strupr( text );
	skip = 0;
	draw_textbox( 11 , 1 );
        _setcursortype( _NOCURSOR );
}

char * text_box :: get_text( void )
{
        if( current_size <= 49 )
        {
		text[ current_size ] = '\0';
        }
        else
        {
		text[ 49 ] = '\0';
        }

	return ( text );
}

void text_box :: set_text( char *String )
{
        int len;
	strcpy( text , String );
        len = strlen( String );

        if( len <= 50 )
        {
		current_size = strlen( String );
        }
        else
        {
        	current_size = 50;
        }
}

int text_box :: read( void )
{
	int repeat_loop = 1;

	while( repeat_loop )
	{
		draw_textbox( 15, 1 );
		goto_xy( from + current_position + 1 , row , page );

		my_key.read_key_stroke();

		if( my_key.get_ascii_code() == 0 )
		{
			switch( my_key.get_scan_code() )
			{
				case 75: //left arrow
					left_arrow();
					break;

				case 77: //right
					right_arrow();
					break;

				case 71: //home key
					home();
					break;

				case 79: //end key
					end();
					break;

				case 83: //del key
					del();
					break;

				case 15: //shift tab
					return ( 1 );
			}
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 8://back_space
					back_space();
					break;

				case 9://tab
					return ( 2 );

				case 13://enter
					return ( 3 );

				case 27: //esc
					return ( 4 );

				default:
					character();
					break;
			}
		}
	}

	return ( 0 );
}

void text_box :: right_arrow( void )
{
	if( ( current_position == length - 1 ) && ( skip + current_position < current_size ) )
	{
		skip++;
	}

	if( ( current_position < length - 1 ) && ( skip + current_position < current_size ) )
	{
		current_position++;
	}
}

void text_box :: left_arrow( void )
{
	if( current_position == 0 && skip > 0 )
	{
		skip--;
	}

	if( current_position > 0 )
	{
		current_position--;
	}
}

void text_box :: del( void )
{
	if( current_size == 0 || skip + current_position == current_size )
	{
		return;
	}

	for(int i = skip + current_position ; i < current_size ; i++ )
	{
		text[ i ] = text[ i + 1 ];
	}

	current_size--;

	if( skip > 0 )
	{
		skip--;
		current_position++;
	}
}

void text_box :: end( void )
{
	if( current_size < length )
	{
		skip = 0;
		current_position = current_size;
	}
	else
	{
		skip = current_size - length + 1;
		current_position = length - 1;
	}
}

void text_box :: back_space( void )
{
	int l;

	if( current_position == 0 )
	{
		return;
	}

	for( l = ( skip + current_position ) ; l < current_size ; l++ )
	{
		text[ l - 1 ] = text[ l ];
	}

	current_size--;

	if( skip > 0 )
	{
		skip--;
	}
	else
	{
		current_position--;
	}
}

void text_box :: character( void )
{
	int i;

	if( current_size >= 50 )
	{
		return;
	}

	current_size++;

	for( i = current_size - 1 ; i >= ( skip + current_position ) + 1 ; i-- )
	{
		text[ i ] = text[ i - 1 ];
	}

	text[i] = my_key.get_ascii_code();

	if( current_position == length - 1 )
	{
		skip++;
	}
	else
	{
		current_position++;
	}
}

void text_box :: home( void )
{
	skip = 0;
	current_position = 0;
}

void text_box :: draw_textbox( int color ,int back_ground_color )
{
	char far * vid_mem = ( char far * )0xB8000000L;
	vid_mem += ( page * 4096 );

	char far * v;
	v = ( char far* ) vid_mem + 160 * ( row - 1 ) + 2 * ( from - 1 );

	int i = skip;

	int attrib = find_color_attribute( color , back_ground_color );

	for( int j = 0 ; j < ( length + 2 ) ; j++ )
	{
		*v = ' ';
		v++;

		*v = attrib;
		v++;
	}

	v = ( char far* ) vid_mem + 160 * ( row - 1 ) + 2 * from;
	j = 0;

	while( i < current_size && j < length )
	{
		*v = text[ i ];
		v++;
		*v = attrib;

		i++;
		v++;
		j++;
	}
}

//THE DATE CLASS

class Date
{
private:
	int day;
        int month;
        int year;

	text_box textboxes[3];
        int tab_counter;
public:
	Date() {}
        int got_focus( int direction );
        void initialize( int from, int row );
        void initialize_textboxes( void );
        void set_date( int day , int month , int year );
        void reset( void );

        int get_day( void );
        int get_month( void );
        int get_year( void );

        int is_valid( void );
        void display_error_message( void );
};

void Date :: initialize(int from, int row)
{
       	textboxes[0].initialize(from      , 3 , row , 1 );
       	textboxes[1].initialize(from + 9  , 3 , row , 1 );
    	textboxes[2].initialize(from + 18 , 5 , row , 1 );

        tab_counter = 0;

        display_string( "DD", 0 , 7 , 4 , from + 6 , row , NO_SHADOW , 1 );
        display_string( "MM", 0 , 7 , 4 , from + 15 , row , NO_SHADOW , 1 );
        display_string( "YY", 0 , 7 , 4 , from + 26 , row , NO_SHADOW , 1 );

        reset();
}

void Date :: set_date( int d , int m , int y )
{
	day = d;
        month = m;
        year = y;
}

int Date :: got_focus( int direction )
{
        int result;
	int repeat_loop = 1;
        key my_key;

        tab_counter = 0;

        if( direction == REAR )
        {
        	tab_counter = 2;
        }

        while( repeat_loop )
        {
		result = textboxes[ tab_counter ].got_focus();

		switch( result )
		{
			case 1: //Shift tab
                        	if( is_valid() )
                                {
                                	if( tab_counter == 0 )
                                        {
                                        	result = 1;
                                                repeat_loop = 0;
                                        }
                                        else
                                        {
                                        	tab_counter--;
                                        }
                                }
				break;

			case 2: //tab
                        	if( is_valid() )
                                {
                                	if( tab_counter == 2 )
                                        {
                                        	result = 2;
                                                repeat_loop = 0;
                                        }
                                        else
                                        {
                                        	tab_counter++;
                                        }
                                }
				break;

			case 3: //Enter
                        	if( is_valid() )
                                {
					result = 3;
					repeat_loop = 0;
                                }
				break;

			case 4: //Escape
				result = 4;
				repeat_loop = 0;
				break;
		}
        }

        return ( result );
}

void Date :: reset( void )
{
        struct date temp_date;
        getdate( &temp_date );

        day = temp_date.da_day;
        month = temp_date.da_mon;
        year = temp_date.da_year;

        initialize_textboxes();
}

void Date :: initialize_textboxes( void )
{
        char string[ 100 ];

	itoa( day , string, 10 );
        textboxes[ 0 ].set_text( string );

	itoa( month , string, 10 );
        textboxes[ 1 ].set_text( string );

	itoa( year , string, 10 );
        textboxes[ 2 ].set_text( string );

	for(int i=0 ; i<=2 ; i++ )
        {
        	textboxes[i].draw_textbox( 11 , 1 );
        }
}

int Date :: get_day( void )
{
	return ( day );
}

int Date :: get_month( void )
{
	return ( month );
}

int Date :: get_year( void )
{
	return ( year );
}

int Date :: is_valid( void )
{
        int value = 0;
	int value_limits[ 3 ][ 2 ] = { 1 , 31 , 1 , 12 , 1900 , 2100 };
        int width_limits[ 3 ] = { 2 , 2 , 4 };
        int days_in_month[ 12 ] = { 31 , 28 , 31 , 30 , 31 , 30 ,
				    31 , 31 , 30 , 31 , 30 , 31 };
        char string[ 50 ];

        strcpy( string, textboxes[ tab_counter ].get_text() );

	int len = strlen( string );

        if( len == 0 || len > width_limits[ tab_counter ] )
        {
                display_error_message();
        	return ( 0 );
        }

	for( int i = 0 ; i < len ; i++ )
       	{
       		if( string[ i ] < 48 || string[ i ] > 57 )
                {
	                display_error_message();
                	return ( 0 );
                }
               	value = ( value * 10 ) + ( string[ i ] - 48  );
        }

        if( value < value_limits[ tab_counter ][ 0 ] || value > value_limits[ tab_counter ][1] )
        {
                display_error_message();
                return ( 0 );
        }
        else
        {
        	switch( tab_counter )
                {
                	case 0:
                        	day = value;
                        	break;
                        case 1:
                        	month = value;
                        	break;
                        case 2:
                        	year = value;
                        	break;
                }
        }

        int leap = 0;
        if( year % 4 == 0 )
       	{
        	leap = 1;

		if( year % 100 == 0 )
                {
                	if( year % 400 == 0 )
                        {
	                	leap = 1;
                        }
                        else
                        {
                        	leap = 0;
                        }
                }
        }

        if( leap )
        {
		days_in_month[ 1 ] = 29;
        }

        if( day > days_in_month[ month - 1 ] )
       	{
		tab_counter = 0;
                display_error_message();
                return ( 0 );
        }
}

void Date :: display_error_message( void )
{
	switch( tab_counter )
	{
               	case 0:
			msgbox( " ERROR " , " PLEASE ENTER A VALID DAY     " , 2 );
                       	break;
		case 1:
			msgbox( " ERROR " , " PLEASE ENTER A VALID MONTH   " , 2 );
                       	break;
		case 2:
			msgbox( " ERROR " , " PLEASE ENTER A VALID YEAR    " , 2 );
                       	break;
	}
}

//FUNCTIONS FOR WRITING REPORTS TO FILES

void write_members_report_to_file( char * filename )
{
        int record_no = 0;
        char temp_string[ 50 ];

        ofstream out_file;
        out_file.open( filename , ios::trunc | ios::binary );

        ifstream in_file;
        in_file.open( "MEMBERS.DAT" , ios::in | ios::binary );

	in_file.read( (char *) & temp_member , sizeof( temp_member ) );

        strcpy( temp_string , "\n                                MEMBERS REPORT");
        out_file.write( temp_string , strlen( temp_string ) );

        while( in_file )
	{
		record_no++;

                strcpy( temp_string , "\n\nRECORD NO. " );
		out_file.write( temp_string , strlen( temp_string ) );
		itoa( record_no , temp_string , 10 );
                strcat( temp_string , temp_string );
		out_file.write( temp_string , strlen( temp_string ) );

                strcpy( temp_string , "\nNAME         :   " );
                strcat( temp_string , temp_member.name );
                out_file.write( temp_string , strlen( temp_string ) );

                strcpy( temp_string , "\nSEX          :   " );
		if( temp_member.sex == 0 )
		{
                	strcat( temp_string , "MALE" );
		}
		else
		{
                	strcat( temp_string , "FEMALE" );
		}
                out_file.write( temp_string , strlen( temp_string ) );

                strcpy( temp_string , "\nADDRESS      :   " );
                strcat( temp_string , temp_member.address );
                out_file.write( temp_string , strlen( temp_string ) );

                strcpy( temp_string , "\nPHONE        :   " );
                strcat( temp_string , temp_member.phone );
                out_file.write( temp_string , strlen( temp_string ) );

                strcpy( temp_string , "\nQUALIFICATION:   " );
                strcat( temp_string , temp_member.qualification );
                out_file.write( temp_string , strlen( temp_string ) );

                strcpy( temp_string , "\nJOINING DATE :   " );
                strcat( temp_string , get_date_string( temp_member.day , temp_member.month , temp_member.year ) );
                out_file.write( temp_string , strlen( temp_string ) );

                strcpy( temp_string , "\nROOM NO.:   " );
                strcat( temp_string , temp_member.room_no );
                out_file.write( temp_string , strlen( temp_string ) );

		in_file.read( (char *) & temp_member , sizeof( temp_member ) );
	}

        in_file.close();
        out_file.close();
}

void write_expenses_report_to_file( char * filename )
{
        int record_no = 0;
        char temp_string[ 80 ];
	float balance_amount = find_total_amount();

	ofstream out_file;
        out_file.open( filename , ios::trunc | ios::binary );

        ifstream in_file;
        in_file.open( expenses_file , ios::in | ios::binary );

	in_file.read( (char *) & temp_expenses , sizeof( temp_expenses ) );

        strcpy( temp_string , "\n                                EXPENSES REPORT");
        out_file.write( temp_string , strlen( temp_string ) );

        strcpy( temp_string , "\n\nNO.  ITEM NAME              PRICE          DATE         BALANCE\n\n" );
        out_file.write( temp_string , strlen( temp_string ) );

        while( in_file )
	{
		record_no++;

		itoa( record_no , temp_string , 10 );
                strcat( temp_string , "." );
                out_file.write( temp_string , strlen( temp_string ) );
                out_file.seekp( 5 - strlen( temp_string ) , ios::cur );

                strcpy( temp_string , temp_expenses.item );
                out_file.write( temp_string , strlen( temp_string ) );
                out_file.seekp( 23 - strlen( temp_string ) , ios::cur );

                strcpy( temp_string , "Rs. " );
                strcat( temp_string , float_to_string( temp_expenses.price ) );
                out_file.write( temp_string , strlen( temp_string ) );
                out_file.seekp( 15 - strlen( temp_string ) , ios::cur );

                strcpy( temp_string , get_date_string( temp_expenses.day , temp_expenses.month , temp_expenses.year ) );
                out_file.write( temp_string , strlen( temp_string ) );
                out_file.seekp( 13 - strlen( temp_string ) , ios::cur );

                balance_amount = balance_amount - temp_expenses.price;
                strcpy( temp_string , "Rs. " );
                strcat( temp_string , float_to_string( balance_amount ) );
                strcat( temp_string , "\n" );
                out_file.write( temp_string , strlen( temp_string ) );

		in_file.read( (char *) & temp_expenses , sizeof( temp_expenses ) );
	}

        in_file.close();
        out_file.close();
}

void write_rooms_report_to_file( char * filename )
{
        int record_no = 0;
        char temp_string[ 80 ];

	ofstream out_file;
        out_file.open( filename , ios::trunc | ios::binary );

        ifstream in_file;
        in_file.open( "ROOMS.DAT" , ios::in | ios::binary );

	in_file.read( (char *) & temp_room , sizeof( temp_room ) );

        strcpy( temp_string , "\n                                ROOMS REPORT");
        out_file.write( temp_string , strlen( temp_string ) );

        strcpy( temp_string ,  "\n\nNO.  ROOM NO.                  CAPACITY      FILLED       DATE\n\n");
        out_file.write( temp_string , strlen( temp_string ) );

        while( in_file )
	{
		record_no++;

		itoa( record_no , temp_string , 10 );
                strcat( temp_string , "." );
                out_file.write( temp_string , strlen( temp_string ) );
                out_file.seekp( 5 - strlen( temp_string ) , ios::cur );

                strcpy( temp_string , temp_room.room_no );
                out_file.write( temp_string , strlen( temp_string ) );
                out_file.seekp( 26 - strlen( temp_string ) , ios::cur );

                itoa( temp_room.capacity , temp_string , 10 );
                out_file.write( temp_string , strlen( temp_string ) );
                out_file.seekp( 14 - strlen( temp_string ) , ios::cur );

                itoa( count_members_in_the_room( temp_room.room_no ) , temp_string , 10 );
                out_file.write( temp_string , strlen( temp_string ) );
                out_file.seekp( 13 - strlen( temp_string ) , ios::cur );

                strcpy( temp_string , get_date_string( temp_room.day , temp_room.month , temp_room.year ) );
                strcat( temp_string , "\n" );
                out_file.write( temp_string , strlen( temp_string ) );

		in_file.read( (char *) & temp_room , sizeof( temp_room ) );
	}

        in_file.close();
        out_file.close();
}

void write_bills_report_to_file( char * filename )
{
        int record_no = 0;
        char temp_string[ 80 ];
        float cumulative_total = 0;

	ofstream out_file;
        out_file.open( filename , ios::trunc | ios::binary );

        ifstream in_file;
        in_file.open( "BILLS.DAT" , ios::in | ios::binary );

	in_file.read( (char *) & temp_bill , sizeof( temp_bill ) );

        strcpy( temp_string , "\n                                BILLS REPORT" );
        out_file.write( temp_string , strlen( temp_string ) );

        strcpy( temp_string , "\n\nNO.  CONTRIBUTOR       DATE         AMOUNT          CUM. TOTAL\n\n" );
        out_file.write( temp_string , strlen( temp_string ) );

        while( in_file )
	{
		record_no++;

		itoa( record_no , temp_string , 10 );
                strcat( temp_string , "." );
                out_file.write( temp_string , strlen( temp_string ) );
                out_file.seekp( 5 - strlen( temp_string ) , ios::cur );

		strncpy( temp_string , temp_bill.contributor , 15 );
		temp_string[ 15 ] = '\0';
                out_file.write( temp_string , strlen( temp_string ) );
                out_file.seekp( 18 - strlen( temp_string ) , ios::cur );

                strcpy( temp_string , get_date_string( temp_bill.day , temp_bill.month , temp_bill.year ) );
                out_file.write( temp_string , strlen( temp_string ) );
                out_file.seekp( 13 - strlen( temp_string ) , ios::cur );

                strcpy( temp_string , "Rs. " );
                strcat( temp_string , float_to_string( temp_bill.amount ) );
                out_file.write( temp_string , strlen( temp_string ) );
                out_file.seekp( 16 - strlen( temp_string ) , ios::cur );

                cumulative_total += temp_bill.amount;
                strcpy( temp_string , "Rs. " );
                strcat( temp_string , float_to_string( cumulative_total ) );
                strcat( temp_string , "\n" );
                out_file.write( temp_string , strlen( temp_string ) );

		in_file.read( (char *) & temp_bill , sizeof( temp_bill ) );
	}

        in_file.close();
        out_file.close();
}

// DEFINITIONS OF COMMON FUNCTIONS

void draw_border( int x1 , int y1 , int x2 , int y2 , int type , int fore_ground_color , int back_ground_color , int shadow , int page )
{
	char far * vid_mem = ( char far * ) 0XB8000000 ;
	char far * v;

	vid_mem += ( page * 4096 ) ;
	char arr[ 6 ] , attrib;

	attrib = find_color_attribute( fore_ground_color , back_ground_color );

	if( type == DOUBLE )
	{
		strcpy( arr , "ÍºÉÈ»¼" );
	}
	else
	{
		strcpy( arr , "Ä³ÚÀ¿Ù" );
	}

	for( int i = x1 ; i < x2 ; i++ )
	{
		v = vid_mem + 160 * ( y1 - 1 ) + i * 2 ;
		*v = arr[ 0 ];
		v++;
		*v = attrib;

		v = vid_mem + 160 * ( y2 - 1 ) + i * 2 ;
		*v = arr[ 0 ];
		v++;
		*v = attrib;
	}

	for( i = y1 ; i < y2 - 1 ; i++ )
	{
		v = vid_mem + 160 * i + ( x1 - 1 ) * 2 ;
		*v = arr[ 1 ];
		v++;
		*v = attrib;

		v = vid_mem + 160 * i + ( x2 - 1 ) * 2 ;
		*v = arr[ 1 ];
		v++;
		*v = attrib;
	}

	v = vid_mem + 160 * ( y1 - 1 ) + ( 2 * ( x1 - 1 ) ) ;		*v = arr[ 2 ]; v++; *v = attrib;
	v = vid_mem + 160 * ( y2 - 1 ) + ( 2 * ( x1 - 1 ) ) ;		*v = arr[ 3 ]; v++; *v = attrib;
	v = vid_mem + 160 * ( y1 - 1 ) + ( 2 * ( x2 - 1 ) ) ;		*v = arr[ 4 ]; v++; *v = attrib;
	v = vid_mem + 160 * ( y2 - 1 ) + ( 2 * ( x2 - 1 ) ) ;		*v = arr[ 5 ]; v++; *v = attrib;

	if( shadow == SHADOW )
	{
		int i;

		for( i = x1 + 1 ; i < x2 ; i++ )
		{
			v = vid_mem + 160 * y2 + 2 * i ;
			v++;
			*v = 8;
		}

		for( i = y1 ; i <= y2 ; i++ )
		{
			v = vid_mem + 160 * i + 2 * x2 ;
			v++;
			*v = 8;

			v = vid_mem + 160 * i + 2 * x2 + 2 ;
			v++;
			*v = 8;
		}
	}
}

void draw_line( int type , int row , int from , int to , int fore_ground_color , int back_ground_color , int page )
{
	char far * vid_mem = ( char far * ) 0XB8000000 ;
	char far * v;

	vid_mem += page * 4096 ;

	int attrib = find_color_attribute( fore_ground_color , back_ground_color );
	char arr[ 3 ];

	if( type == SINGLE )
	{
		strcpy( arr , "ÃÄ´" );
	}
	else
	{
		strcpy( arr , "ÌÍ¹" );
	}

	v = vid_mem + 160 * ( row - 1 ) + 2 * from;
	*v = arr[ 0 ];
	v++;
	*v = attrib;

	v = vid_mem + 160 * ( row - 1 ) + 2 * to;
	*v = arr[ 2 ];
	v++;
	*v = attrib;

	for( int i = from + 1 ; i < to ; i++ )
	{
		v = vid_mem + 160 * ( row - 1 ) + 2 * i;
		*v = arr[ 1 ];

		v++;
		*v = attrib;
	}
}

void fill_screen( int x1 , int y1 , int x2 , int y2 , int color , int page )
{
	char far * vid_mem = ( char far * ) 0XB8000000 ;
	char far * v;

	vid_mem += page * 4096 ;

	char attrib = find_color_attribute ( color , color );

	for( int i = x1 - 1 ; i <= x2 ; i++ )
	{
		for( int j = y1 - 1 ; j < y2; j++ )
		{
			v = vid_mem + 160 * j + 2 * i ;
			*v = ' ' ;

			v++;
			*v = attrib;
		}
	}
}

void copy_video_page( int from , int to )
{
	char far * vid_mem = ( char far * ) 0xB8000000L;

	for( int i = 0 ; i < 4096 ; i++ )
	{
		* ( vid_mem + ( to * 4096 ) + i ) = * ( vid_mem + ( from * 4096 ) + i );
	}
}

void change_active_video_page( int to )
{
	union REGS i , o;

	i.h.ah = 0x05;
	i.h.al = to;

	int86( 0x10 , &i , &o );
}

void goto_xy( int x , int y , int page )
{
	union REGS i , o;

	i.h.ah = 0x02 ;
	i.h.bh = page;

	i.h.dh = ( y - 1 );
	i.h.dl = ( x - 1 );

	int86( 0x10 , &i , &o );
}

int find_color_attribute( int fore_ground_color , int back_ground_color )
{
	return ( back_ground_color * 16 + fore_ground_color );
}

void display_string( char * string , int fore_ground_color , int back_ground_color , int hot_key_color , int column, int row , int shadow , int page )
{
	int i = 0 , j = 0;

	char far * vid_mem = ( char far * ) 0XB8000000;
	char far * v;
	char far * start;

	vid_mem += ( page * 4096 ) ;

	char attrib1 = find_color_attribute( hot_key_color , back_ground_color );
	char attrib2 = find_color_attribute( fore_ground_color , back_ground_color );

	start = ( char far * ) vid_mem + 160 * ( row - 1 ) + 2 * ( column- 1 );

	while( string[ i ] != '\0' )
	{
		v = start + ( j * 2 ) ;

		if( string[ i ] == '&' )
		{
			*v = string[ i + 1 ];
			v++;

			*v = attrib1;
			i++;
		}
		else
		{
			*v = string[ i ];
			v++;
			*v = attrib2;
		}

		i++;
		j++;
	}

	if( shadow == SHADOW )
	{
		int length = strlen( string );

		for( i = column ; i < ( column + length - 1 ) ; i++ )
		{
			v= vid_mem + 160 * row + 2 * i ;
			*v = 'ß' ;

			v++;
			*v = 112;
		}

		v = vid_mem + 160 * ( row - 1 ) + 2 * ( i - 1 ) ;
		*v = 'Ü' ;

		v++;
		*v = 112;
	}
}

void modified_display_string( char * string )
{
        char temp_string[ 50 ];
	int length = strlen( string );
        int count = 0;
        int row = 7;

	fill_screen( 26 , 7 , 76 , 20 , 1 , 0 );

        for( int i = 0 ; i < length; i++ )
        {
        	if( string[ i ] == '*' )
                {
                        temp_string[ count ] = '\0';
	        	display_string( temp_string , 15 , 1 , 4 , 26 , row , 0 , 0 );
                	count = 0;
                        row ++;
                        continue;
                }
                temp_string[ count ] = string[ i ];
                count++;
        }
}

void dos_shell( void )
{
	char *temp;

	temp = searchpath("COMMAND.COM");

	if( temp != NULL )
	{
		copy_video_page( 0 , 1 );
		clrscr();
		_setcursortype(_NORMALCURSOR);
		printf( "TYPE EXIT TO RETURN TO HOSTEL MANAGEMENT. . .\n" );
		system( temp );
		textmode( C80 );
		_setcursortype(_NOCURSOR);
		copy_video_page( 1 , 0 );
	}
	else
	{
		msgbox( " ERROR " , "    THE FILE COMMAND.COM NOT FOUND    " , 1 );
	}
}

int is_filename_valid( char * filename )
{
	int length = strlen( filename );
	int i;
	int j;
	int dot_occured = 0;

	char violations[ 20 ] = "\"\t <>+:;[]|,?*";

        if( length == 0 )
        {
        	return ( 0 );
        }

	for( i = 0 ; i < length ; i++ )
	{
		if( filename[ i ] == '.' )
		{
			if( dot_occured == 1 )
			{
                        	return ( 0 );
			}
			else
			{
				dot_occured = 1;
			}
		}

		for( j = 0 ; j < 14 ; j++ )
		{
			if( filename[ i ] == violations[ j ] )
			{
                        	return ( 0 );
			}
		}
	}
	return ( 1 );
}

int is_chronological( date first , date second )
{
	if( first.da_year < second.da_year )
        {
        	return ( 0 );
        }

	if( ( first.da_mon < second.da_mon ) && ( first.da_year == second.da_year ) )
        {
        	return ( 0 );
        }

	if( ( first.da_day < second.da_day ) && ( first.da_mon == second.da_mon ) )
        {
        	return ( 0 );
        }

        return ( 1 );
}

char * get_date_string( int day , int month , int year )
{
        char date_string[ 50 ];
        char temp_string[ 50 ];

        strcpy( date_string , "" );

        if( day < 10 )
        {
        	strcpy( date_string , "0" );
        }

	itoa( day , temp_string , 10 );
	strcat( date_string , temp_string );
	strcat( date_string , "/" );

        if( month < 10 )
        {
        	strcat( date_string , "0" );
        }

	itoa( month , temp_string , 10 );
	strcat( date_string , temp_string );
	strcat( date_string , "/" );
	itoa( year , temp_string , 10 );
	strcat( date_string , temp_string );

        return ( date_string );
}

int does_room_number_exist( char * room_no )
{
        int result = 0;
	ifstream file;

        file.open( "ROOMS.DAT" , ios::in | ios::binary );
        file.read( (char *) &temp_room , sizeof( temp_room ) );

        while( file )
        {
                if( strcmp( room_no , temp_room.room_no ) == 0 )
                {
                	result = 1;
                        break;
                }
	        file.read( (char *) &temp_room , sizeof( temp_room ) );
        }

        file.close();
        return ( result );
}

int count_members_in_the_room( char * room_no )
{
        int count = 0;
	ifstream file;

        file.open( "MEMBERS.DAT" , ios::in | ios::binary );
        file.read( (char *) &temp_member , sizeof( temp_member ) );

        while( file )
        {
                if( strcmp( room_no , temp_member.room_no ) == 0 )
                {
                	count++;
                }
	        file.read( (char *) &temp_member , sizeof( temp_member ) );
        }

        file.close();
        return ( count );
}

//THE REQUIRED DIALOG BOXES

void msgbox( char * title , char * message , int page )
{
	char ch = 1;
	int len , position;

	copy_video_page( page - 1 , page );

	len = strlen( message );
	position = ( 80 - len ) / 2;

	draw_border( position - 3 , 10 , position + len + 3 , 17 , DOUBLE , 15 , 7 , SHADOW , page );
	fill_screen( position - 2 , 11 , position + len + 1 , 16 , 7 , page );
	fill_screen( position - 1 , 11 , position + len , 13 , 3 , page );

	display_string( message , 0 , 3 , 4 , position , 12 , NO_SHADOW , page );
	display_string( "    &OK    " , 15 , 2 , 14 , 35 , 15 , SHADOW , page );

	len = strlen( title );
	position = ( 80 - len ) / 2;

	display_string( title , 15 , 7 , 4 , position , 10 , NO_SHADOW , page );

	change_active_video_page( page );

	while( ( ch != 13 ) && ( ch != 27 ) && ( ch != 32 ) && ( ch!='o' ) && ( ch!='O' ) )
	{
		ch = getch();
	}
	change_active_video_page( page-1 );
}

int yes_no( char * message )
{
	static char buttons[ 2 ][ 15 ] = {
		"   &YES   " ,
		"    &NO    "
	};

	static int positions[ 2 ] = { 29 , 42 };

	int tab_counter = 0 , repeat_loop = 1 , result ;

	key my_key;

	copy_video_page( 0 , 1 );

	draw_border( 20 , 10 , 60 , 17 , DOUBLE , 15 , 7 , SHADOW , 1 );
	fill_screen( 21 , 11 , 58 , 16 , 7 , 1 );
	fill_screen( 22 , 11 , 57 , 13 , 3 , 1 );

	display_string( " WARNING " , 15 , 7 , 4 , 35 , 10 , NO_SHADOW , 1 );
	display_string( message , 0 , 3 , 4 , 24 , 12 , NO_SHADOW , 1 );

	change_active_video_page( 1 );

	while( repeat_loop )
	{
		for ( int i = 0 ; i <= 1 ; i++ )
		{
			if( i == tab_counter )
			{
				display_string( buttons[ i ] , 15 , 1 , 14 ,  positions[ i ] , 15 , SHADOW , 1 );
			}
			else
			{
				display_string( buttons[ i ] , 15 , 2 , 14 , positions[ i ] , 15 , SHADOW , 1 );
			}
		}

		my_key.read_key_stroke();

		if( my_key.get_ascii_code() == 0 )
		{
			switch( my_key.get_scan_code() )
			{
				case 15: // Shift + tab
					if( tab_counter == 0 )
					{
						tab_counter = 1;
					}
					else
					{
						tab_counter = 0;
					}

					break;
			}
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 27: // Esc
					result = 1;
					repeat_loop = 0;

					break;

				case 13: // Enter
					result = tab_counter ;
					repeat_loop = 0;

					break;

				case 9:  // tab key
					if( tab_counter == 1 )
					{
						tab_counter = 0;
					}
					else
					{
						tab_counter = 1;
					}
					break;
			}
		}
	}

	change_active_video_page( 0 );
	return ( result );
}

int add_member_record_dialog_box( int load_values )
{
        text_box name( 21 , 25 , 8 , 1 );
        text_box address( 14 , 32 , 13 , 1 );
        text_box phone( 22 , 24 , 15 , 1 );
        text_box qualification( 30 , 16 , 17 , 1 );
        text_box room_no( 53 , 10 , 19 , 1 );

	Date my_date;

	key my_key;

        int tab_counter = 0;
        int sex_status = 0;
        int prev_tab = 0;
        int repeat_loop = 1;
        int skip = 0;
        int result = 0;
        int i;

	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        draw_border( 10 , 6 , 70  , 21 , DOUBLE , 15 , 7 , SHADOW , 1 );
	fill_screen( 11 , 7 , 68 , 20 , 7 , 1 );

        if( load_values == NO )
        {
	        display_string( " ADD MEMBER RECORD ", 15 , 7 , 4 , 31 , 6 , NO_SHADOW , 1 );
	        find_room_record( 1 );
	        room_no.set_text( temp_room.room_no );
        }
        else
        {
	        display_string( " MODIFY MEMBER RECORD ", 15 , 7 , 4 , 30 , 6 , NO_SHADOW , 1 );
                name.set_text( temp_member.name );
                address.set_text( temp_member.address );
                phone.set_text( temp_member.phone );
                room_no.set_text( temp_member.room_no );
                qualification.set_text( temp_member.qualification );
                sex_status = temp_member.sex;
                my_date.set_date( temp_member.day , temp_member.month , temp_member.year );
                my_date.initialize_textboxes();
        }

        name.draw_textbox();
        address.draw_textbox();
        phone.draw_textbox();
        qualification.draw_textbox();
        room_no.draw_textbox();

        my_date.initialize(23 , 19);

        display_string( "NAME:", 0 , 7 , 4 , 14 , 8 , NO_SHADOW , 1 );
        display_string( "SEX:  ( )MALE ( )FEMALE", 0 , 7 , 4 , 14 , 10 , NO_SHADOW , 1 );
        display_string( "PERMANENT ADDRESS:", 0 , 7 , 4 , 14 , 12 , NO_SHADOW , 1 );
        display_string( "PHONE:", 0 , 7 , 4 , 14 , 15 , NO_SHADOW , 1 );
        display_string( "QUALIFICATION:", 0 , 7 , 4 , 14 , 17 , NO_SHADOW , 1 );
        display_string( "DATE:", 0 , 7 , 4 , 14 , 19 , NO_SHADOW , 1 );
        display_string( "ROOM NO.:", 0 , 7 , 4 , 53 , 18 , NO_SHADOW , 1 );


        while( repeat_loop )
        {
                result = 0;

        	display_string( "     &OK     ", 0 , 2 , 14 , 53 , 8 , SHADOW , 1 );
	        display_string( "   &RESET    ", 0 , 2 , 14 , 53 , 11 , SHADOW , 1 );
	        display_string( "   &CANCEL   ", 0 , 2 , 14 , 53 , 14 , SHADOW , 1 );

	        switch( tab_counter )
        	{
        		case 7:
		        	display_string( "     &OK     ", 15 , 2 , 14 , 53 , 8 , SHADOW , 1 );
	                        break;
        	        case 8:
			        display_string( "   &RESET    ", 15 , 2 , 14 , 53 , 11 , SHADOW , 1 );
                        	break;
	                case 9:
			        display_string( "   &CANCEL   ", 15 , 2 , 14 , 53 , 14 , SHADOW , 1 );
                		break;
		}

              	if( sex_status == 0 )
		{
			display_string( "*", 0 , 7 , 4 , 21 , 10 , NO_SHADOW , 1 );
		}
		else
		{
			display_string( "*", 0 , 7 , 4 , 29 , 10 , NO_SHADOW , 1 );
		}

	        switch( tab_counter)
        	{
	                case 0:
                        	skip = 1;
                        	result = name.got_focus();
                                break;
        	        case 1:
                        	skip = 1;
                                key temp_key;
                                int exit = 1;
                                _setcursortype( _NORMALCURSOR );

                                while( exit )
                                {
				        display_string( "SEX:  ( )MALE ( )FEMALE", 0 , 7 , 4 , 14 , 10 , NO_SHADOW , 1 );
			              	if( sex_status == 0 )
					{
						display_string( "*", 0 , 7 , 4 , 21 , 10 , NO_SHADOW , 1 );
                                                goto_xy( 21 , 10 , 1 );
					}
					else
					{
						display_string( "*", 0 , 7 , 4 , 29 , 10 , NO_SHADOW , 1 );
                                                goto_xy( 29 , 10 , 1 );
					}

                                	temp_key.read_key_stroke();

                                        //shift tab
					if( temp_key.get_ascii_code() == 0 )
                                        {
						switch( temp_key.get_scan_code() )
                                                {
                                                	case 15:
	        		                               	result = 1;
        	                	                        exit = 0;
                                                                break;
							case 75: //left arrow
                                                        case 77: //right arrow
                                                        	if( sex_status == 1 )
                                                                {
                                                                	sex_status = 0;
                                                                }
                                                                else
                                                                {
                                                                	sex_status = 1;
                                                                }
								break;
                                                }
                                        }
					else
					{
						switch( temp_key.get_ascii_code() )
						{
							case 9: //tab
                                                        	result = 2;
                                                                exit = 0;
                                                        	break;
                                                        case 13://enter
                                                        	result = 3;
                                                                exit = 0;
                                                        	break;
                                                        case 27://esc
                                                        	result = 4;
                                                                exit = 0;
                                                        	break;
                                                }
                                        }
                                }
                                _setcursortype( _NOCURSOR );
                                break;
                	case 2:
                        	skip = 1;
                        	result = address.got_focus();
                                break;
	                case 3:
                        	skip = 1;
                        	result = phone.got_focus();
                                break;
        	        case 4:
                        	skip = 1;
                        	result = qualification.got_focus();
                                break;
                        case 5:
				skip = 1;
                               	if( prev_tab == 6 )
				{
					result = my_date.got_focus( REAR );
				}
				else
				{
	                              	result = my_date.got_focus( FRONT );
                                }
                                break;
                        case 6:
                        	skip = 1;
                                result = room_no.got_focus();
                        	break;
		}

		switch( result )
		{
			case 1: //Shift tab
				my_key.set_values( 0 , 15 );
				break;

			case 2: //tab
				my_key.set_values( 9 , 15 );
				break;

			case 3: //Enter
				my_key.set_values( 13 , 1 );
				break;

			case 4: //Escape
                                my_key.set_values( 27 , 1 );
				break;
		}

		if( skip == 0 )
		{
			my_key.read_key_stroke();
		}

                //shift tab
		if( my_key.get_ascii_code() == 0 && my_key.get_scan_code() == 15 )
		{
                	prev_tab = tab_counter;

			if( tab_counter == 0 )
			{
				tab_counter = 9;
			}
			else
			{
				tab_counter--;
			}
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9: //tab
                                	prev_tab = tab_counter;

					if( tab_counter == 9 )
					{
						tab_counter = 0;
					}
					else
					{
						tab_counter++;
					}
					break;

				case 13:  //enter
					switch( tab_counter )
					{
                                                case 0:
                                                case 1:
                                                case 2:
                                                case 3:
                                                case 4:
                                                case 5:
                                        	case 6:
                                                case 7: //ok button
                                                        if( strcmp( name.get_text() , "" ) == 0 )
                                                        {
                                                                tab_counter = 0;
                                                                msgbox( " ERROR " , "  THE NAME FIELD MUST BE FILLED    " , 2 );
                                                                break;
                                                        }

                                                        if( strcmp( address.get_text() , "" ) == 0 )
                                                        {
                                                                tab_counter = 2;
                                                                msgbox( " ERROR " , "  THE ADDRESS FIELD MUST BE FILLED    " , 2 );
                                                                break;
                                                        }

                                                        if( strcmp( phone.get_text() , "" ) == 0 )
                                                        {
                                                                tab_counter = 3;
                                                                msgbox( " ERROR " , "  THE PHONE FIELD MUST BE FILLED    " , 2 );
                                                                break;
                                                        }

                                                        if( strcmp( qualification.get_text() , "" ) == 0 )
                                                        {
                                                                tab_counter = 4;
                                                                msgbox( " ERROR " , "  THE QUALIFICATION FIELD MUST BE FILLED    " , 2 );
                                                                break;
                                                        }

                                                        if( ! does_room_number_exist( room_no.get_text() ) )
                                                        {
                                                        	tab_counter = 6;
                                                                msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING ROOM NUMBER     " , 2 );
                                                                break;
                                                        }

                                                        strcpy( temp_member.name , name.get_text() );
							temp_member.sex = sex_status;

                                                        strcpy( temp_member.address , address.get_text() );
                                                        strcpy( temp_member.phone , phone.get_text() );
                                                        strcpy( temp_member.qualification , qualification.get_text() );
                                                        strncpy( temp_member.room_no , room_no.get_text() , 20 );

                                                        temp_member.room_no[ 21 ] = '\0';
                                                        temp_member.day = my_date.get_day();
                                                        temp_member.month = my_date.get_month();
                                                        temp_member.year = my_date.get_year();

                                                        result = 1;
                                                        repeat_loop = 0;
                                                	break;
                                        	case 8: //reset
                                                	name.set_text("");
                                                	address.set_text("");
                                                	phone.set_text("");
                                                	qualification.set_text("");
                                                        room_no.set_text( temp_room.room_no );

                                                        name.draw_textbox();
                                                        address.draw_textbox();
                                                        phone.draw_textbox();
                                                        qualification.draw_textbox();

                                                        my_date.reset();
                                                	break;
                                                case 9: //cancel
							repeat_loop = 0;
                                                        result = 0;
							break;
					}
                                        break;
				case 27:   //escape
					repeat_loop = 0;
                                        result = 0;
					break;
			}

		}
		skip = 0;
	}

	change_active_video_page( 0 );
        return ( result );
}

int read_member_record_dialog_box( int * record_no )
{
	int result = 0;
        int skip = 0;
        int tab_counter = 0;
        int repeat_loop = 1;

        key my_key;

        text_box rec_no( 39 , 15 , 11 , 1 );
        text_box name( 24 , 30 , 14 , 1 );

 	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        draw_border( 19 , 9 , 60  , 18 , DOUBLE , 15 , 7 , SHADOW , 1 );
        display_string( " READ MEMBER RECORD ", 15 , 7 , 4 , 30 , 9 , NO_SHADOW , 1 );
	fill_screen( 20 , 10 , 58 , 17 , 7 , 1 );
        display_string( "RECORD NO. :", 0 , 7 , 4 , 24 , 11 , NO_SHADOW , 1 );
        display_string( "MEMBER'S NAME:", 0 , 7 , 4 , 24 , 13 , NO_SHADOW , 1 );

        rec_no.set_text( "1" );
        rec_no.draw_textbox();

	find_member_record( 1 );
	name.set_text( temp_member.name );
        name.draw_textbox( 11 , 1 );

        while( repeat_loop )
        {
	        display_string( "    &OK    ", 0 , 2 , 14 , 28 , 16 , SHADOW , 1 );
	        display_string( "  &CANCEL  ", 0 , 2 , 14 , 42 , 16 , SHADOW , 1 );

                switch( tab_counter )
                {
                        case 0:
                        	skip = 1;
                                result = rec_no.got_focus();
                        	break;
                	case 1:
			        display_string( "    &OK    ", 15 , 2 , 14 , 28 , 16 , SHADOW , 1 );
                                break;
                        case 2:
				display_string( "  &CANCEL  ", 15 , 2 , 14 , 42 , 16 , SHADOW , 1 );
                        	break;
                }

		switch( result )
		{
			case 1: //Shift tab
				my_key.set_values( 0 , 15 );
				break;

			case 2: //tab
				my_key.set_values( 9 , 15 );
				break;

			case 3: //Enter
                                my_key.set_values( 13 , 1 );
				break;

			case 4: //Escape
                                my_key.set_values( 27 , 1 );
				break;
		}

		if( skip == 0 )
		{
			my_key.read_key_stroke();
		}

                //Shift + Tab
		if( my_key.get_ascii_code() == 0 && my_key.get_scan_code() == 15 )
		{
                	switch( tab_counter )
                        {
                        	case 0:
					result = string_to_int( rec_no.get_text() , record_no );

                                	if( ! result )
		                        {
                                        	tab_counter = 0;
						msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                                break;
                		        }

                                	if( ! find_member_record( * record_no ) )
		                        {
                                        	tab_counter = 0;
						msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                                break;
                		        }
                                	else
		                        {
                		        	name.set_text( temp_member.name );
                                		name.draw_textbox( 11 , 1 );
                                                tab_counter  = 2;
		                        }
                                        break;
                                case 1:
                                	tab_counter = 0;
                                        break;
                                case 2:
                                	tab_counter = 1;
                                        break;
                        }
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9: //tab
                                	switch( tab_counter )
                                        {
                                        	case 0:
							result = string_to_int( rec_no.get_text() , record_no );

	        	                        	if( ! result )
				                        {
                	        	                	tab_counter = 0;
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                	        	        break;
			               		        }

                                		        if( ! find_member_record( * record_no ) )
		                                        {
                                                        	tab_counter = 0;
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                                                break;
                		                        }
                                		        else
		                                        {
                		                        	name.set_text( temp_member.name );
                                		                name.draw_textbox( 11 , 1 );
                                                		tab_counter  = 1;
		                                        }
                                                        break;
                                                case 1:
                                                	tab_counter = 2;
                                                	break;
                                                case 2:
                                                	tab_counter = 0;
                                                	break;
                                        }
					break;
				case 13:  //enter
                                	switch( tab_counter )
                                        {
                                                case 0:
                                                case 1:
							string_to_int( rec_no.get_text() , record_no );
                                		        if( ! find_member_record( * record_no ) )
		                                        {
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
                		                        }
                                		        else
		                                        {
	                                                        repeat_loop = 0;
	                                                        result = 1;
		                                        }
                                                        break;
                                        	case 2: //cancel
                                                	repeat_loop = 0;
                                                        result = 0;
                                                        break;
                                        }
                                        break;
				case 27:   //escape
                                	result = 0;
					repeat_loop = 0;
					break;
			}
		}
		skip = 0;
        }

 	change_active_video_page( 0 );
        return ( result );
}

int add_expenses_record_dialog_box( int load_values )
{
        int result = 0;
        int tab_counter = 0;
        int prev_tab = 0;
        int repeat_loop = 1;
        int skip = 0;
        key my_key;
        char temp_string[ 20 ];

        text_box item_name(39, 14 , 10 , 1 );
        text_box price(39 , 14 , 12 , 1 );

        Date my_date;

	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        draw_border( 16 , 8 , 64  , 19 , DOUBLE , 15 , 7 , SHADOW , 1 );
	fill_screen( 17 , 9 , 62 , 18 , 7 , 1 );

        my_date.initialize( 30 , 14 );

        if( load_values == NO )
        {
	        display_string( " ADD EXPENSES RECORD", 15 , 7 , 4 , 30 , 8 , NO_SHADOW , 1 );
        }
        else
        {
	        display_string( " MODIFY EXPENSES RECORD ", 15 , 7 , 4 , 28 , 8 , NO_SHADOW , 1 );
                item_name.set_text( temp_expenses.item );
                price.set_text( float_to_string( temp_expenses.price ) );
                my_date.set_date( temp_expenses.day , temp_expenses.month , temp_expenses.year );
                my_date.initialize_textboxes();
        }

        display_string( "ITEM NAME:", 0 , 7 , 4 , 23 , 10 , NO_SHADOW , 1 );
        display_string( "PRICE:", 0 , 7 , 4 , 23 , 12 , NO_SHADOW , 1 );
        display_string( "RS.", 0 , 7 , 4 , 56 , 12 , NO_SHADOW , 1 );
        display_string( "DATE:", 0 , 7 , 4 , 23 , 14 , NO_SHADOW , 1 );

        item_name.draw_textbox();
        price.draw_textbox();

        while( repeat_loop )
        {
	        display_string( "    &OK    ", 0 , 2 , 14 , 28 , 17 , SHADOW , 1 );
        	display_string( "  &CANCEL  ", 0 , 2 , 14 , 42 , 17 , SHADOW , 1 );

                if( tab_counter > 2 )
                {
                        if( tab_counter == 3)
                        {
	        		display_string( "    &OK    ", 15 , 2 , 14 , 28 , 17 , SHADOW , 1 );
                        }
                        else
                        {
		        	display_string( "  &CANCEL  ", 15 , 2 , 14 , 42 , 17 , SHADOW , 1 );
                        }
                }
                else
                {
	                switch(tab_counter)
	                {
        	                case 0:
                	        	result = item_name.got_focus();
                        		break;
	                        case 1:
        	                	result = price.got_focus();
                	        	break;
                                case 2:
                                	if( prev_tab == 3 )
                                        {
	                                	result = my_date.got_focus( REAR );
                                        }
                                        else
                                        {
	                                	result = my_date.got_focus( FRONT );
                                        }
                                        break;
                        }

			switch( result )
			{
				case 1: //Shift tab
					my_key.set_values( 0 , 15 );
					break;

				case 2: //tab
					my_key.set_values( 9 , 15 );
					break;

				case 3: //Enter
					my_key.set_values( 13 , 1 );
					break;

				case 4: //Escape
                                        my_key.set_values( 27 , 1 );
					break;
			}
                        skip = 1;
                }

		if( skip == 0 )
		{
			my_key.read_key_stroke();
		}

		if( my_key.get_ascii_code() == 0 )
		{
			switch( my_key.get_scan_code() )
                        {
                        	case 15: //shift tab
	        	        	prev_tab = tab_counter;

					if( tab_counter == 0 )
					{
						tab_counter = 4;
					}
					else
					{
						tab_counter--;
					}
                        }
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9: //tab
                                	prev_tab = tab_counter;

					if( tab_counter == 4 )
					{
						tab_counter = 0;
					}
					else
					{
						tab_counter++;
					}

					break;

				case 13:  //enter
                                	if( tab_counter == 4 )
                                        {
                                        	repeat_loop = 0;
                                                result = 0;
                                        	break;
                                        }

					if( strcmp( item_name.get_text() , "" ) == 0 )
					{
						tab_counter = 0;
						msgbox( " ERROR " , "  THE ITEM NAME FIELD MUST BE FILLED    " , 2 );
                                                break;
					}

                                	float Price;
                                	if( ! string_to_float( price.get_text() , &Price ) )
                                        {
                                                tab_counter = 1;
						msgbox( " ERROR " , "  PLEASE ENTER A VALID VALUE FOR PRICE PER ITEM   " , 2 );
                                                break;
                                        }

                                        if( Price > find_balance_amount() )
                                        {
                                                tab_counter = 1;
						msgbox( " ERROR " , "  THE PRICE EXCEEDS THE BALANCE AMOUNT            " , 2 );
                                                break;
                                        }

                                        strncpy( temp_expenses.item , item_name.get_text() , 20 );
                                        temp_expenses.price = Price;
                                        temp_expenses.day = my_date.get_day();
                                        temp_expenses.month = my_date.get_month();
                                        temp_expenses.year = my_date.get_year();

                                        result = 1;
                                        repeat_loop = 0;
                                        break;
				case 27:   //escape
					repeat_loop = 0;
                                        result = 0;
					break;
			}
		}
		skip = 0;
        }
 	change_active_video_page( 0 );
        return ( result );
}

int read_expenses_record_dialog_box( int * record_no )
{
	int result = 0;
        int skip = 0;
        int tab_counter = 0;
        int repeat_loop = 1;

        key my_key;

        text_box rec_no( 39 , 15 , 11 , 1 );
        text_box name( 24 , 30 , 14 , 1 );

 	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        draw_border( 19 , 9 , 60  , 18 , DOUBLE , 15 , 7 , SHADOW , 1 );
        display_string( " READ EXPENSES RECORD ", 15 , 7 , 4 , 29 , 9 , NO_SHADOW , 1 );
	fill_screen( 20 , 10 , 58 , 17 , 7 , 1 );
        display_string( "RECORD NO. :", 0 , 7 , 4 , 24 , 11 , NO_SHADOW , 1 );
        display_string( "NAME OF THE ITEM:", 0 , 7 , 4 , 24 , 13 , NO_SHADOW , 1 );
        rec_no.set_text( "1" );
        rec_no.draw_textbox();

	find_expenses_record( 1 );
	name.set_text( temp_expenses.item );
        name.draw_textbox( 11 , 1 );

        while( repeat_loop )
        {
	        display_string( "    &OK    ", 0 , 2 , 14 , 28 , 16 , SHADOW , 1 );
	        display_string( "  &CANCEL  ", 0 , 2 , 14 , 42 , 16 , SHADOW , 1 );

                switch( tab_counter )
                {
                        case 0:
                        	skip = 1;
                                result = rec_no.got_focus();
                        	break;
                	case 1:
			        display_string( "    &OK    ", 15 , 2 , 14 , 28 , 16 , SHADOW , 1 );
                                break;
                        case 2:
				display_string( "  &CANCEL  ", 15 , 2 , 14 , 42 , 16 , SHADOW , 1 );
                        	break;
                }

		switch( result )
		{
			case 1: //Shift tab
				my_key.set_values( 0 , 15 );
				break;

			case 2: //tab
				my_key.set_values( 9 , 15 );
				break;

			case 3: //Enter
                                my_key.set_values( 13 , 1 );
				break;

			case 4: //Escape
                                my_key.set_values( 27 , 1 );
				break;
		}

		if( skip == 0 )
		{
			my_key.read_key_stroke();
		}

                //Shift + Tab
		if( my_key.get_ascii_code() == 0 && my_key.get_scan_code() == 15 )
		{
                	switch( tab_counter )
                        {
                        	case 0:
					result = string_to_int( rec_no.get_text() , record_no );

                                        if( ! result )
                                        {
                                        	tab_counter = 0;
						msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                                break;
                                        }

                                	if( ! find_expenses_record( * record_no ) )
		                        {
                                        	tab_counter = 0;
						msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                                break;
                		        }
                                	else
		                        {
                		        	name.set_text( temp_expenses.item);
                                		name.draw_textbox( 11 , 1 );
                                                tab_counter  = 2;
		                        }
                                        break;
                                case 1:
                                	tab_counter = 0;
                                        break;
                                case 2:
                                	tab_counter = 1;
                                        break;
                        }
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9: //tab
                                	switch( tab_counter )
                                        {
                                        	case 0:
							result = string_to_int( rec_no.get_text() , record_no );

	        	                        	if( ! result )
				                        {
                	        	                	tab_counter = 0;
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                	        	        break;
			               		        }

                                		        if( ! find_expenses_record( * record_no ) )
		                                        {
                                                        	tab_counter = 0;
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                                                break;
                		                        }
                                		        else
		                                        {
                		                        	name.set_text( temp_expenses.item );
                                		                name.draw_textbox( 11 , 1 );
                                                		tab_counter  = 1;
		                                        }
                                                        break;
                                                case 1:
                                                	tab_counter = 2;
                                                	break;
                                                case 2:
                                                	tab_counter = 0;
                                                	break;
                                        }
					break;
				case 13:  //enter
                                	switch( tab_counter )
                                        {
                                                case 0:
                                                case 1:
							string_to_int( rec_no.get_text() , record_no );
                                		        if( ! find_expenses_record( * record_no ) )
		                                        {
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
                		                        }
                                		        else
		                                        {
	                                                        repeat_loop = 0;
        	                                                result = 1;
		                                        }
                                                        break;
                                        	case 2:
                                                	repeat_loop = 0;
                                                        result = 0;
                                                        break;
                                        }
                                        break;
				case 27:   //escape
					repeat_loop = 0;
                                        result = 0;
					break;
			}
		}
		skip = 0;
        }
 	change_active_video_page( 0 );
        return ( result );
}

int add_bill_record_dialog_box( int load_values )
{
	int result = 0;
        int skip = 0;

        int tab_counter = 0;
        int prev_tab;

        int repeat_loop = 1;
	int temp;

        key my_key;
        Date my_date;

        text_box amount( 37 , 9 , 9 , 1 );
        text_box contributor( 37 , 9 , 11 , 1 );
        text_box contributor_name( 24 , 29 , 14 , 1 );

 	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        draw_border( 19 , 7 , 61  , 20 , DOUBLE , 15 , 7 , SHADOW , 1 );
	fill_screen( 20 , 8 , 59 , 19 , 7 , 1 );

        if( load_values == NO )
        {
	        display_string( " ADD BILL RECORD ", 15 , 7 , 4 , 33 , 7 , NO_SHADOW , 1 );
        }
        else
        {
	        display_string( " MODIFY BILL RECORD ", 15 , 7 , 4 , 32 , 7 , NO_SHADOW , 1 );
                amount.set_text( float_to_string( temp_bill.amount ) );
                contributor.set_text( temp_bill.contributor );
                my_date.set_date( temp_bill.day , temp_bill.month , temp_bill.year );
                my_date.initialize_textboxes();
        }

        display_string( "AMOUNT:", 0 , 7 , 4 , 24 , 9 , NO_SHADOW , 1 );
        display_string( "RS.", 0 , 7 , 4 , 49 , 9 , NO_SHADOW , 1 );
        display_string( "PAYEE:", 0 , 7 , 4 , 24 , 11 , NO_SHADOW , 1 );
        display_string( "RECORD NO.", 0 , 7 , 4 , 49 , 11 , NO_SHADOW , 1 );
        display_string( "PAYEE'S NAME:", 0 , 7 , 4 , 24 , 13 , NO_SHADOW , 1 );
        display_string( "DATE:", 0 , 7 , 4 , 24 , 16 , NO_SHADOW , 1 );

        my_date.initialize( 30 , 16 );

        contributor.set_text("1");
        find_member_record( 1 );
        contributor_name.set_text( temp_member.name );

        amount.draw_textbox();
        contributor.draw_textbox();
        contributor_name.draw_textbox( 11 , 1 );

        while( repeat_loop )
        {
	        display_string( "    &OK    ", 0 , 2 , 14 , 28 , 18 , SHADOW , 1 );
	        display_string( "  &CANCEL  ", 0 , 2 , 14 , 42 , 18 , SHADOW , 1 );

                if( tab_counter > 2 )
                {
                        if ( tab_counter == 3 )
                        {
			        display_string( "    &OK    ", 15 , 2 , 14 , 28 , 18 , SHADOW , 1 );
                        }
                        else
                        {
			        display_string( "  &CANCEL  ", 15 , 2 , 14 , 42 , 18 , SHADOW , 1 );
	                }
                }
                else
                {
                        switch( tab_counter )
                        {
                        	case 0:
					result = amount.got_focus();
                                	break;
                                case 1:
					result = contributor.got_focus();
                                	break;
                                case 2:
                                	if( prev_tab == 3 )
                                        {
	                                	result = my_date.got_focus( REAR );
                                        }
                                        else
                                        {
	                                	result = my_date.got_focus( FRONT );
					}
                                	break;
                        }

			switch( result )
			{
				case 1: //Shift tab
					my_key.set_values( 0 , 15 );
                                        break;
                                case 2: //tab
					my_key.set_values( 9 , 15 );
                                        break;
				case 3: //Enter
					my_key.set_values( 13 , 15 );
					break;
				case 4: //Escape
					my_key.set_values( 27 , 15 );
					break;
			}
                        skip = 1;
		}

		if( skip == 0 )
		{
			my_key.read_key_stroke();
		}

                //Shift + Tab
		if( my_key.get_ascii_code() == 0 && my_key.get_scan_code() == 15 )
		{
                        prev_tab = tab_counter;

                        switch( tab_counter )
                        {
                        	case 0:
                                	tab_counter = 4;
                                        break;
                                case 1:
					string_to_int( contributor.get_text() , &temp );
                                        if( ! find_member_record( temp ) )
                                        {
						msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
                                                break;
                                        }
                                        else
                                        {
                                        	contributor_name.set_text( temp_member.name );
                                                contributor_name.draw_textbox( 11 , 1 );
                                                tab_counter  = 0;
                                        }
                                	break;
                                case 2:
                                case 3:
                                case 4:
                                	tab_counter--;
                        }
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9: //tab
                                	prev_tab = tab_counter;

                                        switch( tab_counter )
                                        {
                                                case 1:
							string_to_int( contributor.get_text() , &temp );
	        	                                if( ! find_member_record( temp ) )
        	        	                        {
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
	                                        	        break;
		                                        }
        		                                else
                		                        {
                        		                	contributor_name.set_text( temp_member.name );
	                        	                        contributor_name.draw_textbox( 11 , 1 );
                                                                tab_counter = 2;
        	                        	        }
                                                	break;
                                                case 0:
                                                case 2:
                                                case 3:
                                                        tab_counter++;
                                                	break;
                                                case 4:
                                                	tab_counter = 0;
                                                        break;
                                        }
					break;

				case 13:  //enter
                                	if( tab_counter == 4 )
                                        {
                                                result = 0;
                                                repeat_loop = 0;
                                        	break;
                                        }

                                	float Amount;
					if( ! string_to_float( amount.get_text() , &Amount ) )
                                        {
                                                tab_counter = 0;
						msgbox( " ERROR " , "  PLEASE ENTER A VALID VALUE FOR AMOUNT   " , 2 );
                                                break;
                                        }

					string_to_int( contributor.get_text() , &temp );
                                        if( ! find_member_record( temp ) )
                                        {
                                                tab_counter = 1;
						msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
                                                break;
                                        }

                                        temp_bill.amount = Amount;
                                        strcpy( temp_bill.contributor , temp_member.name );
                                        temp_bill.day = my_date.get_day();
                                        temp_bill.month = my_date.get_month();
                                        temp_bill.year = my_date.get_year();

                                        result = 1;
                                        repeat_loop = 0;
                                        break;
				case 27:   //escape
					repeat_loop = 0;
                                        result = 0;
					break;
			}
		}
		skip = 0;
        }
 	change_active_video_page( 0 );
        return ( result );
}

int read_bills_record_dialog_box( int * record_no )
{
	int result = 0;
        int skip = 0;
        int tab_counter = 0;
        int repeat_loop = 1;

        key my_key;

        text_box rec_no( 39 , 15 , 11 , 1 );
        text_box name( 24 , 30 , 14 , 1 );

 	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        draw_border( 19 , 9 , 60  , 18 , DOUBLE , 15 , 7 , SHADOW , 1 );
        display_string( " READ BILLS RECORD ", 15 , 7 , 4 , 31 , 9 , NO_SHADOW , 1 );
	fill_screen( 20 , 10 , 58 , 17 , 7 , 1 );
        display_string( "RECORD NO. :", 0 , 7 , 4 , 24 , 11 , NO_SHADOW , 1 );
        display_string( "PAYEE'S NAME:", 0 , 7 , 4 , 24 , 13 , NO_SHADOW , 1 );

        rec_no.set_text( "1" );
        rec_no.draw_textbox();

	find_bills_record( 1 );
	name.set_text( temp_bill.contributor );
        name.draw_textbox( 11 , 1 );

        while( repeat_loop )
        {
	        display_string( "    &OK    ", 0 , 2 , 14 , 28 , 16 , SHADOW , 1 );
	        display_string( "  &CANCEL  ", 0 , 2 , 14 , 42 , 16 , SHADOW , 1 );

                switch( tab_counter )
                {
                        case 0:
                        	skip = 1;
                                result = rec_no.got_focus();
                        	break;
                	case 1:
			        display_string( "    &OK    ", 15 , 2 , 14 , 28 , 16 , SHADOW , 1 );
                                break;
                        case 2:
				display_string( "  &CANCEL  ", 15 , 2 , 14 , 42 , 16 , SHADOW , 1 );
                        	break;
                }

		switch( result )
		{
			case 1: //Shift tab
				my_key.set_values( 0 , 15 );
				break;

			case 2: //tab
				my_key.set_values( 9 , 15 );
				break;

			case 3: //Enter
                                my_key.set_values( 13 , 1 );
				break;

			case 4: //Escape
                                my_key.set_values( 27 , 1 );
				break;
		}

		if( skip == 0 )
		{
			my_key.read_key_stroke();
		}

                //Shift + Tab
		if( my_key.get_ascii_code() == 0 && my_key.get_scan_code() == 15 )
		{
                	switch( tab_counter )
                        {
                        	case 0:
					result = string_to_int( rec_no.get_text() , record_no );

                                	if( ! result )
		                        {
                                        	tab_counter = 0;
						msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                                break;
                		        }

                                	if( ! find_bills_record( * record_no ) )
		                        {
                                        	tab_counter = 0;
						msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                                break;
                		        }
                                	else
		                        {
                		        	name.set_text( temp_bill.contributor );
                                		name.draw_textbox( 11 , 1 );
                                                tab_counter  = 2;
		                        }
                                        break;
                                case 1:
                                	tab_counter = 0;
                                        break;
                                case 2:
                                	tab_counter = 1;
                                        break;
                        }
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9: //tab
                                	switch( tab_counter )
                                        {
                                        	case 0:
							result = string_to_int( rec_no.get_text() , record_no );

	        	                        	if( ! result )
				                        {
                	        	                	tab_counter = 0;
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                	        	        break;
			               		        }

                                		        if( ! find_bills_record( * record_no ) )
		                                        {
                                                        	tab_counter = 0;
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                                                break;
                		                        }
                                		        else
		                                        {
		                		        	name.set_text( temp_bill.contributor );
		                                		name.draw_textbox( 11 , 1 );
                                                		tab_counter  = 1;
		                                        }
                                                        break;
                                                case 1:
                                                	tab_counter = 2;
                                                	break;
                                                case 2:
                                                	tab_counter = 0;
                                                	break;
                                        }
					break;
				case 13:  //enter
                                	switch( tab_counter )
                                        {
                                                case 0:
                                                case 1:
							string_to_int( rec_no.get_text() , record_no );
                                		        if( ! find_bills_record( * record_no ) )
		                                        {
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
                		                        }
                                		        else
		                                        {
	                                                        repeat_loop = 0;
	                                                        result = 1;
		                                        }
                                                        break;
                                        	case 2:
                                                	repeat_loop = 0;
                                                        result = 0;
                                                        break;
                                        }
                                        break;
				case 27:   //escape
					repeat_loop = 0;
                                        result = 0;
					break;
			}
		}
		skip = 0;
        }
 	change_active_video_page( 0 );
        return ( result );
}

int add_room_record_dialog_box( int load_values )
{
	int result = 0;
        int skip = 0;
        int tab_counter = 0;
        int prev_tab;
        int repeat_loop = 1;
	int temp;
        char temp_string[ 20 ];

        key my_key;
        Date my_date;

        text_box room_no( 37 , 9 , 10 , 1 );
        text_box capacity( 37 , 9 , 12 , 1 );

 	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        draw_border( 19 , 8 , 61  , 19 , DOUBLE , 15 , 7 , SHADOW , 1 );
	fill_screen( 20 , 9 , 59 , 18 , 7 , 1 );

        if( load_values == NO )
        {
	        display_string( " ADD ROOM RECORD ", 15 , 7 , 4 , 33 , 8 , NO_SHADOW , 1 );
        }
        else
        {
	        display_string( " MODIFY ROOM RECORD ", 15 , 7 , 4 , 32 , 8 , NO_SHADOW , 1 );
                room_no.set_text( temp_room.room_no );
		itoa( temp_room.capacity , temp_string , 10 );
                capacity.set_text( temp_string );
                my_date.set_date( temp_room.day , temp_room.month , temp_room.year );
                my_date.initialize_textboxes();
        }

        display_string( "ROOM NO.:", 0 , 7 , 4 , 24 , 10 , NO_SHADOW , 1 );
        display_string( "CAPACITY:", 0 , 7 , 4 , 24 , 12 , NO_SHADOW , 1 );
        display_string( "DATE:", 0 , 7 , 4 , 24 , 14 , NO_SHADOW , 1 );

        my_date.initialize( 30 , 14 );

        room_no.draw_textbox();
        capacity.draw_textbox();

        while( repeat_loop )
        {
	        display_string( "    &OK    ", 0 , 2 , 14 , 28 , 17 , SHADOW , 1 );
	        display_string( "  &CANCEL  ", 0 , 2 , 14 , 42 , 17 , SHADOW , 1 );

                if( tab_counter > 2 )
                {
                        if ( tab_counter == 3 )
                        {
			        display_string( "    &OK    ", 15 , 2 , 14 , 28 , 17 , SHADOW , 1 );
                        }
                        else
                        {
			        display_string( "  &CANCEL  ", 15 , 2 , 14 , 42 , 17 , SHADOW , 1 );
	                }
                }
                else
                {
                        switch( tab_counter )
                        {
                        	case 0:
					result = room_no.got_focus();
                                	break;
                                case 1:
					result = capacity.got_focus();
                                	break;
                                case 2:
                                	if( prev_tab == 3 )
                                        {
	                                	result = my_date.got_focus( REAR );
                                        }
                                        else
                                        {
	                                	result = my_date.got_focus( FRONT );
					}
                                	break;
                        }

			switch( result )
			{
				case 1: //Shift tab
					my_key.set_values( 0 , 15 );
                                        break;
                                case 2: //tab
					my_key.set_values( 9 , 15 );
                                        break;
				case 3: //Enter
					my_key.set_values( 13 , 15 );
					break;
				case 4: //Escape
					my_key.set_values( 27 , 15 );
					break;
			}
                        skip = 1;
		}

		if( skip == 0 )
		{
			my_key.read_key_stroke();
		}

                //Shift + Tab
		if( my_key.get_ascii_code() == 0 && my_key.get_scan_code() == 15 )
		{
                        prev_tab = tab_counter;

                        switch( tab_counter )
                        {
                        	case 0:
                                	tab_counter = 4;
                                        break;
                                case 1:
                                case 2:
                                case 3:
                                case 4:
                                	tab_counter--;
                        }
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9: //tab
                                	prev_tab = tab_counter;

                                        switch( tab_counter )
                                        {
                                                case 0:
                                                case 1:
                                                case 2:
                                                case 3:
                                                        tab_counter++;
                                                	break;
                                                case 4:
                                                	tab_counter = 0;
                                                        break;
                                        }
					break;

				case 13:  //enter
                                	if( tab_counter == 4 )
                                        {
                                                result = 0;
                                                repeat_loop = 0;
                                        	break;
                                        }

                                        if( strlen( room_no.get_text() ) == 0 )
                                        {
                                                tab_counter = 0;
						msgbox( " ERROR " , "  PLEASE ENTER A VALUE FOR ROOM NUMBER  " , 2 );                                                break;
                                        }

					if( ! string_to_int( capacity.get_text() , &temp ) )
                                        {
                                                tab_counter = 1;
						msgbox( " ERROR " , "  PLEASE ENTER A VALID VALUE FOR CAPACITY   " , 2 );
                                                break;
                                        }

                                        strncpy( temp_room.room_no , room_no.get_text() , 20 );
                                        temp_room.capacity = temp;
                                        temp_room.day = my_date.get_day();
                                        temp_room.month = my_date.get_month();
                                        temp_room.year = my_date.get_year();

                                        result = 1;
                                        repeat_loop = 0;
                                        break;
				case 27:   //escape
					repeat_loop = 0;
                                        result = 0;
					break;
			}
		}
		skip = 0;
        }
 	change_active_video_page( 0 );
        return ( result );
}

int read_room_record_dialog_box( int * record_no )
{
	int result = 0;
        int skip = 0;
        int tab_counter = 0;
        int repeat_loop = 1;

        key my_key;

        text_box rec_no( 39 , 15 , 11 , 1 );
        text_box room_no( 24 , 30 , 14 , 1 );

 	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        draw_border( 19 , 9 , 60  , 18 , DOUBLE , 15 , 7 , SHADOW , 1 );
        display_string( " READ ROOM RECORD ", 15 , 7 , 4 , 31 , 9 , NO_SHADOW , 1 );
	fill_screen( 20 , 10 , 58 , 17 , 7 , 1 );
        display_string( "RECORD NO. :", 0 , 7 , 4 , 24 , 11 , NO_SHADOW , 1 );
        display_string( "ROOM NO.:", 0 , 7 , 4 , 24 , 13 , NO_SHADOW , 1 );

        rec_no.set_text( "1" );
        rec_no.draw_textbox();

	find_room_record( 1 );
	room_no.set_text( temp_room.room_no );
        room_no.draw_textbox( 11 , 1 );

        while( repeat_loop )
        {
	        display_string( "    &OK    ", 0 , 2 , 14 , 28 , 16 , SHADOW , 1 );
	        display_string( "  &CANCEL  ", 0 , 2 , 14 , 42 , 16 , SHADOW , 1 );

                switch( tab_counter )
                {
                        case 0:
                        	skip = 1;
                                result = rec_no.got_focus();
                        	break;
                	case 1:
			        display_string( "    &OK    ", 15 , 2 , 14 , 28 , 16 , SHADOW , 1 );
                                break;
                        case 2:
				display_string( "  &CANCEL  ", 15 , 2 , 14 , 42 , 16 , SHADOW , 1 );
                        	break;
                }

		switch( result )
		{
			case 1: //Shift tab
				my_key.set_values( 0 , 15 );
				break;

			case 2: //tab
				my_key.set_values( 9 , 15 );
				break;

			case 3: //Enter
                                my_key.set_values( 13 , 1 );
				break;

			case 4: //Escape
                                my_key.set_values( 27 , 1 );
				break;
		}

		if( skip == 0 )
		{
			my_key.read_key_stroke();
		}

                //Shift + Tab
		if( my_key.get_ascii_code() == 0 && my_key.get_scan_code() == 15 )
		{
                	switch( tab_counter )
                        {
                        	case 0:
					result = string_to_int( rec_no.get_text() , record_no );

                                	if( ! result )
		                        {
                                        	tab_counter = 0;
						msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                                break;
                		        }

                                	if( ! find_room_record( * record_no ) )
		                        {
                                        	tab_counter = 0;
						msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                                break;
                		        }
                                	else
		                        {
                		        	room_no.set_text( temp_room.room_no );
                                		room_no.draw_textbox( 11 , 1 );
                                                tab_counter  = 2;
		                        }
                                        break;
                                case 1:
                                	tab_counter = 0;
                                        break;
                                case 2:
                                	tab_counter = 1;
                                        break;
                        }
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9: //tab
                                	switch( tab_counter )
                                        {
                                        	case 0:
							result = string_to_int( rec_no.get_text() , record_no );

	        	                        	if( ! result )
				                        {
                	        	                	tab_counter = 0;
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                	        	        break;
			               		        }

                                		        if( ! find_room_record( * record_no ) )
		                                        {
                                                        	tab_counter = 0;
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
		                                                break;
                		                        }
                                		        else
		                                        {
                		                        	room_no.set_text( temp_room.room_no );
                                		                room_no.draw_textbox( 11 , 1 );
                                                		tab_counter  = 1;
		                                        }
                                                        break;
                                                case 1:
                                                	tab_counter = 2;
                                                	break;
                                                case 2:
                                                	tab_counter = 0;
                                                	break;
                                        }
					break;
				case 13:  //enter
                                	switch( tab_counter )
                                        {
                                                case 0:
                                                case 1:
							string_to_int( rec_no.get_text() , record_no );
                                		        if( ! find_room_record( * record_no ) )
		                                        {
								msgbox( " ERROR " , "  PLEASE ENTER AN EXISTING VALUE FOR RECORD NUMBER   " , 2 );
                		                        }
                                		        else
		                                        {
	                                                        repeat_loop = 0;
	                                                        result = 1;
		                                        }
                                                        break;
                                        	case 2:
                                                	repeat_loop = 0;
                                                        result = 0;
                                                        break;
                                        }
                                        break;
				case 27:   //escape
                                	result = 0;
					repeat_loop = 0;
					break;
			}
		}
		skip = 0;
        }
 	change_active_video_page( 0 );
        return ( result );
}

void settings_dialog_box( void )
{
	int result = 0;
        int skip = 0;
        int tab_counter = 0;
        int repeat_loop = 1;

        key my_key;

        text_box file_name( 39 , 15 , 12 , 1 );

 	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        draw_border( 19 , 10 , 60  , 17 , DOUBLE , 15 , 7 , SHADOW , 1 );
        display_string( " SETTINGS ", 15 , 7 , 4 , 35 , 10 , NO_SHADOW , 1 );
	fill_screen( 20 , 11 , 58 , 16 , 7 , 1 );
        display_string( "EXPENSES FILE:", 0 , 7 , 4 , 24 , 12 , NO_SHADOW , 1 );

        file_name.set_text( expenses_file );
        file_name.draw_textbox();

        while( repeat_loop )
        {
	        display_string( "    &OK    ", 0 , 2 , 14 , 28 , 15 , SHADOW , 1 );
	        display_string( "  &CANCEL  ", 0 , 2 , 14 , 42 , 15 , SHADOW , 1 );

                switch( tab_counter )
                {
                        case 0:
                        	skip = 1;
                                result = file_name.got_focus();
                        	break;
                	case 1:
			        display_string( "    &OK    ", 15 , 2 , 14 , 28 , 15 , SHADOW , 1 );
                                break;
                        case 2:
				display_string( "  &CANCEL  ", 15 , 2 , 14 , 42 , 15 , SHADOW , 1 );
                        	break;
                }

		switch( result )
		{
			case 1: //Shift tab
				my_key.set_values( 0 , 15 );
				break;

			case 2: //tab
				my_key.set_values( 9 , 15 );
				break;

			case 3: //Enter
                                my_key.set_values( 13 , 1 );
				break;

			case 4: //Escape
                                my_key.set_values( 27 , 1 );
				break;
		}

		if( skip == 0 )
		{
			my_key.read_key_stroke();
		}

                //Shift + Tab
		if( my_key.get_ascii_code() == 0 && my_key.get_scan_code() == 15 )
		{
			if( tab_counter == 0 )
			{
				tab_counter = 2;
			}
			else
			{
				tab_counter--;
			}
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9: //tab
					if( tab_counter == 2 )
					{
						tab_counter = 0;
					}
					else
					{
						tab_counter++;
					}
					break;
				case 13:  //enter
                                	switch( tab_counter )
                                        {
                                                case 0:
                                                case 1:
                                                	if( ! is_filename_valid( file_name.get_text() ) )
                                                        {
								tab_counter = 0;
								msgbox( " ERROR " , "  PLEASE ENTER A VALID FILE NAME FOR OUTPUT    " , 2 );
		                                                break;
                                                        }

                                                        strcpy( expenses_file , file_name.get_text() );
                                                        write_settings_to_file( expenses_file );
                                                        repeat_loop = 0;
                                                        break;
                                        	case 2:
                                                	repeat_loop = 0;
                                                        break;
                                        }
                                        break;
				case 27:   //escape
					repeat_loop = 0;
					break;
			}
		}
		skip = 0;
        }
 	change_active_video_page( 0 );
}

int ask_filename_dialog_box( char * file )
{
	int result = 0;
        int skip = 0;
        int tab_counter = 0;
        int repeat_loop = 1;

        key my_key;

        text_box file_name( 40 , 15 , 12 , 2 );

 	copy_video_page( 1 , 2 );
        change_active_video_page( 2 );

        draw_border( 19 , 10 , 60  , 17 , DOUBLE , 15 , 7 , SHADOW , 2 );
        display_string( " WRITE TO FILE ", 15 , 7 , 4 , 33 , 10 , NO_SHADOW , 2 );
	fill_screen( 20 , 11 , 58 , 16 , 7 , 2 );
        display_string( "ENTER FILE NAME:", 0 , 7 , 4 , 23 , 12 , NO_SHADOW , 2 );

        file_name.set_text( "REPORT.TXT" );
        file_name.draw_textbox();

        while( repeat_loop )
        {
	        display_string( "    &OK    ", 0 , 2 , 14 , 28 , 15 , SHADOW , 2 );
	        display_string( "  &CANCEL  ", 0 , 2 , 14 , 42 , 15 , SHADOW , 2 );

                switch( tab_counter )
                {
                        case 0:
                        	skip = 1;
                                result = file_name.got_focus();
                        	break;
                	case 1:
			        display_string( "    &OK    ", 15 , 2 , 14 , 28 , 15 , SHADOW , 2 );
                                break;
                        case 2:
				display_string( "  &CANCEL  ", 15 , 2 , 14 , 42 , 15 , SHADOW , 2 );
                        	break;
                }

		switch( result )
		{
			case 1: //Shift tab
				my_key.set_values( 0 , 15 );
				break;

			case 2: //tab
				my_key.set_values( 9 , 15 );
				break;

			case 3: //Enter
                                my_key.set_values( 13 , 1 );
				break;

			case 4: //Escape
                                my_key.set_values( 27 , 1 );
				break;
		}

		if( skip == 0 )
		{
			my_key.read_key_stroke();
		}

                //Shift + Tab
		if( my_key.get_ascii_code() == 0 && my_key.get_scan_code() == 15 )
		{
			if( tab_counter == 0 )
			{
				tab_counter = 2;
			}
			else
			{
				tab_counter--;
			}
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9: //tab
					if( tab_counter == 2 )
					{
						tab_counter = 0;
					}
					else
					{
						tab_counter++;
					}
					break;
				case 13:  //enter
                                	switch( tab_counter )
                                        {
                                                case 0:
                                                case 1:
                                                	if( ! is_filename_valid( file_name.get_text() ) )
                                                        {
								tab_counter = 0;
								msgbox( " ERROR " , "  PLEASE ENTER A VALID FILE NAME FOR OUTPUT    " , 3 );
		                                                break;
                                                        }

                                                        strcpy( file , file_name.get_text() );
                                                        repeat_loop = 0;
                                                        result = 1;
                                                        break;
                                        	case 2:
                                                	repeat_loop = 0;
                                                        result = 0;
                                                        break;
                                        }
                                        break;
				case 27:   //escape
					repeat_loop = 0;
                                        result = 0;
					break;
			}
		}
		skip = 0;
        }

 	change_active_video_page( 1 );
        return ( result );
}

//FUNCTIONS FOR MODIFYING RECORDS

void modify_member_record( int record_no )
{
        struct member temp = temp_member;
	remove_member_record( record_no );
        temp_member = temp;
        write_member_record_to_file();
}

void modify_expenses_record( int record_no )
{
	struct expenses temp = temp_expenses;
        remove_expenses_record( record_no );
        temp_expenses = temp;
        write_expenses_record_to_file();
}

void modify_bills_record( int record_no )
{
	struct bill temp = temp_bill;
        remove_bills_record( record_no );
        temp_bill = temp;
        write_bill_record_to_file();
}

void modify_room_record( int record_no )
{
	struct room temp = temp_room;
        remove_room_record( record_no );
        temp_room = temp;
        write_room_record_to_file();
}

//REQUIRED DATATYPE CONVERSION FUNCTIONS

char * float_to_string( float value )
{
	unsigned long decimal;
        int mantessa;
        char temp[50];
        char temp2[50];

        decimal = value;
        mantessa =  int( float( value - decimal ) * 100 );
        ultoa( decimal , temp , 10 );
        strcat( temp , "." );
        itoa( mantessa , temp2 , 10 );

        if( strlen( temp2 ) < 2 )
        {
        	strcat( temp2 , "0" );
        }

        strcat( temp , temp2 );

        return ( temp );
}

int string_to_float( char * string , float * value )
{
        int length = strlen( string );
        unsigned long decimal = 0;
        int mantessa = 0;

        if( length == 0 || length > 8 )
        {
        	return ( 0 );
        }

        for( int i = 0 ; i < length && string[ i ] != '.' ; i++ )
        {
        	if( string[ i ] < 48 || string[ i ] > 57 || i > 4 )
                {
                	return ( 0 );
                }
                else
                {
                	if( i > 5 )
                        {
                        	return ( 0 );
                        }
                }

                decimal = decimal * 10 + ( string[ i ] - 48 );
        }

        i++;

        for( ; i < length ; i++ )
        {
        	if( string[ i ] < 48 || string[ i ] > 57 || mantessa > 9 )
                {
                	return ( 0 );
                }
                mantessa = mantessa * 10 + ( string[ i ] - 48 );
        }

	( * value ) = float( decimal + (float) mantessa / 100 );
        return ( 1 );
}

int string_to_int( char * string , int * value )
{
        int len = strlen( string );
        int temp = 0;

        if( len == 0 || len > 4 )
        {
        	return ( 0 );
        }

        for( int i = 0 ; i < len ; i++ )
        {
        	if( string[ i ] < 48 || string[ i ] > 57 )
                {
                	return ( 0 );
                }
               	temp = temp * 10 + ( string[ i ] - 48 );
        }

	( *value ) = temp;
        return ( 1 );
}

//REQUIRED MENU MANIPULATIONS

void main_menu( void )
{
	static char menu_items[ 8 ][ 20 ] = {
        	" &1 ROOMS        " ,
		" &2 MEMBERS      " ,
		" &3 BILLS        " ,
		" &4 EXPENSES     " ,
		" &5 REPORTS      " ,
                " &6 SETTINGS     " ,
		" &7 DOS SHELL    " ,
                " &8 EXIT         "
	};

        int exit = 0;
        int skip = 0;
        int selected = 0;
        int refresh = TRUE;
        int result;
        int record_no;
        int i;
        char ch;

        while( !exit )
        {
        	if( refresh == TRUE )
                {
	                switch( selected )
        	        {
	                	case 0:
				        modified_display_string( "ADD RECORD:*YOU CAN ADD A NEW ROOM TO THE*ROOMS LIST**REMOVE RECORD:*YOU CAN REMOVE AN EXISTING*ROOM FROM THE LIST*");
                                	break;
                                case 1:
				        modified_display_string( "ADD RECORD:*YOU CAN ADD A NEW MEMBER TO THE*REGISTERED MEMBERS LIST**REMOVE RECORD:*YOU CAN REMOVE AN EXISTING*MEMBER FROM THE LIST*");
                	               	break;
	                        case 2:
        	                	modified_display_string( "ADD RECORD:*YOU CAN RECORD THE BILLS*THE MEMBERS PAY**REMOVE RECORD:*YOU CAN REMOVE THE RECORDS OF THE*MONEY BILLS THAT MEMBERS HAVE*PREVIOUSLY MADE*");
                	                break;
	                        case 3:
        	                	modified_display_string( "ADD RECORD:*YOU CAN CREATE ENTRIES OF THE DAILY EXPENSES*AND CAN RECORD THEM**REMOVE RECORD:*YOU CAN REMOVE THE ENTRIES OF THE EXPENSES*THAT HAVE PREVIOUSLY BEEN RECORDED*");
                	                break;
                                case 4:
                        		modified_display_string( "MEMBERS:*YOU CAN VIEW A REPORT WITH THE*DETAILS OF THE CURRENLY REGISTERED MEMBERS**BILLS:*YOU CAN VIEW A REPORT OF THE MONEY BILLS*THAT HAVE BEEN MADE BY THE MEMBERS**EXPENSES:*YOU CAN VIEW A REPORT WITH THE DETAILS*OF THE DAILY EXPENSES*");
	                                break;
        	                case 5:
                	        	modified_display_string( "YOU CAN MAINTAIN A SEPARATE FILE FOR*STORING THE RECORDS OF EXPENSES THAT ARE MADE*IN DIFFERENT TIME PERIODS**HERE YOU CAN CHANGE THE FILE WHICH IS USED*TO RECORD THE ENTRIES OF EXPENSES*" );
                        	        break;
        	                case 6:
	                        	modified_display_string( "YOU CAN TEMPORARILY SWITCH TO THE*COMMAND PROMPT TO EXECUTE DOS COMMANDS**YOU CAN SWITCH BACK TO WHERE YOU LEFT*BY TYPING &E&X&I&T AT THE COMMAND PROMPT*");
                	                break;
                        	case 7:
                        		modified_display_string( "EXIT HOSTEL MANAGEMENT**YOU WILL BE ASKED FOR CONFIRMATION*CHOOSE &N&O IF YOU DO NOT WANT TO*EXIT HOSTEL MANAGEMENT*");
	                                break;
        	        }
                        refresh = FALSE;
                }

	        for( i = 0 ; i <= 7 ; i++ )
	        {
        		if ( i == selected )
                	{
		        	display_string( menu_items[i], 0 , 2 , 4 , 4 , 5+i , 0 , 0 );
	                }
        	        else
                	{
		        	display_string( menu_items[i], 0 , 7 , 4 , 4 , 5+i , 0 , 0 );
	                }
        	}

                if( skip == 0 )
                {
	                ch=getch();
                }
                skip = 0;

                switch( ch )
                {
                        case 72://up
                        case 75://left
                        	refresh = TRUE;
                        	if( selected > 0 )
                                {
	                        	selected--;
                                }
                                else
                                {
                                	selected = 7;
                                }
                                break;
                        case 80: //down
                        case 77: //right
                        	refresh = TRUE;
                        	if( selected < 7 )
                                {
	                        	selected++;

                                }
                                else
                                {
                                	selected = 0;
                                }
                                break;
                        case 13:
                        	switch( selected )
                                {
                                        case 0:
                                        	switch( sub_menu( 6 ) )
                                                {
                                                	case 0:
		                                        	result = add_room_record_dialog_box( NO );

                                                                if( result == 1 )
                                                                {
                                                                        struct room temp = temp_room;
                                                                	if( does_room_number_exist( temp.room_no ) )
                                                                        {
                                                                        	msgbox( " ERROR " , " A ROOM ALREADY EXISTS WITH THAT NUMBER. " , 1 );
                                                                        }
                                                                        else
                                                                        {
                                                                        	temp_room = temp;
	                                                                	write_room_record_to_file();

                                                                        }
                                                                }

                                                        	break;
                                                        case 1:
                                                                if( count_room_records() > 0 )
                                                                {
	                                                        	result = read_room_record_dialog_box( & record_no );

                                                                        if( result == 1 )
                                                                        {
                                                                                find_room_record( record_no );
                                                                        	if( count_members_in_the_room( temp_room.room_no ) == 0 )
                                                                                {
	                                                                        	remove_room_record( record_no );
                                                                                }
                                                                                else
                                                                                {
                                                                                	msgbox( " ERROR " , "  CAN NOT REMOVE ROOM. THE ROOM IS NOT EMPTY  " , 1 );
                                                                                }
                                                                        }
                                                                }
                                                                else
                                                                {
							        	msgbox( " ERROR " , "  THERE ARE NO RECORDS IN THE ROOMS LIST    " , 1 );
                                                                }
                                                        	break;
                                                        case 2:
                                                                if( count_room_records() > 0 )
                                                                {
	                                                        	result = read_room_record_dialog_box( & record_no );

                                                                        if( result == 1 )
                                                                        {
                                                                        	result = add_room_record_dialog_box( YES );
                                                                                if( result == 1 )
                                                                                {
	                                                                        	modify_room_record( record_no );
                                                                                }
                                                                        }
                                                                }
                                                                else
                                                                {
							        	msgbox( " ERROR " , "  THERE ARE NO RECORDS IN THE ROOMS LIST    " , 1 );
                                                                }
                                                        	break;
                                                }
                                        	break;
                                	case 1:
                                        	switch( sub_menu( 7 ) )
                                                {
                                                        case 0:
                                                                if( count_room_records() == 0 )
                                                                {
                                                                	msgbox( " ERROR " , "  THERE ARE NO ROOMS IN THE LIST. ADD A ROOM FIRST   " , 1 );
                                                                        break;
                                                                }

		                                        	result = add_member_record_dialog_box( NO );

                                                                if( result == 1 )
                                                                {
                                                                        struct member temp = temp_member;
                                                                	if( count_members_in_the_room( temp_member.room_no ) > temp_room.capacity )
                                                                        {
                                                                        	msgbox( " ERROR " , "  THE CAPACITY OF THE ROOM IS ALREADY REACHED   " , 1 );
                                                                        }
                                                                        else
                                                                        {
                                                                                temp_member = temp;
	                                                                	write_member_record_to_file();
                                                                        }
                                                                }

                                                                break;
                                                        case 1:
                                                                if( count_member_records() > 0 )
                                                                {
	                                                        	result = read_member_record_dialog_box( & record_no );

                                                                        if( result == 1 )
                                                                        {
                                                                        	remove_member_record( record_no );
                                                                        }
                                                                }
                                                                else
                                                                {
							        	msgbox( " ERROR " , "  THERE ARE NO RECORDS IN THE MEMBERS LIST    " , 1 );
                                                                }
                                                        	break;
                                                        case 2:
                                                                if( count_member_records() > 0 )
                                                                {
	                                                        	result = read_member_record_dialog_box( & record_no );

                                                                        if( result == 1 )
                                                                        {
                                                                        	result = add_member_record_dialog_box( YES );
                                                                                if( result == 1 )
                                                                                {
	                                                                        	modify_member_record( record_no );
                                                                                }
                                                                        }
                                                                }
                                                                else
                                                                {
							        	msgbox( " ERROR " , "  THERE ARE NO RECORDS IN THE MEMBERS LIST    " , 1 );
                                                                }
                                                        	break;
                                                }
                                        	break;
                                        case 2:
                                        	switch( sub_menu( 8 ) )
                                                {
                                                        case 0:
		                                        	result = add_bill_record_dialog_box( NO );

                                                                if( result == 1 )
                                                                {
                                                                	write_bill_record_to_file();
                                                                }

                                                                break;
                                                        case 1:
                                                        	if( count_bills_records() > 0 )
                                                                {
	                                                        	result = read_bills_record_dialog_box( & record_no );

                                                                        if( result == 1 )
                                                                        {
                                                                        	remove_bills_record( record_no );
                                                                        }
                                                                }
                                                                else
                                                                {
							        	msgbox( " ERROR " , "  THERE ARE NO RECORDS IN THE BILLS LIST    " , 1 );
                                                                }
                                                        	break;
                                                        case 2:
                                                                if( count_bills_records() > 0 )
                                                                {
	                                                        	result = read_bills_record_dialog_box( & record_no );

                                                                        if( result == 1 )
                                                                        {
                                                                        	result = add_bill_record_dialog_box( YES );
                                                                                if( result == 1 )
                                                                                {
	                                                                        	modify_bills_record( record_no );
                                                                                }
                                                                        }
                                                                }
                                                                else
                                                                {
							        	msgbox( " ERROR " , "  THERE ARE NO RECORDS IN THE BILLS LIST    " , 1 );
                                                                }
                                                        	break;
                                                }
                                        	break;
                                        case 3:
                                        	switch( sub_menu( 9 ) )
                                                {
                                                        case 0:
		                                        	result = add_expenses_record_dialog_box( NO );

                                                                if( result == 1 )
                                                                {
                                                                	write_expenses_record_to_file();
                                                                }

                                                                break;
                                                        case 1:
                                                        	if( count_expenses_records() > 0 )
                                                                {
	                                                        	result = read_expenses_record_dialog_box( & record_no );

                                                                        if( result == 1 )
                                                                        {
                                                                        	remove_expenses_record( record_no );
                                                                        }
                                                                }
                                                                else
                                                                {
							        	msgbox( " ERROR " , "  THERE ARE NO RECORDS IN THE EXPENSES LIST    " , 1 );
                                                                }
                                                        	break;
                                                        case 2:
                                                                if( count_expenses_records() > 0 )
                                                                {
	                                                        	result = read_expenses_record_dialog_box( & record_no );

                                                                        if( result == 1 )
                                                                        {
                                                                        	result = add_expenses_record_dialog_box( YES );
                                                                                if( result == 1 )
                                                                                {
	                                                                        	modify_expenses_record( record_no );
                                                                                }
                                                                        }
                                                                }
                                                                else
                                                                {
							        	msgbox( " ERROR " , "  THERE ARE NO RECORDS IN THE EXPENSES LIST    " , 1 );
                                                                }
                                                        	break;
                                                }
                                        	break;
                                        case 4:
                                        	result = reports_menu();
		                        	switch( result )
                		                {
                                                        case 0:
                                                        	rooms_report();
                                                        	break;
		                                	case 1:
                		                        	members_report();
								break;
		                                        case 2:
                		                        	bills_report();
		                                        	break;
		                                        case 3:
                	        	                	expenses_report();
                        	        	                break;
		                                }
                                        	break;
                                        case 5:
                                        	settings_dialog_box();
                                        	break;
                                        case 6:
                                        	dos_shell();
                                                break;
                                	case 7:
                                                if( yes_no( "ARE YOU SURE YOU WANT TO EXIT ?" ) == 0 )
                                                {
	                                        	exit = 1;
                                                }
                                                break;
                        	}
	                        break;
                        case 27://ESC
				if( yes_no( "ARE YOU SURE YOU WANT TO EXIT ?" ) == 0 )
				{
	                        	exit = 1;
				}
                                break;
                        default:
                        	if( ch > 48 && ch < 57 )
                                {
                                	selected = ch - 49;
                                        ch = 13;
                                        skip = 1;
                                }
                        	break;
                }
        }
}

int reports_menu( void )
{
        int selected = 0;
        int exit = 0;
        int skip = 0;
        char ch;
        int result = -1;
        static char items[ 4 ][ 20 ] = {
        				 " &1 ROOMS        ",
					 " &2 MEMBERS      ",
        			   	 " &3 BILLS        ",
        			  	 " &4 EXPENSES     "
        			       };

	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        draw_border( 4 , 10 , 21  , 15 , SINGLE , 0 , 7 , SHADOW , 1 );

        while( !exit )
        {
	        for( int i = 0; i <= 3 ; i++ )
	        {
        		if( i == selected )
	                {
			        display_string( items[ i ] , 0 , 2 , 4 , 5 , 11 + i , NO_SHADOW , 1 );
	                }
        	        else
                	{
				display_string( items[ i ] , 0 , 7 , 4 , 5 , 11 + i , NO_SHADOW , 1 );
        	        }
	        }

                if( skip == 0 )
                {
	                ch=getch();
                }
                skip = 0;

                switch( ch )
                {
                        case 72://up
                        case 75://left
                        	if( selected > 0 )
                                {
	                        	selected--;
                                }
                                else
                                {
                                	selected = 3;
                                }
                                break;
                        case 80: //down
                        case 77: //right
                        	if( selected < 3 )
                                {
	                        	selected++;
                                }
                                else
                                {
                                	selected = 0;
                                }
                                break;
                        case 27:
                        	exit = 1;
                                break;
                        case 13:
                        	exit = 1;
                                result = selected;
                                break;
                        default:
                        	if( ch > 48 && ch < 53 )
                                {
                                	selected = ch - 49;
                                        ch = 13;
                                        skip = 1;
                                }
                        	break;
                }
        }
        change_active_video_page( 0 );
        return ( result );
}

int sub_menu( int row )
{
        int selected = 0;
        int exit = 0;
        int skip = 0;
        int result = -1;
        char ch;
        static char items[ 3 ][ 20 ] = { " &1 ADD          ",
        			  	 " &2 REMOVE       ",
                                         " &3 MODIFY       "
        			       };

	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        draw_border( 4 , row , 21  , row + 4 , SINGLE , 0 , 7 , SHADOW , 1 );

        while( !exit )
        {
	        for( int i = 0; i < 3 ; i++ )
	        {
        		if( i == selected )
	                {
			        display_string( items[ i ] , 0 , 2 , 4 , 5 , row + 1 + i , NO_SHADOW , 1 );
	                }
        	        else
                	{
				display_string( items[ i ] , 0 , 7 , 4 , 5 , row + 1 + i , NO_SHADOW , 1 );
        	        }
	        }

                if( skip == 0 )
                {
	                ch=getch();
                }
                skip = 0;

                switch( ch )
                {
                        case 72://up
                        case 75://left
                        	if( selected > 0 )
                                {
                                	selected--;
                                }
                                else
                                {
                                	selected = 2;
                                }
                                break;
                        case 80: //down
                        case 77: //right
                        	if( selected < 2 )
                                {
                                	selected++;
                                }
                                else
                                {
                                	selected = 0;
                                }
                                break;
                        case 27:
                        	exit = 1;
                                break;
                        case 13:
                        	exit = 1;
                        	switch( selected )
                                {
                                	case 0:
                                                result = 0;
						break;
                                        case 1:
                                                result = 1;
                                        	break;
                                        case 2:
                                        	result = 2;
                                                break;
                                }
                                break;
                        default:
                        	if( ch > 48 && ch < 52 )
                                {
                                	selected = ch - 49;
                                        ch = 13;
                                        skip = 1;
                                }
                        	break;
                }
        }
        change_active_video_page( 0 );
        return ( result );
}

//REQUIRED REPORTS

void expenses_report( void )
{
        int counter = 0;
        int record_no = 0;
        int tab_counter = 0;
        int repeat_loop = 1;
        int skip = 0;
        int count = 0;
        int temp;
        int refresh = TRUE;

        char temp_string[20];

	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        count = count_expenses_records();

        if( count == 0 )
        {
        	msgbox( " ERROR " , "  THERE ARE NO RECORDS IN THE EXPENSES LIST    " , 1 );
                return;
        }

        float total_amount = find_total_amount();
        float balance_amount = total_amount;

        ifstream file;
        file.open( expenses_file , ios::in | ios::binary );

        key my_key;

        draw_border( 3 , 2 , 78  , 24 , DOUBLE , 15 , 7 , SHADOW , 1 );
	fill_screen( 4 , 3 , 76 , 23 , 7 , 1 );
        display_string( " EXPENSES REPORT ", 15 , 7 , 15 , 31 , 2 , NO_SHADOW , 1 );
        display_string( "NO.  ITEM NAME              PRICE          DATE         BALANCE", 15 , 7 , 15 , 7 , 4 , NO_SHADOW , 1 );
	display_string( "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" , 15 , 7 , 4 , 5 , 5 , NO_SHADOW , 1 );

        while( repeat_loop )
        {
                balance_amount = total_amount;
                counter = 0;

	        display_string( "  &PREVIOUS  "   , 0 , 2 , 14 , 12 , 22 , SHADOW , 1 );
	        display_string( "   &NEXT   "     , 0 , 2 , 14 , 27 , 22 , SHADOW , 1 );
        	display_string( " &WRITE TO FILE ", 0 , 2 , 14 , 40 , 22 , SHADOW , 1 );
	        display_string( "    &OK    "     , 0 , 2 , 14 , 58 , 22 , SHADOW , 1 );

		switch( tab_counter )
		{
                	case 0:
			        display_string( "  &PREVIOUS  "   , 15 , 2 , 14 , 12 , 22 , SHADOW , 1 );
                        	break;
                        case 1:
			        display_string( "   &NEXT   "     , 15 , 2 , 14 , 27 , 22 , SHADOW , 1 );
                        	break;
                        case 2:
		        	display_string( " &WRITE TO FILE ", 15 , 2 , 14 , 40 , 22 , SHADOW , 1 );
                        	break;
                        case 3:
			        display_string( "    &OK    "     , 15 , 2 , 14 , 58 , 22 , SHADOW , 1 );
                        	break;
		}

                temp = skip;

                if( refresh == TRUE )
                {
			fill_screen( 4 , 6 , 76 , 21 , 7 , 1 );

			file.read( (char *) & temp_expenses , sizeof( temp_expenses ) );

	                while( file && temp-- )
        	        {
                                record_no++;
		                balance_amount = balance_amount - temp_expenses.price;
				file.read( (char *) & temp_expenses , sizeof( temp_expenses ) );
	                }

		        while( file && counter < 15 )
        		{
                                record_no++;
                                itoa( record_no , temp_string , 10 );
                                strcat( temp_string , "." );
			        display_string(  temp_string , 15 , 7 , 4 , 7 , counter + 6 , NO_SHADOW , 1 );

			        display_string( temp_expenses.item , 0 , 7 , 4 , 12 , counter + 6 , NO_SHADOW , 1 );
        			display_string( "Rs." , 15 , 7 , 4 , 35 , counter + 6 , NO_SHADOW , 1 );
        			display_string( float_to_string( temp_expenses.price ) , 0 , 7 , 4 , 39 , counter + 6 , NO_SHADOW , 1 );

		        	display_string( get_date_string( temp_expenses.day , temp_expenses.month , temp_expenses.year ) , 0 , 7 , 4 , 50 , counter + 6 , NO_SHADOW , 1 );

		                balance_amount = balance_amount - temp_expenses.price;
        			display_string( "Rs." , 15 , 7 , 4 , 63 , counter + 6 , NO_SHADOW , 1 );
        			display_string( float_to_string( balance_amount ) , 0 , 7 , 4 , 67 , counter + 6 , NO_SHADOW , 1 );

			        counter++;
				file.read( (char *) & temp_expenses , sizeof( temp_expenses ) );
			}
                        record_no = 0;
                        refresh = FALSE;
                }

                my_key.read_key_stroke();

		if( my_key.get_ascii_code() == 0 )
		{
			switch( my_key.get_scan_code() )
			{
				case 15: //shift tab
                                	if( tab_counter == 0 )
                                        {
                                        	tab_counter = 3;
                                        }
                                        else
                                        {
                                        	tab_counter--;
                                        }
                                        break;
                                case 80: //down
					if( skip < count - 15 )
					{
						refresh = TRUE;
						skip++;
					}
					break;
                                case 72: //up
					if( skip > 0 )
					{
						refresh = TRUE;
						skip--;
					}
                                        break;
				case 71: //home key
                                        if( skip != 0 )
                                        {
	                                        skip = 0;
                                                refresh = TRUE;
                                        }
					break;

				case 79: //end key
                                	if( skip < count - 15 )
                                        {
		                                skip = count - 15;
                                        	refresh = TRUE;
                                        }
					break;
				case 81://page down
                                	if( skip >= count - 15 )
                                        {
                                        	break;
                                        }

                                        refresh = TRUE;
                                	skip = skip + 15;

                                        if( skip > ( count - 15 ) )
                                        {
                                        	skip = ( count - 15 );
                                        }

					break;
				case 73://page up
                                	if( skip > 15 )
                                        {
                                        	skip -= 15;
                                                refresh = TRUE;
                                        }
                                        else
                                        {
                                                if( skip != 0 )
                                                {
	                                        	skip = 0;
                                                        refresh = TRUE;
                                                }
                                        }
					break;
			}
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9://tab
                                	if( tab_counter == 3 )
                                        {
                                        	tab_counter = 0;
                                        }
                                        else
                                        {
                                        	tab_counter++;
                                        }
                                        break;

				case 13://enter
                                	switch( tab_counter )
                                        {
                                        	case 0:
                                                	if( skip > 0 )
                                                        {
                                                                refresh = TRUE;
                                                        	skip--;
                                                        }
                                                	break;
                                                case 1:
                                                	if( skip < count - 15 )
                                                        {
                                                                refresh = TRUE;
								skip++;
                                                        }
                                                	break;
                                                case 2:
                                                	int result = ask_filename_dialog_box( temp_string );
                                                        if( result == 1 )
                                                        {
                                                        	write_expenses_report_to_file( temp_string );
                                                        }
                                                	break;
                                                case 3:
		                                        repeat_loop = 0;
		                                        break;
					}
                                        break;
                                case 27://ESC
                                	repeat_loop = 0;
                                        break;

			}
		}
                file.clear();
                file.seekg( 0 , ios::beg );
	}

        file.close();
        change_active_video_page( 0 );
}

void rooms_report( void )
{
        int counter = 0;
        int record_no = 0;
        int tab_counter = 0;
        int repeat_loop = 1;
        int skip = 0;
        int count = 0;
        int temp;
        int refresh = TRUE;

        char temp_string[20];

	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        count = count_room_records();

        if( count == 0 )
        {
        	msgbox( " ERROR " , "  THERE ARE NO RECORDS IN THE ROOMS LIST    " , 1 );
                return;
        }

        ifstream file;
        file.open( "ROOMS.DAT" , ios::in | ios::binary );

        key my_key;

        draw_border( 3 , 2 , 78  , 24 , DOUBLE , 15 , 7 , SHADOW , 1 );
	fill_screen( 4 , 3 , 76 , 23 , 7 , 1 );
        display_string( " ROOMS REPORT ", 15 , 7 , 15 , 32 , 2 , NO_SHADOW , 1 );
        display_string( "NO.  ROOM NO.                  CAPACITY      FILLED       DATE", 15 , 7 , 15 , 7 , 4 , NO_SHADOW , 1 );
	display_string( "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" , 15 , 7 , 4 , 5 , 5 , NO_SHADOW , 1 );

        while( repeat_loop )
        {
                counter = 0;

	        display_string( "  &PREVIOUS  "   , 0 , 2 , 14 , 12 , 22 , SHADOW , 1 );
	        display_string( "   &NEXT   "     , 0 , 2 , 14 , 27 , 22 , SHADOW , 1 );
        	display_string( " &WRITE TO FILE ", 0 , 2 , 14 , 40 , 22 , SHADOW , 1 );
	        display_string( "    &OK    "     , 0 , 2 , 14 , 58 , 22 , SHADOW , 1 );

		switch( tab_counter )
		{
                	case 0:
			        display_string( "  &PREVIOUS  "   , 15 , 2 , 14 , 12 , 22 , SHADOW , 1 );
                        	break;
                        case 1:
			        display_string( "   &NEXT   "     , 15 , 2 , 14 , 27 , 22 , SHADOW , 1 );
                        	break;
                        case 2:
		        	display_string( " &WRITE TO FILE ", 15 , 2 , 14 , 40 , 22 , SHADOW , 1 );
                        	break;
                        case 3:
			        display_string( "    &OK    "     , 15 , 2 , 14 , 58 , 22 , SHADOW , 1 );
                        	break;
		}

                temp = skip;

                if( refresh == TRUE )
                {
			fill_screen( 4 , 6 , 76 , 21 , 7 , 1 );

			file.read( (char *) & temp_room , sizeof( temp_room ) );

	                while( file && temp-- )
        	        {
                                record_no++;
				file.read( (char *) & temp_room , sizeof( temp_room ) );
	                }

		        while( file && counter < 15 )
        		{
                                record_no++;
                                itoa( record_no , temp_string , 10 );
                                strcat( temp_string , "." );
			        display_string(  temp_string , 15 , 7 , 4 , 7 , counter + 6 , NO_SHADOW , 1 );

			        display_string( temp_room.room_no , 0 , 7 , 4 , 12 , counter + 6 , NO_SHADOW , 1 );

                                itoa( temp_room.capacity , temp_string , 10 );
        			display_string( temp_string , 0 , 7 , 4 , 38 , counter + 6 , NO_SHADOW , 1 );

                                itoa( count_members_in_the_room( temp_room.room_no ) , temp_string , 10 );
        			display_string( temp_string , 0 , 7 , 4 , 52 , counter + 6 , NO_SHADOW , 1 );

		        	display_string( get_date_string( temp_room.day , temp_room.month , temp_room.year ) , 0 , 7 , 4 , 65 , counter + 6 , NO_SHADOW , 1 );

			        counter++;
				file.read( (char *) & temp_room , sizeof( temp_room ) );
			}
                        record_no = 0;
                        refresh = FALSE;
                }

                my_key.read_key_stroke();

		if( my_key.get_ascii_code() == 0 )
		{
			switch( my_key.get_scan_code() )
			{
				case 15: //shift tab
                                	if( tab_counter == 0 )
                                        {
                                        	tab_counter = 3;
                                        }
                                        else
                                        {
                                        	tab_counter--;
                                        }
                                        break;
                                case 80: //down
					if( skip < count - 15 )
					{
						refresh = TRUE;
						skip++;
					}
					break;
                                case 72: //up
					if( skip > 0 )
					{
						refresh = TRUE;
						skip--;
					}
                                        break;
				case 71: //home key
                                        if( skip != 0 )
                                        {
	                                        skip = 0;
                                                refresh = TRUE;
                                        }
					break;

				case 79: //end key
                                	if( skip < count - 15 )
                                        {
		                                skip = count - 15;
                                        	refresh = TRUE;
                                        }
					break;
				case 81://page down
                                	if( skip >= count - 15 )
                                        {
                                        	break;
                                        }

                                        refresh = TRUE;
                                	skip = skip + 15;

                                        if( skip > ( count - 15 ) )
                                        {
                                        	skip = ( count - 15 );
                                        }

					break;
				case 73://page up
                                	if( skip > 15 )
                                        {
                                        	skip -= 15;
                                                refresh = TRUE;
                                        }
                                        else
                                        {
                                                if( skip != 0 )
                                                {
	                                        	skip = 0;
                                                        refresh = TRUE;
                                                }
                                        }
					break;
			}
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9://tab
                                	if( tab_counter == 3 )
                                        {
                                        	tab_counter = 0;
                                        }
                                        else
                                        {
                                        	tab_counter++;
                                        }
                                        break;

				case 13://enter
                                	switch( tab_counter )
                                        {
                                        	case 0:
                                                	if( skip > 0 )
                                                        {
                                                                refresh = TRUE;
                                                        	skip--;
                                                        }
                                                	break;
                                                case 1:
                                                	if( skip < count - 15 )
                                                        {
                                                                refresh = TRUE;
								skip++;
                                                        }
                                                	break;
                                                case 2:
                                                	int result = ask_filename_dialog_box( temp_string );
                                                        if( result == 1 )
                                                        {
                                                        	write_rooms_report_to_file( temp_string );
                                                        }
                                                	break;
                                                case 3:
		                                        repeat_loop = 0;
		                                        break;
					}
                                        break;
                                case 27://ESC
                                	repeat_loop = 0;
                                        break;

			}
		}
                file.clear();
                file.seekg( 0 , ios::beg );
	}

        file.close();
        change_active_video_page( 0 );
}

void bills_report( void )
{
        int counter = 0;
        int record_no = 0;
        int tab_counter = 0;
        int repeat_loop = 1;
        int skip = 0;
        int count = 0;
        int temp;
        int refresh = TRUE;
        float cumulative_total = 0;

        char temp_string[ 21 ];

	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        count = count_bills_records();

        if( count == 0 )
        {
        	msgbox( " ERROR " , "  THERE ARE NO RECORDS IN THE BILLS LIST    " , 1 );
                return;
        }

        ifstream file;
        file.open( "BILLS.DAT" , ios::in | ios::binary );

        key my_key;

        draw_border( 3 , 2 , 78  , 24 , DOUBLE , 15 , 7 , SHADOW , 1 );
	fill_screen( 4 , 3 , 76 , 23 , 7 , 1 );
        display_string( " BILLS REPORT ", 15 , 7 , 15 , 32 , 2 , NO_SHADOW , 1 );
        display_string( "NO.  CONTRIBUTOR       DATE         AMOUNT          CUM. TOTAL", 15 , 7 , 15 , 7 , 4 , NO_SHADOW , 1 );
	display_string( "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" , 15 , 7 , 4 , 5 , 5 , NO_SHADOW , 1 );

        while( repeat_loop )
        {
                counter = 0;
                cumulative_total = 0;

	        display_string( "  &PREVIOUS  "   , 0 , 2 , 14 , 12 , 22 , SHADOW , 1 );
	        display_string( "   &NEXT   "     , 0 , 2 , 14 , 27 , 22 , SHADOW , 1 );
        	display_string( " &WRITE TO FILE ", 0 , 2 , 14 , 40 , 22 , SHADOW , 1 );
	        display_string( "    &OK    "     , 0 , 2 , 14 , 58 , 22 , SHADOW , 1 );

		switch( tab_counter )
		{
                	case 0:
			        display_string( "  &PREVIOUS  "   , 15 , 2 , 14 , 12 , 22 , SHADOW , 1 );
                        	break;
                        case 1:
			        display_string( "   &NEXT   "     , 15 , 2 , 14 , 27 , 22 , SHADOW , 1 );
                        	break;
                        case 2:
		        	display_string( " &WRITE TO FILE ", 15 , 2 , 14 , 40 , 22 , SHADOW , 1 );
                        	break;
                        case 3:
			        display_string( "    &OK    "     , 15 , 2 , 14 , 58 , 22 , SHADOW , 1 );
                        	break;
		}

                temp = skip;

                if( refresh == TRUE )
                {
			fill_screen( 4 , 6 , 76 , 21 , 7 , 1 );

			file.read( (char *) & temp_bill , sizeof( temp_bill ) );

	                while( file && temp-- )
        	        {
                                record_no++;
				file.read( (char *) & temp_bill , sizeof( temp_bill ) );
                                cumulative_total += temp_bill.amount;
	                }

		        while( file && counter < 15 )
        		{
                                record_no++;
                                itoa( record_no , temp_string , 10 );
                                strcat( temp_string , "." );
			        display_string(  temp_string , 15 , 7 , 4 , 7 , counter + 6 , NO_SHADOW , 1 );

                                strncpy( temp_string , temp_bill.contributor , 15 );
                                temp_string[ 15 ] = '\0';
			        display_string( temp_string , 0 , 7 , 4 , 12 , counter + 6 , NO_SHADOW , 1 );

		        	display_string( get_date_string( temp_bill.day , temp_bill.month , temp_bill.year ) , 0 , 7 , 4 , 30 , counter + 6 , NO_SHADOW , 1 );

        			display_string( "Rs." , 15 , 7 , 4 , 43 , counter + 6 , NO_SHADOW , 1 );
        			display_string( float_to_string( temp_bill.amount ) , 0 , 7 , 4 , 47 , counter + 6 , NO_SHADOW , 1 );

                                cumulative_total += temp_bill.amount;
        			display_string( "Rs." , 15 , 7 , 4 , 59 , counter + 6 , NO_SHADOW , 1 );
        			display_string( float_to_string( cumulative_total ) , 0 , 7 , 4 , 63 , counter + 6 , NO_SHADOW , 1 );

			        counter++;
				file.read( (char *) & temp_bill , sizeof( temp_bill ) );
			}
                        record_no = 0;
                        refresh = FALSE;
                }

                my_key.read_key_stroke();

		if( my_key.get_ascii_code() == 0 )
		{
			switch( my_key.get_scan_code() )
			{
				case 15: //shift tab
                                	if( tab_counter == 0 )
                                        {
                                        	tab_counter = 3;
                                        }
                                        else
                                        {
                                        	tab_counter--;
                                        }
                                        break;
                                case 80: //down
					if( skip < count - 15 )
					{
						refresh = TRUE;
						skip++;
					}
					break;
                                case 72: //up
					if( skip > 0 )
					{
						refresh = TRUE;
						skip--;
					}
                                        break;
				case 71: //home key
                                        if( skip != 0 )
                                        {
	                                        skip = 0;
                                                refresh = TRUE;
                                        }
					break;

				case 79: //end key
                                	if( skip < count - 15 )
                                        {
		                                skip = count - 15;
                                        	refresh = TRUE;
                                        }
					break;
				case 81://page down
                                	if( skip >= count - 15 )
                                        {
                                        	break;
                                        }

                                        refresh = TRUE;
                                	skip = skip + 15;

                                        if( skip > ( count - 15 ) )
                                        {
                                        	skip = ( count - 15 );
                                        }

					break;
				case 73://page up
                                	if( skip > 15 )
                                        {
                                        	skip -= 15;
                                                refresh = TRUE;
                                        }
                                        else
                                        {
                                                if( skip != 0 )
                                                {
	                                        	skip = 0;
                                                        refresh = TRUE;
                                                }
                                        }
					break;
			}
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9://tab
                                	if( tab_counter == 3 )
                                        {
                                        	tab_counter = 0;
                                        }
                                        else
                                        {
                                        	tab_counter++;
                                        }
                                        break;

				case 13://enter
                                	switch( tab_counter )
                                        {
                                        	case 0:
                                                	if( skip > 0 )
                                                        {
                                                                refresh = TRUE;
                                                        	skip--;
                                                        }
                                                	break;
                                                case 1:
                                                	if( skip < count - 15 )
                                                        {
                                                                refresh = TRUE;
								skip++;
                                                        }
                                                	break;
                                                case 2:
                                                	int result = ask_filename_dialog_box( temp_string );
                                                        if( result == 1 )
                                                        {
                                                        	write_bills_report_to_file( temp_string );
                                                        }
                                                	break;
                                                case 3:
		                                        repeat_loop = 0;
		                                        break;
					}
                                        break;
                                case 27://ESC
                                	repeat_loop = 0;
                                        break;

			}
		}
                file.clear();
                file.seekg( 0 , ios::beg );
	}

        file.close();
        change_active_video_page( 0 );
}

void members_report( void )
{
        int counter = 0;
        int jump = 9;
        int record_no = 0;
        int tab_counter = 0;
        int repeat_loop = 1;
        int skip = 0;
        int count = 0;
        int temp;
        int refresh = TRUE;
        char temp_string[ 5 ];

	copy_video_page( 0 , 1 );
        change_active_video_page( 1 );

        count = count_member_records();

        if( count == 0 )
        {
        	msgbox( " ERROR " , "  THERE ARE NO RECORDS IN THE MEMBERS LIST    " , 1 );
                return;
        }

        ifstream file;
        file.open( "MEMBERS.DAT" , ios::in | ios::binary );

        key my_key;

        draw_border( 3 , 2 , 78  , 24 , DOUBLE , 15 , 7 , SHADOW , 1 );
	fill_screen( 4 , 3 , 76 , 23 , 7 , 1 );
        display_string( " MEMBERS REPORT ", 15 , 7 , 15 , 32 , 2 , NO_SHADOW , 1 );

        while( repeat_loop )
        {
                counter = 0;

	        display_string( "  &PREVIOUS  "   , 0 , 2 , 14 , 12 , 22 , SHADOW , 1 );
	        display_string( "   &NEXT   "     , 0 , 2 , 14 , 27 , 22 , SHADOW , 1 );
        	display_string( " &WRITE TO FILE ", 0 , 2 , 14 , 40 , 22 , SHADOW , 1 );
	        display_string( "    &OK    "     , 0 , 2 , 14 , 58 , 22 , SHADOW , 1 );

		switch( tab_counter )
		{
                	case 0:
			        display_string( "  &PREVIOUS  "   , 15 , 2 , 14 , 12 , 22 , SHADOW , 1 );
                        	break;
                        case 1:
			        display_string( "   &NEXT   "     , 15 , 2 , 14 , 27 , 22 , SHADOW , 1 );
                        	break;
                        case 2:
		        	display_string( " &WRITE TO FILE ", 15 , 2 , 14 , 40 , 22 , SHADOW , 1 );
                        	break;
                        case 3:
			        display_string( "    &OK    "     , 15 , 2 , 14 , 58 , 22 , SHADOW , 1 );
                        	break;
		}

                temp = skip;

                if( refresh == TRUE )
                {
			fill_screen( 4 , 3 , 76 , 21 , 7 , 1 );

			file.read( (char *) & temp_member , sizeof( temp_member ) );

	                while( file && temp-- )
        	        {
                        	record_no++;
				file.read( (char *) & temp_member , sizeof( temp_member ) );
	                }

		        while( file && counter < 2 )
        		{
			        display_string( "RECORD NO." , 15 , 7 , 4 , 7 , jump * counter + 4 , NO_SHADOW , 1 );
        			display_string( "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ" , 15 , 7 , 4 , 7 , jump * counter + 5 , NO_SHADOW , 1 );
	        		display_string( "NAME         :" , 15 , 7 , 4 , 7 , jump * counter + 6 , NO_SHADOW , 1 );
		        	display_string( "SEX          :" , 15 , 7 , 4 , 7 , jump * counter + 7 , NO_SHADOW , 1 );
		        	display_string( "ADDRESS      :" , 15 , 7 , 4 , 7 , jump * counter + 8 , NO_SHADOW , 1 );
			        display_string( "PHONE        :" , 15 , 7 , 4 , 7 , jump * counter + 9 , NO_SHADOW , 1 );
        			display_string( "QUALIFICATION:" , 15 , 7 , 4 , 7 , jump * counter + 10 , NO_SHADOW , 1 );
	        		display_string( "JOINING DATE :" , 15 , 7 , 4 , 7 , jump * counter + 11 , NO_SHADOW , 1 );
	        		display_string( "ROOM NO.:" , 15 , 7 , 4 , 40 , jump * counter + 11 , NO_SHADOW , 1 );

                                record_no++;
                                itoa( record_no , temp_string , 10 );
			        display_string(  temp_string , 15 , 7 , 4 , 18 , jump * counter + 4 , NO_SHADOW , 1 );
			        display_string( temp_member.name , 0 , 7 , 4 , 24 , jump * counter + 6 , NO_SHADOW , 1 );

        			if( temp_member.sex == 0 )
			        {
				        display_string( "MALE" , 0 , 7 , 4 , 24 , jump * counter + 7 , NO_SHADOW , 1 );
		        	}
			        else
        			{
				        display_string( "FEMALE" , 0 , 7 , 4 , 24 , jump * counter + 7 , NO_SHADOW , 1 );
		        	}

			        display_string( temp_member.address , 0 , 7 , 4 , 24 , jump * counter + 8 , NO_SHADOW , 1 );
        			display_string( temp_member.phone , 0 , 7 , 4 , 24 , jump * counter + 9 , NO_SHADOW , 1 );
		        	display_string( temp_member.qualification , 0 , 7 , 4 , 24 , jump * counter + 10 , NO_SHADOW , 1 );
			        display_string( temp_member.qualification , 0 , 7 , 4 , 24 , jump * counter + 10 , NO_SHADOW , 1 );

		        	display_string( get_date_string( temp_member.day , temp_member.month , temp_member.year ) , 0 , 7 , 4 , 24 , jump * counter + 11 , NO_SHADOW , 1 );
		        	display_string( temp_member.room_no , 0 , 7 , 4 , 50 , jump * counter + 11 , NO_SHADOW , 1 );

			        counter++;
				file.read( (char *) & temp_member , sizeof( temp_member ) );
			}
                        refresh = FALSE;
                        record_no = 0;
                }

                my_key.read_key_stroke();

		if( my_key.get_ascii_code() == 0 )
		{
			switch( my_key.get_scan_code() )
			{
				case 15: //shift tab
                                	if( tab_counter == 0 )
                                        {
                                        	tab_counter = 3;
                                        }
                                        else
                                        {
                                        	tab_counter--;
                                        }
                                        break;
                                case 80: //down arrow
					if( skip < count - 2 )
					{
						refresh = TRUE;
						skip++;
					}
					break;
                                case 72: //up arrow
					if( skip > 0 )
					{
						refresh = TRUE;
						skip--;
					}
					break;
				case 71: //home key
                                        if( skip != 0 )
                                        {
	                                        skip = 0;
                                                refresh = TRUE;
                                        }
					break;

				case 79: //end key
                                	if( skip < count - 2 )
                                        {
		                                skip = count - 2;
                                        	refresh = TRUE;
                                        }
					break;
				case 81://page down
                                	if( skip < count - 4 )
                                        {
                                        	skip = skip + 2 ;
                                                refresh = TRUE;
                                        }
                                        else
                                        {
                                                if( skip != count - 2 )
                                                {
	                                        	skip = count - 2;
                                                        refresh = TRUE;
                                                }
                                        }
					break;
				case 73://page up
                                	if( skip > 2 )
                                        {
                                        	skip -= 2;
                                                refresh = TRUE;
                                        }
                                        else
                                        {
                                                if( skip != 0 )
                                                {
	                                        	skip = 0;
                                                        refresh = TRUE;
                                                }
                                        }
					break;
			}
		}
		else
		{
			switch( my_key.get_ascii_code() )
			{
				case 9://tab
                                	if( tab_counter == 3 )
                                        {
                                        	tab_counter = 0;
                                        }
                                        else
                                        {
                                        	tab_counter++;
                                        }
                                        break;

				case 13://enter
                                	switch( tab_counter )
                                        {
                                        	case 0:
                                                	if( skip > 0 )
                                                        {
                                                                refresh = TRUE;
                                                        	skip--;
                                                        }
                                                	break;
                                                case 1:
                                                	if( skip < count - 2 )
                                                        {
                                                                refresh = TRUE;
								skip++;
                                                        }
                                                	break;
                                                case 2:
                                                	int result = ask_filename_dialog_box( temp_string );
                                                        if( result == 1 )
                                                        {
                                                        	write_members_report_to_file( temp_string );
                                                        }
                                                	break;
                                                case 3:
		                                        repeat_loop = 0;
		                                        break;
					}
                                        break;
                                case 27://ESC
                                	repeat_loop = 0;
                                        break;

			}
		}
                file.clear();
                file.seekg( 0 , ios::beg );
	}

        file.close();
        change_active_video_page( 0 );
}

//FUNCTIONS FOR COUNTING RECORDS

int count_member_records( void )
{
        int count = 0;
	ifstream file;
        file.open( "MEMBERS.DAT" , ios::in | ios::binary );
        file.read( (char *) &temp_member , sizeof( temp_member ) );

        while( file )
        {
                count++;
	        file.read( (char *) &temp_member , sizeof( temp_member ) );
        }

        file.close();
        return ( count );
}

int count_expenses_records( void )
{
        int count = 0;
	ifstream file;
        file.open( expenses_file , ios::in | ios::binary );
        file.read( (char *) &temp_expenses , sizeof( temp_expenses ) );

        while( file )
        {
                count++;
	        file.read( (char *) &temp_expenses , sizeof( temp_expenses ) );
        }

        file.close();
        return ( count );
}

int count_bills_records( void )
{
        int count = 0;

	ifstream file;
        file.open( "BILLS.DAT" , ios::in | ios::binary );
        file.read( (char *) &temp_bill , sizeof( temp_bill ) );

        while( file )
        {
                count++;
	        file.read( (char *) &temp_bill , sizeof( temp_bill ) );
        }

        file.close();
        return ( count );
}

int count_room_records( void )
{
        int count = 0;

	ifstream file;
        file.open( "ROOMS.DAT" , ios::in | ios::binary );
        file.read( (char *) &temp_room , sizeof( temp_room ) );

        while( file )
        {
                count++;
	        file.read( (char *) &temp_room , sizeof( temp_room ) );
        }

        file.close();
        return ( count );
}

//FUNCTIONS FOR FINDING RECORDS

int find_member_record( int record_no )
{
        int result = 0;
        int rec = 0;
	ifstream file;

        file.open( "MEMBERS.DAT" , ios::in | ios::binary );
        file.read( (char *) &temp_member , sizeof( temp_member ) );

        while( file )
        {
                rec++;
		if( rec == record_no )
		{
			result = 1;
			break;
		}
	        file.read( (char *) &temp_member , sizeof( temp_member ) );
        }


        file.close();
        return ( result );
}

int find_expenses_record( int record_no )
{
        int result = 0;
	ifstream file;
        int rec = 0;

        file.open( expenses_file , ios::in | ios::binary );
        file.read( (char *) &temp_expenses , sizeof( temp_expenses ) );

        while( file )
        {
                rec++;
                if( rec == record_no )
                {
                	result = 1;
                        break;
                }
	        file.read( (char *) &temp_expenses , sizeof( temp_expenses ) );
        }

        file.close();
        return ( result );
}

int find_bills_record( int record_no )
{
        int result = 0;
	ifstream file;
        int rec = 0;

        file.open( "BILLS.DAT" , ios::in | ios::binary );
        file.read( (char *) &temp_bill , sizeof( temp_bill ) );

        while( file )
        {
                rec++;
                if( rec == record_no )
                {
                	result = 1;
                        break;
                }
	        file.read( (char *) &temp_bill , sizeof( temp_bill ) );
        }

        file.close();
        return ( result );
}

int find_room_record( int record_no )
{
        int result = 0;
	ifstream file;
        int rec = 0;

        file.open( "ROOMS.DAT" , ios::in | ios::binary );
        file.read( (char *) &temp_room , sizeof( temp_room ) );

        while( file )
        {
                rec++;
                if( rec == record_no )
                {
                	result = 1;
                        break;
                }
	        file.read( (char *) &temp_room , sizeof( temp_room ) );
        }

        file.close();
        return ( result );
}

//FUNCTIONS FOR WRITING RECORDS

void write_member_record_to_file( void )
{
        ifstream file;
        ofstream temp;

        date first;
        date second;

        member temp2_member;

        first.da_day = temp_member.day;
        first.da_mon = temp_member.month;
        first.da_year = temp_member.year;

        file.open( "MEMBERS.DAT" , ios::in | ios::binary );
        temp.open( "TEMP.DAT" , ios::trunc | ios::binary );

	file.read( (char *) &temp2_member , sizeof( temp2_member ) );

        second.da_day = temp2_member.day;
	second.da_mon = temp2_member.month;
        second.da_year = temp2_member.year;

        while( is_chronological( first , second ) && file )
        {
		temp.write( (char *) &temp2_member, sizeof( temp2_member ) );
                file.read( (char *) &temp2_member , sizeof( temp2_member ) );

	        second.da_day = temp2_member.day;
		second.da_mon = temp2_member.month;
	        second.da_year = temp2_member.year;
        }

        temp.write( ( char * ) &temp_member , sizeof( temp_member ) );

        while( file )
        {
        	temp.write( ( char * ) &temp2_member , sizeof( temp2_member ) );
                file.read( (char *) &temp2_member , sizeof( temp2_member ) );
        }

        file.close();
        temp.close();

        unlink( "MEMBERS.DAT" );
        rename( "TEMP.DAT" , "MEMBERS.DAT" );
}

void write_expenses_record_to_file( void )
{
        ifstream file;
        ofstream temp;

        date first;
        date second;

        expenses temp2_expenses;

        first.da_day = temp_expenses.day;
        first.da_mon = temp_expenses.month;
        first.da_year = temp_expenses.year;

        file.open( expenses_file , ios::in | ios::binary );
        temp.open( "TEMP.DAT" , ios::trunc | ios::binary );

	file.read( (char *) &temp2_expenses , sizeof( temp2_expenses ) );

        second.da_day = temp2_expenses.day;
	second.da_mon = temp2_expenses.month;
        second.da_year = temp2_expenses.year;

        while( is_chronological( first , second ) && file )
        {
		temp.write( (char *) &temp2_expenses, sizeof( temp2_expenses ) );
                file.read( (char *) &temp2_expenses , sizeof( temp2_expenses ) );

	        second.da_day = temp2_expenses.day;
		second.da_mon = temp2_expenses.month;
	        second.da_year = temp2_expenses.year;
        }

        temp.write( ( char * ) &temp_expenses , sizeof( temp_expenses ) );

        while( file )
        {
        	temp.write( ( char * ) &temp2_expenses , sizeof( temp2_expenses ) );
                file.read( (char *) &temp2_expenses , sizeof( temp2_expenses ) );
        }

        file.close();
        temp.close();

        unlink( expenses_file );
        rename( "TEMP.DAT" , expenses_file );
}

void write_bill_record_to_file( void )
{
        ifstream file;
        ofstream temp;

        date first;
        date second;

        bill temp2_bill;

        first.da_day = temp_bill.day;
        first.da_mon = temp_bill.month;
        first.da_year = temp_bill.year;

        file.open( "BILLS.DAT" , ios::in | ios::binary );
        temp.open( "TEMP.DAT" , ios::trunc | ios::binary );

	file.read( (char *) &temp2_bill , sizeof( temp2_bill ) );

        second.da_day = temp2_bill.day;
	second.da_mon = temp2_bill.month;
        second.da_year = temp2_bill.year;

        while( is_chronological( first , second ) && file )
        {
		temp.write( (char *) &temp2_bill, sizeof( temp2_bill ) );
                file.read( (char *) &temp2_bill , sizeof( temp2_bill ) );

	        second.da_day = temp2_bill.day;
		second.da_mon = temp2_bill.month;
	        second.da_year = temp2_bill.year;
        }

        temp.write( ( char * ) &temp_bill , sizeof( temp_bill ) );

        while( file )
        {
        	temp.write( ( char * ) &temp2_bill , sizeof( temp2_bill ) );
                file.read( (char *) &temp2_bill , sizeof( temp2_bill ) );
        }

        file.close();
        temp.close();

        unlink( "BILLS.DAT" );
        rename( "TEMP.DAT" , "BILLS.DAT" );
}

void write_room_record_to_file( void )
{
        ifstream file;
        ofstream temp;

        date first;
        date second;

        struct room temp2_room;

        first.da_day = temp_room.day;
        first.da_mon = temp_room.month;
        first.da_year = temp_room.year;

        file.open( "ROOMS.DAT" , ios::in | ios::binary );
        temp.open( "TEMP.DAT" , ios::trunc | ios::binary );

	file.read( (char *) &temp2_room , sizeof( temp2_room ) );

        second.da_day = temp2_room.day;
	second.da_mon = temp2_room.month;
        second.da_year = temp2_room.year;

        while( is_chronological( first , second ) && file )
        {
		temp.write( (char *) &temp2_room , sizeof( temp2_room ) );
                file.read( (char *) &temp2_room , sizeof( temp2_room ) );

	        second.da_day = temp2_room.day;
		second.da_mon = temp2_room.month;
	        second.da_year = temp2_room.year;
        }

        temp.write( ( char * ) &temp_room , sizeof( temp_room ) );

        while( file )
        {
        	temp.write( ( char * ) &temp2_room , sizeof( temp2_room ) );
                file.read( (char *) &temp2_room , sizeof( temp2_room ) );
        }

        file.close();
        temp.close();

        unlink( "ROOMS.DAT" );
        rename( "TEMP.DAT" , "ROOMS.DAT" );
}

//FUNCTIONS FOR REMOVING RECORDS

void remove_member_record( int record_no )
{
        int rec = 0;

	ifstream file;
        ofstream temp;

        file.open( "MEMBERS.DAT" , ios::in | ios::binary );
        temp.open( "TEMP.DAT" , ios::in | ios::binary );

        file.read( (char *) &temp_member , sizeof( temp_member ) );

        while( file )
        {
                rec++;
                if( rec != record_no )
                {
                	temp.write( (char *) &temp_member , sizeof( temp_member ) );
                }
	        file.read( (char *) &temp_member , sizeof( temp_member ) );
        }

        file.close();
        temp.close();

        unlink( "MEMBERS.DAT" );
        rename( "TEMP.DAT" , "MEMBERS.DAT" );
}

void remove_expenses_record( int record_no )
{
        int rec = 0;

	ifstream file;
        ofstream temp;

        file.open( expenses_file , ios::in | ios::binary );
        temp.open( "TEMP.DAT" , ios::in | ios::binary );

        file.read( (char *) &temp_expenses , sizeof( temp_expenses ) );

        while( file )
        {
                rec++;
                if( rec != record_no )
                {
                	temp.write( (char *) &temp_expenses , sizeof( temp_expenses ) );
                }
	        file.read( (char *) &temp_expenses , sizeof( temp_expenses ) );
        }

        file.close();
        temp.close();

        unlink( expenses_file );
        rename( "TEMP.DAT" , expenses_file );
}

void remove_bills_record( int record_no )
{
        int rec = 0;

	ifstream file;
        ofstream temp;

        file.open( "BILLS.DAT" , ios::in | ios::binary );
        temp.open( "TEMP.DAT" , ios::in | ios::binary );

        file.read( (char *) &temp_bill , sizeof( temp_bill ) );

        while( file )
        {
                rec++;
                if( rec != record_no )
                {
                	temp.write( (char *) &temp_bill , sizeof( temp_bill ) );
                }
	        file.read( (char *) &temp_bill , sizeof( temp_bill ) );
        }

        file.close();
        temp.close();

        unlink( "BILLS.DAT" );
        rename( "TEMP.DAT" , "BILLS.DAT" );
}

void remove_room_record( int record_no )
{
        int rec = 0;

	ifstream file;
        ofstream temp;

        file.open( "ROOMS.DAT" , ios::in | ios::binary );
        temp.open( "TEMP.DAT" , ios::in | ios::binary );

        file.read( (char *) &temp_room , sizeof( temp_room ) );

        while( file )
        {
                rec++;
                if( rec != record_no )
                {
                	temp.write( (char *) &temp_room , sizeof( temp_room ) );
                }
	        file.read( (char *) &temp_room , sizeof( temp_room ) );
        }

        file.close();
        temp.close();

        unlink( "ROOMS.DAT" );
        rename( "TEMP.DAT" , "ROOMS.DAT" );
}

//FUNCTIONS FOR WRITING AND READING BACK SETTINGS

void write_settings_to_file( char * file_name )
{
	ofstream file;

        file.open( "SETTINGS.DAT", ios::trunc | ios::binary );
        file.write( file_name , 50 );

        file.close();
}

void load_settings( void )
{
	ifstream file;

        file.open( "SETTINGS.DAT" , ios::in | ios::binary );
        file.read( expenses_file , 50 );

        file.close();
}

//FUNCTIONS FOR FINDING TOTAL AND BALANCE AMOUNTS

float find_total_amount( void )
{
	float total = 0;
	ifstream file;

        file.open( "BILLS.DAT" , ios::in | ios::binary );
        file.read( (char *) &temp_bill , sizeof( temp_bill ) );

        while( file )
        {
                total = total + temp_bill.amount;
	        file.read( (char *) &temp_bill , sizeof( temp_bill ) );
        }

        file.close();
        return ( total );
}

float find_balance_amount( void )
{
        float balance;
	ifstream file;

        balance = find_total_amount();

        file.open( expenses_file , ios::in | ios::binary );
        file.read( (char *) &temp_expenses , sizeof( temp_expenses ) );

        while( file )
        {
                balance = balance - temp_expenses.price;
	        file.read( (char *) &temp_expenses , sizeof( temp_expenses ) );
        }

        file.close();
        return ( balance );
}

//THE MAIN FUNCTION

int main(void)
{
        _setcursortype(_NOCURSOR);
	fill_screen( 0 , 0 , 79 , 25 , 1 , 0 );
        draw_border( 1 , 1 , 80 , 25 , DOUBLE , 7 , 1 , NO_SHADOW , 0 );
        draw_line( DOUBLE , 3 , 0 , 79 , 7 , 1 , 0 );
        display_string( "H O S T E L   M A N A G E M E N T", 15 , 1 , 4 , 24 , 2 , NO_SHADOW , 0 );
        draw_border( 3 , 4 , 20 , 13 , SINGLE , 0 , 7 , SHADOW , 0 );
        draw_border( 24 , 4 , 78 , 24 , SINGLE , 7 , 1 , NO_SHADOW , 0 );
        draw_line( SINGLE , 6 , 23 , 77 , 7 , 1 , 0 );
        display_string( "O V E R V I E W   O F  M E N U   I T E M S" , 15 , 1 , 4 , 31 , 5 , NO_SHADOW , 0 );
        load_settings();

        if( strlen( expenses_file ) == 0 )
        {
        	strcpy( expenses_file , "EXPENSES.DAT" );
        }

	main_menu();
        clrscr();
        _setcursortype( _NORMALCURSOR );
	return ( 0 );
}


