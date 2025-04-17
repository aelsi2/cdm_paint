asect 0
asm_main: ext
asm_handler1: ext
asm_handler2: ext
asm_handler3: ext
asm_handler4: ext
asm_input: ext
asm_input_repeating: ext

# IVT
dc asm_main, 0b1000000000000000
dc asm_handler1, 0
dc asm_handler2, 0
dc asm_handler3, 0
dc asm_handler4, 0
dc asm_input, 0
dc asm_input_repeating, 0
align 0x80

rsect handlers
main: ext
handle_input: ext
handle_input_repeating: ext

asm_main>
jsr main
halt

asm_handler1>
ldi r0, 0xDED1
pop r1
halt

asm_handler2>
ldi r0, 0xDED2
pop r1
halt

asm_handler3>
ldi r0, 0xDED3
pop r1
halt

asm_handler4>
ldi r0, 0xDED4
pop r1
halt

asm_input>
save r0
save r1
save r2
save r3
save r4
save r5
save r6
save r7
jsr handle_input
restore
restore
restore
restore
restore
restore
restore
restore
rti

asm_input_repeating>
save r0
save r1
save r2
save r3
save r4
save r5
save r6
save r7
jsr handle_input_repeating
restore
restore
restore
restore
restore
restore
restore
restore
rti

end.
