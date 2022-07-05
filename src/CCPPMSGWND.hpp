#pragma once

#ifndef __H_CCPPMSGWND__
#define __H_CCPPMSGWND__

#include <ICPPMSGWND.hpp>

#include <functional>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <future>

#include <Windows.h>

namespace __N_CPPMSGWND__
{
    using WND_LAMBDA_MAP = std::unordered_map<unsigned int, WND_LAMBDA>;

	class CCPPMSGWND : public ICPPMSGWND
	{
	private:
		unsigned short  m_iIndex{ 0 };
		HWND		    m_hwnd{};
		unsigned int    m_iThreadId{ 0 };
		std::thread	    m_hThread{};
		std::string	    m_strWindowClass{};
		std::string	    m_strWindowName{};
		std::mutex	    m_PushMutex{};

		static WND_LAMBDA_MAP m_mapRegisteredCallbakFunctions;

		void InformRegistredModules(int, unsigned int, int, int) noexcept;
		bool TTCreateWindow(std::promise<bool>&&) noexcept;

	protected:
	public:
		CCPPMSGWND() = default;
		CCPPMSGWND(const CCPPMSGWND&) = delete;
		CCPPMSGWND(CCPPMSGWND&&) = delete;
		CCPPMSGWND& operator = (const CCPPMSGWND&) = delete;
		CCPPMSGWND& operator = (CCPPMSGWND&&) = delete;
		virtual ~CCPPMSGWND() { this->UnInitialize(); }

		bool Initialize(const CPPMSGWND_INIT&) noexcept final;
		bool UnInitialize() noexcept final;

		unsigned short RegisterCallbackFunction(WND_LAMBDA) noexcept final;
		bool DeRegisterCallbackFunction(const unsigned short) noexcept final;
		int GetHWND() const noexcept final { return (int)this->m_hwnd; }

		static LRESULT CALLBACK AppWndProc(HWND, UINT, WPARAM, LPARAM);
	};
} // !__N_CPPMSGWND__

#endif // !__H_CCPPMSGWND__
