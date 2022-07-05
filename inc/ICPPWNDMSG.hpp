#pragma once

#ifndef __H_ICPPWNDMSG__
#define __H_ICPPWNDMSG__

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif // !__cplusplus

#ifdef CPPWNDMSG_EXPORTS
#define CPPWNDMSG_API EXTERNC __declspec(dllexport)
#else
#define CPPWNDMSG_API EXTERNC __declspec(dllimport)
#pragma comment(lib, "cppwndmsg")
#endif // !CPPWNDMSG_EXPORTS

#include <functional>
#include <string>

namespace __N_CPPWNDMSG__
{
    typedef struct _cppmsgwnd_init
    {
        std::string window_class{};
        std::string window_name{};
    } CPPWNDMSG_INIT, * LP_CPPWNDMSG_INIT;

	class ICPPWNDMSG
	{
	private:
	protected:
		bool m_bInitialized{ false };
        std::string m_strLastError{};

	public:
		ICPPWNDMSG() = default;
		ICPPWNDMSG(const ICPPWNDMSG&) = delete;
		ICPPWNDMSG(ICPPWNDMSG&&) = delete;
		ICPPWNDMSG& operator = (const ICPPWNDMSG&) = delete;
		ICPPWNDMSG& operator = (ICPPWNDMSG&&) = delete;
		virtual ~ICPPWNDMSG() = default;

		virtual bool Initialize(const CPPWNDMSG_INIT&) noexcept = 0;
		virtual bool UnInitialize() noexcept = 0;
		bool IsInitialized() const noexcept { return this->m_bInitialized; }
        
        virtual bool send(unsigned int, int, int) noexcept = 0;
        virtual bool post(unsigned int, int, int) noexcept = 0;

        std::string getLastError() const noexcept { return this->m_strLastError; }
	};

	CPPWNDMSG_API ICPPWNDMSG* CreateCPPWNDMSG() noexcept;
    CPPWNDMSG_API void DestroyCPPWNDMSG(ICPPWNDMSG**) noexcept;
} // !__N_CPPWNDMSG__

#endif // !__H_ICPPWNDMSG__