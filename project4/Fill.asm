// Set the initial state
@R2 // state variable
M=0 // Initialize state to 0 (WHITE)
// 1 for BLACK

(CHECK)
    // Check if keyboard gets input
    @KBD
    D=M // Read keyboard input   
    @WHITE
    D;JEQ // If keyboard does not get input, goto WHITE
    @BLACK
    D;JNE // If keyboard gets input, goto BLACK

(WHITE)
@R2
D=M
@CHECK
D;JEQ // if the previous state was WHITE, then skip filling pixels with WHITE
@R0 // counter
M=0 // Initialize counter to 0
@8192
D=A
@R1 // End address
M=D // set end address to 8192 pixels from the start of the screen
    (SUBLOOP1)
    // Fill the piexel with WHITE
    @SCREEN
    D=A // Set D to the address of the screen
    @R0
    A=D+M // Set A to the address of the pixel to fill
    M=0 // Fill with WHITE (0000000000000000)
    @R0
    M=M+1 // Increment counter
    D=M
    @R1
    D=D-M // Check if counter has reached the end address
    @SUBLOOP1
    D;JLT // If not reached, continue filling
    @R2
    M=0 // Set state to WHITE
    @CHECK
    D;JEQ // Jump to CHECK to see if keyboard input is received

(BLACK)
@R2
D=M
@CHECK
D-1;JEQ // if the previous state was BLACK, then skip filling piexels with BLACK
@R0 // counter
M=0 // Initialize counter to 0
@8192
D=A
@R1 // End address
M=D // set end address to 8192 pixels from the start of the screen
    (SUBLOOP2)
    // Fill the pixel with BLACK
    @SCREEN
    D=A // Set D to the address of the screen
    @R0
    A=D+M // Set A to the address of the pixel to fill
    M=-1 // Fill with BLACK (1111111111111111)
    @R0
    M=M+1 // Increment counter
    D=M
    @R1
    D=D-M // Check if counter has reached the end address
    @SUBLOOP2
    D;JLT // If not reached, continue filling
    @R2
    M=1 // Set state to BLACK
    @CHECK
    D;JEQ // Jump to CHECK to see if keyboard input is received