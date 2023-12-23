.586 
 .MODEL FLAT, STDCALL 
 includelib kernel32.lib 
 includelib user32.lib 
 includelib libucrt.lib
 includelib ../Debug/write.lib 
includelib ../Debug/callErrors.lib 
 ExitProcess PROTO: DWORD 
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD
 SetConsoleTitleA PROTO :DWORD
EXTERN writeString: PROC
EXTERN writeLineString: PROC
EXTERN readCon:PROC
EXTERN waitPause: PROC
EXTERN ErrorType: PROC
 EXTERN ErrorStackEmpty: PROC
 EXTERN ErrorStackOverflow: PROC
EXTERN ErrorIncorInd:PROC
includelib ../Debug/Math.lib 
 EXTERN factor_fun: PROC
 EXTERN power_fun: PROC
includelib ../Debug/String.lib 
 EXTERN length_fun: PROC
 EXTERN compare_fun: PROC
EXTERN print_fun:PROC
EXTERN compS_fun: PROC
includelib ../Debug/Math.lib 
 EXTERN factor_fun: PROC
 EXTERN power_fun: PROC
includelib ../Debug/String.lib 
 EXTERN length_fun: PROC
 EXTERN compare_fun: PROC
EXTERN print_fun:PROC
EXTERN compS_fun: PROC

.STACK 4096 
 .DATA
MB_OK	EQU	0 
message	db	'Произошла ошибка во время выполнения!'
caption	db	'Ошибка в строке:' 
MB_ICONERROR	EQU	16 
current_string	 DWORD	 0
buffer	db 4096 dup(0)
ptrBuffer dword OFFSET buffer
consoletitle	db	'in',0

;VARS
stklength	db	 1, 0,4 dup(0)
stkcompare	db	 1, 0,4 dup(0)
stkcompS	db	 1, 0,4 dup(0)
stkprint	db	 1, 0,4 dup(0)
stkpower	db	 1, 0,4 dup(0)
stkfactor	db	 1, 0,4 dup(0)
stkexample	db	 1, 0,4 dup(0)
b_example	db	2,4 dup(0)
stkmain	db	 1, 0,4 dup(0)
t_main	db	2,4 dup(0)
arr_main	db	2,6*4 dup(0)
ind_main	db	1,0
str_main	db	7,10 dup(-1),0
var1_main	db	2,4 dup(0)
var2_main	db	2,4 dup(0)
.CONST
L0	db	1,5
L2	db	7,'hello world',0
L3	db	1,3
L4	db	1,2
L5	db	1,11
L6	db	1,15
L8	db	7,'t=',0
L9	db	1,6
L10	db	1,0
L11	db	1,1
L13	db	7,'Вывод массива:',0
true	db	3,1
L16	db	7,'hello',0
L17	db	1,10
L19	db	7,'Введите строку(не больше 10 может поместиться)',0
L21	db	7,'Длина строки',0
L23	db	7,'Сумма чисел',0
L25	db	7,'Первая переменаня',0
L27	db	7,'Вторая переменная',0
L29	db	7,'Результат',0
L31	db	7,'Результат выражения var1+var2/3+example(4)*2*(10-5)',0
L32	db	1,4
false	db	3,0


.CODE
int_to_char PROC uses eax ebx ecx edi esi, 
 pstr		: dword, 
 intfield : sdword 
 
 mov edi, pstr 
 mov esi, 0 
 mov eax, intfield 
 cdq 
 test eax, eax 
 mov ebx, 10 
 idiv ebx 
 jns plus1 
 neg eax 
 neg edx 
 mov cl, '-' 
 mov [edi], cl 
 inc edi 
 
 plus1: 
 push dx 
 inc esi 
 test eax, eax 
 jz fin 
 cdq 
 idiv ebx 
 jmp plus1 
 
 fin: 
 mov ecx, esi 
 
 write: 
 pop bx 
 add bl, '0' 
 mov [edi], bl 
 inc edi 
 loop write 
 mov byte ptr [edi], 0 ; Добавление нулевого символа в конец строки 
 ret 
 
 int_to_char ENDP
