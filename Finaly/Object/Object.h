#pragma once
#include <stdlib.h>
namespace FinlayLib {

	class Object
	{
	public:
		

		virtual ~Object()
		{

		}
		bool operator ==(const Object& object);
		void* operator new (size_t size) throw();
		void operator delete(void* p);

		void* operator new[](size_t size)throw();

		void operator delete[](void* p);

	};

}


