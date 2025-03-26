rsect multiply

multiply>

clr r2
save r3
while
tst r1
stays ne
    if
    ldi r3, 1
        and r1,r3
    is ne
        add r0,r2
    fi
    shl r0
    shr r1
wend
restore
move r2,r0

rts
end.