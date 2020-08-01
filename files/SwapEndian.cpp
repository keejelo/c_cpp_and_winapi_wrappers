//---------------------------------------------------------------------------------------------
// ** SwapEndian.cpp
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "SwapEndian.h"


//---------------------------------------------------------------------------------------------
// ** Two similar functions to swap endianess of a number. Both do basically the same thing.
//---------------------------------------------------------------------------------------------    


//---------------------------------------------------------------------------------------------
// ** Swap Endian
//---------------------------------------------------------------------------------------------
int SwapEndian(int n)
{
    unsigned char b1, b2, b3, b4;

    b1 = n & 0xFF;         
    b2 = (n >> 8) & 0xFF;  
    b3 = (n >> 16) & 0xFF; 
    b4 = (n >> 24) & 0xFF; 

    return ((int)b1 << 24) + ((int)b2 << 16) + ((int)b3 << 8) + b4;
};
//---------------------------------------------------------------------------------------------
// ** END: Swap Endian
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Swap Endian
//---------------------------------------------------------------------------------------------
int EndianSwap(int value)  
{  
    // This var holds the leftmost 8 bits of the output. 
    int leftmost_byte;  

    // This holds the left middle 8 bits of the output  
    int left_middle_byle;  

    // This holds the right middle 8 bits of the output  
    int right_middle_byte;  

    // This holds the rightmost 8 bits of the output  
    int rightmost_byte;  

    // To store the result after conversion  
    int result;  

    // Get the rightmost 8 bits of the number  
    // by anding it 0x000000FF. since the last  
    // 8 bits are all ones, the result will be the  
    // rightmost 8 bits of the number. this will  
    // be converted into the leftmost 8 bits for the  
    // output (swapping)  
    leftmost_byte = (value & 0x000000FF) >> 0;  

    // Similarly, get the right middle and left  
    // middle 8 bits which will become  
    // the left_middle bits in the output  
    left_middle_byle = (value & 0x0000FF00) >> 8;  

    right_middle_byte = (value & 0x00FF0000) >> 16;  

    // Get the leftmost 8 bits which will be the rightmost 8 bits of the output  
    rightmost_byte = (value & 0xFF000000) >> 24;  

    // Left shift the 8 bits by 24 so that it is shifted to the leftmost end  
    leftmost_byte <<= 24;  

    // Similarly, left shift by 16  
    // so that it is in the left_middle  
    // position. i.e, it starts at the  
    // 9th bit from the left and ends at the  
    // 16th bit from the left  
    left_middle_byle <<= 16;  

    right_middle_byte <<= 8;  

    // The rightmost bit stays as it is as it is in the correct position  
    rightmost_byte <<= 0;  

    // Result is the concatenation of all these values.  
    result = (leftmost_byte | left_middle_byle | right_middle_byte | rightmost_byte);  

    return result;  
};
//---------------------------------------------------------------------------------------------
// ** END: Swap Endian
//---------------------------------------------------------------------------------------------


