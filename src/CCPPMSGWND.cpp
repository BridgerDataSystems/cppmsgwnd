
#include "CCPPMSGWND.hpp"

namespace __N_CPPMSGWND__
{
    #define ASSERTINITIALIZED_BOOL if (!this->IsInitialized()) { this->m_strLastError.assign("FAILED because CCPPMSGWND is not initialized"); return false; }
    #define ASSERTINITIALIZED_INT if (!this->IsInitialized()) { this->m_strLastError.assign("FAILED because CCPPMSGWND is not initialized"); return 0; }

	WND_LAMBDA_MAP	CCPPMSGWND::m_mapRegisteredCallbakFunctions;

	bool CCPPMSGWND::Initialize(const CPPMSGWND_INIT& init) noexcept
	{
		if (this->m_bInitialized)
		{
			this->m_strLastError.assign("CCPPMSGWND::Initialize - FAILED because CCPPMSGWND is already initialized");
			return false;
		}

		this->m_strWindowClass.assign(init.window_class);
		this->m_strWindowName.assign(init.window_name);

		std::promise<bool>_bPromiseInitialized;
		std::future<bool>_bFutureInitialized = _bPromiseInitialized.get_future();

		this->m_hThread = std::thread(&CCPPMSGWND::TTCreateWindow, this, std::forward<std::promise<bool>>(_bPromiseInitialized));

		std::chrono::system_clock::time_point two_seconds_passed
			= std::chrono::system_clock::now() + std::chrono::seconds(2);

		if (std::future_status::ready == _bFutureInitialized.wait_until(two_seconds_passed))
			this->m_bInitialized = _bFutureInitialized.get();
		else
		{
			this->m_strLastError.assign("CCPPMSGWND::Initialize - FAILED to start window - TIMEOUT");
			this->m_bInitialized = false;
            return false;
		}

		this->m_bInitialized = true;

		return true;
	}

	bool CCPPMSGWND::UnInitialize() noexcept
	{
		ASSERTINITIALIZED_BOOL

		PostThreadMessage(m_iThreadId, WM_QUIT, NULL, NULL);
		PostThreadMessage(m_iThreadId, WM_CLOSE, NULL, NULL);

		this->m_hThread.join();

		this->m_bInitialized = false;

		return true;
	}

	unsigned short CCPPMSGWND::RegisterCallbackFunction(WND_LAMBDA lambda) noexcept
	{
		ASSERTINITIALIZED_INT

		std::lock_guard<std::mutex>lock(m_PushMutex);

		int _index = m_iIndex;
		auto _mapRet = m_mapRegisteredCallbakFunctions.insert(std::make_pair(m_iIndex, lambda));
		if (false == _mapRet.second)
		{
			this->m_strLastError.assign("CCPPMSGWND::RegisterCallbackFunction - FAILED to insert into m_mapRegisteredCallbakFunctions");
			return -1;
		}

		this->m_iIndex++;
        
		return _index;
	}

	bool CCPPMSGWND::DeRegisterCallbackFunction(unsigned short index) noexcept
	{
		ASSERTINITIALIZED_BOOL

		std::lock_guard<std::mutex>_lock(m_PushMutex);
		try
		{
			auto it = m_mapRegisteredCallbakFunctions.find(index);
			if (it != m_mapRegisteredCallbakFunctions.end())
				m_mapRegisteredCallbakFunctions.erase(it);
		}
		catch (...)
		{
			this->m_strLastError.assign("CCPPMSGWND::DeregisterCallBackFunction - EXCEPTION occurred while trying to erase");
			return false;
		}
        
		return true;
	}

	void CCPPMSGWND::InformRegistredModules(const int hwnd, unsigned int uInt, int wparm, int lparam) noexcept
	{
		for (auto elem : m_mapRegisteredCallbakFunctions)
			elem.second(hwnd, uInt, wparm, lparam);
	}

	bool CCPPMSGWND::TTCreateWindow(std::promise<bool>&& promise) noexcept
	{
		m_iThreadId = GetCurrentThreadId();

		// Register the Message structur
		HINSTANCE l_hInst = (HINSTANCE)GetCurrentProcess();

		WNDCLASSEXA wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEXA);
		wcex.lpfnWndProc = (WNDPROC)CCPPMSGWND::AppWndProc;
		wcex.hInstance = l_hInst;
		wcex.lpszClassName = this->m_strWindowClass.c_str();

