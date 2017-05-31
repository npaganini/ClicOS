GLOBAL cpuVendor
GLOBAL sti
GLOBAL setPicMaster
GLOBAL irq0Handler
GLOBAL irq1Handler
GLOBAL read_port
GLOBAL write_port

EXTERN irqDispatcher

%include "./asm/macros.m"

section .text

irq0Handler:
	irqHandler 0
	
irq1Handler:
	irqHandler 1

sti:
	sti
	ret
	
setPicMaster:
	push rbp
	mov rbp, rsp
	
	mov rax, rdi
	out 21h, al
 	
	mov rsp, rbp
	pop rbp
	ret

;setPicSlave:
;	push rbp
;	mov rbp, rsp
;
;	mov rax, rdi
;	out a1h, al
;
;	mov rsp, rbp
;	pop rbp
;	ret

read_port:
	mov edx, [esp + 4]
	in al, dx
	ret

write_port:
	mov edx, [esp + 4]
	mov al, [esp + 4 + 4]
	out dx, al
	ret

cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret
