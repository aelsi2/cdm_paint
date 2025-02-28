asect 0
asm_main: ext
asm_handler: ext

# IVT
dc asm_main, 0
dc asm_handler, 0
dc asm_handler, 0
dc asm_handler, 0
dc asm_handler, 0
align 0x80

rsect handlers
main: ext

asm_main>
ldi r0, 0xFFF8
stsp r0
jsr main
halt

asm_handler>
halt

end.
