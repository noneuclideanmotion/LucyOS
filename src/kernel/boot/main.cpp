#include <stddef.h>
#include <stdint.h>
#include <kernel/include/memory/memory.hpp>
#include <kernel/include/memory/allocate.hpp>
#include <kernel/include/memory/copy.hpp>
#include <kernel/include/print.hpp>
#include <kernel/include/utility/wait.hpp>
#include <kernel/include/utility/map.hpp>
#include <kernel/include/utility/keyboard.hpp>

inline void  __attribute__((always_inline)) dump_registers() {
	//register int eax asm ("eax");
	register int ebx asm ("ebx");
	register int ecx asm ("ecx");
	register int edx asm ("edx");
	register int esi asm ("esi");
	register int edi asm ("edi");
	register int ebp asm ("ebp");
	register int esp asm ("esp");
	int eax;
	asm("" :"=a"(eax));
	write_string("EAX:  ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 0);
	write_string(uint32_to_fixed_width_hex_string(eax), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 6, 0);
	
	write_string("EBX:  ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 1);
	write_string(uint32_to_fixed_width_hex_string(ebx), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 6, 1);
	
	write_string("ECX:  ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 2);
	write_string(uint32_to_fixed_width_hex_string(ecx), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 6, 2);

	write_string("EDX:  ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 0, 3);
	write_string(uint32_to_fixed_width_hex_string(edx), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 6, 3);


	write_string("   ESI:  ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 20-3, 0);
	write_string(uint32_to_fixed_width_hex_string(esi), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 26, 0);

	write_string("   EDI:  ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 20-3, 1);
	write_string(uint32_to_fixed_width_hex_string(edi), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 26, 1);

	write_string("   EBP:  ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 20-3, 2);
	write_string(uint32_to_fixed_width_hex_string(ebp), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 26, 2);

	write_string("   ESP:  ", VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 20-3, 3);
	write_string(uint32_to_fixed_width_hex_string(esp), VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 26, 3);
}


extern "C" int kmain() {

	
	int i = 0;
	utility::io::out(0x60, 0xED);
	utility::io::out(0x60, 2);
	uint8_t key = 0;

	ksd::data_structure::pair<int, int> p {3, 7};
	cls(VGA::constants::colour::BLACK);
	//write_string(o, VGA::constants::colour::WHITE, VGA::constants::colour::BLACK, 20, 8);
	keyboard::get_line();
	while(true) {
		
		/*for(int i = 0; i < 255; ++i){
			string[i] = get_next_printable_key();
			if(string[i] == '\n') {
				string[i+1] = '\0';
				break;
			}
			if(i == 255) {
				string[255] = '\0';
				break;
			}
			write_character
		}
		
		return string;*/
	/*
		key = utility::io::in(0x60);
		if(i%1000==0) {
			cls(VGA::constants::colour::GREY);}
		write_string("#######################################", 
		VGA::constants::colour::RED, VGA::constants::colour::BLUE, 20, 10);
		write_string("#######################################", 
		VGA::constants::colour::RED, VGA::constants::colour::BLUE, 20, 12);
		write_string("#############~~~        ~~~############", VGA::constants::colour::RED, VGA::constants::colour::BLUE, 20, 11);
		write_string("LucyOS", VGA::constants::colour::WHITE, VGA::constants::colour::BLUE, 40-(int)(strlen("LucyOS")/2), 11);
		write_string(keyboard::ps2::utility::scancode_to_name_string(key), VGA::constants::colour::RED, VGA::constants::colour::BLACK, 35, 20);
		write_string(uint32_to_fixed_width_dec_string(i), VGA::constants::colour::RED, VGA::constants::colour::BLACK, 0, 24);
		write_string(uint32_to_dec_string(p.first), VGA::constants::colour::RED, VGA::constants::colour::BLACK, 0, 10);
		write_string(",", VGA::constants::colour::RED, VGA::constants::colour::BLACK, 2, 10);
		write_string(uint32_to_dec_string(p.second), VGA::constants::colour::RED, VGA::constants::colour::BLACK, 3, 10);*/
	}
	return 0xDEADBEEF;
}

/* outb(0x60, 0xED);
outb(0x60, 2);*/