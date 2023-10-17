#pragma once

#include <stddef.h>
#include <stdint.h>

namespace VGA {
	namespace constants {
		enum colour : unsigned char {
			BLACK,
			BLUE,
			GREEN,
			CYAN,
			RED,
			MAGENTA,
			BROWN,
			WHITE,
			GREY,
			LIGHT_BLUE,
			LIGHT_GREEN,
			LIGHT_CYAN,
			LIGHT_RED,
			LIGHT_MAGENTA,
			YELLOW,
			BRIGHT_WHITE
		};
	}
	namespace memory {
		volatile uint16_t* TEXT_BUFFER = (uint16_t*)(0xB8000);
	}
}

namespace keyboard {

	namespace ps2 {

		enum scan_set {
			SCAN_SET_ONE,
			SCAN_SET_TWO,
			SCAN_SET_THREE
		};

		namespace scan_set_one {
			enum key : unsigned char {
				NULL_KEY = 0,
				Q_PRESSED = 0x10,
				Q_RELEASED = 0x90,
				W_PRESSED = 0x11,
				W_RELEASED = 0x91,
				E_PRESSED = 0x12,
				E_RELEASED = 0x92,
				R_PRESSED = 0x13,
				R_RELEASED = 0x93,
				T_PRESSED = 0x14,
				T_RELEASED = 0x94,
				Z_PRESSED = 0x15,
				Z_RELEASED = 0x95,
				U_PRESSED = 0x16,
				U_RELEASED = 0x96,
				I_PRESSED = 0x17,
				I_RELEASED = 0x97,
				O_PRESSED = 0x18,
				O_RELEASED = 0x98,
				P_PRESSED = 0x19,
				P_RELEASED = 0x99,
				A_PRESSED = 0x1E,
				A_RELEASED = 0x9E,
				S_PRESSED = 0x1F,
				S_RELEASED = 0x9F,
				D_PRESSED = 0x20,
				D_RELEASED = 0xA0,
				F_PRESSED = 0x21,
				F_RELEASED = 0xA1,
				G_PRESSED = 0x22,
				G_RELEASED = 0xA2,
				H_PRESSED = 0x23,
				H_RELEASED = 0xA3,
				J_PRESSED = 0x24,
				J_RELEASED = 0xA4,
				K_PRESSED = 0x25,
				K_RELEASED = 0xA5,
				L_PRESSED = 0x26,
				L_RELEASED = 0xA6,
				Y_PRESSED = 0x2C,
				Y_RELEASED = 0xAC,
				X_PRESSED = 0x2D,
				X_RELEASED = 0xAD,
				C_PRESSED = 0x2E,
				C_RELEASED = 0xAE,
				V_PRESSED = 0x2F,
				V_RELEASED = 0xAF,
				B_PRESSED = 0x30,
				B_RELEASED = 0xB0,
				N_PRESSED = 0x31,
				N_RELEASED = 0xB1,
				M_PRESSED = 0x32,
				M_RELEASED = 0xB2,

				ZERO_PRESSED = 0x0B,
				ONE_PRESSED = 0x02,
				ONE_RELEASED = 0x82,
				TWO_PRESSED = 0x03,
				TWO_RELEASED = 0x83,
				THREE_PRESSED = 0x04,
				THREE_RELEASED = 0x84,
				FOUR_PRESSED = 0x05,
				FOUR_RELEASED = 0x85,
				FIVE_PRESSED = 0x06,
				FIVE_RELEASED = 0x86,
				SIX_PRESSED = 0x07,
				SIX_RELEASED = 0x87,
				SEVEN_PRESSED = 0x08,
				SEVEN_RELEASED = 0x88,
				EIGHT_PRESSED = 0x09,
				EIGHT_RELEASED = 0x89,
				NINE_PRESSED = 0xA,
				NINE_RELEASED = 0x8A,

				GRAVE_PRESSED = 0x29,
				GRAVE_RELEASED = 0xA9,
				MINUS_PRESSED = 0x0c,
				MINUS_RELEASED = 0x8c,
				EQUALS_PRESSED = 0x0d,
				EQUALS_RELEASED = 0x0d,
				LEFT_SQUARE_BRACKET_PRESSED = 0x1a,
				LEFT_SQUARE_BRACKET_RELEASED = 0x9A,
				RIGHT_SQUARE_BRACKET_PRESSED = 0x1b,
				RIGHT_SQUARE_BRACKET_RELEASED = 0x9B,
				BACK_SLASH_PRESSED = 0x2B,
				BACK_SLASH_RELEASED = 0xAB,
				SEMICOLON_PRESSED = 0x27,
				SEMICOLON_RELEASED = 0xA7,
				SINGLE_QUOTE_PRESSED = 0x28,
				SINGLE_QUOTE_RELEASED = 0xA8,
				COMMA_PRESSED = 0x33,
				COMMA_RELEASED = 0xB3,
				FULL_STOP_PRESSED = 0x34,
				FULL_STOP_RELEASED = 0xB4,
				FORWARD_SLASH_PRESSED = 0x35,

