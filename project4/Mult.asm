// set iterator
@i
M=0
@sum
M=0
(LOOP)
    // if i >= R1; goto STOP
    @i
    D=M
    @R1
    D=D-M
    @STOP
    D;JGE
    // sum = sum + R0
    @sum
    D=M
    @R0
    D=D+M
    @sum
    M=D
    // i = i + 1
    @i
    M=M+1
    // goto LOOP
    @LOOP
    0;JMP
(STOP)
    // R2 = sum
    @sum
    D=M
    @R2
    M=D
(END)
    // end program
    @END
    0;JMP