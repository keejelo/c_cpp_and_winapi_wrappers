// ** Example of how to use and integer array inside a vector

#include <stdio.h>
#include <vector>


int main()
{    
    // ** Create struct of an integer array that can hold 3 values
    struct Int3
    {
        int a[3] = { 0 };
    };

    // ** Create a vector that holds the array struct
    std::vector<Int3> v;
    
    // ** Push back values in vector
    v.push_back({ 8, 5, 6 });

    // ..or set them one by one
    // v[0].a[0] = 9;
    // v[0].a[1] = 4;
    // v[0].a[2] = 7;

    // ** Output values
    printf("%d\n", v[0].a[0]);
    printf("%d\n", v[0].a[1]);
    printf("%d\n", v[0].a[2]);

    // ** Pause before exit
    getchar();
    
    return 0;
};

