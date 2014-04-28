; OS sample code
; (c) 2011-2012 Serge Goncharov, see EULA.
; NASM 2.09 used
; Download it from here: http://www.nasm.us/
; Compile file with the following command line:
; nasm kernel.asm -o kernel.sys -Ox
extern main
extern boot2
extern _init
extern _start

section .boot

	; Multipush macro
%macro	push	1-*
  %rep	%0
	push	%1
	%rotate 1
  %endrep
%endmacro



	; Multipop macro
%macro	pop	1-*
  %rep	%0
	%rotate -1
	pop	%1
  %endrep
%endmacro

global Message
global PrintChar
	; Print message macro
%macro	msg	1+
	call	Message
	db	%1, 0
%endmacro



Base:	equ	600h		; The standard base that OS kernel will be loaded to.


	cpu	386
	bits	16
	
	resb	Base

global boot
boot:
	; Initialize CS with far jump
	jmp	0:Start

	; Initialize data segment registers
Start:	push	cs
	pop	ds

	; Save parameters passed by loader
	mov	[Drive], dl
	mov	[Partition], dh
	mov	[VolumeID], ebx
	mov	[PartitionStart], eax
	mov	[PartitionStart+4], ecx

	; Set stack to the top of base memory
	xor	ax, ax
	int	12h		; Get available base memory in AX, kB
	sub	ax, 64		; Reserve whole segment 64k
	shl	ax, 6		; Convert kilobytes to paragraphs
	mov	ss, ax		; This will be the base of our stack segment. No need to disable interrupts, see Intel manuals!
	mov	sp, 0		; Set stack pointer to the top of the segment


	; All initialization is done, just do some interesting stuff
	; Print base memory available
	msg	`Mirmik was here.\n`


	mov	ah, 0Eh
	mov	bx, 7		; Page 0, light gray color
	mov al , 'M'
	int	10h
	
	mov	ah, 0Eh
	mov	bx, 7		; Page 0, light gray color
	mov al , 'I'
	int	10h
	
	mov	ah, 0Eh
	mov	bx, 7		; Page 0, light gray color
	mov al , 'R'
	int	10h
	int 10h
	

msg `_start`
call _start

msg `\n\nCallBoot2`
call boot2


	; Show "Any key" message...
.1:	msg	"Press any key for warm reboot..."
	mov	ah, 0
	int	16h	; Wait for a key
;	int	19h	; Reload OS

	; ...and reboot
	mov	word [472h], 1234h	; Warm reboot flag
	jmp	0FFFFh:0	; Reboot system



	; Print null-terminated string after the call to this function.
Message:
	push	bp
	mov	bp, sp
	push	ax, si
	mov	si, [bp+2]
	cld
.1:	cs	lodsb
	cmp	al, 0
	jz	.2	; End of string?
	call	PrintChar
	jmp	.1
.2:	mov	[bp+2], si	; Fix up return address
	pop	bp, ax, si
	ret



	; Print the EDX:EAX contents in hexadecimal format.
PrintEDAX:
	xchg	eax, edx
	call	PrintEAX
	xchg	eax, edx
	; Stall through to PrintEAX

	; Print the EAX contents in hexadecimal format.
PrintEAX:
	rol	eax, 16
	call	PrintAX
	rol	eax, 16
	; Stall through to PrintAX

	; Print the AX contents in hexadecimal format.
PrintAX:
	xchg	al, ah
	call	PrintAL
	xchg	al, ah
	; Stall through to PrintAL

	; Print the AL contents in hexadecimal format.
PrintAL:
	rol	al, 4
	call	PrintHexDigit
	rol	al, 4
	; Stall through to PrintHexDigit

	; Print one hexadecimal digit in AL
PrintHexDigit:
	push	ax
	and	al, 0Fh
	cmp	al, 10
	sbb	al, 69h
	das
	call	PrintChar
	pop	ax
	ret



	; Print single character in AL
PrintChar:
	pushad			; Some VGA BIOSes destroy high parts of 32-bit registers
	mov	ah, 0Eh
	mov	bx, 7		; Page 0, light gray color
	cmp	al, 10		; If LF, simulate CR/LF pair
	jnz	.1
	int	10h
	mov	al, 13
.1:	int	10h
	popad
	ret



	; Print EAX in decimal base
PrintDecimal:
	push	eax, ebx, cx, edx, di
	sub	sp, 10		; Largest number can contain 10 digits
	mov	di, sp
	xor	cx, cx
	mov	ebx, 10
.1:	xor	edx, edx
	div	ebx
	mov	[ss:di], dl
	inc	di
	inc	cx
	test	eax, eax
	jnz	.1
.2:	dec	di
	mov	al, [ss:di]
	add	al, "0"
	call	PrintChar
	loop	.2
	add	sp, 10
	pop	eax, ebx, cx, edx, di
	ret


global debug_str
debug_str:
pushad
msg	`Mirmik was here!!!.\n`
popad
ret
	



	section	.bss

Drive:		resb	1
Partition:	resb	1
VolumeID:	resd	1
PartitionStart:	resq	1


	section .text
	
global debug_str2
debug_str2:
pushad
msg	`Mirmik was here!!!\n`
popad
ret

global PrintChar2
PrintChar2:
	pushad			; Some VGA BIOSes destroy high parts of 32-bit registers
	mov al, 63
	
	mov	ah, 0Eh
	mov	bx, 7		; Page 0, light gray color
	nop
	int	10h
	popad
	ret
