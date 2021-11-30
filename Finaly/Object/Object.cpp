#include "Object.h"
#include <cstdlib>

namespace FinlayLib {
	bool Object::operator==(const Object& object)
	{
		return (this==&object);
	}
	void* Object::operator new(size_t size) throw()
	{
		return malloc(size);
	}

	void Object::operator delete(void* p)
	{
		free(p);
	}

	void* Object::operator new[](size_t size) throw()
	{
		return malloc(size);
	}

		void Object::operator delete[](void* p)
	{
		free(p);
	}
}
