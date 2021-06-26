#include "vm.h"

/**
*	Konstruktor inicializuje program_memory na hodnoty 0xffff v celem rozsahu.
**/
vm::vm() {
	for (uint16_t i = 0x0000; i < 0xffff; i++) {
		memory[i] = 0xffff;
	}
}

void vm::fetch(void) {
	
}

void vm::eval(void) {

}

void vm::getMemory(uint16_t memory_adress) { 
	std::cout << std::hex << "0x" << memory_adress << ":" << "0x" << std::hex << memory[memory_adress] << std::endl;
}
