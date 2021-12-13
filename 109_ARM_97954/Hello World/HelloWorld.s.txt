.data 
tempRet:	.word	1

str1: .asciz "Hello World!"

.text
.global main
.func main

main:
		ldr R1, =tempRet
		str	LR, [R1]
		
		ldr	R0, =str1
		bl	puts	
		
		ldr	R1, =tempRet
		ldr LR, [R1]
		
		mov R0, #23
		bx	LR
		.data 
