#pragma once
//---------------------------------------------------------------------------------------------
// ** DefineArraySize.h
//---------------------------------------------------------------------------------------------
#ifndef DEFINEARRAYSIZE_H
#define DEFINEARRAYSIZE_H
//---------------------------------------------------------------------------------------------


// ** The number of elements in the array 
#define ARRAY_SIZE(arr)     (sizeof(arr) / sizeof((arr)[0])

// The above is reported buggy, so it is recommended adding assert for safety, source: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=94746)
// #define ARRAY_SIZE(arr)     (sizeof(arr) / sizeof((arr)[0]) + Static_assert_eval0_array(arr))

// ** The size of the elements of the array (data-type size)
#define ARRAY_SSIZE(arr)    ((ptrdiff_t)ARRAY_SIZE(arr))

// ** The size in bytes that the array uses in memory
#define ARRAY_BYTES(arr)    (sizeof((arr)[0]) * ARRAY_SIZE(arr))



//---------------------------------------------------------------------------------------------
#endif // DEFINEARRAYSIZE_H
//---------------------------------------------------------------------------------------------
