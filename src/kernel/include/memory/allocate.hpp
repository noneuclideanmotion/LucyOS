#pragma once
#include <stddef.h>
#include <stdint.h>
#include <kernel/include/print.hpp>
#include <kernel/include/utility/wait.hpp>

/*namespace ksd {
	namespace memory {
		volatile size_t* allocation_header 			= (size_t*)(0x00200000+sizeof(size_t));
		volatile size_t* allocation_header_size 	= (size_t*)0x00200000;
		static int counter = 0;


		//allocates in sizeof(size_t) byte chunks (i.e. allocate(1) allocates 32 bits
		void* allocate(size_t amount) {
			//converts amount in bytes to proper allocation amount
			amount=amount/sizeof(size_t)+1;
			void* next_free_address = (void*)allocation_header;
			//write_string(uint32_to_hex_string((uint32_t)next_free_address), VGA::constants::colour::RED, VGA::constants::colour::BLACK, 10, counter);
			//write_string(uint32_to_dec_string((uint32_t)*allocation_header_size), VGA::constants::colour::RED, VGA::constants::colour::BLACK, 0, counter);
			if(*allocation_header_size==0) {
				allocation_header[0]=amount;
				counter++;
				(*allocation_header_size)=1;
				return next_free_address+sizeof(size_t);
			}
			size_t current_block_size;
			for(size_t i = 0; i < *allocation_header_size; ++i) {
				//write_string(uint32_to_hex_string((uint32_t)(0x00200000+sizeof(size_t))), VGA::constants::colour::RED, VGA::constants::colour::BLACK, counter*10, i);
				current_block_size = *(size_t*)(next_free_address);
				next_free_address+=current_block_size+sizeof(size_t);
				write_string(uint32_to_hex_string((uint32_t)current_block_size), VGA::constants::colour::RED, VGA::constants::colour::BLACK, counter*10, i);
			}
			*(size_t*)(next_free_address-sizeof(size_t))=current_block_size;
			(*allocation_header_size)++;
			for(size_t i =0; i < amount*sizeof(size_t); i++) {
				*(char*)(next_free_address+i) = 63;
			}
			counter++;
			//write_string(uint32_to_hex_string(*(uint32_t*)(next_free_address-1)), VGA::constants::colour::RED, VGA::constants::colour::BLACK, 50, counter);
			return next_free_address;
		}
		__attribute__((constructor)) void initialise_heap() {
			*allocation_header_size = 0;
		}
	}
}*/

namespace ksd {
	namespace memory {

		struct header {
			size_t size = 0;
			header* next_header = nullptr;
			header* previous_header = nullptr;
		};

		// this is how it is stored: (0x00200000)header_first:header_first_memory:header_second:header_second_memory:header_third...

		// Memory address where the entry point to the heap is located (i.e. where the head of the linked list of headers will go)
		const size_t heap_start = 0x00200000;
		size_t       count      = 0;
		
		// The first header
		header* head = reinterpret_cast<header*>(heap_start); 

		int test() {
			return (int)(head);
		}

		int head_size() {
			return head->size;
		}

