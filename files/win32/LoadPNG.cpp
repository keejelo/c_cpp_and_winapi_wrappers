//---------------------------------------------------------------------------------------------
// ** LoadPNG.cpp
//---------------------------------------------------------------------------------------------
// Load a PNG resource and directly output it as a GDI+ object guarded by a smart pointer
// Source: https://www.enlyze.com/blog/writing-win32-apps-like-its-2020/part-3/
// TIP: Have one high-resolution image and then let GDI+ resize it as needed
//---------------------------------------------------------------------------------------------
/*
    // USAGE:
    // Draw the loaded image onto any Device Context like this:

    Gdiplus::Graphics g(hDC);
    g.DrawImage(m_pLogoBitmap.get(), x, y, width, height);
*/
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "LoadPNG.h"


//---------------------------------------------------------------------------------------------
// ** Load PNG resource
//---------------------------------------------------------------------------------------------
std::unique_ptr<Gdiplus::Bitmap> LoadPNGAsGdiplusBitmap(HINSTANCE hInstance, UINT uID)
{
    HRSRC hFindResource = FindResourceW(hInstance, MAKEINTRESOURCEW(uID), L"PNG");
    if (hFindResource == nullptr)
    {
        return nullptr;
    }

    DWORD dwSize = SizeofResource(hInstance, hFindResource);
    if (dwSize == 0)
    {
        return nullptr;
    }

    HGLOBAL hLoadResource = LoadResource(hInstance, hFindResource);
    if (hLoadResource == nullptr)
    {
        return nullptr;
    }

    const void* pResource = LockResource(hLoadResource);
    if (!pResource)
    {
        return nullptr;
    }

    std::unique_ptr<Gdiplus::Bitmap> pBitmap;
    HGLOBAL hBuffer = GlobalAlloc(GMEM_MOVEABLE, dwSize);
    if (hBuffer)
    {
        void* pBuffer = GlobalLock(hBuffer);
        if (pBuffer)
        {
            CopyMemory(pBuffer, pResource, dwSize);

            IStream* pStream;
            if (CreateStreamOnHGlobal(pBuffer, FALSE, &pStream) == S_OK)
            {
                pBitmap.reset(Gdiplus::Bitmap::FromStream(pStream));
                pStream->Release();
            }

            GlobalUnlock(pBuffer);
        }

        GlobalFree(hBuffer);
    }

    return pBitmap;
};
//---------------------------------------------------------------------------------------------
// ** END: Load PNG resource
//---------------------------------------------------------------------------------------------
