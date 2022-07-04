
#include <ICPPMSGWND.hpp>

#include <iostream>
#include <thread>

int main()
{
    auto l_pWND = __N_CPPMSGWND__::CreateCPPMSGWND();

    __N_CPPMSGWND__::CPPMSGWND_INIT l_init{};
    l_init.window_class.assign("class_name");
    l_init.window_name.assign("window_name");
    if (!l_pWND->Initialize(l_init))
    {
        std::cout << l_pWND->getLastError() << std::endl;
        return 1;
    }

    l_pWND->RegisterCallbackFunction([](int hwnd, unsigned int msg, int lparam, int wparam) {
        std::cout << "hwnd: " << hwnd << " msg: " << msg << " lparam: " << lparam << " wparam: " << wparam << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(20000));

    l_pWND->UnInitialize();

    return 0;
}