				//Special keys
				ESCAPE_PRESSED = 0x01,
				ESCAPE_RELEASED = 0x81,
				BACKSPACE_PRESSED = 0x0E,
				BACKSPACE_RELEASED = 0x8E,
				TAB_PRESSED = 0x0F,
				TAB_RELEASED = 0x8F,
				ENTER_PRESSED = 0x1C,
				ENTER_RELEASED = 0x9C,
				LEFT_SHIFT_PRESSED = 0x2A,
				LEFT_SHIFT_RELEASED = 0xAA,
				RIGHT_SHIFT_PRESSED = 0x36,
				RIGHT_SHIFT_RELEASED = 0xB6,
				LEFT_CTRL_PRESSED = 0x1E,
				LEFT_CTRL_RELEASED = 0x9D,
				LEFT_ALT_PRESSED = 0x38,
				LEFT_ALT_RELEASED = 0xB8,
				SPACE_PRESSED = 0x39,
				SPACE_RELEASED = 0xB9,
				CAPS_LOCK_PRESSED = 0x3A,
				CAPS_LOCK_RELEASED = 0xBA,

				MAX_KEY_VALUE = 0xBB

			};
		}

	/*class keyboard_state {
		public:
		keyboard::ps2::scan_set scan_set = keyboard::ps2::scan_set::SCAN_SET_ONE;
		bool is_caps_on() {
			if(!caps_lock) {
				return  state & (0b0000000000000000000000000000000000000000010000000000010000000000); 
			}
			else {
				return  !(state & (0b0000000000000000000000000000000000000000010000000000010000000000)); 
			}
			
		}	

		void update(keyboard::ps2::scan_set_one::key key) {
			//pressed
			if(key==keyboard::ps2::scan_set_one::key::CAPS_LOCK_PRESSED) { 
				caps_lock = true;
			}
			if(key>64) {	
				//set "key"th bit to 1
				state |= 1UL << key;	
			}
			//released
			else {
				//set "key"th bit to 0
				key = static_cast<keyboard::ps2::scan_set_one::key>(static_cast<char>(key) - 128);
				state  &= ~(1UL << key);
			}
			return;
		}

		private:
			bool caps_lock = false;
			uint64_t state;
	};

	keyboard_state state;*/

