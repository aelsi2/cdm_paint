asect 0x80

screen_row:
ds 4  #0x80
screen_row_index:
ds 1  #0x84
timer_enable:
ds 1  #0x85
cursor_position:
ds 2  #0x86
menu_data:
ds 1  #0x88
menu_cursor_position:
ds 1  #0x89
joy>
ds 1  #0x8a

rsect funcs

screen_write_cursor>
ldi r1, cursor_position
stw r1, r0
rts

# r0: first half, r1: second half, r2: row index
screen_write_row>
ldi r3, screen_row_index
stw r3, r2
ldi r3, screen_row
stw r3, r0
add r3, 2
stw r3, r1
rts

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
