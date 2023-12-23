#pragma once
#include"stdafx.h"
#include"IT.h"
#include"LT.h"
#define TAB '\t'
#define NEW '\n'
#define COM ','
#define NULL_SYM ",0"
#define BYTE_TYPE "db"
#define DD_TYPE "dd"
#define BYTE_LABEL "1,"
#define BYTE_DECLARE "1,0"
#define BYTE_ARRAY_DECLARE "*1 dup(0)"
#define INT_LABEL "2,"
#define INT_DECLARE "2,4 dup(0)"
#define INT_ARRAY_DECLARE "*4 dup(0)"
#define BOOL_LABEL "3,"
#define BOOL_DECLARE "3,0"
#define ARRAY_INT_LABEL "4,"
#define ARRAY_BYTE_LABEL "5,"
#define ARRA_BOOL_LABEL "6,"
#define STRING_LABEL "7,"
#define MATH_LIB "includelib ../Debug/Math.lib \n EXTERN factor_fun: PROC\n EXTERN power_fun: PROC\n"
#define STRING_LIB "includelib ../Debug/String.lib \n EXTERN length_fun: PROC\n EXTERN compare_fun: PROC\nEXTERN print_fun:PROC\nEXTERN compS_fun: PROC\n"
#define HEADER ".586 \n .MODEL FLAT, STDCALL \n includelib kernel32.lib \n includelib user32.lib \n includelib libucrt.lib\n includelib ../Debug/write.lib \nincludelib ../Debug/callErrors.lib \n ExitProcess PROTO: DWORD \nMessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD\n SetConsoleTitleA PROTO :DWORD\nEXTERN writeString: PROC\nEXTERN writeLineString: PROC\nEXTERN readCon:PROC\nEXTERN waitPause: PROC\nEXTERN ErrorType: PROC\n EXTERN ErrorStackEmpty: PROC\n EXTERN ErrorStackOverflow: PROC\nEXTERN ErrorIncorInd:PROC\n"
#define HEEDER_DATA  "\n.STACK 4096 \n .DATA"
#define HEADER_CONST ".CONST"
#define CODE "\n\n.CODE\n"
#define INT_TO_CHAR_FUN "int_to_char PROC uses eax ebx ecx edi esi, \n \
pstr		: dword, \n \
intfield : sdword \n \
\n \
mov edi, pstr \n \
mov esi, 0 \n \
mov eax, intfield \n \
cdq \n \
test eax, eax \n \
mov ebx, 10 \n \
idiv ebx \n \
jns plus1 \n \
neg eax \n \
neg edx \n \
mov cl, '-' \n \
mov [edi], cl \n \
inc edi \n \
\n \
plus1: \n \
push dx \n \
inc esi \n \
test eax, eax \n \
jz fin \n \
cdq \n \
idiv ebx \n \
jmp plus1 \n \
\n \
fin: \n \
mov ecx, esi \n \
\n \
write: \n \
pop bx \n \
add bl, '0' \n \
mov [edi], bl \n \
inc edi \n \
loop write \n \
mov byte ptr [edi], 0 ; Добавление нулевого символа в конец строки \n \
ret \n \
\n \
int_to_char ENDP\n"
#define SHOW_ERROR_MESSAGEBOX_FUN "showErrorMessageBox PROC \n \
PUSH MB_OK + MB_ICONERROR \n \
PUSH OFFSET message \n \
PUSH OFFSET caption \n \
PUSH 0 \n \
call MessageBoxA \n \
push 0 \n \
call ExitProcess \n \
showErrorMessageBox ENDP\n"
#define SHOW_ERROR_TYPE_MESSAGEBOX_FUN "showErrorTypeMessageBox PROC \n \
PUSH OFFSET caption\n\
call ErrorType\n\
push 0 \n \
call ExitProcess\n \
showErrorTypeMessageBox ENDP\n"
#define SHOW_ERROR_EMPTY_STK_MESSAGEBOX_FUN "showErrorEmptyMessageBox PROC \n \
PUSH OFFSET caption\n\
call ErrorStackEmpty\n\
push 0 \n \
call ExitProcess\n \
showErrorEmptyMessageBox ENDP\n"
#define SHOW_ERROR_OVERFLOW_STK_MESSAGEBOX_FUN "showErrorOverMessageBox PROC \n \
PUSH OFFSET caption\n\
call ErrorStackOverflow\n\
push 0 \n \
call ExitProcess\n \
showErrorOverMessageBox ENDP\n"
#define SHOW_ERROR_INDEX_STK_MESSAGEBOX_FUN "showErrorIndexMessageBox PROC \n \
PUSH OFFSET caption\n\
call ErrorIncorInd\n\
push 0 \n \
call ExitProcess\n \
showErrorIndexMessageBox ENDP\n"
#define ERROR_DATA "MB_OK\tEQU\t0 \n\
message\tdb\t'Произошла ошибка во время выполнения!'\n\
caption\tdb\t'Ошибка в строке:' \n\
MB_ICONERROR\tEQU\t16 \n\
current_string\t DWORD\t 0\n"
#define BUFFER "buffer	db 4096 dup(0)\n\
ptrBuffer dword OFFSET buffer\n"
#define SET_CONOSLE_TITLE "push OFFSET consoletitle\n call SetConsoleTitleA\n"

