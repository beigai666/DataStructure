#pragma once
#include "Exception.h"
namespace FinlayLib {
	class ArithmeticException : public Exception
	{
		ArithmeticException() :Exception(0) {}

		ArithmeticException(const char* message) :Exception(message) {}

		ArithmeticException(const char* file, int line) :Exception(file, line) {}

		ArithmeticException(const char* message, const char* file, int line) :Exception(message, file, line) {}

		ArithmeticException(const ArithmeticException& e) :Exception(e) {}

		ArithmeticException& operator= (const ArithmeticException& e)
		{
			Exception::operator=(e);
			return *this;
		}

	};
}