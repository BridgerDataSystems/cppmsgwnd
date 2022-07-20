#pragma once

#ifndef __H_ICPPMSGWND__
#define __H_ICPPMSGWND__

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif // !__cplusplus

#ifdef CPPMSGWND_EXPORTS
#define CPPMSGWND_API EXTERNC __declspec(dllexport)
#else
#define CPPMSGWND_API EXTERNC __declspec(dllimport)
#pragma comment(lib, "cppmsgwnd")
#endif // !CPPMSGWND_EXPORTS

#include <functional>
#include <string>

namespace __N_CPPMSGWND__
{
	using WND_LAMBDA = std::function<void(int, unsigned int, int, int)>;

    typedef struct _cppmsgwnd_init
    {
        std::string window_class{};
        std::string window_name{};
    } CPPMSGWND_INIT, * LP_CPPMSGWND_INIT;

	class ICPPMSGWND
	{
	private:
	protected:
	public:
		ICPPMSGWND() = default;
		ICPPMSGWND(const ICPPMSGWND&) = delete;
		ICPPMSGWND(ICPPMSGWND&&) = delete;
		ICPPMSGWND& operator = (const ICPPMSGWND&) = delete;
		ICPPMSGWND& operator = (ICPPMSGWND&&) = delete;
		virtual ~ICPPMSGWND() = default;

		virtual bool Initialize(const CPPMSGWND_INIT&) noexcept = 0;
		virtual bool UnInitialize() noexcept = 0;
		virtual bool IsInitialized() const noexcept = 0;

		virtual unsigned short RegisterCallbackFunction(WND_LAMBDA) noexcept = 0;
		virtual bool DeRegisterCallbackFunction(const unsigned short) noexcept = 0;
		virtual int GetHWND() const noexcept = 0;

        virtual std::string getLastError() const noexcept = 0;
	};

	CPPMSGWND_API ICPPMSGWND* CreateCPPMSGWND() noexcept;
    CPPMSGWND_API void DestroyCPPMSGWND(ICPPMSGWND**) noexcept;
} // !__N_CPPMSGWND__

#endif // !__H_ICPPMSGWND__