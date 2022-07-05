
#include <ICPPWNDMSG.hpp>

#include <iostream>

int main()
{
    auto l_pMSG = __N_CPPWNDMSG__::CreateCPPWNDMSG();

    __N_CPPWNDMSG__::CPPWNDMSG_INIT l_init{};
    l_init.window_class.assign("class_name");
    l_init.window_name.assign("window_name");
    if (!l_pMSG->Initialize(l_init))
    {
        std::cout << l_pMSG->getLastError() << std::endl;
        return 1;
    }
    
    l_pMSG->send(2048, 1, 2);
    l_pMSG->send(2048, 1, 2);
    l_pMSG->send(2048, 1, 2);
    
    l_pMSG->post(2048, 1, 2);
    l_pMSG->post(2048, 1, 2);
    l_pMSG->post(2048, 1, 2);

    l_pMSG->UnInitialize();

    return 0;
}