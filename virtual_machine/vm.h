#pragma once

#include <iostream>
#include "compiler.h"

class vm : private compiler{
public:
	vm();
	void getMemory(uint16_t);

private:
	uint16_t memory[65535];
	
	// registry 
	struct Registers {
		uint16_t R0 = 0x0000;
		uint16_t R1 = 0x0000;
		uint16_t R2 = 0x0000;
		uint16_t R3 = 0x0000;
		uint16_t R4 = 0x0000;
		uint16_t R5 = 0x0000;
		uint16_t R6 = 0x0000;
		uint16_t R7 = 0x0000;
		uint16_t PC = 0x0000;	// program counter
	}registers;

	// flagy
	typedef enum {
		POS = 1 << 0,	// 1
		ZRO = 1 << 1,	// 2
		NEG = 1 << 2	// 4
	}flags;

	// instrukcni sada
	typedef enum {
		ADD = 0,
		LD,
		ST,
		JMP,
		LDR,
		STR,
		AND,
		OR,
		NOT
	}instructions;

	void fetch(void);
	void eval(void);
};
