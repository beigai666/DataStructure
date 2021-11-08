#pragma once
#include "Exception.h"
namespace FinlayLib {
	class NoEnoughMemoryException : public Exception
	{
		NoEnoughMemoryException() :Exception(0) {}

		NoEnoughMemoryException(const char* message) :Exception(message) {}

		NoEnoughMemoryException(const char* file, int line) :Exception(file, line) {}

		NoEnoughMemoryException(const char* message, const char* file, int line) :Exception(message, file, line) {}

		NoEnoughMemoryException(const NoEnoughMemoryException& e) :Exception(e) {}

		NoEnoughMemoryException& operator= (const NoEnoughMemoryException& e)
		{
			Exception::operator=(e);
			return *this;
		}

	};
}