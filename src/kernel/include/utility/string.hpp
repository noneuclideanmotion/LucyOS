#pragma once

#include <stddef.h>

template <size_t buffer_length>
class string {
	public:
		string() {};

		string(const char* in_string, bool overflow_safety = true) {
			if(overflow_safety) {

			}
			m_c_string = in_string;
		}

		const size_t& length() const {
			return m_string_length
		}

		const size_t& buffer_length() constexpr {
			return buffer_length;
		}

		static size_t length(const char* in_string) {
			size_t i;
			for(i = 0; (in_string[i] != '\0'); ++i) {}
			return i;
		}

		static size_t length(string in_string) {
			return string.length();
		}		

	private:
		const char[string_size] m_c_string;
		size_t m_string_length;
};