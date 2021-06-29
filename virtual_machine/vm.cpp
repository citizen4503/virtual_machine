#include "vm.h"
 
vm::vm() {
	this->resetMemory();
	this->resetRegisters();
}

void vm::load(const char* image_name) {
	unsigned char temp;
	uint8_t two_bytes[2] = {0x00, 0x00};
	bool bytes_for_pc = true;
	int memory_index = 0;
	int i = 0;

	// otevreme soubor ke cteni s testem na chybu
	std::ifstream rom_image = std::ifstream(image_name, std::ios::binary);
	if (!rom_image.is_open()) {
		std::cout << "Error: File path is wrong or file doesnt exist" << std::endl;
	}

	// REF.: https://www.programmersought.com/article/26696240059/
	// cteme data ze souboru po jednom bajtu za cyklus dokud tam neco je
	while (rom_image.read((char*)&temp, 1)) {
		
		// nabereme prvni dva bajty
		two_bytes[i] = temp;
		// inkrementujeme pro zapis dalsich dvou bajtu do pole 'two_bytes'
		i++;

		// jakmile nam inkrementor rekne ze jsou oba prvky pole naplneny
		if (i == 2) {
			// provedeme bitovy posun pro prvnich 8 bitu z prvniho precteneho bajtu a pridame k tomu zbyvajicich 8 bitu z druheho bajtu logickym OR
			uint16_t res = (two_bytes[0] << 8) | (two_bytes[1]);

			// pokud jsme nabrali prvni dva bajty, musime si je ulozit do registru PC
			if (bytes_for_pc == true) {
				bytes_for_pc = false;
				this->registers.PC = res;
				// nove nastaveny PC nam urcuje na jakou adresu budeme zapisovat precteny program do programove pameti
				memory_index = this->registers.PC;
			}
			else {
				// vysledne 2 bajty (16 bitu) zapiseme na adresu do pameti
				this->memory[memory_index] = res;
				memory_index++;
			}

			//std::cout << std::hex << two_bytes[0] << " + " << std::hex << two_bytes[1] << " = " << std::hex << res << std::endl;
			
			// nakonec si vsechno vynulujeme abysme mohli jit odznova
			two_bytes[0] = 0x00;
			two_bytes[1] = 0x00;
			res = 0x00;
			i = 0;
		}
	}

	// zavreme soubor
	rom_image.close();
}

std::pair <uint16_t, uint16_t> vm::fetch(void) {
	// precteme instrukci na adrese v pameti na kterou nam ukazuje PC
	uint16_t instruction = this->readMemory(this->registers.PC);
	// bitovym posunem o 12 bitu ziskame posledni 4 bity instrukce (ta obsahuje operacni kod)
	uint16_t op = instruction >> 12;
	std::cout	<< "FETCH>\t\t"
				<< "PC: " << "0x" << std::hex << this->registers.PC
				<< " | INSTRUCTION: " << std::hex << instruction
				<< " | OP: " << std::hex << op
				<< std::endl;
	
	// inkrementujeme PC na dalsi adresu v pameti
	this->registers.PC++;

	return std::make_pair(op, instruction);
}

void vm::eval(std::pair <uint16_t, uint16_t> op_and_instruction) {
	
	uint16_t op = op_and_instruction.first;
	uint16_t instruction = op_and_instruction.second;

	switch (op) {
		case this->ADD: {
			std::cout << "ADD>\t\t" << std::hex << instruction << std::endl;
			break;
		}
		case this->AND: {
			std::cout << "AND" << std::endl;
			break;
		}
		case this->NOT: {
			break;
		}
		case this->BR: {
			break;
		}
		case this->JMP: {
			break;
		}
		case this->JSR: {
			break;
		}
		case this->LD: {
			break;
		}
		case this->LDI: {
			break;
		}
		case this->LDR: {
			break;
		}
		case this->LEA: {
			break;
		}
		case this->ST: {
			break;
		}
		case this->STI: {
			break;
		}
		case this->STR: {
			break;
		}
		case this->TRAP: {
			break;
		}
		case this->RES: {
			break;
		}
		case this->RTI: {
			break;
		}
		default: {
			// spatny op kod
			break;
		}
	}
}

void vm::resetMemory(void) {
	for (uint16_t i = 0x0000; i < 0xffff; i++) {
		this->memory[i] = 0xffff;
	}
}

void vm::resetRegisters(void) {
	this->registers.R0 = 0x0000;
	this->registers.R1 = 0x0000;
	this->registers.R2 = 0x0000;
	this->registers.R3 = 0x0000;
	this->registers.R4 = 0x0000;
	this->registers.R5 = 0x0000;
	this->registers.R6 = 0x0000;
	this->registers.R7 = 0x0000;
	this->registers.NEG = 0x0000;
	this->registers.ZRO = 0x0000;
	this->registers.POS = 0x0000;
}

uint16_t vm::readMemory(uint16_t memory_address) { 
	return this->memory[memory_address];
}

void vm::memoryDump(uint16_t memory_address) {
	std::cout << "MEM_DUMP>\t" << std::hex << "0x" << memory_address << ":" << "0x" << std::hex << this->memory[memory_address] << std::endl;
}

void vm::test_running(void) {
	this->eval(this->fetch());
}