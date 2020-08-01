//---------------------------------------------------------------------------------------------
// ** XOR_Encrypt_Decrypt.cpp
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "XOR_Encrypt_Decrypt.h"


//---------------------------------------------------------------------------------------------
// ** XOR - Encrypt
//---------------------------------------------------------------------------------------------
std::string XOR_Encrypt(char strIn[], char xorKey)
{
    // ** Calculate length of input string 
    int len = strlen(strIn);

    // ** Perform XOR operation of key with every caracter in string 
    for (int i = 0; i < len; i++)
    {		
        strIn[i] ^= xorKey; // Do the XOR'ing
        strIn[i] += i;      // Incrementing (+i) to break pattern and make it harder to read, same characters side by side won't look like: aaaaaaaaaa
    }

    return strIn;
};
//---------------------------------------------------------------------------------------------
// ** END: XOR - Encrypt
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** XOR - Decrypt (reverse the encryption)
//---------------------------------------------------------------------------------------------
std::string XOR_Decrypt(char strIn[], char xorKey)
{
    // ** Define XOR key, any character value will work 
    //char xorKey = 'W'; //W

    // ** Calculate length of input string 
    int len = strlen(strIn);

    // ** Perform XOR operation of key with every caracter in string 
    for (int i = 0; i < len; i++)
    {
        strIn[i] -= i;      // Decrementing (-i) since we incremented during encryption
        strIn[i] ^= xorKey; // Do the XOR'ing
    }

    return strIn;
};
//---------------------------------------------------------------------------------------------
// ** END: XOR - Decrypt
//---------------------------------------------------------------------------------------------



/*
// ** EXAMPLE USAGE

#include <stdio.h>
#include <string>

int main() 
{ 
	// ** String when it is decrypted.
	char strIn[] = "hello"; 

	// ** Key character used as XOR, can be any character
	char key = 'J';

	// ** Encrypt the string 
	std::string strEncrypted;
	strEncrypted = XOR_Encrypt(strIn, key);
	printf("%s\n, strEncrypted"); 

	// ** Decrypt the string
	std::string strDecrypted;
	strDecrypted = XOR_Decrypt(strEncrypted, key);
	printf("%s\n, strDecrypted");

	return 0; 
};

*/
