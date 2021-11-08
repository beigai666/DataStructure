#pragma once
#include "Exception.h"
namespace FinlayLib {
	class IndexOutOfBoundsException : public Exception
	{
		IndexOutOfBoundsException() :Exception(0) {}

		IndexOutOfBoundsException(const char* message) :Exception(message) {}

		IndexOutOfBoundsException(const char* file, int line) :Exception(file, line) {}

		IndexOutOfBoundsException(const char* message, const char* file, int line) :Exception(message, file, line) {}

		IndexOutOfBoundsException(const IndexOutOfBoundsException& e) :Exception(e) {}

		IndexOutOfBoundsException& operator= (const IndexOutOfBoundsException& e)
		{
			Exception::operator=(e);
			return *this;
		}

	};
}