		namespace utility {
			/*const char* key_to_string(uint8_t key_code, keyboard::ps2::scan_set scan_set = keyboard::ps2::scan_set::SCAN_SET_ONE) constexpr {
				switch(scan_set) {
					case keyboard::ps2::scan_set::SCAN_SET_ONE:
						switch(key_code) {
						case 0x01:
							return "ESCAPE";
						case 0x02:
							return "ONE";
						case 0x03:
							return "TWO";
						
						case 0x0E:
							return "BACKSPACE";

						case 0x1C:
							return "ENTER";
						default:
							return "UNKOWN KEY";
					}
				}
				return "NONE";
			}*/
			const char* scancode_to_name_string(uint8_t key_code, keyboard::ps2::scan_set scan_set = keyboard::ps2::scan_set::SCAN_SET_ONE) {
					switch(key_code) {
					case 0x0B:
						return "ZERO PRESSED";
					case 0x8b:
						return "ZERO RELEASED";
					case 0x02:
						return "ONE PRESSED";
					case 0x82:
						return "ONE RELEASED";
					case 0x03:
						return "TWO PRESSED";
					case 0x83:
						return "TWO RELEASED";
					case 0x04:
						return "THREE PRESSED";
					case 0x84:
						return "THREE RELEASED";
					case 0x05:
						return "FOUR PRESSED";
					case 0x85:
						return "FOUR RELEASED";
					case 0x06:
						return "FIVE PRESSED";
					case 0x86:
						return "FIVE RELEASED";
					case 0x07:
						return "SIX PRESSED";
					case 0x87:
						return "SIX RELEASED";
					case 0x08:
						return "SEVEN PRESSED";
					case 0x88:
						return "SEVEN RELEASED";
					case 0x09:
						return "EIGHT PRESSED";
					case 0x89:
						return "EIGHT RELEASED";
					case 0x0A:
						return "NINE PRESSED";
					case 0x8a:
						return "NINE RELEASED";
					case 0x1E:
						return "A PRESSED";
					case 0x9e:
						return "A RELEASED";
					case 0x30:
						return "B PRESSED";
					case 0xb0:
						return "B RELEASED";
					case 0x2E:
						return "C PRESSED";
					case 0xae:
						return "C RELEASED";
					case 0x20:
						return "D PRESSED";
					case 0xa0:
						return "D RELEASED";
					case 0x12:
						return "E PRESSED";
					case 0x92:
						return "E RELEASED";
					case 0x21:
						return "F PRESSED";
					case 0xa1:
						return "F RELEASED";
					case 0x22:
						return "G PRESSED";
					case 0xa2:
						return "G RELEASED";
					case 0x23:
						return "H PRESSED";
					case 0xa3:
						return "H RELEASED";
					case 0x17:
						return "I PRESSED";
					case 0x97:
						return "I RELEASED";
					case 0x24:
						return "J PRESSED";
					case 0xa4:
						return "J RELEASED";
					case 0x25:
						return "K PRESSED";
					case 0xa5:
						return "K RELEASED";
					case 0x26:
						return "L PRESSED";
					case 0xa6:
						return "L RELEASED";
					case 0x32:
						return "M PRESSED";
					case 0xb2:
						return "M RELEASED";
					case 0x31:
						return "N PRESSED";
					case 0xb1:
						return "N RELEASED";
					case 0x18:
						return "O PRESSED";
					case 0x98:
						return "O RELEASED";
					case 0x19:
						return "P PRESSED";
					case 0x99:
						return "P RELEASED";
					case 0x10:
						return "Q PRESSED";
					case 0x90:
						return "Q RELEASED";
					case 0x13:
						return "R PRESSED";
					case 0x93:
						return "R RELEASED";
					case 0x1F:
						return "S PRESSED";
					case 0x9f:
						return "S RELEASED";
					case 0x14:
						return "T PRESSED";
					case 0x94:
						return "T RELEASED";
					case 0x16:
						return "U PRESSED";
					case 0x96:
						return "U RELEASED";
					case 0x2F:
						return "V PRESSED";
					case 0xaf:
						return "V RELEASED";
					case 0x11:
						return "W PRESSED";
					case 0x91:
						return "W RELEASED";
					case 0x2D:
						return "X PRESSED";
					case 0xad:
						return "X RELEASED";
					case 0x15:
						return "Y PRESSED";
					case 0x95:
						return "Y RELEASED";
					case 0x2C:
						return "Z PRESSED";
					case 0xac:
						return "Z RELEASED";
					case 0x3B:
						return "F1 PRESSED";
					case 0xbb:
						return "F1 RELEASED";
					case 0x3C:
						return "F2 PRESSED";
					case 0xbc:
						return "F2 RELEASED";
					case 0x3D:
						return "F3 PRESSED";
					case 0xbd:
						return "F3 RELEASED";
					case 0x3E:
						return "F4 PRESSED";
					case 0xbe:
						return "F4 RELEASED";
					case 0x3F:
						return "F5 PRESSED";
					case 0xbf:
						return "F5 RELEASED";
					case 0x40:
						return "F6 PRESSED";
					case 0xc0:
						return "F6 RELEASED";
					case 0x41:
						return "F7 PRESSED";
					case 0xc1:
						return "F7 RELEASED";
					case 0x42:
						return "F8 PRESSED";
					case 0xc2:
						return "F8 RELEASED";
					case 0x43:
						return "F9 PRESSED";
					case 0xc3:
						return "F9 RELEASED";
					case 0x44:
						return "F10 PRESSED";
					case 0xc4:
						return "F10 RELEASED";
					case 0x57:
						return "F11 PRESSED";
					case 0xd7:
						return "F11 RELEASED";
					case 0x58:
						return "F12 PRESSED";
					case 0xd8:
						return "F12 RELEASED";
					case 0x29:
						return "GRAVE PRESSED";
					case 0xa9:
						return "GRAVE RELEASED";
					case 0x0C:
						return "MINUS PRESSED";
					case 0x8c:
						return "MINUS RELEASED";
					case 0x0D:
						return "EQUALS PRESSED";
					case 0x8d:
						return "EQUALS RELEASED";
					case 0x1A:
						return "LEFT_SQUARE_BRACKET PRESSED";
					case 0x9a:
						return "LEFT_SQUARE_BRACKET RELEASED";
					case 0x1B:
						return "RIGHT_SQUARE_BRACKET PRESSED";
					case 0x9b:
						return "RIGHT_SQUARE_BRACKET RELEASED";
					case 0x2B:
						return "BACK_SLASH PRESSED";
					case 0xab:
						return "BACK_SLASH RELEASED";
					case 0x27:
						return "SEMICOLON PRESSED";
					case 0xa7:
						return "SEMICOLON RELEASED";
					case 0x28:
						return "SINGLE_QUOTE PRESSED";
					case 0xa8:
						return "SINGLE_QUOTE RELEASED";
					case 0x33:
						return "COMMA PRESSED";
					case 0xb3:
						return "COMMA RELEASED";
					case 0x34:
						return "FULL_STOP PRESSED";
					case 0xb4:
						return "FULL_STOP RELEASED";
					case 0x35:
						return "FORWARD_SLASH PRESSED";
					case 0xb5:
						return "FORWARD_SLASH RELEASED";
					case 0x01:
						return "ESCAPE PRESSED";
					case 0x81:
						return "ESCAPE RELEASED";
					case 0x39:
						return "SPACE PRESSED";
					case 0xb9:
						return "SPACE RELEASED";
					case 0x0E:
						return "BACKSPACE PRESSED";
					case 0x8e:
						return "BACKSPACE RELEASED";
					case 0x0F:
						return "TAB PRESSED";
					case 0x8f:
						return "TAB RELEASED";
					case 0x3A:
						return "CAPS_LOCK PRESSED";
					case 0xba:
						return "CAPS_LOCK RELEASED";
					case 0x2A:
						return "LEFT_SHIFT PRESSED";
					case 0xaa:
						return "LEFT_SHIFT RELEASED";
					case 0x36:
						return "RIGHT_SHIFT PRESSED";
					case 0xb6:
						return "RIGHT_SHIFT RELEASED";
					case 0x1C:
						return "ENTER PRESSED";
					case 0x9c:
						return "ENTER RELEASED";
					case 0x1D:
						return "CTRL PRESSED";
					case 0x9d:
						return "CTRL RELEASED";
					case 0x38:
						return "ALT PRESSED";
					case 0xb8:
						return "ALT RELEASED";
					default:
						return "UNKOWN";
				};
				return "NULL";
			}
			
		}
	}
}