#define TITLE_CONSOLE(title)\
	do { \
    writeCode << "consoletitle\tdb\t'"; \
    int z = 0; \
    while (title[z] != L'\0' && title[z]!=L'.') { \
        writeCode << char(title[z]); \
        z++; \
    } \
    writeCode << "',0\n"; \
} while (0)
#define MINUS_STK(value,fun) \
	do{\
		writeCode<<"sub stk";\
		if(fun!=NULL)\
		{\
		for(int w=0;w<strlen(fun->id);w++)\
		{\
			writeCode<<fun->id[w];\
		}\
		writeCode<<" +1,"<< value<<"\n"<<"cmp stk";\
		for(int w=0;w<strlen(fun->id);w++)\
		{\
			writeCode<<fun->id[w];\
		}\
		writeCode<<"+1, 0\n jl callErrorEmpty\n";\
		}\
		else\
		{\
			writeCode<<"main+1, "<<value<<"\n"<<"cmp stkmain+1,0\n jl callErrorEmpty\n";\
		}\
	}while(0)
#define PLUS_STK(fun)\
	do{\
		writeCode<<"add stk";\
		if(fun!=NULL)\
		{\
		for(int w=0;w<strlen(fun->id);w++)\
		{\
			writeCode<<fun->id[w];\
		}\
		writeCode<<" +1,1\n";\
		writeCode<<"cmp stk";\
		for(int w=0;w<strlen(fun->id);w++)\
		{\
			writeCode<<fun->id[w];\
		}\
		writeCode<<"+1,32\n jg callErrorOver\n";\
		}\
		else\
		{\
			writeCode<<"main+1, 1\n";\
			writeCode<<"cmp stkmain+1, 32\n jg callErrorOver\n";\
		}\
	}while (0)
#define CHECK_STK(value,fun) {\
	writeCode<<"cmp stk";\
	if(fun!=NULL)\
		{\
		for(int w=0;w<strlen(fun->id);w++)\
		{\
			writeCode<<fun->id[w];\
		}\
		writeCode<<" +1,";\
		writeCode<<value;\
		writeCode<<'\n';\
		}\
		else\
		{\
			writeCode<<"main+1, ";\
			writeCode << value<<'\n';\
		}\
		writeCode<<"jl callErrorEmpty\n";\
}

#define PL_STRING(value) do{\
		writeCode << "mov current_string,";\
		writeCode << value;\
		writeCode << NEW;\
	}while (0)

