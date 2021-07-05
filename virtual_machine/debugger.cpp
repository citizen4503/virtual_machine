#include "debugger.h"

DBG::DBG() {

}

DBG::DBG(VM* p_vm) {
	// ukazatel predany v parametru si ulozime do instancni ukazatelove promenne, pres kterou budeme pristupovat k verejnym metodam objektu VM
	vm = p_vm;
}

void DBG::registerDump(int register_index) {
	const char* reg[] = { "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "PC", "ZRO", "POS", "NEG"};
	uint16_t regVal = vm->getRegisterValue(register_index);
	std::cout << std::hex << regVal << std::endl;
}

void DBG::memoryDump(uint16_t memory_address) {
	uint16_t memVal = vm->getMemoryValue(memory_address);
	std::cout << std::hex << "0x" << memory_address << ":" << memVal << std::endl;
}