		template<class T>
		T* allocate(size_t amount) {
			

			
			/*cls(VGA::constants::colour::BLACK);
			write_string("Allocator called with amount:", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 0);
			write_string(uint32_to_dec_string((uint32_t)amount), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 30, 0);
			write_string("Count is: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 1);
			write_string(uint32_to_dec_string((uint32_t)count), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 11, 1);
			utility::wait_for_keystroke();
			cls(VGA::constants::colour::BLACK);*/
			
			
			if(count == 0) {
				
				
				head->size 	=  amount*sizeof(T);

				
				/*write_string("size is: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 0);
				write_string(uint32_to_dec_string((uint32_t)(head->size)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 10, 0);*/
					
		
				count++;
				
				
				/*write_string("head is: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 1);
				write_string(uint32_to_fixed_width_hex_string((uint32_t)(head)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 10, 1);
				write_string("sizeof header: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 2);
				write_string(uint32_to_fixed_width_hex_string((uint32_t)sizeof(header)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 16, 2);

				write_string("returned address: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 3);
				write_string(uint32_to_fixed_width_hex_string((uint32_t)(reinterpret_cast<void*>(head)+sizeof(header)+1)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 19, 3);
				utility::wait_for_keystroke();
				cls(VGA::constants::colour::BLACK);*/
				

				// Remember that (int)(head+1) is equal to (int)(head)+(int)(sizeof(head))
				// because when adding one to head you are adding one sizeof(head), not 1 byte
				return reinterpret_cast<T*>(reinterpret_cast<void*>(head)+sizeof(header)+1);
			} else {
				//find last header
				header* temp = head;
				for(int i = 0; i < count-1; ++i) { 					
					temp = temp->next_header;
				}


				//temp is now the last header
				//create new header
				//adding 4 insetad of 1 makes sure the address is aligned to a good value
				header* next = reinterpret_cast<header*>(reinterpret_cast<void*>(temp)+temp->size+sizeof(header)+1);
				temp->next_header = next;
				next->size= amount*sizeof(T);
				next->previous_header = temp;


					/*write_string("Information of last header:", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 0);

					write_string("   address: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 1);
					write_string(uint32_to_fixed_width_hex_string((uint32_t)(temp)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 15, 1);

					write_string("   size: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 2);
					write_string(uint32_to_dec_string((uint32_t)(temp->size)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, strlen("   size:       "), 2);
					
					write_string("   next:", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 3);
					write_string(uint32_to_fixed_width_hex_string((uint32_t)(temp->next_header)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, strlen("   next:       "), 3);

					write_string("   previous:", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 4);
					write_string(uint32_to_fixed_width_hex_string((uint32_t)(temp->previous_header)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, strlen("   previous:   "), 4);
					*/
				
				
				/*write_string("New header and it's info:", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 6);

				write_string("   address: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 7);
				write_string(uint32_to_fixed_width_hex_string((uint32_t)(next)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 15, 7);

				write_string("   size: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 8);
				write_string(uint32_to_dec_string((uint32_t)(next->size)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 15, 8);
					
				write_string("   next:", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 9);
				write_string(uint32_to_fixed_width_hex_string((uint32_t)(next->next_header)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 15, 9);

				write_string("   previous:", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 10);
				write_string(uint32_to_fixed_width_hex_string((uint32_t)(next->previous_header)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 15, 10);
				*/
				
				
				count++;

				/*write_string("Difference in address: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 13);
				write_string(uint32_to_hex_string((uint32_t)(next-temp)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, strlen("Difference in address: "), 13);
				write_string(" 0d", 
								VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 
								strlen("Difference in address: ")+strlen(uint32_to_hex_string((uint32_t)(next-temp))), 13);
				write_string(uint32_to_dec_string((uint32_t)(next-temp)), 
								VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 
								strlen("Difference in address: ")+strlen(uint32_to_hex_string((uint32_t)(next-temp)))+strlen(" 0d"), 13);
				

				write_string("Address returned: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 14);
				write_string(uint32_to_fixed_width_hex_string((uint32_t)(next+1)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, strlen("Address returned: "), 14);

				utility::wait_for_keystroke();
				cls(VGA::constants::colour::BLACK);*/

				header* temp2 = head;
				for(int i = 0; i < count; ++i) { 
					
					//write_string("Information of header[", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 0);
					//write_string(uint32_to_dec_string((uint32_t)(i)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, strlen("Information of header["), 0);
					//write_string("]:", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, strlen("Information of header[i"), 0);

					//write_string("   address: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 1);
					//write_string(uint32_to_fixed_width_hex_string((uint32_t)(temp2)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 15, 1);

					//write_string("   size: ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 2);
					//write_string(uint32_to_dec_string((uint32_t)(temp2->size)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, strlen("   size:       "), 2);
					
					//write_string("   next:", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 3);
					//write_string(uint32_to_fixed_width_hex_string((uint32_t)(temp2->next_header)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, strlen("   next:       "), 3);

					//write_string("   previous:", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 4);
					//write_string(uint32_to_fixed_width_hex_string((uint32_t)(temp2->previous_header)), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, strlen("   previous:   "), 4);

					//write_string("   str value:", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 5);
					char* value = reinterpret_cast<char*>(reinterpret_cast<void*>(temp2)+sizeof(header)+1);
					//write_string(value, VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 15, 5);

					//write_string("   int value:", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 6);

					//write_string(uint32_to_hex_string((uint32_t)value), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 15, 5);
					/*int j = 0;
					int position = 0;
					while(value[j]!=0){
						uint32_to_dec_string(value[j])
						position+=strlen(uint32_to_dec_string(value[j]));
					}*/
					/*for(int j = 0; j < temp2->size; ++j) {
						write_character(value[j], VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 15+j, 5);
					}
					for(int j = 0; j < temp2->size; ++j) {
						write_string(uint32_to_dec_string(value[j]), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 15+j, 5);
					}*/

				
					//utility::wait_for_keystroke();
					//cls(VGA::constants::colour::BLACK);
					
					temp2 = temp2->next_header;
				}
				return reinterpret_cast<T*>(reinterpret_cast<void*>(next)+sizeof(header)+1);
			}
		}

		/*volatile size_t* allocation_header 			= (size_t*)(0x00200000+sizeof(size_t));
		volatile size_t* allocation_header_size 	= (size_t*)0x00200000;
		static int counter = 0;*/
	}
}