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

# IO
asect 0xFFFB
io_row_index>
ds 1
align 0x02
io_row>
ds 4

rsect io_funcs
# r0: row index, r1: block 1, r2: block 2
write_row>
ldi r3, io_row_index
st r3, r0
ldi r3, io_row
stw r3, r1
add r3, 2
stw r3, r2
rts

end.
