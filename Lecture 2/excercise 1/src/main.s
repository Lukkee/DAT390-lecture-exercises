.globl main # Make main function visible to startup code
main:
    ###########################################################################
    # Assignment 1: Calculate t0 = a + b
    # =================================================
    # Check that you have the correct value in t0 using "register list"
    # in the debugger
    ###########################################################################
    
    la t1, a
    lh t1, 0(t1)

    la t2, b
    lb t2, 0(t2)

    add t0, t1, t2

    ###########################################################################
    # Assignment 3: Store the value of t0 into variable c
    # ==================================================================
    # What is the address of c?
    # Open the memory view in the debugger to check that c has the correct value
    # If not, or if your simserver yells at you, check the hint in assignment 2
    ###########################################################################

    la t1, c
    sw t0, 0(t1)

end: j end  # End with a forever loop

.align 1
a: .hword 10
b: .byte 20
    ###########################################################################
    # Assignment 2: Declare a variable c that is a signed 4-byte integer and
    #               initialize it to 1000
    # =================================================
    # (hint: don't forget about alignment!)
    ###########################################################################
.align 2
c: .word 1000