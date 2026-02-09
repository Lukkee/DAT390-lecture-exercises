############################################################
# Lecture 04 - Exercise 01
#
# For this exercice, you need to connect a bargraph to 
# GPIO port D, bits 8-15.
# 
# The assignments buld on each other, so do them in order.
############################################################

.section .text

#   GPIOD registers
.equ    GPIOD,  0x40011400
.equ    CFGHR,  0x40011404
.equ    OUTDR,  0x4001140C

.globl main
main: 
    ########################################################
    # Assignment 1: Configure GPIOD pins 8-15 as:
    #                - output 2Mhz
    #                - push-pull
    # (refer to the lecture notes and/or QuickGuide)
    # (also make sure you have done the quiz for this lecture)
    ########################################################
    # <Your code goes here>
    
    #la t0, 0x40011404

    #   Configure GPIOD CFGHR
    li t0, CFGHR
    li t1, 0x22222222  
    sw t1, 0(t0)

    #   Set delay
    li a1, 10000

    #   Clear pins
    li t0, OUTDR
    li t2, 0
    sh t2, 0(t0)

loop:
    li a0, 0

    iteration_loop:
        # call    set_led
        call    bshr_led
        call    delay
        call    clear_led
        call    delay
        addi    a0, a0, 1
        li t1, 8
        bne a0, t1, iteration_loop

    j loop

assignment4: 
    ########################################################
    # Assignment 4: Blink one LED by calling the set_led
    # and clear_led functions and then loop.
    #
    # Step through it with the debugger to see it work
    # Press F5 to let it run at full speed.
    ########################################################
    # <Your code goes here>
    

    j assignment4               # Repeat forever

assignment5: 
    ########################################################
    # Assignment 5: Create a "delay" function that simply
    #               loops a certain number of times to make
    #               transitions visible to the human eye.
    #
    ########################################################
    # <Your code goes here>
    j assignment5               # Repeat forever

assignment6: 
    ########################################################
    # Assignment 6: Challenge!
    #               In each iteration of the loop, move to 
    #               the next led in the bargraph, going back 
    #               to the first led after the last one.    
    ########################################################
    # <Your code goes here>
    j assignment6               # Repeat forever

delay:
    mv t0, a1

    delay_loop:
        addi t0, t0, -1
        bnez t0, delay_loop

    ret

set_led:
    ########################################################
    # Assignment 2: 
    # Write a function that turns on a specific led
    # It should not affect the other leds
    # You will do this by setting the correct bit in the 
    # GPIOD ODATA register
    #
    # Input: 
    # a0 - The led (0-7) to turn on
    ########################################################
    # <Your code goes here>

    #   Load Address
    li t0, OUTDR
    mv t1, a0

    li t2, 8
    li t3, 1

    sll t3, t3, t2
    sll t3, t3, t1
    mv t1, t3

    lh t2, 0(t0)
    or t1, t1, t2

    sh t1, 0(t0)
    ret

clear_led:
    ########################################################
    # Assignment 3:
    # Write a function that turns off a specific led
    # It should not affect the other leds
    # You will do this by clearing the correct bit in the
    # GPIOD ODATA register
    #
    # Input:
    # a0 - The led (0-7) to turn off
    ########################################################
    # <Your code goes here>

    #   Turn off LED
    li t0, OUTDR
    mv t1, a0
    
    li t2, 8
    li t3, 1

    sll t3, t3, t2
    sll t3, t3, t1
    mv t1, t3

    xori t1, t1, -1
    lh t2, 0(t0)
    and t1, t1, t2
    
    sh t1, 0(t0)
    ret

bshr_led:
    mv t2, a0
    la t0, 0x40011410    # GPIO_D_BSHR
    sh t2, 0(t0)       # Set only bit 2 (leave the others as they are)