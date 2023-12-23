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
stkfact	db	 1, 0,4 dup(0)
b_fact	db	2,4 dup(0)
stkmain	db	 1, 0,4 dup(0)
a_main	db	2,4 dup(0)
.CONST
L0	db	1,0
L1	db	1,1
true	db	3,1
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
mov current_string,1
fact_fun PROC n_fact_type: ptr byte,n_fact: ptr byte
START:
mov eax, n_fact_type
mov al, [eax]
cmp al, 2

je go_next
cmp al, 1
jne CallErrorType
go_next:
mov dword ptr stkfact+2, esp
mov current_string,2
mov current_string,3
mov current_string,4
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
push n_fact
push n_fact_type
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
push offset L0+1
push offset L0
sub stkfact +1,2
cmp stkfact+1, 0
 jl callErrorEmpty
call LESSFUN
 push ebx
push eax
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
sub stkfact +1,1
cmp stkfact+1, 0
 jl callErrorEmpty
pop eax
pop eax
 mov al, [eax]
 cmp al,[byte ptr true+1]
jne goIf1
mov current_string,6
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
push offset L0+1
push offset L0
pop eax
pop ebx
ret
mov current_string,7
goIf1:
mov current_string,8
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
push n_fact
push n_fact_type
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
push offset L0+1
push offset L0
sub stkfact +1,2
cmp stkfact+1, 0
 jl callErrorEmpty
call EQUAL
 push ebx
push eax
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
sub stkfact +1,1
cmp stkfact+1, 0
 jl callErrorEmpty
pop eax
pop eax
 mov al, [eax]
 cmp al,[byte ptr true+1]
jne goIf2
mov current_string,10
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
push offset L1+1
push offset L1
pop eax
pop ebx
ret
mov current_string,11
goIf2:
mov current_string,12
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
push n_fact
push n_fact_type
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
push n_fact
push n_fact_type
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
push offset L1+1
push offset L1
sub stkfact +1,2
cmp stkfact+1, 0
 jl callErrorEmpty
call MINUS
 push ebx
push eax
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
sub stkfact +1,1
cmp stkfact+1, 0
 jl callErrorEmpty
call fact_fun
add eax, 1
 push eax
 sub eax,1
 push eax
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
sub stkfact +1,2
cmp stkfact+1, 0
 jl callErrorEmpty
call MULT
 push ebx
push eax
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
mov current_string,13
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
push offset b_fact+1
push offset b_fact
sub stkfact +1,2
cmp stkfact+1, 0
 jl callErrorEmpty
call Assign
mov current_string,14
add stkfact +1,1
cmp stkfact+1,32
 jg callErrorOver
push offset b_fact+1
push offset b_fact
pop eax
pop ebx
ret
mov current_string,15

mov esp,dword ptr stkfact+2
ret
fact_fun  ENDP
mov current_string,16

main PROC
START :
push OFFSET consoletitle
 call SetConsoleTitleA
mov current_string,16
mov dword ptr stkmain+2, esp
mov current_string,17
mov current_string,18
mov current_string,19
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset a_main+1
push offset a_main
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
mov current_string,20
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
push offset a_main+1
push offset a_main
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
call fact_fun
add eax, 1
 push eax
 sub eax,1
 push eax
add stkmain+1, 1
cmp stkmain+1, 32
 jg callErrorOver
mov current_string,21
cmp stkmain+1, 1
jl callErrorEmpty
call writeLineString
sub stkmain+1, 1
cmp stkmain+1,0
 jl callErrorEmpty
pop eax
 pop eax
mov eax,0
mov current_string,22
call waitPause
mov esp,dword ptr stkmain+2

push - 1
call ExitProcess
main ENDP
end main
