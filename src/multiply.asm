rsect multiply

multiply>
ldi r2, 0
save r4
ldi r4, 1
if
    tst r0
is mi
    neg r0
    neg r4
fi
if
    tst r1
is mi
    neg r1
    neg r4
fi
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
if 
    tst r4
is mi
    neg r2
fi
restore
move r2,r0

rts
end.