#define ASSIGN_FUN "Assign PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte\n\
START :\n\
mov eax, type1\n\
mov al, [eax]\n\
mov ebx, type2\n\
mov bl, [ebx]\n\
cmp al, bl\n\
jne not_equal\n\
cmp al, 1\n\
jne go_int\n\
mov eax, var1\n\
mov ebx, 0\n\
mov ebx, var2\n\
mov ebx, [ebx]\n\
mov cl, bl\n\
mov ebx, 0\n\
mov bl, cl\n\
mov byte ptr[eax], bl\n\
mov eax, 0\n\
mov ebx, 0\n\
ret\n\
\n\
\n\
go_int: \n\
cmp al, 2\n\
jne go_bool\n\
mov eax, dword ptr var1\n\
mov ebx, 0\n\
mov ebx, dword ptr var2\n\
mov ebx, [ebx]\n\
mov dword ptr[eax], ebx\n\
mov eax, 0\n\
mov ebx, 0\n\
ret\n\
\n\
\n\
go_bool :\n\
cmp al, 3\n\
jne go_string\n\
mov eax, var1\n\
mov ebx, 0\n\
mov ebx, var2\n\
mov ebx, [ebx]\n\
mov cl, bl\n\
mov ebx, 0\n\
mov bl, cl\n\
mov byte ptr[eax], bl\n\
mov eax, 0\n\
mov ebx, 0\n\
ret\n\
\n\
\n\
go_string :\n\
cmp al, 7\n\
jne callErrorType\n\
cmp bl, 7\n\
jne callErrorType\n\
mov eax, var1\n\
mov ebx, var2\n\
copy :\n\
mov dl, [ebx]; Load the current character from the string in var2 into dl\n\
mov[eax], dl; Store the character in dl to the string in var1\n\
add eax, 1; Increment the pointer to var1\n\
add ebx, 1; Increment the pointer to var2\n\
cmp byte ptr[ebx], 0; Check if the end of the string in var2 is reached\n\
je next;\n\
cmp byte ptr[eax], 0\n\
jne copy; If not, continue to the next iteration\n\
next :\n\
ret\n\
\n\
not_equal :\n\
\n\
cmp al,2\n\
jne callErrorType\n\
cmp bl, 1\n\
jne callErrorType\n\
; int < -byte\n\
	mov eax, dword ptr var1\n\
	mov ebx, 0\n\
	mov ebx, var2\n\
	movsx ebx, byte ptr [ebx]\n\
	mov ecx, ebx\n\
	mov ebx, 0\n\
	mov ebx, ecx\n\
	mov dword ptr[eax], ebx\n\
	mov eax, 0\n\
	mov ebx, 0\n\
	ret\n\
	callErrorType :\n\
add current_string, 1\n\
INVOKE int_to_char, OFFSET caption, current_string\n\
call showErrorTypeMessageBox\n\
Assign ENDP\n"
#define PLUS_FUN "PLUS PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte\n\
mov eax, type1\n\
mov al, [eax]; Тип первой переменной\n\
\n\
mov ebx, type2\n\
mov bl, [ebx]; Тип второй переменной\n\
\n\
cmp al, 2\n\
je var1Int\n\
cmp al,1\n\
jne callErrorType\n\
mov eax, 0\n\
mov ecx, var1\n\
movsx eax, byte ptr [ecx]\n\
jmp second_var\n\
\n\
var1Int :\n\
mov eax, 0\n\
mov ecx, var1\n\
mov eax, [ecx]\n\
\n\
second_var :\n\
	cmp bl, 2\n\
	je var2Int\n\
	cmp bl,1\n\
	jne callErrorType\n\
	mov ebx, 0\n\
	mov ecx, var2\n\
	movsx ebx, byte ptr [ecx]\n\
	jmp done\n\
\n\
	var2Int :\n\
mov ebx, 0\n\
mov ecx, var2\n\
mov ebx, [ecx]\n\
\n\
done :\n\
	add eax, ebx\n\
	cmp eax, 127; Сравнение с 127\n\
	jg greater; Переход, если значение больше 127\n\
	cmp eax, -128; Сравнение с - 128\n\
	jl less; Переход, если значение меньше - 128\n\
\n\
	; Значение в EAX находится в диапазоне от - 128 до 127\n\
	mov ebx, 1; Сохраняем 1 в EBX\n\
	mov ecx, ptrBuffer\n\
	mov[byte ptr[ecx]], bl; Переходим к завершению\n\
	mov[byte ptr[ecx + 1]], al\n\
	add ptrBuffer,2\n\
	mov eax, ecx\n\
	inc ecx\n\
	mov ebx, ecx\n\
	ret\n\
	greater :\n\
