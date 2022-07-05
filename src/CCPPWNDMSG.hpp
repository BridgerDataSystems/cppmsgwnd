#pragma once

#ifndef __H_CCPPWNDMSG__
#define __H_CCPPWNDMSG__

#include <ICPPWNDMSG.hpp>

namespace __N_CPPWNDMSG__
{
	class CCPPWNDMSG : public ICPPWNDMSG
	{
	private:
		std::string	    m_strWindowClass{};
		std::string	    m_strWindowName{};

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
	};
} // !__N_CPPMSGWND__

#endif // !__H_CCPPWNDMSG__
