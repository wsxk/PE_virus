#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
	char a[16] = "user32.dll\0";
	char b[16] = "MessageBoxA\0";
	char c[16] = "wsxk\0";
	char d[16] = "virus!\0";
	__asm {
		call A
		A:	
		pop ebx						//eip
		mov edx, fs: [30h]        //获得PEB
		mov edx, [edx + 0ch]//get peb_ldr_data
		mov edx, [edx + 1ch]//get InInitializationOrderModuleList
		mov edx, [edx]
		mov edx, [edx + 50h]//此时eax中存放的就是kernel32.dll的地址
		
		push edx
		push ebx
		sub ebx,0x45
		push ebx //user32.dll
		mov eax,edx
		add eax,0x20bd0
		call eax //loadlibrary,调用后返回user32.dll的地址

		pop ebx
		pop edx
		add edx,0x1f550//getprocaddress
		push ebx
		sub ebx,0x35
		push ebx
		push eax
		
		mov eax,edx
		call eax	//返回messagebox地址

		pop ebx
		push 0
		sub ebx,0x25
		push ebx
		add ebx,0x10
		push ebx
		push 0
		call eax //MESSAGEBOX
		
		ret 0xc


	}
}