; Значение в EAX больше 127\n\
mov ebx, 2; Сохраняем 2 в EBX\n\
mov ecx, ptrBuffer\n\
mov[byte ptr[ecx]], bl; Переходим к завершению\n\
mov[dword ptr[ecx + 1]], eax\n\
add ptrBuffer,5\n\
mov eax, ecx\n\
inc ecx\n\
mov ebx, ecx\n\
ret\n\
\n\
less :\n\
; Значение в EAX меньше - 128\n\
mov ebx, 2; Сохраняем 2 в EBX\n\
mov ecx, ptrBuffer\n\
mov[byte ptr[ecx]], bl; Переходим к завершению\n\
mov[dword ptr[ecx + 1]], eax\n\
add ptrBuffer,5\n\
mov eax, ecx\n\
inc ecx\n\
mov ebx, ecx\n\
ret\n\
PLUS ENDP\n"
#define MINUS_FUN "MINUS PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte\n\
mov eax, type1\n\
mov al, [eax]; Тип первой переменной\n\
\n\
mov ebx, type2\n\
mov bl, [ebx]; Тип второй переменной\n\
\n\
cmp al, 2\n\
je var1Int\n\
cmp al,1\n\
jne callErrorType\n\
mov eax, 0\n\
mov ecx, var1\n\
movsx eax,byte ptr [ecx]\n\
jmp second_var\n\
\n\
var1Int :\n\
mov eax, 0\n\
mov ecx, var1\n\
mov eax, [ecx]\n\
\n\
second_var :\n\
	cmp bl, 2\n\
	je var2Int\n\
	cmp bl,1\n\
	jne callErrorType\n\
	mov ebx, 0\n\
	mov ecx, var2\n\
	movsx ebx,byte ptr [ecx]\n\
	jmp done\n\
\n\
	var2Int :\n\
mov ebx, 0\n\
mov ecx, var2\n\
mov ebx, [ecx]\n\
\n\
done :\n\
	sub ebx, eax\n\
	mov eax, ebx\n\
	cmp eax, 127; Сравнение с 127\n\
	jg greater; Переход, если значение больше 127\n\
	cmp eax, -128; Сравнение с - 128\n\
	jl less; Переход, если значение меньше - 128\n\
\n\
	; Значение в EAX находится в диапазоне от - 128 до 127\n\
	mov ebx, 1; Сохраняем 1 в EBX\n\
	mov ecx, ptrBuffer\n\
	mov[byte ptr[ecx]], bl; Переходим к завершению\n\
	mov[byte ptr[ecx + 1]], al\n\
	add ptrBuffer,2\n\
	mov eax, ecx\n\
	inc ecx\n\
	mov ebx, ecx\n\
	ret\n\
	greater :\n\
; Значение в EAX больше 127\n\
mov ebx, 2; Сохраняем 2 в EBX\n\
mov ecx, ptrBuffer\n\
mov[byte ptr[ecx]], bl; Переходим к завершению\n\
mov[dword ptr[ecx + 1]], eax\n\
add ptrBuffer,5\n\
mov eax, ecx\n\
inc ecx\n\
mov ebx, ecx\n\
ret\n\
\n\
less :\n\
; Значение в EAX меньше - 128\n\
mov ebx, 2; Сохраняем 2 в EBX\n\
mov ecx, ptrBuffer\n\
mov[byte ptr[ecx]], bl; Переходим к завершению\n\
mov[dword ptr[ecx + 1]], eax\n\
add ptrBuffer,5\n\
mov eax, ecx\n\
inc ecx\n\
mov ebx, ecx\n\
ret\n\
MINUS ENDP\n"
#define MULT_FUN "MULT PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte\n\
mov eax, type1\n\
mov al, [eax]; Тип первой переменной\n\
\n\
mov ebx, type2\n\
mov bl, [ebx]; Тип второй переменной\n\
\n\
cmp al, 2\n\
je var1Int\n\
cmp al,1\n\
jne callErrorType\n\
mov eax, 0\n\
mov ecx, var1\n\
movsx eax,byte ptr [ecx]\n\
jmp second_var\n\
\n\
var1Int :\n\
mov eax, 0\n\
mov ecx, var1\n\
mov eax, [ecx]\n\
\n\
second_var :\n\
	cmp bl, 2\n\
	je var2Int\n\
	cmp bl,1\n\
	jne callErrorType\n\
	mov ebx, 0\n\
	mov ecx, var2\n\
	movsx ebx, byte ptr [ecx]\n\
	jmp done\n\