showErrorMessageBox PROC 
 PUSH MB_OK + MB_ICONERROR 
 PUSH OFFSET message 
 PUSH OFFSET caption 
 PUSH 0 
 call MessageBoxA 
 push 0 
 call ExitProcess 
 showErrorMessageBox ENDP
showErrorTypeMessageBox PROC 
 PUSH OFFSET caption
call ErrorType
push 0 
 call ExitProcess
 showErrorTypeMessageBox ENDP
showErrorEmptyMessageBox PROC 
 PUSH OFFSET caption
call ErrorStackEmpty
push 0 
 call ExitProcess
 showErrorEmptyMessageBox ENDP
showErrorOverMessageBox PROC 
 PUSH OFFSET caption
call ErrorStackOverflow
push 0 
 call ExitProcess
 showErrorOverMessageBox ENDP
showErrorIndexMessageBox PROC 
 PUSH OFFSET caption
call ErrorIncorInd
push 0 
 call ExitProcess
 showErrorIndexMessageBox ENDP
Assign PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte
START :
mov eax, type1
mov al, [eax]
mov ebx, type2
mov bl, [ebx]
cmp al, bl
jne not_equal
cmp al, 1
jne go_int
mov eax, var1
mov ebx, 0
mov ebx, var2
mov ebx, [ebx]
mov cl, bl
mov ebx, 0
mov bl, cl
mov byte ptr[eax], bl
mov eax, 0
mov ebx, 0
ret


go_int: 
cmp al, 2
jne go_bool
mov eax, dword ptr var1
mov ebx, 0
mov ebx, dword ptr var2
mov ebx, [ebx]
mov dword ptr[eax], ebx
mov eax, 0
mov ebx, 0
ret


go_bool :
cmp al, 3
jne go_string
mov eax, var1
mov ebx, 0
mov ebx, var2
mov ebx, [ebx]
mov cl, bl
mov ebx, 0
mov bl, cl
mov byte ptr[eax], bl
mov eax, 0
mov ebx, 0
ret


go_string :
cmp al, 7
jne callErrorType
cmp bl, 7
jne callErrorType
mov eax, var1
mov ebx, var2
copy :
mov dl, [ebx]; Load the current character from the string in var2 into dl
mov[eax], dl; Store the character in dl to the string in var1
add eax, 1; Increment the pointer to var1
add ebx, 1; Increment the pointer to var2
cmp byte ptr[ebx], 0; Check if the end of the string in var2 is reached
je next;
cmp byte ptr[eax], 0
jne copy; If not, continue to the next iteration
next :
ret

not_equal :

cmp al,2
jne callErrorType
cmp bl, 1
jne callErrorType
; int < -byte
	mov eax, dword ptr var1
	mov ebx, 0
	mov ebx, var2
	movsx ebx, byte ptr [ebx]
	mov ecx, ebx
	mov ebx, 0
	mov ebx, ecx
	mov dword ptr[eax], ebx
	mov eax, 0
	mov ebx, 0
	ret
	callErrorType :
add current_string, 1
INVOKE int_to_char, OFFSET caption, current_string
call showErrorTypeMessageBox
Assign ENDP
PLUS PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte
mov eax, type1
mov al, [eax]; Тип первой переменной

mov ebx, type2
mov bl, [ebx]; Тип второй переменной

cmp al, 2
je var1Int
cmp al,1
jne callErrorType
mov eax, 0
mov ecx, var1
movsx eax, byte ptr [ecx]
jmp second_var

var1Int :
mov eax, 0
mov ecx, var1
mov eax, [ecx]

second_var :
	cmp bl, 2
	je var2Int
	cmp bl,1
	jne callErrorType
	mov ebx, 0
	mov ecx, var2
	movsx ebx, byte ptr [ecx]
	jmp done

	var2Int :
mov ebx, 0
mov ecx, var2
mov ebx, [ecx]

done :
	add eax, ebx
	cmp eax, 127; Сравнение с 127
	jg greater; Переход, если значение больше 127
	cmp eax, -128; Сравнение с - 128
	jl less; Переход, если значение меньше - 128

	; Значение в EAX находится в диапазоне от - 128 до 127
	mov ebx, 1; Сохраняем 1 в EBX
	mov ecx, ptrBuffer
	mov[byte ptr[ecx]], bl; Переходим к завершению
	mov[byte ptr[ecx + 1]], al
	add ptrBuffer,2
	mov eax, ecx
	inc ecx
	mov ebx, ecx
	ret
	greater :
