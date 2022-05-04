#pragma once
#ifndef NULL
	#ifdef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void *)0)
	#endif
#endif
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


