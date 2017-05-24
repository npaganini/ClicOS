GLOBAL _keyboard

section .text

_keyboard:
;	push rbp
;	mov rbp, rsp

;	mov	rax, rdi
;	out	64h, al
;	in	al, 60h

;	mov rbp, rsp
;	in al, 60h
;	mov rdi, rax
;	mov rsp, rbp

	push rbp
	mov rbp, rsp
	in al, 60h
	mov rdi, rax
	mov rsp, rbp
	pop rbp
	ret

;	mov rsp, rbp
;	pop rbp
;	ret
