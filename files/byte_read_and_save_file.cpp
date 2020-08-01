
//---------------------------------------------------------------------------------------------
// ** Read file values and put them into edit controls
//---------------------------------------------------------------------------------------------
bool ReadFileValues(HWND hWnd)
{	
	// ** Get file and return string
	std::string strFileName = BrowseFile(hWnd, "%UserProfile%\\appdata\\local\\pineapple\\saved\\savegames");

	// ** Set filename to global variable so we can use it later when saving
	g_strFileName = strFileName;

	// ** Check if file is not loaded
	if (strFileName != "")
	{
		SetCursor(hCursorWait);

		FILE *pFile = NULL;
		errno_t errorCode = fopen_s(&pFile, strFileName.c_str(), "rb");

		if (pFile != NULL)
		{
			fseek(pFile, 0, SEEK_END);
			unsigned int uFileSize = ftell(pFile);
			rewind(pFile);

			//char *cBuf = (char*)malloc(uFileSize * sizeof(char*));  // <-- changed from this to the line under, was outputting FFFFFFFF instead of FF in byte value  (-1 numbers)
			unsigned char *cBuf = (unsigned char*)malloc(uFileSize * sizeof(char));

			if (cBuf == NULL)
			{ 
				log("Error, could not allocate memory for file buffer!");
				MessageBox(hWnd, "Error, could not allocate memory for file buffer!", "Error", MB_OK | MB_ICONERROR);
				return false;
			}
			else
			{
				fread(cBuf, 1, uFileSize, pFile);
				fclose(pFile);
				pFile = NULL;
			}


			// ..do stuff here

			// ** Flag to indicate if search was found, default: false 
			bool bValueFound = false;


			//-----------------------------------------------------------------------------
			// ** Search for hexstring in buffer
			//-----------------------------------------------------------------------------
			int patternSize = sizeof(hexstr1) / sizeof(hexstr1[0]);
			unsigned int n = FindBytePattern(hexstr1, cBuf, uFileSize, patternSize);
			if (n == std::string::npos)
			{
				log("Pattern not found!\nReturn value: %d ( 0x%x )\n", n, n);
			}
			else if(n != std::string::npos)
			{
				// ** position is n
				log("Pattern found at offset: %d ( 0x%x )\n", n, n);

				// ** Get the value and put into integer
				unsigned int hexValue[10];
				hexValue[0] = cBuf[n + 35];
				hexValue[1] = cBuf[n + 34];
				hexValue[2] = cBuf[n + 33];

				//printf("%x%x%x\n", hexValue[0], hexValue[1], hexValue[2]);

				std::string hexFinal;
				char buf1[10];

				_itoa_s(hexValue[0], buf1, 16);
				if (hexValue[0] < 0x10)
				{
					hexFinal = "0";
					hexFinal += buf1;
				}
				else
				{
					hexFinal = buf1;
				}

				_itoa_s(hexValue[1], buf1, 16);
				if (hexValue[1] < 0x10)
				{
					hexFinal += "0";
					hexFinal += buf1;
				}
				else
				{
					hexFinal += buf1;
				}

				_itoa_s(hexValue[2], buf1, 16);
				if (hexValue[2] < 0x10)
				{
					hexFinal += "0";
					hexFinal += buf1;
				}
				else
				{
					hexFinal += buf1;
				}

				//printf("%s\n", hexFinal.c_str());

				// ** Get the value and put into integer
				int nOffsetValue = hex2dec(hexFinal.c_str());

				//printf("Hex: %x\n", nOffsetValue); // prints out hex
				//printf("Dec: %u\n", nOffsetValue); // prints out dec

				// ** Convert int to string
				char buf2[10];
				_itoa_s(nOffsetValue, buf2, 10);

				// ** Set value in editbox
				SetWindowText(editCtrl1, buf2);

				// ** Set flag to indicate match
				bValueFound = true;
			}
			//-----------------------------------------------------------------------------
			// ** END: Search for hexstring in buffer
			//-----------------------------------------------------------------------------


			//-----------------------------------------------------------------------------
			// ** Enable the editbox if value found
			//-----------------------------------------------------------------------------
			bValueFound ? EnableWindow(editCtrl1, true) : EnableWindow(editCtrl1, false);
			//-----------------------------------------------------------------------------

			// ** Reset before next search
			bValueFound = false;

			//-----------------------------------------------------------------------------
			// ** NEXT
			//-----------------------------------------------------------------------------


			//-----------------------------------------------------------------------------
			// ** Search for hexstring in buffer
			//-----------------------------------------------------------------------------
			patternSize = sizeof(hexstr2) / sizeof(hexstr2[0]);
			n = FindBytePattern(hexstr2, cBuf, uFileSize, patternSize);
			if (n == std::string::npos)
			{
				log("Pattern not found!\nReturn value: %d ( 0x%x )\n", n, n);
			}
			else if (n != std::string::npos)
			{
				// position is n
				log("Pattern found at offset: %d ( 0x%x )\n", n, n);

				// ** Get the value and put into integer
				unsigned int hexValue[10];
				hexValue[0] = cBuf[n + 38];
				hexValue[1] = cBuf[n + 37];
				hexValue[2] = cBuf[n + 36];

				//printf("%x%x%x\n", hexValue[0], hexValue[1], hexValue[2]);

				std::string hexFinal;
				char buf1[10];

				_itoa_s(hexValue[0], buf1, 16);
				if (hexValue[0] < 0x10)
				{
					hexFinal = "0";
					hexFinal += buf1;
				}
				else
				{
					hexFinal = buf1;
				}

				_itoa_s(hexValue[1], buf1, 16);
				if (hexValue[1] < 0x10)
				{
					hexFinal += "0";
					hexFinal += buf1;
				}
				else
				{
					hexFinal += buf1;
				}

				_itoa_s(hexValue[2], buf1, 16);
				if (hexValue[2] < 0x10)
				{
					hexFinal += "0";
					hexFinal += buf1;
				}
				else
				{
					hexFinal += buf1;
				}

				//printf("%s\n", hexFinal.c_str());

				// ** Get the value and put into integer
				int nOffsetValue = hex2dec(hexFinal.c_str());

				//printf("Hex: %x\n", nOffsetValue); // prints out hex
				//printf("Dec: %u\n", nOffsetValue); // prints out dec

				// ** Convert int to string
				char buf2[10];
				_itoa_s(nOffsetValue, buf2, 10);

				// ** Set value in editbox
				SetWindowText(editCtrl2, buf2);

				// ** Set flag to indicate match
				bValueFound = true;
			}
			//-----------------------------------------------------------------------------
			// ** END: Search for hexstring in buffer
			//-----------------------------------------------------------------------------

			//-----------------------------------------------------------------------------
			// ** Enable the editbox if value found
			//-----------------------------------------------------------------------------
			bValueFound ? EnableWindow(editCtrl2, true) : EnableWindow(editCtrl2, false);
			//-----------------------------------------------------------------------------

			// ** Reset before next search
			bValueFound = false;

			//-----------------------------------------------------------------------------
			// ** NEXT
			//-----------------------------------------------------------------------------

		
			//-----------------------------------------------------------------------------
			// ** Search for hexstring in buffer
			//-----------------------------------------------------------------------------
			patternSize = sizeof(hexstr3) / sizeof(hexstr3[0]);
			n = FindBytePattern(hexstr3, cBuf, uFileSize, patternSize);
			if (n == std::string::npos)
			{
				log("Pattern not found!\nReturn value: %d ( 0x%x )\n", n, n);
			}
			else if (n != std::string::npos)
			{
				// position is n
				log("Pattern found at offset: %d ( 0x%x )\n", n, n);

				unsigned int hexValue[10];
				hexValue[0] = cBuf[n + 35];
				hexValue[1] = cBuf[n + 34];
				hexValue[2] = cBuf[n + 33];

				//printf("%x%x%x\n", hexValue[0], hexValue[1], hexValue[2]);

				std::string hexFinal;
				char buf1[10];

				_itoa_s(hexValue[0], buf1, 16);
				if (hexValue[0] < 0x10)
				{
					hexFinal = "0";
					hexFinal += buf1;
				}
				else
				{
					hexFinal = buf1;
				}

				_itoa_s(hexValue[1], buf1, 16);
				if (hexValue[1] < 0x10)
				{
					hexFinal += "0";
					hexFinal += buf1;
				}
				else
				{
					hexFinal += buf1;
				}

				_itoa_s(hexValue[2], buf1, 16);
				if (hexValue[2] < 0x10)
				{
					hexFinal += "0";
					hexFinal += buf1;
				}
				else
				{
					hexFinal += buf1;
				}

				//printf("%s\n", hexFinal.c_str());

				// ** Get the value and put into integer					
				int nOffsetValue = hex2dec(hexFinal.c_str());

				//printf("Hex: %x\n", nOffsetValue); // prints out hex
				//printf("Dec: %u\n", nOffsetValue); // prints out dec

				// ** Convert int to string
				char buf2[10];
				_itoa_s(nOffsetValue, buf2, 10);

				// ** Set value in editbox
				SetWindowText(editCtrl3, buf2);

				// ** Set flag to indicate match
				bValueFound = true;
			}
			//-----------------------------------------------------------------------------
			// ** END: Search for hexstring in buffer
			//-----------------------------------------------------------------------------

			//-----------------------------------------------------------------------------
			// ** Enable the editbox if value found
			//-----------------------------------------------------------------------------
			bValueFound ? EnableWindow(editCtrl3, true) : EnableWindow(editCtrl3, false);
			//-----------------------------------------------------------------------------

			// ** Reset before next search
			bValueFound = false;

			//-----------------------------------------------------------------------------
			// ** NEXT
			//-----------------------------------------------------------------------------


			//-----------------------------------------------------------------------------
			// ** Search for hexstring in buffer
			//-----------------------------------------------------------------------------
			patternSize = sizeof(hexstr4) / sizeof(hexstr4[0]);
			n = FindBytePattern(hexstr4, cBuf, uFileSize, patternSize);
			if (n == std::string::npos)
			{
				log("Pattern not found!\nReturn value: %d ( 0x%x )\n", n, n);
			}
			else if (n != std::string::npos)
			{
				// position is n
				log("Pattern found at offset: %d ( 0x%x )\n", n, n);

				unsigned int hexValue[10];
				hexValue[0] = cBuf[n + 37];
				hexValue[1] = cBuf[n + 36];
				hexValue[2] = cBuf[n + 35];

				//printf("%x%x%x\n", hexValue[0], hexValue[1], hexValue[2]);

				std::string hexFinal;
				char buf1[10];

				_itoa_s(hexValue[0], buf1, 16);
				if (hexValue[0] < 0x10)
				{
					hexFinal = "0";
					hexFinal += buf1;
				}
				else
				{
					hexFinal = buf1;
				}

				_itoa_s(hexValue[1], buf1, 16);
				if (hexValue[1] < 0x10)
				{
					hexFinal += "0";
					hexFinal += buf1;
				}
				else
				{
					hexFinal += buf1;
				}

				_itoa_s(hexValue[2], buf1, 16);
				if (hexValue[2] < 0x10)
				{
					hexFinal += "0";
					hexFinal += buf1;
				}
				else
				{
					hexFinal += buf1;
				}

				//printf("%s\n", hexFinal.c_str());

				// ** Get the value and put into integer
				int nOffsetValue = hex2dec(hexFinal.c_str());

				//printf("Hex: %x\n", nOffsetValue); // prints out hex
				//printf("Dec: %u\n", nOffsetValue); // prints out dec

				// ** Convert int to string
				char buf2[10];
				_itoa_s(nOffsetValue, buf2, 10);

				// ** Set value in editbox
				SetWindowText(editCtrl4, buf2);

				// ** Set flag to indicate match
				bValueFound = true;
			}
			//-----------------------------------------------------------------------------
			// ** END: Search for hexstring in buffer
			//-----------------------------------------------------------------------------

			log("File read!\n");

			//-----------------------------------------------------------------------------
			// ** Clean up
			//-----------------------------------------------------------------------------
			free(cBuf);

			//-----------------------------------------------------------------------------
			// ** Enable the editbox if value found
			//-----------------------------------------------------------------------------
			bValueFound ? EnableWindow(editCtrl4, true) : EnableWindow(editCtrl4, false);
			//-----------------------------------------------------------------------------

			//-----------------------------------------------------------------------------
			// ** Enable the save button so it can be used, if any matches were found
			//-----------------------------------------------------------------------------
			if ( IsWindowEnabled(editCtrl1) || IsWindowEnabled(editCtrl2) || 
				 IsWindowEnabled(editCtrl3) || IsWindowEnabled(editCtrl4) )
			{
				EnableWindow(btnSave, true);
			}
			else
			{
				EnableWindow(btnSave, false);
				
				// ** Reset values
				SetWindowText(editCtrl1, "0");
				SetWindowText(editCtrl2, "0");
				SetWindowText(editCtrl3, "0");
				SetWindowText(editCtrl4, "0");

				std::string str;
				str =  "Sorry, no values were found!\n\nPossible reasons why:\n";
				str += "->File is not a \"SpongeBob: Rehydrated\" savefile (PC,Steam) ?\n";
				str += "->Game has been patched, changed or updated its savefile encryption ?\n";
				str += "->Savefile is damaged or corrupted ?";

				MessageBox(hWnd, str.c_str(), "!", MB_OK);

				return false;
			}
			//-----------------------------------------------------------------------------

		}
		else if(strFileName != "" && pFile == NULL)
		{
			char buf[10];
			_itoa_s(errorCode, buf, 10);

			std::string err;
			err += "Error opening file!\nErrorcode: ";
			err += buf;

			// ..error opening file
			MessageBox(hWnd, err.c_str(), "Error", MB_OK);

			return false;
		}		
	}

	return true;
};
//---------------------------------------------------------------------------------------------
// ** END: Read file values and put them into edit controls
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Save values to file
//---------------------------------------------------------------------------------------------
bool SaveFileValues(HWND hWnd)
{
	// ** Get filename from global variable
	std::string strFileName = g_strFileName;

	// ** Check that string is not empty
	if (strFileName != "")
	{
		SetCursor(hCursorWait);

		FILE *pFile = NULL;
		errno_t errorCode = fopen_s(&pFile, strFileName.c_str(), "rb");

		if (pFile != NULL)
		{
			fseek(pFile, 0, SEEK_END);
			unsigned int uFileSize = ftell(pFile);
			rewind(pFile);

			//char *cBuf = (char *)malloc(uFileSize * sizeof(char *));  // <-- changed from this to the line under, was reading FFFFFFFF instead of FF in byte value
			unsigned char *cBuf = (unsigned char*)malloc(uFileSize * sizeof(char));

			if (cBuf == NULL)
			{
				log("Error, could not allocate memory for file buffer!");
				MessageBox(hWnd, "Error, could not allocate memory for file buffer!", "Error", MB_OK | MB_ICONERROR);
				return false;
			}
			else
			{
				fread(cBuf, 1, uFileSize, pFile);
				fclose(pFile);
				pFile = NULL;
			}


			// ..do stuff here

			//-----------------------------------------------------------------------------
			// ** Search for hexstring in buffer
			//-----------------------------------------------------------------------------
			int patternSize = sizeof(hexstr1) / sizeof(hexstr1[0]);
			unsigned int n = FindBytePattern(hexstr1, cBuf, uFileSize, patternSize);
			if (n == std::string::npos)
			{
				log("Pattern not found!\nReturn value: %d ( 0x%x )\n", n, n);
			}
			else if (n != std::string::npos)
			{	
				// ** position is n
				log("Pattern found at offset: %d ( 0x%x )\n", n, n);

				// ** Get text from editbox1
				char bufText[5];
				GetWindowText(editCtrl1, bufText, sizeof(bufText));

				// ** Convert string to int
				int input = atoi(bufText);

				// ** Convert dec to hex
				char hex[10];
				sprintf_s(hex, "%x", input);
				//printf("The number %d, turned to hexadecimal is: %s\n", input, hex);

				// ** Convert hex into byte array
				unsigned char bytes[4];
				int num = input;
				//bytes[0] = (num >> 24) & 0xFF;
				bytes[2] = (num >> 16) & 0xFF;
				bytes[1] = (num >> 8) & 0xFF;
				bytes[0] = num & 0xFF;

				// ** Write to buffer
				cBuf[n + 35] = bytes[2];
				cBuf[n + 34] = bytes[1];
				cBuf[n + 33] = bytes[0];
			}
			//-----------------------------------------------------------------------------
			// ** END: Search for hexstring in buffer
			//-----------------------------------------------------------------------------


			//-----------------------------------------------------------------------------
			// ** NEXT
			//-----------------------------------------------------------------------------


			//-----------------------------------------------------------------------------
			// ** Search for hexstring in buffer
			//-----------------------------------------------------------------------------
			patternSize = sizeof(hexstr2) / sizeof(hexstr2[0]);
			n = FindBytePattern(hexstr2, cBuf, uFileSize, patternSize);
			if (n == std::string::npos)
			{
				log("Pattern not found!\nReturn value: %d ( 0x%x )\n", n, n);
			}
			else if (n != std::string::npos)
			{
				// position is n
				log("Pattern found at offset: %d ( 0x%x )\n", n, n);

				// ** Get text from editbox2
				char bufText[5];
				GetWindowText(editCtrl2, bufText, sizeof(bufText));

				// ** Convert string to int
				int input = atoi(bufText);

				// ** Convert dec to hex
				char hex[10];
				sprintf_s(hex, "%x", input);
				//printf("The number %d, turned to hexadecimal is: %s\n", input, hex);

				// ** Convert hex into byte array
				unsigned char bytes[4];
				int num = input;
				//bytes[0] = (num >> 24) & 0xFF;
				bytes[2] = (num >> 16) & 0xFF;
				bytes[1] = (num >> 8) & 0xFF;
				bytes[0] = num & 0xFF;

				// ** Write to buffer
				cBuf[n + 38] = bytes[2];
				cBuf[n + 37] = bytes[1];
				cBuf[n + 36] = bytes[0];
			}
			//-----------------------------------------------------------------------------
			// ** END: Search for hexstring in buffer
			//-----------------------------------------------------------------------------


			//-----------------------------------------------------------------------------
			// ** NEXT
			//-----------------------------------------------------------------------------


			//-----------------------------------------------------------------------------
			// ** Search for hexstring in buffer
			//-----------------------------------------------------------------------------
			patternSize = sizeof(hexstr3) / sizeof(hexstr3[0]);
			n = FindBytePattern(hexstr3, cBuf, uFileSize, patternSize);
			if (n == std::string::npos)
			{
				log("Pattern not found!\nReturn value: %d ( 0x%x )\n", n, n);
			}
			else if (n != std::string::npos)
			{
				// position is n
				log("Pattern found at offset: %d ( 0x%x )\n", n, n);

				// ** Get text from editbox3
				char bufText[10];
				GetWindowText(editCtrl3, bufText, sizeof(bufText));

				// ** Convert string to int
				int input = atoi(bufText);

				// ** Convert dec to hex
				char hex[10];
				sprintf_s(hex, "%x", input);
				//printf("The number %d, turned to hexadecimal is: %s\n", input, hex);

				// ** Convert hex into byte array
				unsigned char bytes[4];
				int num = input;
				//bytes[0] = (num >> 24) & 0xFF;
				bytes[2] = (num >> 16) & 0xFF;
				bytes[1] = (num >> 8) & 0xFF;
				bytes[0] = num & 0xFF;

				// ** Write to buffer
				cBuf[n + 35] = bytes[2];
				cBuf[n + 34] = bytes[1];
				cBuf[n + 33] = bytes[0];
			}
			//-----------------------------------------------------------------------------
			// ** END: Search for hexstring in buffer
			//-----------------------------------------------------------------------------


			//-----------------------------------------------------------------------------
			// ** NEXT
			//-----------------------------------------------------------------------------


			//-----------------------------------------------------------------------------
			// ** Search for hexstring in buffer
			//-----------------------------------------------------------------------------
			patternSize = sizeof(hexstr4) / sizeof(hexstr4[0]);
			n = FindBytePattern(hexstr4, cBuf, uFileSize, patternSize);
			if (n == std::string::npos)
			{
				log("Pattern not found!\nReturn value: %d ( 0x%x )\n", n, n);
			}
			else if (n != std::string::npos)
			{
				// position is n
				log("Pattern found at offset: %d ( 0x%x )\n", n, n);

				// ** Get text from editbox4
				char bufText[5];
				GetWindowText(editCtrl4, bufText, sizeof(bufText));

				// ** Convert string to int
				int input = atoi(bufText);

				// ** Convert dec to hex
				char hex[10];
				sprintf_s(hex, "%x", input);
				//printf("The number %d, turned to hexadecimal is: %s\n", input, hex);

				// ** Convert hex into byte array
				unsigned char bytes[4];
				int num = input;
				//bytes[0] = (num >> 24) & 0xFF;
				bytes[2] = (num >> 16) & 0xFF;
				bytes[1] = (num >> 8) & 0xFF;
				bytes[0] = num & 0xFF;

				// ** Write to buffer
				cBuf[n + 37] = bytes[2];
				cBuf[n + 36] = bytes[1];
				cBuf[n + 35] = bytes[0];
			}
			//-----------------------------------------------------------------------------
			// ** END: Search for hexstring in buffer
			//-----------------------------------------------------------------------------


			//-----------------------------------------------------------------------------
			// ** WRITE TO FILE
			//-----------------------------------------------------------------------------
			errno_t errorCode = fopen_s(&pFile, strFileName.c_str(), "wb");

			if (pFile != NULL)
			{
				fwrite(cBuf, 1, uFileSize, pFile);
				fclose(pFile);
				free(cBuf);

				log("File saved!\n");
			}
			else
			{
				free(cBuf);
				MessageBox(hWnd, "Unable to open file for writing.", "Error", MB_OK);				

				return false;
			}
			//-----------------------------------------------------------------------------
		}
		else if (strFileName != "" && pFile == NULL)
		{
			char buf[10];
			_itoa_s(errorCode, buf, 10);

			std::string err;
			err += "Error opening file!\nErrorcode: ";
			err += buf;

			// ..error opening file
			MessageBox(hWnd, err.c_str(), "Error", MB_OK);

			return false;
		}
	}

	return true;
};
//---------------------------------------------------------------------------------------------
// ** END: Save values to file
//---------------------------------------------------------------------------------------------
