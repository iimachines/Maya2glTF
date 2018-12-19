#pragma once
#include <windows.h>

#ifdef WIN32
class WindowFinder
{
public:
    WindowFinder(const char* windowStyleName, HWND parentWindowHandle);

    const char* styleName;
    HWND windowHandle;

private:
    bool Find(HWND hWnd);
    static BOOL Find(HWND hWnd, LPARAM param);
};

#endif

class OutputWindow
{
public:
    OutputWindow();

    void clear() const;

private:
#ifdef WIN32
    HWND m_editControlHandle;
#endif
};

