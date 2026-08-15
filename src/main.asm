asect 0
_start: ext
_ex_handler: ext
on_input_interrupt: ext
on_timer_interrupt: ext

# IVT
dc _start, 0x8000
dc _ex_handler, 0x1
dc _ex_handler, 0x2
dc _ex_handler, 0x3
dc _ex_handler, 0x4
dc _ex_handler, 0x5
dc _ex_handler, 0x6
dc _ex_handler, 0x7
dc _ex_handler, 0x8
dc _ex_handler, 0x9
dc _ex_handler, 0xA
dc _ex_handler, 0xB
dc _ex_handler, 0xC
dc _ex_handler, 0xD
dc _ex_handler, 0xE
dc _ex_handler, 0xF
dc on_input_interrupt, 0
dc on_timer_interrupt, 0
align 0x100

rsect handlers
main: ext

_start>
ldi fp, 0
stsp fp
addsp -8
jsr main
addsp 8
halt

_ex_handler>
ldps r1
ldi r0, 0xDED0
add r0, r1, r0
pop r1
halt

end.
