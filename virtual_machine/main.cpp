#include "vm.h"
 
int main() {

	vm test_machine; 

	test_machine.load("example1.bin");

	test_machine.getMemory(0x3000);
	
	return 0;
}