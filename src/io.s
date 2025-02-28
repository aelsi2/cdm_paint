asect 0x80

screen_row:
ds 4
screen_row_index:
ds 1

rsect funcs
# r0: row index, r1: block 1, r2: block 2
write_row>
ldi r3, screen_row_index
st r3, r0
ldi r3, screen_row
stw r3, r1
add r3, 2
stw r3, r2
rts

# r0: buffer address
write_buffer>
save r4
save r5
ldi r1, 0
ldi r2, 32
ldi r3, screen_row_index
ldi r4, screen_row
while
cmp r1, r2
stays lo
st r3, r1
ldw r0, r5
stw r4, r5
add r4, 2
add r0, 2
ldw r0, r5
stw r4, r5
sub r4, 2
add r0, 2
inc r1
wend
restore
restore
rts

end.
