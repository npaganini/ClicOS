GLOBAL cpuVendor
GLOBAL sti
GLOBAL setPicMaster
GLOBAL setPicSlave
GLOBAL irq0Handler
GLOBAL irq1Handler
GLOBAL irq2Handler
GLOBAL irq3Handler
GLOBAL irq4Handler
GLOBAL irq5Handler
GLOBAL irq6Handler
GLOBAL irq7Handler
GLOBAL irq8Handler
GLOBAL irq9Handler
GLOBAL irq10Handler
GLOBAL irq11Handler
GLOBAL irq12Handler
GLOBAL irq13Handler
GLOBAL irq14Handler
GLOBAL irq15Handler
GLOBAL irq80Handler
GLOBAL read_port
GLOBAL write_port

EXTERN irqDispatcher
EXTERN systemCallReceiver
EXTERN systemCallHandler

%include "./asm/macros.m"

section .text

irq0Handler:
	irqHandler 0
	
irq1Handler:
	irqHandler 1

irq2Handler:
	irqHandler 2

irq3Handler:
	irqHandler 3

irq4Handler:
	irqHandler 4

irq5Handler:
	irqHandler 5

irq6Handler:
	irqHandler 6

irq7Handler:
	irqHandler 7

irq8Handler:
	irqHandler 8

irq9Handler:
	irqHandler 9

irq10Handler:
	irqHandler 10

irq11Handler:
	irqHandler 11

irq12Handler:
	pushaq

	mov rdi, 12
	call irqDispatcher

	mov al, 20h
	out 0xA0, al	; EOI PIC SLAVE
	out 20h, al		; EOI PIC MASTER

	popaq

	iretq

irq13Handler:
	irqHandler 13

irq14Handler:
	irqHandler 14

irq15Handler:
	irqHandler 15

irq80Handler:
	pushaq

	mov rdi, rax
	mov rsi, rbx
	mov rdx, rcx
	call systemCallHandler

	mov rdi, 16
	call irqDispatcher

	mov al, 20h
	out 20h, al		; EOI PIC MASTER

	popaq

	iretq

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

setPicSlave:
	push rbp
	mov rbp, rsp

	mov rax, rdi
	out 0xA1, al

	mov rsp, rbp
	pop rbp
	ret

read_port:
	push rbp
	mov rbp, rsp
	mov rdx, rdi
	in al, dx
	mov rsp, rbp
	pop rbp
	ret

write_port:
	push rbp
	mov rbp, rsp
	mov rdx, rdi
	mov rax, rsi
	out dx, al
	mov rsp, rbp
	pop rbp
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

