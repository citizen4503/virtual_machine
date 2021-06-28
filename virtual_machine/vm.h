#pragma once
 
#include <iostream>
#include <fstream>
#include "compiler.h"

class vm : private compiler{
public:
	/*
	*	Konstruktor vola metody pro inicializaci pameti a nulovani registru.
	*/
	vm();

	/*
	* Metoda prevezme binarni soubor. Nastavi PC, a zapise si program do pameti.
	* @param const char*: nazev souboru, nebo uplna cesta k souboru
	*/
	void load(const char*);

	/*
	* Posle obsah pameti na predane adrese na stdout 
	* @param uint16_t: adresa pameti zapsana v 16-tkove notaci
	*/
	void memoryDump(uint16_t);

	void test_running(void);

private:
	uint16_t memory[65535];
	
	struct Registers {
		uint16_t R0 = 0x0000;
		uint16_t R1 = 0x0000;
		uint16_t R2 = 0x0000;
		uint16_t R3 = 0x0000;
		uint16_t R4 = 0x0000;
		uint16_t R5 = 0x0000;
		uint16_t R6 = 0x0000;
		uint16_t R7 = 0x0000;
		uint16_t PC = 0x0000;
		uint16_t NEG = 0x0000;
		uint16_t ZRO = 0x0000;
		uint16_t POS = 0x0000;
	}registers;

	typedef enum {
		POS = 1 << 0,	// 1
		ZRO = 1 << 1,	// 2
		NEG = 1 << 2	// 4
	}flags;

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
	
	/*
	* Vraci obsah pameti na adrese
	* @param uint16_t: adresa pameti zapsana v 16-tkove notaci
	* @return uint16_t: hexa obsah pameti na pozadovane adrese
	*/
	uint16_t readMemory(uint16_t);

	/*
	* Inicializace pameti na hodnoty 0xffff.
	*/
	void resetMemory(void);
	
	/*
	* Vynulovani registru
	*/
	void resetRegisters(void);
};
