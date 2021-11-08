#pragma once

namespace FinlayLib {

	class Object
	{
		void* operator new (size_t size) throw();
		void operator delete(void* p);

		void* operator new[](size_t size)throw();

		void operator delete[](void* p);

	};

}


