#pragma once
#include <string>
#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak();
#define DEBUG_CALL_ERROR(x) Debug::Log(std::string(__FILE__) + " (" + std::to_string(__LINE__) + ") : " + x, Debug::ERROR);

class Debug
{
private:
	static bool m_Active;
public:
	~Debug();
	enum log_type {
		INFO, DEBUG, WARNING, ERROR
	};

	static void activate();

	static void Log(std::string message, log_type);
	static void Log(std::string message);

};