#pragma once

#ifndef ITTMSGHANDLER_H
#define ITTMSGHANDLER_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#ifdef TTMSGHANDLER_EXPORTS
#define TTMSGHANDLER_API EXTERNC __declspec(dllexport)
#else
#define TTMSGHANDLER_API EXTERNC __declspec(dllimport)
#endif

#include <functional>
#include <Windows.h>

namespace TTMSGHandler
{
	using WINDOW_CALLBACK_LAMBDA = std::function<void(unsigned int uInt, WPARAM wparm, LPARAM lparam)>;

	class ITTMSGHandler
	{
	private:
	protected:
	public:
		ITTMSGHandler() = default;
		ITTMSGHandler(const ITTMSGHandler&) = delete;
		ITTMSGHandler(ITTMSGHandler&&) = delete;
		ITTMSGHandler& operator = (const ITTMSGHandler&) = delete;
		ITTMSGHandler& operator = (ITTMSGHandler&&) = delete;
		virtual ~ITTMSGHandler() = default;

		virtual bool Initialize(const char* lpszWindowClassName, const char* lpszWindowName) = 0;
		virtual bool Initialize(const wchar_t* lpwszWindowClassName, const wchar_t* lpwszWindowName) = 0;
		virtual bool UnInitialize() = 0;
		virtual bool IsInitialized() const noexcept = 0;

		virtual int	 RegisterCallbackFunction(WINDOW_CALLBACK_LAMBDA) = 0;
		virtual bool DeRegisterCallbackFunction(unsigned int index) = 0;
		virtual HWND GetHWND() const noexcept = 0;

		// Not need to be initialized
		virtual bool SendNotificationMessage(const char* lpszWindowClassName, const char* lpszWindowName, unsigned int uInt, WPARAM wparm, LPARAM lparam) = 0;
		virtual bool SendNotificationMessage(HWND hwnd, unsigned int uInt, WPARAM wparm, LPARAM lparam) = 0;
	};

	TTMSGHANDLER_API ITTMSGHandler* CreateTTMSGHandler();
}

#endif // !ITTMSGHANDLER_H