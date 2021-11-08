#pragma once
#include "stdio.h"
#include <Object.h>
namespace FinlayLib {
	class Counter : public Object
	{
	public:
		Counter();
		~Counter();
		int share_count;
		int weak_count;
	private:

	};

	Counter::Counter() :share_count(0), weak_count(0)
	{
		printf("create Counter\n");
	}

	Counter::~Counter()
	{
		printf("delete Counter\n");
	}

}