#include "vm.h"
 
int main() {

	vm test_machine; 

	test_machine.load("example1.bin");

	test_machine.test_running();
	
	return 0;
}