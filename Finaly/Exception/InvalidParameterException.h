#pragma once
#include "Exception.h"
namespace FinlayLib {
	class InvalidParameterException : public Exception
	{
		InvalidParameterException() :Exception(0) {}

		InvalidParameterException(const char* message) :Exception(message) {}

		InvalidParameterException(const char* file, int line) :Exception(file, line) {}

		InvalidParameterException(const char* message, const char* file, int line) :Exception(message, file, line) {}

		InvalidParameterException(const InvalidParameterException& e) :Exception(e) {}

		InvalidParameterException& operator= (const InvalidParameterException& e)
		{
			Exception::operator=(e);
			return *this;
		}

	};
}