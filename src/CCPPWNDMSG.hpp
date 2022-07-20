#pragma once

#ifndef __H_CCPPWNDMSG__
#define __H_CCPPWNDMSG__

#include <ICPPWNDMSG.hpp>

namespace __N_CPPWNDMSG__
{
	class CCPPWNDMSG : public ICPPWNDMSG
	{
	private:
		std::string m_strWindowClass{};
		std::string m_strWindowName{};
        
		bool m_bInitialized{ false };
        std::string m_strLastError{};

	protected:
	public:
		CCPPWNDMSG() = default;
		CCPPWNDMSG(const CCPPWNDMSG&) = delete;
		CCPPWNDMSG(CCPPWNDMSG&&) = delete;
		CCPPWNDMSG& operator = (const CCPPWNDMSG&) = delete;
		CCPPWNDMSG& operator = (CCPPWNDMSG&&) = delete;
		virtual ~CCPPWNDMSG() { this->UnInitialize(); }

		bool Initialize(const CPPWNDMSG_INIT&) noexcept final;
		bool UnInitialize() noexcept final;
        
        bool send(unsigned int, int, int) noexcept final;
        bool post(unsigned int, int, int) noexcept final;

        std::string getLastError() const noexcept final { return this->m_strLastError; }
		bool IsInitialized() const noexcept final { return this->m_bInitialized; }
	};
} // !__N_CPPMSGWND__

#endif // !__H_CCPPWNDMSG__
