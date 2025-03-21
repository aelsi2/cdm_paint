asect 0
asm_main: ext
asm_handler1: ext
asm_handler2: ext
asm_handler3: ext
asm_handler4: ext
asm_input: ext

# IVT
dc asm_main, 0b1000000000000000
dc asm_handler1, 0
dc asm_handler2, 0
dc asm_handler3, 0
dc asm_handler4, 0
dc asm_input, 0
align 0x80

rsect handlers
main: ext
handle_input: ext

asm_main>
jsr main
halt

asm_handler1>
ldi r0, 0xDED1
halt

asm_handler2>
ldi r0, 0xDED2
halt

asm_handler3>
ldi r0, 0xDED3
halt

asm_handler4>
ldi r0, 0xDED4
halt

asm_input>
jsr handle_input
rti

end.
