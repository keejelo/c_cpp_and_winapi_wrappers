//------------------------------------------------------------------------------------------
// ** Example of how to use and integer array inside a vector
//    Great for lists with items and subitems etc.
//------------------------------------------------------------------------------------------
#include <stdio.h>
#include <vector>


int main()
{    
    // ** Create struct of an integer array that can hold 3 values
    struct Int3
    {
        int arr[3] = { 0 };
    };

    // ** Create a vector that holds the array struct
    std::vector<Int3> vec;
    
    // ** Push back values in vector
    vec.push_back({ 8, 5, 6 });

    // ..or set them one by one
    // vec[0].arr[0] = 9;
    // vec[0].arr[1] = 4;
    // vec[0].arr[2] = 7;

    // ** Output values
    printf("%d\n", vec[0].arr[0]);
    printf("%d\n", vec[0].arr[1]);
    printf("%d\n", vec[0].arr[2]);

    // ** Pause before exit
    getchar();
    
    return 0;
};