; Значение в EAX больше 127
mov ebx, 2; Сохраняем 2 в EBX
mov ecx, ptrBuffer
mov[byte ptr[ecx]], bl; Переходим к завершению
mov[dword ptr[ecx + 1]], eax
add ptrBuffer,5
mov eax, ecx
inc ecx
mov ebx, ecx
ret

less :
; Значение в EAX меньше - 128
mov ebx, 2; Сохраняем 2 в EBX
mov ecx, ptrBuffer
mov[byte ptr[ecx]], bl; Переходим к завершению
mov[dword ptr[ecx + 1]], eax
add ptrBuffer,5
mov eax, ecx
inc ecx
mov ebx, ecx
ret
PLUS ENDP
MINUS PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte
mov eax, type1
mov al, [eax]; Тип первой переменной

mov ebx, type2
mov bl, [ebx]; Тип второй переменной

cmp al, 2
je var1Int
cmp al,1
jne callErrorType
mov eax, 0
mov ecx, var1
movsx eax,byte ptr [ecx]
jmp second_var

var1Int :
mov eax, 0
mov ecx, var1
mov eax, [ecx]

second_var :
	cmp bl, 2
	je var2Int
	cmp bl,1
	jne callErrorType
	mov ebx, 0
	mov ecx, var2
	movsx ebx,byte ptr [ecx]
	jmp done

	var2Int :
mov ebx, 0
mov ecx, var2
mov ebx, [ecx]

done :
	sub ebx, eax
	mov eax, ebx
	cmp eax, 127; Сравнение с 127
	jg greater; Переход, если значение больше 127
	cmp eax, -128; Сравнение с - 128
	jl less; Переход, если значение меньше - 128

	; Значение в EAX находится в диапазоне от - 128 до 127
	mov ebx, 1; Сохраняем 1 в EBX
	mov ecx, ptrBuffer
	mov[byte ptr[ecx]], bl; Переходим к завершению
	mov[byte ptr[ecx + 1]], al
	add ptrBuffer,2
	mov eax, ecx
	inc ecx
	mov ebx, ecx
	ret
	greater :
; Значение в EAX больше 127
mov ebx, 2; Сохраняем 2 в EBX
mov ecx, ptrBuffer
mov[byte ptr[ecx]], bl; Переходим к завершению
mov[dword ptr[ecx + 1]], eax
add ptrBuffer,5
mov eax, ecx
inc ecx
mov ebx, ecx
ret

less :
; Значение в EAX меньше - 128
mov ebx, 2; Сохраняем 2 в EBX
mov ecx, ptrBuffer
mov[byte ptr[ecx]], bl; Переходим к завершению
mov[dword ptr[ecx + 1]], eax
add ptrBuffer,5
mov eax, ecx
inc ecx
mov ebx, ecx
ret
MINUS ENDP
MULT PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte
mov eax, type1
mov al, [eax]; Тип первой переменной

mov ebx, type2
mov bl, [ebx]; Тип второй переменной

cmp al, 2
je var1Int
cmp al,1
jne callErrorType
mov eax, 0
mov ecx, var1
movsx eax,byte ptr [ecx]
jmp second_var

var1Int :
mov eax, 0
mov ecx, var1
mov eax, [ecx]

second_var :
	cmp bl, 2
	je var2Int
	cmp bl,1
	jne callErrorType
	mov ebx, 0
	mov ecx, var2
	movsx ebx, byte ptr [ecx]
	jmp done

	var2Int :
mov ebx, 0
mov ecx, var2
mov ebx, [ecx]

done :
	mul ebx
	cmp eax, 127; Сравнение с 127
	jg greater; Переход, если значение больше 127
	cmp eax, -128; Сравнение с - 128
	jl less; Переход, если значение меньше - 128

	; Значение в EAX находится в диапазоне от - 128 до 127
	mov ebx, 1; Сохраняем 1 в EBX
	mov ecx, ptrBuffer
	mov[byte ptr[ecx]], bl; Переходим к завершению
	mov[byte ptr[ecx + 1]], al
	add ptrBuffer,2
	mov eax, ecx
	inc ecx
	mov ebx, ecx
	ret
	greater :
