
#include <iostream>
#include <Windows.h>

int main()
{
    HWND l_hwnd = ::FindWindowA("class_name", "window_name");

    ::PostMessageA(l_hwnd, 2048, NULL, NULL);
    ::PostMessageA(l_hwnd, 2048, NULL, NULL);
    ::PostMessageA(l_hwnd, 2048, NULL, NULL);
    ::PostMessageA(l_hwnd, 2048, NULL, NULL);

    return 0;
}