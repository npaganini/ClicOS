GLOBAL _sysTime

section .text

_sysTime:
	push rbp
	mov rbp, rsp

	mov	rax, rdi
	out	70h, al
	in	al, 71h

	mov rsp, rbp
	pop rbp
	ret

