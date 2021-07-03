#pragma once
 
#include <iostream>
#include <fstream>
#include "debugger.h"

class vm : private debugger{
public:
	/*
	*	Konstruktor vola metody pro inicializaci pameti a nulovani registru a flagu.
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

	/*
	* Posle obsah registru na stdout
	* @param 
	*/
	void registerDump(int);

	/*
	* Zacne zpracovavat program nahrany v pameti od adresy na PC
	*/
	void run(void);

protected:
	// Pametova oblast
	uint16_t memory[65535];

	// Oblast obsahu registru
	uint16_t registers[12];

	typedef enum {
		R0 = 0,
		R1,
		R2,
		R3,
		R4,
		R5,
		R6,
		R7,
		PC,
		ZRO,
		POS,
		NEG
	}Registers;

	typedef enum {
		ADD = 1,
		AND,
		NOT,
		BR,
		JMP,
		JSR,
		LD,
		LDI,
		LDR,
		LEA,
		ST,
		STI,
		STR,
		TRAP,
		RES,
		RTI
	}instructions;

	/*
	* Metoda precte instrukci v pameti na kterou ukazuje registr PC a bitovym posunem ziska OP kod, ktery vraci.
	* return uint16_t : op kod 
	* return uint16_t : instrukce
	*/
	std::pair <uint16_t, uint16_t> fetch(void);
	
	/*
	* Metoda slouzi ke zpracovani dane instrukce
	* @param pair: operacni kod a instrukce pro zpracovani
	*/
	void eval(std::pair <uint16_t, uint16_t>);
	
	/*
	* Metoda doplni n-bitove cislo na velikost 16-ti bitu
	* @param uint16_t: predana instrukce, z ktere budeme zpracovavat pocet bitu dle druheho parametru
	* @param int: pocet bitu ke zpracovani
	* @return uint16_t: vraci n-bitove cislo doplnene o nuly nebo jednicky (dle typu instrukce)
	*/
	uint16_t extend(uint16_t, int);

	void update_flag(uint16_t);

	/*
	* Inicializace pameti na hodnoty 0xffff.
	*/
	void resetMemory(void);
	
	/*
	* Vynulovani registru
	*/
	void resetRegisters(void);

	/*
	* Nuluje hodnoty priznakovych registru
	*/
	void resetFlags(void);

	/*
	* Vraci obsah pameti na adrese
	* @param uint16_t: adresa pameti zapsana v 16-tkove notaci
	* @return uint16_t: hexa obsah pameti na pozadovane adrese
	*/
	uint16_t readMemory(uint16_t);

	/*
	* Vraci obsah registru dle parametru
	* @param int: index v poli registru
	* @return uint16_t: hodnota registru predaneho v parametru funkce
	*/
	uint16_t readRegister(int);
};
