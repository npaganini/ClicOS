GLOBAL systemCall

section .text

; parameters from C are passed in order through registers rdi, rsi, rdx, rcx
; parameters in Linux's system calls are in rax, rbx, rcx, rdx before int 80h

systemCall:
	push rbp
	mov rbp, rsp

	mov rax, rdi
	mov rbx, rsi

	int 80h

	mov rsp, rbp
	pop rbp

	ret