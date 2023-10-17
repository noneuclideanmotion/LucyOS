#pragma once
#pragma once
#include <stddef.h>

namespace ksd {
	namespace memory {

		template<typename copy_type>
		void copy_array(copy_type& input, copy_type& output, size_t length) {
			size_t i = 0;
			while (input+i!=input+length) {
				*(input+i) = *(output+i);
				i++;
			}
		}

		void copy_string(const char* src, char* dest) {
			while((*dest++ = *src++));
		}
	}
}