#include "vm.h"
 
int main() {

	vm test_machine; 

	// nahrani binarky do pameti stroje
	test_machine.load("ldi.bin");


	// spusteni programu
	test_machine.run();
	test_machine.run();
	test_machine.run();
	test_machine.run();
	test_machine.run();
	test_machine.run();
	test_machine.run();
		
	// vypis pameti na adrese 0x3000
	test_machine.memoryDump(0x3000, 0x3010);


	// vypis vsech registru
	for (int i = 0; i < 12; i++) {
		test_machine.registerDump(i);
	}

	
	
	return 0;
}