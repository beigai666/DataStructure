#include "BSTree.h"
#include "AVLTreeNode.h"
#define LH	 -1
#define EH	 0
#define RH   1
namespace FinlayLib
{
	template <typename T>
	class AVLTree : public BSTree<T>
	{
		bool shorter;

		//�ҵ���                                                                                                
		void RotateR(AVLTreeNode<T>* node)
		{
			AVLTreeNode<T>* nodeP = dynamic_cast<AVLTreeNode<T>*>(node->parent);
			AVLTreeNode<T>* nodeL = dynamic_cast<AVLTreeNode<T>*>(node->left);
			//AVLTreeNode<T>* nodeR = dynamic_cast<AVLTreeNode<T>*>(node->right);
			AVLTreeNode<T>* nodeLR = dynamic_cast<AVLTreeNode<T>*>(nodeL->right);

			//1 :�Ƚ��游�ڵ���nodeL����
			if (nodeP==NULL)
			{
				nodeL->parent = NULL;
				this->m_root = nodeL;
			}
			else
			{
				nodeL->parent = nodeP;
				if (nodeP->left == node)
				{
					nodeP->left = nodeL;
				}
				else if(nodeP->right == node)
				{
					nodeP->right = nodeL;
				}
			}
			//2������nodeL��������node��nodeL����
			nodeL->right = node;
			node->parent = nodeL;
			//3������node������������nodeLR��node����
			node->left = nodeLR;
			if (nodeLR) {
				nodeLR->parent = node;
			}
			//4������ƽ������
			node->bf = 0;
			nodeL->bf = 0;
		}
		//����
		void RotateL(AVLTreeNode<T>* node)
		{
			AVLTreeNode<T>* nodeP = dynamic_cast<AVLTreeNode<T>*>(node->parent);
			AVLTreeNode<T>* nodeL = dynamic_cast<AVLTreeNode<T>*>(node->left);
			AVLTreeNode<T>* nodeR = dynamic_cast<AVLTreeNode<T>*>(node->right);
			AVLTreeNode<T>* nodeRL = dynamic_cast<AVLTreeNode<T>*>(nodeR->left);
			//1 :�Ƚ��游�ڵ���nodeR����
			if (nodeP == NULL)
			{
				nodeR->parent = NULL;
				this->m_root = nodeR;
			}
			else
			{
				nodeR->parent = nodeP;
				if (nodeP->left == node)
				{
					nodeP->left = nodeR;
				}
				else if (nodeP->right == node)
				{
					nodeP->right = nodeR;
				}
			}
			//2������nodeR��������node��nodeR����
			nodeR->left = node;
			node->parent = nodeR;
			//3������node������������nodeRL��node����
			node->right = nodeRL;
			if (nodeRL) {
				nodeRL->parent = node;
			}
			//4������ƽ������
			node->bf = 0;
			nodeR->bf = 0;
		}
		//����˫��
		void RotateLR(AVLTreeNode<T>* node)
		{
			AVLTreeNode<T>* pNode = node;
			AVLTreeNode<T>* nodeL = dynamic_cast<AVLTreeNode<T>*>(node->left);
			AVLTreeNode<T>* nodeLR = dynamic_cast<AVLTreeNode<T>*>(nodeL->right);
			int bf = nodeLR->bf;
			RotateL(dynamic_cast<AVLTreeNode<T>*>(node->left));
			RotateR(node);
			if (bf == 1)
			{
				pNode->bf = 0;
				nodeL->bf = -1;
			}
			else if(bf == -1)
			{
				pNode->bf = 1;
				nodeL->bf = 0;
			}
			else
			{
				pNode->bf = 0;
				nodeL->bf = 0;
			}
		}
		//����˫��
		void RotateRL(AVLTreeNode<T>* node)
		{
			AVLTreeNode<T>* pNode = node;
			AVLTreeNode<T>* nodeR = dynamic_cast<AVLTreeNode<T>*>(node->right);
			AVLTreeNode<T>* nodeRL = dynamic_cast<AVLTreeNode<T>*>(nodeR->left);
			int bf = nodeRL->bf;
			RotateR(dynamic_cast<AVLTreeNode<T>*>(node->right));
			RotateL(node);
			if (bf == 1)
			{
				pNode->bf = -1;
				nodeR->bf = 0;
			}
			else if (bf == -1)
			{
				pNode->bf = 0;
				nodeR->bf = 1;
			}
			else
			{
				pNode->bf = 0;
				nodeR->bf = 0;
			}
		}

		void replace(AVLTreeNode<T>* node, AVLTreeNode<T>* target)
		{
			BSTree<T>::replace(node, target);
			if (target) {
				target->bf = node->bf;
			}
		}
		

