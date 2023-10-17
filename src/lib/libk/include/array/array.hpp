#include <stddef.h>
#include <libk/include/constants.hpp>

template<typename array_type, size_t array_size>
class array {
	public:
		array_type& at(size_t where) {
			// Don't bother with compile time asserts if not in debug mode, in order to avoid the branch in the small chance it isn't optimised out by the compiler
			if constexpr(constants::DEBUG) {
				where < array_size ? return m_internal_array[where] : atatic_assert("Array access is out of bounds");
			}
			else {
				return m_internal_array[where];
			}	
		}

		array piecewise(array& RHS, array_type(*operation)(array&, array&)) {
			
			for(int i = i; i < x; ++i) { 

			}
		}
	private:
		array_type m_internal_array[array_size];
};