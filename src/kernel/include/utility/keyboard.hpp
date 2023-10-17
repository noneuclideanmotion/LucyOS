#pragma once
#include <kernel/include/memory/allocate.hpp>
#include <kernel/include/print.hpp>
#include <kernel/include/utility/map.hpp>

namespace keyboard {
	
	char get_next_printable_key();
	char get_key();
	uint8_t keyboard_to_ascii(uint8_t key);

	char* _qwertyuiop = "qwertyuiop"; // 0x10-0x1c
 	char* _asdfghjkl = "asdfghjkl";
 	char* _zxcvbnm = "zxcvbnm";
 	char* _num = "123456789";
	bool _shift = false;
	char _prev_key  = 0;

	char* get_line() {
		char* string = ksd::memory::allocate<char>(256);
		for(int i = 0; i < 255; ++i){
			string[i] = get_next_printable_key();
			write_character(string[i], VGA::constants::WHITE, VGA::constants::BLACK, i, 0);
			if(string[i] == '\n') {
				string[i+1] = '\0';
				return string;
			}
		}
		string[255] = '\0';
		return string;
	}


	//valid keys: 0x02 to 0x32
	char get_next_printable_key() {
		char key = 0;
		do {
			key = get_key();
		} while(keyboard_to_ascii(key)==0);
		
		//wait before key is released before returning (otherwise the key will be sent multiple times)
		 while(keyboard_to_ascii(get_key())!=0) {}

		//As soon as keyboard to ascii returns a non null key, pass it on.
		return keyboard_to_ascii(key);
	}


	inline char get_key() {
		return utility::io::in(0x60);
	}

	

	uint8_t keyboard_to_ascii(uint8_t key)
	{
		if(key==keyboard::ps2::scan_set_one::LEFT_SHIFT_PRESSED || key==keyboard::ps2::scan_set_one::RIGHT_SHIFT_PRESSED ) {
				_shift = true;
		} 
		if(key==keyboard::ps2::scan_set_one::LEFT_SHIFT_RELEASED || key==keyboard::ps2::scan_set_one::RIGHT_SHIFT_RELEASED ) {
				_shift = false;
		}

		if(key == 0x1C) return '\n';
		if(key == 0x39) return ' ';
		if(key == 0xE) return '\r';

		if(!_shift) {
			if(key == keyboard::ps2::scan_set_one::GRAVE_PRESSED) return '`';
			if(key == keyboard::ps2::scan_set_one::MINUS_PRESSED) return '-';
			if(key == keyboard::ps2::scan_set_one::EQUALS_PRESSED) return '=';
			if(key == keyboard::ps2::scan_set_one::LEFT_SQUARE_BRACKET_PRESSED) return '[';
			if(key == keyboard::ps2::scan_set_one::RIGHT_SQUARE_BRACKET_PRESSED) return ']';
			if(key == keyboard::ps2::scan_set_one::BACK_SLASH_PRESSED) return '\\';
			if(key == keyboard::ps2::scan_set_one::SEMICOLON_PRESSED) return ';';
			if(key == keyboard::ps2::scan_set_one::SINGLE_QUOTE_PRESSED) return '\'';
			if(key == keyboard::ps2::scan_set_one::COMMA_PRESSED) return ',';
			if(key == keyboard::ps2::scan_set_one::FULL_STOP_PRESSED) return '.';
			if(key == keyboard::ps2::scan_set_one::FORWARD_SLASH_PRESSED) return '/';
		} else {
			if(key == keyboard::ps2::scan_set_one::GRAVE_PRESSED) return '¬';
			if(key == keyboard::ps2::scan_set_one::MINUS_PRESSED) return '_';
			if(key == keyboard::ps2::scan_set_one::EQUALS_PRESSED) return '+';
			if(key == keyboard::ps2::scan_set_one::LEFT_SQUARE_BRACKET_PRESSED) return '{';
			if(key == keyboard::ps2::scan_set_one::RIGHT_SQUARE_BRACKET_PRESSED) return '}';
			if(key == keyboard::ps2::scan_set_one::BACK_SLASH_PRESSED) return '|';
			if(key == keyboard::ps2::scan_set_one::SEMICOLON_PRESSED) return ':';
			if(key == keyboard::ps2::scan_set_one::SINGLE_QUOTE_PRESSED) return '@';
			if(key == keyboard::ps2::scan_set_one::COMMA_PRESSED) return '<';
			if(key == keyboard::ps2::scan_set_one::FULL_STOP_PRESSED) return '>';
			if(key == keyboard::ps2::scan_set_one::FORWARD_SLASH_PRESSED) return '?';
		}

		
		if(key == keyboard::ps2::scan_set_one::ZERO_PRESSED) return '0';
		if(key >= keyboard::ps2::scan_set_one::ONE_PRESSED && key <= keyboard::ps2::scan_set_one::NINE_PRESSED)
			return _num[key - keyboard::ps2::scan_set_one::ONE_PRESSED];
		if(key >= 0x10 && key <= 0x1C)
		{
			return _qwertyuiop[key - 0x10] - 32*_shift;
		} else if(key >= 0x1E && key <= 0x26)
		{
			return _asdfghjkl[key - 0x1E] - 32*_shift;
		} else if(key >= 0x2C && key <= 0x32)
		{
			return _zxcvbnm[key - 0x2C] - 32*_shift;
		}
		return 0;
	}

	/*class keyboard_state() {
		public:
			void update() {
				keyboard::ps2::SCAN_SET_ONE key = get_key();
				//if key >= 0x90 then it is RELEASED
				//else it is PRESSED
				//PRESSED, set key bit to one
				if(key < 0x90) {
					//If greater than 64, the second half of state needs to be used (since each half is only 64 bits)
					if(key < 64) {
						state[0] = state[0] | (1 << key);
					} else {
						// -64 is needed otherwise you would be shifting greater than the number of bits in the state
						state[1] = state[1] | (1 << (key-64));
					}
				}
				// RELEASED. Set key bit to zero
				else {
					//If greater than 64, the second half of state needs to be used (since each half is only 64 bits)
					if(key < 64) {
						state[0] = state[0] & ~(1 << key);
					} else {
						// -64 is needed otherwise you would be shifting greater than the number of bits in the state
						state[1] = state[1] & ~(1 << (key-64));
					}
				}
			}
			char get_ascii() {
				
			}
		private:
			uint64_t state[2];

			// since the scancode uses qwerty ordering and ascii uses alphabetical ordering, these maps allow 
			//easy conversion between the two
			char* m_qwertzuiop = "qwertzuiop"; // 0x10-0x1c
			char* m_asdfghjkl = "asdfghjkl";
			char* m_yxcvbnm = "yxcvbnm";
			char* m_numbers = "123456789";
	}*/

	/*namespace ps2 {
		namespace SCAN_SET_ONE {
			ksd::data_structure::map<key, char, key::MAX_KEY_VALUE> scan_set_one_ASCII_map = {
			{0x10, 51},
			{0x11, 57},
			}
		}
	}
	*/
}