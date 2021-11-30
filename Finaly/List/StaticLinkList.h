#pragma once
#include"LinkList.h"
namespace FinlayLib {
	template<typename T, int N>
	class StaticLinkList : public LinkList<T> 
	{
	protected:
		typedef typename LinkList<T>::Node Node;

		struct SNode : public Node
		{
			void* operator new(size_t size, void* loc) {
				return loc;
			}
		};

		unsigned char m_space[sizeof(SNode) * N];
		char m_used[N];

		Node* create() {
			Node* ret = NULL;
			for (size_t i = 0; i < N; i++)
			{
				if (!m_used[i]) {
					ret = reinterpret_cast<SNode*>(m_space)+i;
					ret = new(ret)SNode();
					m_used[i] = 1;
					break;
				}
			}
			return ret;
		}

		virtual void destory(Node* pn) {
			SNode* space = reinterpret_cast<SNode*>(m_space);
			SNode* psn = dynamic_cast<SNode*>(pn);
			for (size_t i = 0; i < N; i++)
			{
				if (psn == (space+i)) {
					m_used[i] = 0;
					psn->~SNode();
					break;
				}
			}
		}

	public:
		StaticLinkList() {
			memset(m_used, 0, N);
		}
		~StaticLinkList() {
			this->clear();
		}
		int capacity() {
			return N;
		}
	private:

	};


}