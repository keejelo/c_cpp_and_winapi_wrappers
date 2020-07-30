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
std::string XOR_Encrypt(char inpString[], char xorKey)
{
	// ** Calculate length of input string 
	int len = strlen(inpString);

	// ** Perform XOR operation of key with every caracter in string 
	for (int i = 0; i < len; i++)
	{		
		inpString[i] ^= xorKey;	// Do the XOR'ing
		inpString[i] += i;      // Incrementing (+i) to break pattern and make it harder to read, same characters side by side won't look like: aaaaaaaaaa
	}

	return inpString;
};
//---------------------------------------------------------------------------------------------
// ** END: XOR - Encrypt
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** XOR - Decrypt (reverse the encryption)
//---------------------------------------------------------------------------------------------
std::string XOR_Decrypt(char inpString[], char xorKey)
{
	// ** Define XOR key, any character value will work 
	//char xorKey = 'W'; //W

	// ** Calculate length of input string 
	int len = strlen(inpString);

	// ** Perform XOR operation of key with every caracter in string 
	for (int i = 0; i < len; i++)
	{
		inpString[i] -= i;      // Decrementing (-i) since we incremented during encryption
		inpString[i] ^= xorKey; // Do the XOR'ing
	}

	return inpString;
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
	char key = 'A';
    
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