namespace utility {
	namespace io {
		void out(uint16_t address, uint8_t value) {
 			 asm("outb %b0,%w1": :"a" (value), "Nd" (address));
		}

		static __inline unsigned char in(uint16_t address)
		{
			uint8_t response;
			asm volatile ("inb %w1,%0":"=a" (response):"Nd" (address));
			return response;
		}
	}
}

void uint32_to_dec_string(uint32_t input, char* output) {
	//10 is max length of uint32_t (null is automatically added) so output must be 11 in size
	//char output[11] = "4294967295";
	uint32_t input_buffer = input;
	unsigned char digit = 1;
	unsigned char len = 0;
	unsigned char count = 1;
	while(input_buffer) {
		digit = input_buffer % 10;
		input_buffer = (input_buffer -digit)/10;
		len++;
	}
	output[len] = '\0';
	while(input) {
		digit = input % 10;
		output[len-count] = digit + '0'; //+48 to convert to ascii
		input = (input - digit)/10;
		count++;
	}
	return;
}

char*  uint32_to_dec_string(uint32_t input) {
	//10 is max length of uint32_t (null is automatically added) so output must be 11 in size
	if(input==0) {
		return (char*)"0";
	}
	static char output[11] = "4294967295";
	uint32_t input_buffer = input;
	unsigned char digit = 1;
	unsigned char len = 0;
	unsigned char count = 1;
	while(input_buffer) {
		digit = input_buffer % 10;
		input_buffer = (input_buffer -digit)/10;
		len++;
	}
	output[len] = '\0';
	while(input) {
		digit = input % 10;
		output[len-count] = digit + '0'; //+48 to convert to ascii
		input = (input - digit)/10;
		count++;
	}
	return output;
}

char*  uint32_to_fixed_width_dec_string(uint32_t input) {
	//10 is max length of uint32_t (null is automatically added) so output must be 11 in size
	if(input==0) {
		return (char*)"0x0";
	}
	static char output[11] = "4294967295";
	uint32_t input_buffer = input;
	unsigned char digit = 1;
	unsigned char len = 0;
	unsigned char count = 1;
	while(input_buffer) {
		digit = input_buffer % 10;
		input_buffer = (input_buffer -digit)/10;
		len++;
	}
	//output[len] = '\0';
	while(input) {
		digit = input % 10;
		output[11-count] = digit + '0'; //+48 to convert to ascii
		input = (input - digit)/10;
		count++;
	}
	while(11-count>=0) {
		output[11-count] = '0';
		count++;
	}
	return output;
}

