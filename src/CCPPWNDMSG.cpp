
#include "./CCPPWNDMSG.hpp"

#include <Windows.h>

#include <sstream>

namespace __N_CPPWNDMSG__
{
    #define ASSERTINITIALIZED if (!this->IsInitialized()) { this->m_strLastError.assign("FAILED because CCPPWNDMSG is not initialized"); return false; }

	bool CCPPWNDMSG::Initialize(const CPPWNDMSG_INIT& init) noexcept
    {
        if (this->m_bInitialized)
        {
            this->m_strLastError.assign("FAILED because CCPPWNDMSG is already initialized");
            return false;
        }

        this->m_strWindowClass.assign(init.window_class);
        this->m_strWindowName.assign(init.window_name);

        this->m_bInitialized = true;
        return true;
    }

	bool CCPPWNDMSG::UnInitialize() noexcept
    {
        ASSERTINITIALIZED

        this->m_bInitialized = false;

        return true;
    }

    bool CCPPWNDMSG::send(unsigned int msg, int lparam, int wparam) noexcept
    {
        ASSERTINITIALIZED
        
        HWND l_hwnd = ::FindWindowA(this->m_strWindowClass.c_str(), this->m_strWindowName.c_str());
        if (NULL == l_hwnd)
        {
            std::stringstream l_stream{};
            l_stream << "CCPPWNDMSG::send - FindWindowA FAILED to find window with error code: " << ::GetLastError();
            this->m_strLastError.assign(l_stream.str());
            return false;
        }

        if (!::SendMessageA(l_hwnd, msg, lparam, wparam))
        {
            std::stringstream l_stream{};
            l_stream << "CCPPWNDMSG::send - SendMessageA FAILED to post message with error code: " << ::GetLastError();
            this->m_strLastError.assign(l_stream.str());
            return false;
        }

        return true;
    }

    bool CCPPWNDMSG::post(unsigned int msg, int lparam, int wparam) noexcept
    {
        ASSERTINITIALIZED
        
        HWND l_hwnd = ::FindWindowA(this->m_strWindowClass.c_str(), this->m_strWindowName.c_str());
        if (NULL == l_hwnd)
        {
            std::stringstream l_stream{};
            l_stream << "CCPPWNDMSG::post - FindWindowA FAILED to find window with error code: " << ::GetLastError();
            this->m_strLastError.assign(l_stream.str());
            return false;
        }

        if (!::PostMessageA(l_hwnd, msg, lparam, wparam))
        {
            std::stringstream l_stream{};
            l_stream << "CCPPWNDMSG::post - PostMessageA FAILED to post message with error code: " << ::GetLastError();
            this->m_strLastError.assign(l_stream.str());
            return false;
        }

        return true;
    }

	ICPPWNDMSG* CreateCPPWNDMSG() noexcept
    {
        return new CCPPWNDMSG;
    }

    void DestroyCPPWNDMSG(ICPPWNDMSG** ppObj) noexcept
    {
        if (!ppObj)
            return;

        if (!*ppObj)
            return;

        delete *ppObj;
        *ppObj = nullptr;
    }
} // !__N_CPPWNDMSG__