; Значение в EAX больше 127
mov ebx, 2; Сохраняем 2 в EBX
mov ecx, ptrBuffer
mov[byte ptr[ecx]], bl; Переходим к завершению
mov[dword ptr[ecx + 1]], eax
add ptrBuffer,5
mov eax, ecx
inc ecx
mov ebx, ecx
ret

less :
; Значение в EAX меньше - 128
mov ebx, 2; Сохраняем 2 в EBX
mov ecx, ptrBuffer
mov[byte ptr[ecx]], bl; Переходим к завершению
mov[dword ptr[ecx + 1]], eax
add ptrBuffer,5
mov eax, ecx
inc ecx
mov ebx, ecx
ret
MULT ENDP
DIVIDE PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte
mov eax, type1
mov al, [eax]; Тип первой переменной

mov ebx, type2
mov bl, [ebx]; Тип второй переменной

cmp al, 2
je var1Int
cmp al,1
jne callErrorType
mov eax, 0
mov ecx, var1
movsx eax, byte ptr [ecx]
cmp al,0
je callErrorType
jmp second_var

var1Int :
mov eax, 0
mov ecx, var1
mov eax, [ecx]
cmp eax,0
je callErrorType

second_var :
	cmp bl, 2
	je var2Int
	cmp bl,1
	jne callErrorType
	mov ebx, 0
	mov ecx, var2
	movsx ebx, byte ptr [ecx]
	jmp done

	var2Int :
mov ebx, 0
mov ecx, var2
mov ebx, [ecx]

done :
	mov ecx, ebx
	mov ebx, eax
	mov eax, ecx
	xor edx, edx
	div ebx
	cmp eax, 127; Сравнение с 127
	jg greater; Переход, если значение больше 127
	cmp eax, -128; Сравнение с - 128
	jl less; Переход, если значение меньше - 128

	; Значение в EAX находится в диапазоне от - 128 до 127
	mov ebx, 1; Сохраняем 1 в EBX
	mov ecx, ptrBuffer
	mov[byte ptr[ecx]], bl; Переходим к завершению
	mov[byte ptr[ecx + 1]], al
	add ptrBuffer,2
	mov eax, ecx
	inc ecx
	mov ebx, ecx
	ret
	greater :
; Значение в EAX больше 127
mov ebx, 2; Сохраняем 2 в EBX
mov ecx, ptrBuffer
mov[byte ptr[ecx]], bl; Переходим к завершению
mov[dword ptr[ecx + 1]], eax
add ptrBuffer,5
mov eax, ecx
inc ecx
mov ebx, ecx
ret

less :
; Значение в EAX меньше - 128
mov ebx, 2; Сохраняем 2 в EBX
mov ecx, ptrBuffer
mov[byte ptr[ecx]], bl; Переходим к завершению
mov[dword ptr[ecx + 1]], eax
add ptrBuffer,5
mov eax, ecx
inc ecx
mov ebx, ecx
ret
DIVIDE ENDP
MORE PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte
mov eax, type1
mov al, [eax]; Тип первой переменной

mov ebx, type2
mov bl, [ebx]; Тип второй переменной

cmp al, 2
je var1Int
cmp al, 1
jne callErrorType
mov eax, 0
mov ecx, var1
movsx eax, byte ptr [ecx]
jmp second_var

var1Int :
mov eax, 0
mov ecx, var1
mov eax, [ecx]

second_var :
	cmp bl, 2
	je var2Int
	cmp bl, 1
	jne callErrorType
	mov ebx, 0
	mov ecx, var2
	movsx ebx, byte ptr [ecx]
	jmp done

	var2Int :
mov ebx, 0
mov ecx, var2
mov ebx, [ecx]

done :
	cmp ebx, eax
	jg great
	less :
mov eax, offset false
mov ebx, offset false + 1
ret
great :
mov eax, offset true
mov ebx, offset true + 1
ret
MORE ENDP
LESSFUN PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte
mov eax, type1
mov al, [eax]; Тип первой переменной

mov ebx, type2
mov bl, [ebx]; Тип второй переменной