\n\
	var2Int :\n\
mov ebx, 0\n\
mov ecx, var2\n\
mov ebx, [ecx]\n\
\n\
done :\n\
	mul ebx\n\
	cmp eax, 127; Сравнение с 127\n\
	jg greater; Переход, если значение больше 127\n\
	cmp eax, -128; Сравнение с - 128\n\
	jl less; Переход, если значение меньше - 128\n\
\n\
	; Значение в EAX находится в диапазоне от - 128 до 127\n\
	mov ebx, 1; Сохраняем 1 в EBX\n\
	mov ecx, ptrBuffer\n\
	mov[byte ptr[ecx]], bl; Переходим к завершению\n\
	mov[byte ptr[ecx + 1]], al\n\
	add ptrBuffer,2\n\
	mov eax, ecx\n\
	inc ecx\n\
	mov ebx, ecx\n\
	ret\n\
	greater :\n\
; Значение в EAX больше 127\n\
mov ebx, 2; Сохраняем 2 в EBX\n\
mov ecx, ptrBuffer\n\
mov[byte ptr[ecx]], bl; Переходим к завершению\n\
mov[dword ptr[ecx + 1]], eax\n\
add ptrBuffer,5\n\
mov eax, ecx\n\
inc ecx\n\
mov ebx, ecx\n\
ret\n\
\n\
less :\n\
; Значение в EAX меньше - 128\n\
mov ebx, 2; Сохраняем 2 в EBX\n\
mov ecx, ptrBuffer\n\
mov[byte ptr[ecx]], bl; Переходим к завершению\n\
mov[dword ptr[ecx + 1]], eax\n\
add ptrBuffer,5\n\
mov eax, ecx\n\
inc ecx\n\
mov ebx, ecx\n\
ret\n\
MULT ENDP\n"
#define DIV_FUN "DIVIDE PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte\n\
mov eax, type1\n\
mov al, [eax]; Тип первой переменной\n\
\n\
mov ebx, type2\n\
mov bl, [ebx]; Тип второй переменной\n\
\n\
cmp al, 2\n\
je var1Int\n\
cmp al,1\n\
jne callErrorType\n\
mov eax, 0\n\
mov ecx, var1\n\
movsx eax, byte ptr [ecx]\n\
cmp al,0\n\
je callErrorType\n\
jmp second_var\n\
\n\
var1Int :\n\
mov eax, 0\n\
mov ecx, var1\n\
mov eax, [ecx]\n\
cmp eax,0\n\
je callErrorType\n\
\n\
second_var :\n\
	cmp bl, 2\n\
	je var2Int\n\
	cmp bl,1\n\
	jne callErrorType\n\
	mov ebx, 0\n\
	mov ecx, var2\n\
	movsx ebx, byte ptr [ecx]\n\
	jmp done\n\
\n\
	var2Int :\n\
mov ebx, 0\n\
mov ecx, var2\n\
mov ebx, [ecx]\n\
\n\
done :\n\
	mov ecx, ebx\n\
	mov ebx, eax\n\
	mov eax, ecx\n\
	xor edx, edx\n\
	div ebx\n\
	cmp eax, 127; Сравнение с 127\n\
	jg greater; Переход, если значение больше 127\n\
	cmp eax, -128; Сравнение с - 128\n\
	jl less; Переход, если значение меньше - 128\n\
\n\
	; Значение в EAX находится в диапазоне от - 128 до 127\n\
	mov ebx, 1; Сохраняем 1 в EBX\n\
	mov ecx, ptrBuffer\n\
	mov[byte ptr[ecx]], bl; Переходим к завершению\n\
	mov[byte ptr[ecx + 1]], al\n\
	add ptrBuffer,2\n\
	mov eax, ecx\n\
	inc ecx\n\
	mov ebx, ecx\n\
	ret\n\
	greater :\n\
