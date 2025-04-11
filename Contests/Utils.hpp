#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h> 
#include <Windows.h>

void CopyToClipboard(const std::string& text)
{
    // Open the clipboard
    if (!OpenClipboard(nullptr))
    {
        std::cerr << "Failed to open clipboard!" << std::endl;
        return;
    }

    // Empty the clipboard
    EmptyClipboard();

    // Allocate a global memory object for the text
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
    if (!hMem)
    {
        std::cerr << "Failed to allocate global memory!" << std::endl;
        CloseClipboard();
        return;
    }

    // Copy the text to the memory object
    memcpy(GlobalLock(hMem), text.c_str(), text.size() + 1);
    GlobalUnlock(hMem);

    // Set the clipboard data
    if (!SetClipboardData(CF_TEXT, hMem))
    {
        std::cerr << "Failed to set clipboard data!" << std::endl;
        GlobalFree(hMem);
        CloseClipboard();
        return;
    }

    // Close the clipboard
    CloseClipboard();
    std::cout << "Text copied to clipboard successfully!" << std::endl;
}
std::string GetFromClipboard() 
{
    std::string clipboardText;

    // Open the clipboard
    if (!OpenClipboard(nullptr)) 
    {
        std::cerr << "Failed to open clipboard!" << std::endl;
        return clipboardText;
    }

    // Get clipboard data in CF_TEXT format
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (!hData) 
    {
        std::cerr << "Failed to get clipboard data!" << std::endl;
        CloseClipboard();
        return clipboardText;
    }

    // Lock the handle to get the actual text pointer
    char* pszText = static_cast<char*>(GlobalLock(hData));
    if (pszText) 
    {
        clipboardText = pszText;  // Copy the text from the clipboard
        GlobalUnlock(hData);
    }
    else
        std::cerr << "Failed to lock global memory!" << std::endl;

    // Close the clipboard
    CloseClipboard();

    return clipboardText;
}

#endif // !UTILS_H
