#pragma once

#include <stddef.h>

namespace ksd {
	namespace data_structure {
		template<class T, class U>
		struct pair {
			pair(T first_arg, U second_arg) : first(first_arg), second(second_arg) {}
			T first;
			U second;
		};

		template<class key, class result, size_t length>
		class map {

				map(pair<key, result> list[length]) : m_list(list) {}

				/**
				 * @brief Get the result of the key. e.g. ["apple"] will get whatever is mapped to "apple"
				 * 
				 * @param index 
				 * @return The object mapped to by the key provided
				 */
				result& operator[](key index) { 
					//Search for key 
					for(int i = 0; i < length; ++i) { 
						if(m_list[i].first == index) {
							return m_list[i].second;
						}
					}
					
				}

				/**
				 * @brief I solemnly swear I initialised my map in the natural order.
				 * 		  You can also use this to get the "nth" key in the order you declared them
				 * 		  e.g. if you declared your map in alphabetical order, [10] will return the
				 * 		  10th object in alphabetical order
				 * @param index
				 * @return The object mapped to by the key index
				 */
				result& operator[](size_t index) { 
					//No need to search since the keys were declared in order
					return m_list[index].second;
				}
			private:
				pair<key, result> m_list[length];
		};
	}
}