///////////////////////////////////////////////////////////////////////////////
// Lecture 06 - Exercise 01
// ============================================================================
// In this exercise you will practice pointers in C. 
// Like previous exercises, you should connect a console to usart1 and 
// implement the functions below to pass all test. 
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Assignment 1: When the function returns, the value originally pointed to 
//               by `a` should be stored in the location pointed to by `b` and
//               vice versa. Implement the body of the function to achieve this.
///////////////////////////////////////////////////////////////////////////////
void swap(int32_t *a, int32_t *b)
{
    int32_t temp = *a;
    *a = *b;
    *b = temp;
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 2: In this assignment, you get the addresses as integer values.
//               When the function returns, the value originally stored at the
//               address `address_to_a` should be stored at the address
//               `address_to_b` and vice versa. Implement the body of the
//               function to achieve this.
///////////////////////////////////////////////////////////////////////////////
void swap2(int32_t address_to_a, int32_t address_to_b)
{
    int32_t *a_ptr = (int32_t *)address_to_a;
    int32_t *b_ptr = (int32_t *)address_to_b;
    int32_t temp = *a_ptr;
    *a_ptr = *b_ptr;
    *b_ptr = temp;
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 3: `a` and `b` point to the beginning of two arrays of equal 
//               length `length`. When the function returns, the contents of
//               the two arrays should be swapped. Implement the body of the
//               function to achieve this.
///////////////////////////////////////////////////////////////////////////////
void swap_arrays(int32_t *a, int32_t *b, int32_t length)
{
    for (int32_t i = 0; i < length; i++) {
        int32_t temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}   

///////////////////////////////////////////////////////////////////////////////
// Assignment 4: `a` points to an array of unsigned  integers of length 
//               `length`. All elements that are smaller than 0xFF shall be 
//               copied to the unsigned char array pointed to by `b`. The number
//               of copied elements shall be written into the location pointed to
//               by `num_copied`. Implement the body of the function to achieve
//               this.
///////////////////////////////////////////////////////////////////////////////
void filter_array(const uint32_t *a, int32_t length, 
                  uint8_t *b, int32_t *num_copied)
{
    int count = 0;
    for (int32_t i = 0; i < length; i++) {
        if (a[i] < 0xFF) {
            b[count] = a[i];
            count++;
        }
    }
    *num_copied = (int32_t)count;
}   

///////////////////////////////////////////////////////////////////////////////
// Assignment 5: `fifth_element` points to the FIFTH element of an array of
//                shorts. Change the value of the FIRST element in the array 
//                to 42.
//                `ptr_to_slightly_before_a` points to an address 6 bytes
//                before a variable a of type unsigned int. Change the value
//                of `a` to 0xDEADBEEF.
///////////////////////////////////////////////////////////////////////////////
void set_first_element(short *fifth_element, short *ptr_to_slightly_before_a)
{
    fifth_element[-4] = 42;
    unsigned int *a_ptr = (unsigned int *)((char *)ptr_to_slightly_before_a + 6);
    *a_ptr = 0xDEADBEEF;
}



///////////////////////////////////////////////////////////////////////////////
// Assignment 6: This one is a bit tricky. You have two global variables
//               `global_a` and `global_b` of type `short`. Your function
//               shall swap these values and then put a pointer to `global_a`
//               into the location pointed to by `ptr_to_ptr_to_a` and a 
//               pointer to `global_b` into the location pointed to by 
//               `ptr_to_ptr_to_b`.
///////////////////////////////////////////////////////////////////////////////

short global_a = 42;
short global_b = 43; 

void swap_globals(short ** ptr_to_ptr_to_a, short ** ptr_to_ptr_to_b)
{
    short *a_ptr = &global_a;
    short *b_ptr = &global_b;

    short temp = *a_ptr;
    *a_ptr = *b_ptr;
    *b_ptr = temp;

    *ptr_to_ptr_to_a = a_ptr;
    *ptr_to_ptr_to_b = b_ptr;
}