; Значение в EAX больше 127\n\
mov ebx, 2; Сохраняем 2 в EBX\n\
mov ecx, ptrBuffer\n\
mov[byte ptr[ecx]], bl; Переходим к завершению\n\
mov[dword ptr[ecx + 1]], eax\n\
add ptrBuffer,5\n\
mov eax, ecx\n\
inc ecx\n\
mov ebx, ecx\n\
ret\n\
\n\
less :\n\
; Значение в EAX меньше - 128\n\
mov ebx, 2; Сохраняем 2 в EBX\n\
mov ecx, ptrBuffer\n\
mov[byte ptr[ecx]], bl; Переходим к завершению\n\
mov[dword ptr[ecx + 1]], eax\n\
add ptrBuffer,5\n\
mov eax, ecx\n\
inc ecx\n\
mov ebx, ecx\n\
ret\n\
DIVIDE ENDP\n"
#define MORE_FUN "MORE PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte\n\
mov eax, type1\n\
mov al, [eax]; Тип первой переменной\n\
\n\
mov ebx, type2\n\
mov bl, [ebx]; Тип второй переменной\n\
\n\
cmp al, 2\n\
je var1Int\n\
cmp al, 1\n\
jne callErrorType\n\
mov eax, 0\n\
mov ecx, var1\n\
movsx eax, byte ptr [ecx]\n\
jmp second_var\n\
\n\
var1Int :\n\
mov eax, 0\n\
mov ecx, var1\n\
mov eax, [ecx]\n\
\n\
second_var :\n\
	cmp bl, 2\n\
	je var2Int\n\
	cmp bl, 1\n\
	jne callErrorType\n\
	mov ebx, 0\n\
	mov ecx, var2\n\
	movsx ebx, byte ptr [ecx]\n\
	jmp done\n\
\n\
	var2Int :\n\
mov ebx, 0\n\
mov ecx, var2\n\
mov ebx, [ecx]\n\
\n\
done :\n\
	cmp ebx, eax\n\
	jg great\n\
	less :\n\
mov eax, offset false\n\
mov ebx, offset false + 1\n\
ret\n\
great :\n\
mov eax, offset true\n\
mov ebx, offset true + 1\n\
ret\n\
MORE ENDP\n"
#define MORE_EQUAL_FUN "MOREEQUAL PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte\n\
mov eax, type1\n\
mov al, [eax]; Тип первой переменной\n\
\n\
mov ebx, type2\n\
mov bl, [ebx]; Тип второй переменной\n\
\n\
cmp al, 2\n\
je var1Int\n\
cmp al, 1\n\
jne callErrorType\n\
mov eax, 0\n\
mov ecx, var1\n\
movsx eax, byte ptr [ecx]\n\
jmp second_var\n\
\n\
var1Int :\n\
mov eax, 0\n\
mov ecx, var1\n\
mov eax, [ecx]\n\
\n\
second_var :\n\
	cmp bl, 2\n\
	je var2Int\n\
	cmp bl, 1\n\
	jne callErrorType\n\
	mov ebx, 0\n\
	mov ecx, var2\n\
	movsx ebx,byte ptr [ecx]\n\
	jmp done\n\
\n\
	var2Int :\n\
mov ebx, 0\n\
mov ecx, var2\n\
mov ebx, [ecx]\n\
\n\
done :\n\
	cmp ebx, eax\n\
	je great\n\
	jg great\n\
mov eax, offset false\n\
mov ebx, offset false + 1\n\
ret\n\
great :\n\
mov eax, offset true\n\
mov ebx, offset true + 1\n\
ret\n\
MOREEQUAL ENDP\n"
#define LESS_FUN "LESSFUN PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte\n\
mov eax, type1\n\
mov al, [eax]; Тип первой переменной\n\
\n\
mov ebx, type2\n\
mov bl, [ebx]; Тип второй переменной\n\
\n\
cmp al, 2\n\
je var1Int\n\
cmp al, 1\n\
jne callErrorType\n\
mov eax, 0\n\
mov ecx, var1\n\
movsx eax, byte ptr [ecx]\n\
jmp second_var\n\
\n\
var1Int :\n\
mov eax, 0\n\
mov ecx, var1\n\
mov eax, [ecx]\n\
\n\
second_var :\n\
	cmp bl, 2\n\
	je var2Int\n\
	cmp bl, 1\n\
	jne callErrorType\n\
	mov ebx, 0\n\
	mov ecx, var2\n\
	movsx ebx, byte ptr [ecx]\n\
	jmp done\n\
