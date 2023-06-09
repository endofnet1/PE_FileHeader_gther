/*
Created with Hope
endOfnet 9 June 2023
*/

#include <stdio.h>
#include <windows.h>


LPVOID base(LPCSTR *filename) //Find the starting point of the file in memory
{
	HANDLE file, map;
	LPVOID memory;
	
	file = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE){
		printf(" [!] Error in CreateFileA function!\n");
	}
	
	map = CreateFileMapping(file, NULL, PAGE_READONLY, 0, 0, NULL);
		if (file == NULL){
		printf(" [!] Error in CreateFileMapping function!\n");
	}
	
		memory = MapViewOfFile(map,FILE_MAP_READ,0 ,0 ,0);
		if (file == NULL){
		printf(" [!] Error in MapViewOfFile function!\n");
	}
	
	return memory;
}


PIMAGE_NT_HEADERS nt_gether(LPVOID memory) //Find the starting point of Nt Header With the help of Dos Header
{
	PIMAGE_DOS_HEADER dos;
	PIMAGE_NT_HEADERS nt;
	
	dos = (PIMAGE_DOS_HEADER) memory;
	nt = (PIMAGE_NT_HEADERS) (memory + dos->e_lfanew);
	
	return nt;
}


int main(int argc , char *argv[])
{

	if (argc != 2){
	printf("\n [!] Just Valid Arguments!\n");
	return 1;
	}
	
	WORD m, s, soh, charac;
	DWORD time, nos;
	
	LPCSTR filename = argv[1];
	LPVOID memory = base(filename);
	PIMAGE_NT_HEADERS nt = nt_gether(memory);
	
	printf(" [-] File Header : \n\n");
	m = nt->FileHeader.Machine;
	printf("   > Machine : %X\n\n", m);
	
	
	s = nt->FileHeader.NumberOfSections;
	printf("   > NumberOfSection : %d\n\n", s);
	
	time = nt->FileHeader.TimeDateStamp;
	printf("   > TimeStamp : %d\n\n", time);
	
	soh = nt->FileHeader.SizeOfOptionalHeader;
	printf("   > SizeOfOptionalHeader : %d\n\n", soh);
	
	charac = nt->FileHeader.Characteristics;
	printf("   > Characteristics : %X\n\n", charac);
	
	nos = nt->FileHeader.NumberOfSymbols;
	printf("   > NumberOfSymbols : %d\n\n", nos);
	
	getch();
}