		virtual AVLTreeNode<T>* DeleteNode(BTreeNode<T>* node,const T& var)
		{
			AVLTreeNode<T>* root = dynamic_cast<AVLTreeNode<T>*>(node);
			AVLTreeNode<T>* ret= NULL;
			if (root->value > var)
			{
				ret = DeleteNode(root->left, var);
				if (shorter)
				{
					switch (root->bf)
					{
						//ԭ����ߣ�bf==-1��������������1������ƽ��
					case LH:
						root->bf=0; shorter = true;
						break;
						//ԭ���ȸߣ�bf==0,������������1 ������bf==1
					case EH:
						root->bf = 1; shorter = false;
						break;
						//ԭ���Ҹߣ�bf==1��������������1����������
					case RH:
						RotateL(root); shorter = true;
						break;

					default:
						break;
					}
				}
			}
			else if(root->value < var)
			{
				ret = DeleteNode(root->right, var);
				if (shorter)
				{
					switch (root->bf)
					{
						//ԭ����ߣ�bf==-1��������������1��������Ҫ����������ƽ��
					case LH:
						RotateR(root); shorter = true;
						break;
						//ԭ���ȸߣ�bf==0,������������1 ������bf==-1
					case EH:
						root->bf = -1; shorter = false;
						break;
						//ԭ���Ҹߣ�bf==1��������������1������ƽ��
					case RH:
						root->bf = 0; shorter = true;
						break;

					default:
						break;
					}
				}
			}
			else if(root!=NULL)
			{
				ret = dynamic_cast<AVLTreeNode<T>*>(root);
				if (root->right)
				{
					AVLTreeNode<T>* target = dynamic_cast<AVLTreeNode<T>*>(BSTree<T>::MinElement(root->right));
					DeleteNode(root->right, target->value);
					replace(dynamic_cast<AVLTreeNode<T>*>(root),target);
					root = target;
					if (shorter)
					{
						switch (root->bf)
						{
							//ԭ����ߣ�bf==-1��������������1��������Ҫ����������ƽ��
						case LH:
							RotateR(root); shorter = true;
							break;
							//ԭ���ȸߣ�bf==0,������������1 ������bf==-1
						case EH:
							root->bf = -1; shorter = false;
							break;
							//ԭ���Ҹߣ�bf==1��������������1������ƽ��
						case RH:
							root->bf = 0; shorter = true;
							break;
						
						default:
							break;
						}
					}

				}
				else if(root->left)
				{
					replace(dynamic_cast<AVLTreeNode<T>*>(root), dynamic_cast<AVLTreeNode<T>*>(root->left));
					root->left = NULL;
					shorter = true;
				}
				else
				{
					replace(dynamic_cast<AVLTreeNode<T>*>(root), NULL);
					shorter = true;
				}
			}
			else
			{
				ret = NULL;
			}
			return ret;
		}


		virtual bool insert(BTreeNode<T>* n, BTreeNode<T>* np)
		{
			bool ret = false;
			AVLTreeNode<T>* cur = dynamic_cast<AVLTreeNode<T>*>(n);
			ret = BSTree<T>::insert(cur, np);
			AVLTreeNode<T>* parent = dynamic_cast<AVLTreeNode<T>*>(cur->parent);
			while (parent)
			{
				if (cur == parent->left)
				{
					parent->bf--;
				}
				else if(cur == parent->right)
				{
					parent->bf++;
				}
				if (parent->bf == 0)
				{
					break;
				}
				else if(parent->bf == -1 || parent->bf==1)
				{
					cur = parent;
					parent = dynamic_cast<AVLTreeNode<T>*>(parent->parent);
				}
				else
				{
					if (parent->bf == 2)
					{
						if (cur->bf == 1)
						{
							RotateL(parent);
						}
						else
						{
							RotateLR(parent);
						}
					}
					else if(parent->bf == -2)
					{
						if (cur->bf == -1)
						{
							RotateR(parent);
						}
						else
						{
							RotateRL(parent);
						}
					}
					break;
				}
			}
			return ret;
		}
	public:
		AVLTree()
		{
			shorter = false;
		}
		~AVLTree()
		{

		}
		virtual AVLTreeNode<T>* root() const
		{
			return dynamic_cast<AVLTreeNode<T>*> (this->m_root);
		}
		virtual bool insert(const T& value)
		{
			bool ret = false;
			AVLTreeNode<T>* node = AVLTreeNode<T>::NewNode();
			if (node == NULL)
			{
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to cretae new node ...");
			}
			else
			{
				node->value = value;
				ret = BSTree<T>::insert(node);
				if (!ret)
				{
					delete node;
				}
			}
			return ret;
		}
		/*
		virtual bool DeleteNode(const T& value)
		{
			bool ret = false;
			AVLTreeNode<T>* node= DeleteNode(root(), value);
			if (node)
			{
				ret = true;
				this->free(node);
			}
			return ret;
		}
		*/
	};
}