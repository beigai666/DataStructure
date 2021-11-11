#pragma once
#include "Exception.h"
namespace FinlayLib{
	class InvalidOperationException : public Exception 
	{
	public:
		InvalidOperationException():Exception(0){}

		InvalidOperationException(const char* message):Exception(message){}

		InvalidOperationException(const char* file,int line):Exception(file,line){}

		InvalidOperationException(const char* message,const char* file,int line):Exception(message,file,line){}

		InvalidOperationException(const InvalidOperationException& e):Exception(e){}

		InvalidOperationException& operator= (const InvalidOperationException& e)
		{
			Exception::operator=(e);
			return *this;
		}

	};
}