cmp al, 2
je var1Int
cmp al, 1
jne callErrorType
mov eax, 0
mov ecx, var1
movsx eax, byte ptr [ecx]
jmp second_var

var1Int :
mov eax, 0
mov ecx, var1
mov eax, [ecx]

second_var :
	cmp bl, 2
	je var2Int
	cmp bl, 1
	jne callErrorType
	mov ebx, 0
	mov ecx, var2
	movsx ebx, byte ptr [ecx]
	jmp done

	var2Int :
mov ebx, 0
mov ecx, var2
mov ebx, [ecx]

done :
	cmp ebx, eax
	jl great
mov eax, offset false
mov ebx, offset false + 1
ret
great :
mov eax, offset true
mov ebx, offset true + 1
ret
LESSFUN ENDP
MOREEQUAL PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte
mov eax, type1
mov al, [eax]; Тип первой переменной

mov ebx, type2
mov bl, [ebx]; Тип второй переменной

cmp al, 2
je var1Int
cmp al, 1
jne callErrorType
mov eax, 0
mov ecx, var1
movsx eax, byte ptr [ecx]
jmp second_var

var1Int :
mov eax, 0
mov ecx, var1
mov eax, [ecx]

second_var :
	cmp bl, 2
	je var2Int
	cmp bl, 1
	jne callErrorType
	mov ebx, 0
	mov ecx, var2
	movsx ebx,byte ptr [ecx]
	jmp done

	var2Int :
mov ebx, 0
mov ecx, var2
mov ebx, [ecx]

done :
	cmp ebx, eax
	je great
	jg great
mov eax, offset false
mov ebx, offset false + 1
ret
great :
mov eax, offset true
mov ebx, offset true + 1
ret
MOREEQUAL ENDP
LESEQUAL PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte
mov eax, type1
mov al, [eax]; Тип первой переменной

mov ebx, type2
mov bl, [ebx]; Тип второй переменной

cmp al, 2
je var1Int
cmp al, 1
jne callErrorType
mov eax, 0
mov ecx, var1
movsx eax, byte ptr [ecx]
jmp second_var

var1Int :
mov eax, 0
mov ecx, var1
mov eax, [ecx]

second_var :
	cmp bl, 2
	je var2Int
	cmp bl, 1
	jne callErrorType
	mov ebx, 0
	mov ecx, var2
	movsx ebx, byte ptr [ecx]
	jmp done

	var2Int :
mov ebx, 0
mov ecx, var2
mov ebx, [ecx]

done :
	cmp ebx, eax
	je great
	jl great
	les1:
mov eax, offset false
mov ebx, offset false + 1
ret
great :
mov eax, offset true
mov ebx, offset true + 1
ret
LESEQUAL ENDP
callError:
INVOKE int_to_char, OFFSET caption + 16, current_string
call showErrorMessageBox
callErrorType:
INVOKE int_to_char, OFFSET caption, current_string
call showErrorTypeMessageBox
callErrorEmpty:
INVOKE int_to_char, OFFSET caption, current_string
call showErrorEmptyMessageBox
callErrorOver:
INVOKE int_to_char, OFFSET caption, current_string
call showErrorOverMessageBox
callErrorIncorInd:
INVOKE int_to_char, OFFSET caption, current_string
call showErrorIndexMessageBox
EQUAl PROC type1 : ptr byte, var1 : ptr byte, type2 : ptr byte, var2 : ptr byte
mov eax, type1
mov al, [eax]; Тип первой переменной

mov ebx, type2
mov bl, [ebx]; Тип второй переменной

cmp al, 2
je var1Int
cmp al, 1
jne callErrorType
mov eax, 0
mov ecx, var1
movsx eax, byte ptr [ecx]
jmp second_var

var1Int :
mov eax, 0
mov ecx, var1
mov eax, [ecx]

second_var :
	cmp bl, 2
	je var2Int
	cmp bl, 1
	jne callErrorType
	mov ebx, 0
	mov ecx, var2
	movsx ebx, byte ptr [ecx]
	jmp done

	var2Int :
mov ebx, 0
mov ecx, var2
mov ebx, [ecx]

done :
	cmp ebx, eax
	je great
	less :
