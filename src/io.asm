asect 0x80

screen_row:
ds 4
screen_row_index:
ds 1

rsect funcs

# r0: buffer address, r1: start row index, r2: end row index
screen_write_range>
save r4
save r5
add r1, r0
add r1, r0
add r1, r0
add r1, r0
ldi r3, screen_row_index
ldi r4, screen_row
while
cmp r1, r2
stays le
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