\n\
	var2Int :\n\
mov ebx, 0\n\
mov ecx, var2\n\
mov ebx, [ecx]\n\
\n\
done :\n\
	cmp ebx, eax\n\
	jl great\n\
mov eax, offset false\n\
mov ebx, offset false + 1\n\
ret\n\
great :\n\
mov eax, offset true\n\
mov ebx, offset true + 1\n\
ret\n\
LESSFUN ENDP\n"
#define LESS_EQUAL_FUN "LESEQUAL PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte\n\
mov eax, type1\n\
mov al, [eax]; Тип первой переменной\n\
\n\
mov ebx, type2\n\
mov bl, [ebx]; Тип второй переменной\n\
\n\
cmp al, 2\n\
je var1Int\n\
cmp al, 1\n\
jne callErrorType\n\
mov eax, 0\n\
mov ecx, var1\n\
movsx eax, byte ptr [ecx]\n\
jmp second_var\n\
\n\
var1Int :\n\
mov eax, 0\n\
mov ecx, var1\n\
mov eax, [ecx]\n\
\n\
second_var :\n\
	cmp bl, 2\n\
	je var2Int\n\
	cmp bl, 1\n\
	jne callErrorType\n\
	mov ebx, 0\n\
	mov ecx, var2\n\
	movsx ebx, byte ptr [ecx]\n\
	jmp done\n\
\n\
	var2Int :\n\
mov ebx, 0\n\
mov ecx, var2\n\
mov ebx, [ecx]\n\
\n\
done :\n\
	cmp ebx, eax\n\
	je great\n\
	jl great\n\
	les1:\n\
mov eax, offset false\n\
mov ebx, offset false + 1\n\
ret\n\
great :\n\
mov eax, offset true\n\
mov ebx, offset true + 1\n\
ret\n\
LESEQUAL ENDP\n"
#define EQUAL_FUN "EQUAl PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte\n\
mov eax, type1\n\
mov al, [eax]; Тип первой переменной\n\
\n\
mov ebx, type2\n\
mov bl, [ebx]; Тип второй переменной\n\
\n\
cmp al, 2\n\
je var1Int\n\
cmp al, 1\n\
jne callErrorType\n\
mov eax, 0\n\
mov ecx, var1\n\
movsx eax, byte ptr [ecx]\n\
jmp second_var\n\
\n\
var1Int :\n\
mov eax, 0\n\
mov ecx, var1\n\
mov eax, [ecx]\n\
\n\
second_var :\n\
	cmp bl, 2\n\
	je var2Int\n\
	cmp bl, 1\n\
	jne callErrorType\n\
	mov ebx, 0\n\
	mov ecx, var2\n\
	movsx ebx, byte ptr [ecx]\n\
	jmp done\n\
\n\
	var2Int :\n\
mov ebx, 0\n\
mov ecx, var2\n\
mov ebx, [ecx]\n\
\n\
done :\n\
	cmp ebx, eax\n\
	je great\n\
	less :\n\
mov eax, offset false\n\
mov ebx, offset false + 1\n\
ret\n\
great :\n\
mov eax, offset true\n\
mov ebx, offset true + 1\n\
ret\n\
EQUAL ENDP\n"
#define NOTEQUAL_FUN "NOTEQUAl PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte\n\
mov eax, type1\n\
mov al, [eax]; Тип первой переменной\n\
\n\
mov ebx, type2\n\
mov bl, [ebx]; Тип второй переменной\n\
\n\
cmp al, 2\n\
je var1Int\n\
cmp al, 1\n\
jne callErrorType\n\
mov eax, 0\n\
mov ecx, var1\n\
movsx eax, byte ptr [ecx]\n\
jmp second_var\n\
\n\
var1Int :\n\
mov eax, 0\n\
mov ecx, var1\n\
mov eax, [ecx]\n\
\n\
second_var :\n\
	cmp bl, 2\n\
	je var2Int\n\
	cmp bl, 1\n\
	jne callErrorType\n\
	mov ebx, 0\n\
	mov ecx, var2\n\
	movsx ebx, byte ptr [ecx]\n\
	jmp done\n\
