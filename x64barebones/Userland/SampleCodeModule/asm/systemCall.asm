GLOBAL systemCall

section .text

; parameters from C are passed in order through registers rdi, rsi, rdx
; parameters in Linux's system calls are in rax, rbx, rcx before int 80h

systemCall:
	push rbp
	mov rbp, rsp

	mov rax, rdi
	mov rbx, rsi
	mov rcx, rdx

	int 80h

	mov rsp, rbp
	pop rbp

	ret

section .bss