mov eax, offset false
mov ebx, offset false + 1
ret
great :
mov eax, offset true
mov ebx, offset true + 1
ret
EQUAL ENDP
mov current_string,3
example_fun PROC a_example_type: ptr byte,a_example: ptr byte
START:
mov eax, a_example_type
mov al, [eax]
cmp al, 2

je go_next
cmp al, 1
jne CallErrorType
go_next:
mov dword ptr stkexample+2, esp
mov current_string,4
mov current_string,5
mov current_string,6
add stkexample +1,1
cmp stkexample+1,32
 jg callErrorOver
push offset L0+1
push offset L0
add stkexample +1,1
cmp stkexample+1,32
 jg callErrorOver
push offset b_example+1
push offset b_example
sub stkexample +1,2
cmp stkexample+1, 0
 jl callErrorEmpty
call Assign
mov current_string,7
add stkexample +1,1
cmp stkexample+1,32
 jg callErrorOver
push offset b_example+1
push offset b_example
add stkexample +1,1
cmp stkexample+1,32
 jg callErrorOver
push a_example
push a_example_type
sub stkexample +1,2
cmp stkexample+1, 0
 jl callErrorEmpty
call PLUS
 push ebx
push eax
add stkexample +1,1
cmp stkexample+1,32
 jg callErrorOver
mov current_string,8
add stkexample +1,1
cmp stkexample+1,32
 jg callErrorOver
push offset b_example+1
push offset b_example
sub stkexample +1,2
cmp stkexample+1, 0
 jl callErrorEmpty
call Assign
mov current_string,9
add stkexample +1,1
cmp stkexample+1,32
 jg callErrorOver
push offset b_example+1
push offset b_example
pop eax
pop ebx
ret
mov current_string,10

mov esp,dword ptr stkexample+2
ret
example_fun  ENDP
mov current_string,11

main PROC
START :
push OFFSET consoletitle
 call SetConsoleTitleA
mov current_string,11
mov dword ptr stkmain+2, esp
mov current_string,12
mov current_string,13
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L2+1
push offset L2
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,14
mov current_string,15
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L3+1
push offset L3
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call factor_fun
pop edx
pop edx
add eax, 1
 push eax
 sub eax,1
 push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
mov current_string,16
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset t_main+1
push offset t_main
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call Assign
mov current_string,17
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L4+1
push offset L4
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset t_main+1
push offset t_main
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call power_fun
pop edx
pop edx
pop edx
pop edx
add eax, 1
 push eax
 sub eax,1
 push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
mov current_string,18
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
pop eax
pop ebx
push ebx
push eax
push ebx
push eax
 mov eax,0 
 mov ebx,0
cmp stkmain+1, 1
jl callErrorEmpty
call writeLineString
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
pop eax
 pop eax
mov eax,0
mov current_string,19
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset t_main+1
push offset t_main
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call Assign
mov current_string,20
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L5+1
push offset L5
mov current_string,21
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call example_fun
add eax, 1
 push eax
 sub eax,1
 push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset t_main+1
push offset t_main
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call Assign
mov current_string,22
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L6+1
push offset L6
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset t_main+1
push offset t_main
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call LESSFUN
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
pop eax
pop eax
 mov al, [eax]
 cmp al,[byte ptr true+1]
jne goIf1
mov current_string,24
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L8+1
push offset L8
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,25
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset t_main+1
push offset t_main
cmp stkmain+1, 1
jl callErrorEmpty
call writeLineString
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
pop eax
 pop eax
mov eax,0
mov current_string,26
goIf1:
mov current_string,27
mov current_string,28
while2:
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L10+1
push offset L10
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset t_main+1
push offset t_main
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call LESSFUN
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
pop eax
pop eax
 mov al, [eax]
 cmp al,[byte ptr true+1]
 jne endWhile2
mov current_string,30
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset t_main+1
push offset t_main
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L11+1
push offset L11
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call MINUS
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
mov current_string,31
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset t_main+1
push offset t_main
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call Assign
mov current_string,32
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset t_main+1
push offset t_main
cmp stkmain+1, 1
jl callErrorEmpty
call writeLineString
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
pop eax
 pop eax