\n\
	var2Int :\n\
mov ebx, 0\n\
mov ecx, var2\n\
mov ebx, [ecx]\n\
\n\
done :\n\
	cmp ebx, eax\n\
	je great\n\
	less :\n\
mov eax, offset true\n\
mov ebx, offset true + 1\n\
ret\n\
great :\n\
mov eax, offset false\n\
mov ebx, offset false + 1\n\
ret\n\
NOTEQUAL ENDP\n"


#define DUPLICATE "pop eax\npop ebx\npush ebx\npush eax\npush ebx\npush eax\n mov eax,0 \n mov ebx,0\n"
#define G_DROP "pop eax\npop ebx\n mov eax,0 \n mov ebx,0\n"
#define G_SWAP "pop eax\npop ebx\npop ecx\npop edx\n push edx\n push ecx\n push ebx\n push eax\nmov eax,0 \n mov ebx,0\n mov ecx,0\n mov edx,0\n"
#define G_OVER "pop eax\npop ebx\npop ecx\npop edx\n push edx\n push ecx\n push ebx\n push eax\n push edx\n push ecx\n mov eax,0 \n mov ebx,0\n mov ecx,0\n mov edx,0\n"
#define G_IF "pop eax\npop eax\n cmp eax, true+1"
#define CALL_ERROR "callError:\n\
INVOKE int_to_char, OFFSET caption + 16, current_string\n\
call showErrorMessageBox\n"
#define CALL_ERROR_TYPE "callErrorType:\n\
INVOKE int_to_char, OFFSET caption, current_string\n\
call showErrorTypeMessageBox\n"
#define CALL_ERROR_EMPTY_STK "callErrorEmpty:\n\
INVOKE int_to_char, OFFSET caption, current_string\n\
call showErrorEmptyMessageBox\n"
#define CALL_ERROR_OVER_STK "callErrorOver:\n\
INVOKE int_to_char, OFFSET caption, current_string\n\
call showErrorOverMessageBox\n"
#define CALL_ERROR_INDEX "callErrorIncorInd:\n\
INVOKE int_to_char, OFFSET caption, current_string\n\
call showErrorIndexMessageBox\n"
#define DEAPTH_STK(fun) \
	do{\
		writeCode<<"push OFFSET stk";\
		if(fun!=NULL)\
		{\
		for(int w=0;w<strlen(fun->id);w++)\
		{\
			writeCode<<fun->id[w];\
		}\
		writeCode<<" +1\n";\
		writeCode<<"push OFFSET stk";\
		for(int w=0;w<strlen(fun->id);w++)\
		{\
			writeCode<<fun->id[w];\
		}\
		writeCode<<"\n";\
		}\
		else\
		{\
			writeCode<<"main+1\n";\
			writeCode<<"push OFFSET stkmain\n";\
		}\
	}while(0)
#define MAIN "\nmain PROC\nSTART :\n"
#define FOOTER "\npush - 1\ncall ExitProcess\nmain ENDP\nend main\n"
#define MAKEPAUSE "call waitPause\n"
#define PUSH "push "    
#define OFFSET "offset "
#define PROC "PROC "
#define ENDP " ENDP\n"
#define START "START:\n"
#define PTR_BYTE ": ptr byte"
#define ASSIGN_VALUE "pop eax\n pop ebx\n callCheckVar "
namespace GEN
{	enum CONSTRUCT{IF=1,WHILE=2};
	struct CONSTR
	{
		CONSTRUCT type;
		int number;
	};
	void Generator(LT::LexTable& lextable, IT::IdTable& idtable, Parm::PARM parms, PreProc::lib)	;
	void GenerateMemory(IT::IdTable& idtable, ofstream& writeCode);
}