		if (!RegisterClassExA(&wcex) && ERROR_CLASS_ALREADY_EXISTS != GetLastError())
		{
			this->m_strLastError.assign("CCPPMSGWND::TTCreateWindow - RegisterClassEx FAILED to Register Window Class with error code: %d", GetLastError());
			promise.set_value(FALSE);
			return false;
		}

		// Create the main window.
		this->m_hwnd = CreateWindowExA(
			NULL,
			this->m_strWindowClass.c_str(),
			this->m_strWindowName.c_str(),
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			HWND_MESSAGE,
			NULL,
			NULL,
			NULL);

		// If the main window cannot be created, terminate the application.
		if (!m_hwnd)
		{
			this->m_strLastError.assign("CCPPMSGWND::TTCreateWindow - CreateWindowEx FAILED to Create Window with error code: %d", GetLastError());
			UnregisterClassA(this->m_strWindowClass.c_str(), l_hInst);
			promise.set_value(FALSE);
			return false;
		}

		// promise
		promise.set_value(TRUE);

		// Start the message loop.
		MSG msg{ 0 };
        bool bRet{ true };
		while (bRet)
		{
            bRet = GetMessage(&msg, NULL, 0, 0);
			if (!bRet) {
				this->m_strLastError.assign("CCPPMSGWND::TTCreateWindow FAILURE in GetMessage function");
			} else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		if (!DestroyWindow(this->m_hwnd))
		{
			this->m_strLastError.assign("CCPPMSGWND::TTDestroyWindow - DestroyWindow FAILED with error: %d", GetLastError());
			return false;
		}

		if (!UnregisterClassA(this->m_strWindowClass.c_str(), l_hInst))
		{
			this->m_strLastError.assign("CCPPMSGWND::TTDestroyWindow - UnregisterClass FAILED with error: %d", GetLastError());
			return false;
		}

		return true;
	}

	LRESULT CALLBACK CCPPMSGWND::AppWndProc(HWND hWnd, UINT uInt, WPARAM wParam, LPARAM lParam)
	{
	//	cout << "CCPPMSGWND::WndProc: " << uInt << endl;
	//	switch (uInt)
	//	{
	//	case WM_CREATE: cout << "CCPPMSGWND::WndProc: WM_CREATE" << endl; break;
	//	case WM_QUIT: cout << "CCPPMSGWND::WndProc: WM_QUIT" << endl; break;
	//	case TT_MSG_TERMINATE: /*PostQuitMessage(0);*/ cout << "CCPPMSGWND::WndProc: TT_MSG_TERMINATE" << endl; break;
	//	case WM_NCDESTROY: /*PostQuitMessage(0);*/ cout << "CCPPMSGWND::WndProc: WM_NCDESTROY" << endl; break;
	//	case WM_DESTROY:  /*PostQuitMessage(0);*/ cout << "CCPPMSGWND::WndProc: WM_DESTROY" << endl; break;
	//	case WM_CLOSE: /*PostQuitMessage(0);*/ cout << "CCPPMSGWND::WndProc: WM_CLOSE" << endl; break;
	//	}
		
		//if (WM_USER <= uInt && WM_USER + 100 >= uInt)
			for (auto elem : m_mapRegisteredCallbakFunctions)
				if (NULL != elem.second)
                {
					auto t = std::thread([elem, hWnd, uInt, wParam, lParam](){ elem.second((int)hWnd, uInt, wParam, lParam); });
                    t.detach();
                }
		
		return DefWindowProc(hWnd, uInt, wParam, lParam);
	}

	ICPPMSGWND* CreateCPPMSGWND() noexcept
    {
        return new CCPPMSGWND;
    }

    void DestroyCPPMSGWND(ICPPMSGWND** ppObj) noexcept
    {
        if (!ppObj)
            return;

        if (!*ppObj)
            return;

        delete *ppObj;
        *ppObj = nullptr;
    }
} // !__N_CPPMSGWND__