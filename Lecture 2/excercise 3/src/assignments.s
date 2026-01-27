############################################################
# Lecture 02 - Exercise 3
# ==========================================================
#
# This is the only file you should edit for the excercise. 
# The file main.c is a test harness to help you test your code.
#
# Before you start: 
# Start simserver and choose Server->IO Setup
# For "Serial Communication Interface 1", choose "06 Console"
# Then run the program with F5 (if it breaks on main, 
# continue with F5 again)
# You should see output on the simserver console telling you 
# which assignments are passed. 
#
############################################################
    .text
    .global question1
    .global question2
    .global question3
    .global question4
    .global question5
    .global question6
    .global question7
    .global shared_value

############################################################
# Global variables (you are NOT meant to modify these)
############################################################

    .data
    .align 2
shared_value:
    .word 0
signed_byte:    
    .byte -5
    .byte 0
    .byte 0
    .byte 0
unsigned_half: 
    .half -30000
    .half 0
.text


############################################################
# Assignment 1
#
# Task:
#   Store the value 42 into the global variable 'shared_value'
#
############################################################
question1:
    la t0, shared_value
    li t1, 42
    sw t1, 0(t0)
    ret


############################################################
# Assignment 2
#
# Task:
#   Load the value from 'shared_value' and
#   return it in a0.
#
############################################################
question2:
    la t0, shared_value
    lw a0, 0(t0)
    ret

############################################################
# Assignment 3
#
# Task:
#   Read the word stored at address 0x20010000
#   and write the same word to address 0x20010004.
#
# Notes:
#   Both addresses are guaranteed to be valid SRAM
#   locations. Do not use the stack.
#
############################################################
question3:
    li t0, 0x20010000
    lw t1, 0(t0)
    li t0, 0x20010004
    sw t1, 0(t0) # 0(adress)
    ret

############################################################
# Assignment 4
#
# Input:
#   a0 = integer x
#
# Task:
#   Store x into shared_value.
#
############################################################
question4:
    la t0, shared_value
    mv t1, a0
    sw t1, 0(t0)
    ret


############################################################
# Assignment 5
#
# Task:
#   Load 'shared_value', add 22 to it, and
#   return the result in a0.
#
############################################################
question5:
    la t0, shared_value
    lw t1, 0(t0)
    add a0, t1, 22
    ret

############################################################
# Assignment 6
#
# Task:
#   Read the value at label 'signed_byte' 
#   and return it.
#
# Notes:
#   * 'signed_byte' is a signed 8-bit value.
#
############################################################
question6:
    la t0, signed_byte
    lb a0, 0(t0)
    ret    

############################################################
# Assignment 7
#
# Task:
#   Read the value at label 'unsigned_half' and subtract
#   the value in a0 and return.
#
#   I.e. a0 = unsigned_half - a0
#
# Notes:
#   * 'unsigned_half' is an unsigned 16-bit value.
#
############################################################
question7:
    la t0, unsigned_half
    lhu t1, 0(t0)
    sub a0, t1, a0
    ret    