char* uint32_to_hex_string(uint32_t input) {
	//8 is max length of uint32_t +1 for null +2 for 0x at the beginning so output must be 11 in size
	static char output[11] = "0xFFFFFFFF";
	uint32_t input_buffer = input;
	unsigned char digit = 1;
	unsigned char len = 0;
	unsigned char count = 1;
	while(input_buffer) {
		digit = input_buffer % 16;
		input_buffer = (input_buffer -digit)/16;
		len++;
	}
	output[0] = '0';
	output[1] = 'x';
	output[len+2] = '\0';
	while(input) {
		digit = input % 16;
		output[len+2-count] = (digit <= 9 ? digit + '0' : digit + 'A' - 10); //+'0' to convert to ascii 'A' for letters because they're in a different place
		input = (input - digit)/16;
		count++;
	}

	return output;
}

char* uint32_to_fixed_width_hex_string(uint32_t input) {
	//8 is max length of uint32_t +1 for null +2 for 0x at the beginning so output must be 11 in size
	static char output[11] = "0xFFFFFFFF";
	uint32_t input_buffer = input;
	unsigned char digit = 1;
	unsigned char len = 0;
	unsigned char count = 1;
	while(input_buffer) {
		digit = input_buffer % 16;
		input_buffer = (input_buffer -digit)/16;
		len++;
	}
	output[0] = '0';
	output[1] = 'x';
	//output[len+2] = '\0';
	while(input) {
		digit = input % 16;
		output[11-count] = (digit <= 9 ? digit + '0' : digit + 'A' - 10); //+'0' to convert to ascii 'A' for letters because they're in a different place
		input = (input - digit)/16;
		count++;
	}
	while(11-count>1) {
		output[11-count] = '0';
		count++;
	}

	return output;
}

void sleep(int amount) {
	for(int ticks = 0; ticks < amount; ticks++) {}
	return;
}

void cls(VGA::constants::colour colour) {
	volatile uint16_t * where;
	for(int w = 0; w < 80; ++w) {
		for(int h = 0; h < 25; ++h) {
			where = (volatile uint16_t *)0xB8000 + (h * 80 + w);
			*where = 32 | (((colour << 4) | (0 & 0x0F)) << 8);
		}
	}
}

void write_character(unsigned char c, VGA::constants::colour forecolour, VGA::constants::colour backcolour, int x, int y)
{
	uint16_t attrib = (backcolour << 4) | (forecolour & 0x0F);
	VGA::memory::TEXT_BUFFER[y * 80 + x] = c | (attrib << 8);
	/* Alternates, (when TEXT BUFFER is a constant)
	volatile uint16_t* where;
	where = const_cast<volatile uint16_t*>(VGA::constants::TEXT_BUFFER) + (y * 80 + x);
	*where = c | (attrib << 8);
		Alternative 2
	volatile uint16_t* where;
	where = const_cast<volatile uint16_t*>(&VGA::constants::TEXT_BUFFER[y*80+x]);
	*where = c | (attrib << 8); */
}

void scroll(size_t amount) {
	for(int row = 0; row < 24; row++) {
		for(int c = 0; c < 80; c++) {
			VGA::memory::TEXT_BUFFER[row * 80 + c] = VGA::memory::TEXT_BUFFER[(row+1) * 80 + c];
		}
	}
	for(int c = 0; c < 80; c++) {
		write_character(' ', VGA::constants::colour::GREY, VGA::constants::colour::GREY, c, 24);
	}
}

size_t strlen(const char* string) {
	size_t i;
	for (i=0; string[i] != '\0'; i++);
	return i;
}

void write_string(const char* string, VGA::constants::colour forecolour, VGA::constants::colour backcolour, int x, int y) {
	size_t string_length = strlen(string);
	size_t spaces_left = 80*25-(y*80+x);
	if(string_length < spaces_left) {
		for(size_t i = 0; i<string_length;++i) {
			if(x==80) {x=0;y++;}
			write_character(string[i], forecolour, backcolour, x, y);
			x++;
		}
	}
	return;
}


void write_string_2(const char* string, VGA::constants::colour forecolour, VGA::constants::colour backcolour, int x, int y) {
	size_t string_length = strlen(string);
	for(size_t i = 0; i<string_length;++i) {
		//if(x==80) {x=0;y++;}
		write_character(string[i], forecolour, backcolour, x, y);
		x++;
	}
	return;
}