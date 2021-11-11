#pragma once
#include "Exception.h"
namespace FinlayLib {
	class NullPointerException : public Exception
	{
	public:
		NullPointerException() :Exception(0) {}

		NullPointerException(const char* message) :Exception(message) {}

		NullPointerException(const char* file, int line) :Exception(file, line) {}

		NullPointerException(const char* message, const char* file, int line) :Exception(message, file, line) {}

		NullPointerException(const NullPointerException& e) :Exception(e) {}

		NullPointerException& operator= (const NullPointerException& e)
		{
			Exception::operator=(e);
			return *this;
		}

	};
}