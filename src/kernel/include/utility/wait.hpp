
#pragma once

#include <kernel/include/print.hpp>


namespace utility {

	void wait_for_keystroke(uint8_t wait_key = 0x39) {
		while(utility::io::in(0x60)!=wait_key) {}
		
		//if the CPU is too fast for the keyboard, to prevent future waits being skipped by this press
		while(utility::io::in(0x60)==wait_key) {} 

		return;
	}
}