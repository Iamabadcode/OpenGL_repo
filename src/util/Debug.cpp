#include <iostream>
#include "Debug.h"

bool Debug::m_Active = false;

void Debug::activate()
{
	m_Active = true;
}

void Debug::Log(std::string message, log_type type)
{
	if (!m_Active) return;
	switch (type)
	{
	case INFO:
		std::cout << "> " << message << std::endl; return;
	case DEBUG: 
		std::cout << "[DEBUG] : " << message << std::endl; return;
	case WARNING:
		std::cout << "[WARNING] : " << message << std::endl; return;
	case ERROR:
		std::cout << "[ERROR] : " << message << std::endl; return;
	default:
		return;
	}
}
void Debug::Log(std::string message)
{
	std::cout << message;
}