mov eax,0
mov current_string,33
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset t_main+1
push offset t_main
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L9+1
push offset L9
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call LESSFUN
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
pop eax
pop eax
 mov al, [eax]
 cmp al,[byte ptr true+1]
jne goIf3
mov current_string,35
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset t_main+1
push offset t_main
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
mov eax, OFFSET arr_main
add eax,1
mov ebx, OFFSET t_main
add ebx,1
mov edx,0
 mov edx, [ebx]
 shl edx, 2
add eax, edx
push eax
shr edx,2
cmp edx, 6
je callErrorIncorInd
jg callErrorIncorInd
push OFFSET arr_main

sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call Assign
mov current_string,36
goIf3:
mov current_string,37
jmp while2
endWhile2:
mov current_string,38
mov current_string,39
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L10+1
push offset L10
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset ind_main+1
push offset ind_main
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call Assign
mov current_string,40
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L13+1
push offset L13
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,41
while4:
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset ind_main+1
push offset ind_main
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L9+1
push offset L9
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call LESSFUN
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
pop eax
pop eax
 mov al, [eax]
 cmp al,[byte ptr true+1]
 jne endWhile4
mov current_string,43
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
mov eax, OFFSET arr_main
add eax,1
mov ebx, OFFSET ind_main
add ebx,1
mov edx,0
 mov dl, [ebx]
 shl edx, 2
add eax, edx
push eax
shr edx,2
cmp edx, 6
je callErrorIncorInd
jg callErrorIncorInd
push OFFSET arr_main

cmp stkmain+1, 1
jl callErrorEmpty
call writeLineString
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
pop eax
 pop eax
mov eax,0
mov current_string,44
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset ind_main+1
push offset ind_main
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L11+1
push offset L11
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call PLUS
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
mov current_string,45
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset ind_main+1
push offset ind_main
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call Assign
mov current_string,46
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset true+1
push offset true
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
pop eax
pop eax
 mov al, [eax]
 cmp al,[byte ptr true+1]
jne goIf5
mov current_string,48
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L16+1
push offset L16
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,49
goIf5:
mov current_string,50
jmp while4
endWhile4:
mov current_string,51
mov current_string,52
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L19+1
push offset L19
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,53
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset str_main+1
push offset str_main
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
INVOKE int_to_char, OFFSET caption, current_string
 push OFFSET caption
call readCon
pop eax
 pop eax
pop eax
mov eax,0
mov current_string,54
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L21+1
push offset L21
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,55
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset str_main+1
push offset str_main
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call length_fun
pop edx
pop edx
add eax, 1
 push eax
 sub eax,1
 push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
cmp stkmain+1, 1
jl callErrorEmpty
call writeLineString
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
pop eax
 pop eax
mov eax,0
mov current_string,56
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L23+1
push offset L23
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,57
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L25+1
push offset L25
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,58
mov current_string,59
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset var1_main+1
push offset var1_main
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
INVOKE int_to_char, OFFSET caption, current_string
 push OFFSET caption
call readCon
pop eax
 pop eax
pop eax
mov eax,0
mov current_string,60
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L27+1
push offset L27
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,61
mov current_string,62
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset var2_main+1
push offset var2_main
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
INVOKE int_to_char, OFFSET caption, current_string
 push OFFSET caption
call readCon
pop eax
 pop eax
pop eax
mov eax,0
mov current_string,63
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset var1_main+1
push offset var1_main
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset var2_main+1
push offset var2_main
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call PLUS
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
mov current_string,64
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L29+1
push offset L29
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,65
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,66
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L31+1
push offset L31
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,67
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset var1_main+1
push offset var1_main
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset var2_main+1
push offset var2_main
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L3+1
push offset L3
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call DIVIDE
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L32+1
push offset L32
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call example_fun
add eax, 1
 push eax
 sub eax,1
 push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L4+1
push offset L4
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L17+1
push offset L17
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset L0+1
push offset L0
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call MINUS
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call MULT
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call MULT
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call PLUS
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
sub stkmain+1, 2
cmp stkmain+1,0
 jl callErrorEmpty
call PLUS
 push ebx
push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
mov current_string,68
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call print_fun
pop edx
pop edx
mov current_string,69
call waitPause
mov esp,dword ptr stkmain+2

push - 1
call ExitProcess
main ENDP
end main
