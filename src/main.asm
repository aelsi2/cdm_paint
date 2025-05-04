asect 0
asm_main: ext
asm_handler1: ext
asm_handler2: ext
asm_handler3: ext
asm_handler4: ext
asm_input_handler: ext
asm_timer_handler: ext

# IVT
dc asm_main, 0b1000000000000000
dc asm_handler1, 0
dc asm_handler2, 0
dc asm_handler3, 0
dc asm_handler4, 0
dc asm_input_handler, 0
dc asm_timer_handler, 0
align 0x80

rsect handlers
main: ext
on_input_interrupt: ext
on_timer_interrupt: ext

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

asm_input_handler>
save r0
save r1
save r2
save r3
save r4
save r5
save r6
save r7
jsr on_input_interrupt
restore
restore
restore
restore
restore
restore
restore
restore
rti

asm_timer_handler>
save r0
save r1
save r2
save r3
save r4
save r5
save r6
save r7
jsr on_timer_interrupt
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
