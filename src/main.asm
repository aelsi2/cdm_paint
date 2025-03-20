asect 0
asm_main: ext
asm_handler: ext
asm_input: ext

# IVT
dc asm_main, 0b1000000000000000
dc asm_handler, 0
dc asm_handler, 0
dc asm_handler, 0
dc asm_handler, 0
dc asm_input, 0
align 0x80

rsect handlers
main: ext
handle_input: ext

asm_main>
jsr main
halt

asm_handler>
halt

asm_input>
jsr handle_input
rti

end.
