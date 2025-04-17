asect 0x80

screen_frame_buffer:
ds 128
screen_cursor:
ds 2
joy>
ds 1

rsect funcs

screen_write_cursor>
ldi r1, screen_cursor
stw r1, r0
rts

# r0: first half, r1: second half, r2: row index
screen_write_row>
shl r2, 2
ldi r3, screen_frame_buffer
add r2, r3
stw r3, r0
add r3, 2
stw r3, r1
rts

# r0: buffer address, r1: start row index, r2: end row index
screen_write_range>
shl r1, 2
shl r2, 2
ldi r3, screen_frame_buffer
add r1, r3
add r0, r1
add r0, r2
add r2, 2
while 
cmp r1, r2
stays le
ldw r1, r0
stw r3, r0
add r1, 2
add r3, 2
wend
rts

end.
