#pragma once
#include "BSTree.h"
#include "RBTreeNode.h"
namespace FinlayLib {
	template <typename T>
	class RBTree : public BSTree<T>
	{
		//�ҵ���                                                                                                
		void RotateR(BTreeNode<T>* node)
		{
			BTreeNode<T>* nodeP = dynamic_cast<BTreeNode<T>*>(node->parent);
			BTreeNode<T>* nodeL = dynamic_cast<BTreeNode<T>*>(node->left);
			BTreeNode<T>* nodeLR = dynamic_cast<BTreeNode<T>*>(nodeL->right);

			//1 :�Ƚ��游�ڵ���nodeL����
			if (nodeP == NULL)
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
				else if (nodeP->right == node)
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
		}
		//����
		void RotateL(BTreeNode<T>* node)
		{
			BTreeNode<T>* nodeP = dynamic_cast<BTreeNode<T>*>(node->parent);
			BTreeNode<T>* nodeR = dynamic_cast<BTreeNode<T>*>(node->right);
			BTreeNode<T>* nodeRL = dynamic_cast<BTreeNode<T>*>(nodeR->left);
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
		}
		//����˫��
		void RotateLR(BTreeNode<T>* node)
		{
			BTreeNode<T>* pNode = node;
			BTreeNode<T>* nodeL = dynamic_cast<BTreeNode<T>*>(node->left);
			BTreeNode<T>* nodeLR = dynamic_cast<BTreeNode<T>*>(nodeL->right);
			RotateL(dynamic_cast<BTreeNode<T>*>(node->left));
			RotateR(node);
		}
		//����˫��
		void RotateRL(BTreeNode<T>* node)
		{
			BTreeNode<T>* pNode = node;
			BTreeNode<T>* nodeR = dynamic_cast<BTreeNode<T>*>(node->right);
			BTreeNode<T>* nodeRL = dynamic_cast<BTreeNode<T>*>(nodeR->left);
			RotateR(dynamic_cast<BTreeNode<T>*>(node->right));
			RotateL(node);
		}
		void RBTree_Delete_FixUp(RBTreeNode<T>* node) {
			RBTreeNode<T>* parent = NULL;
			RBTreeNode<T>* s_node = NULL;
			while (node !=this->m_root&& node->color==BLACK)
			{
				parent = dynamic_cast<BTreeNode<T>*>(node->parent);
				
				//��ǰ�ڵ�Ϊ���ڵ�����������ֵܽڵ���������
				if (node == parent->left)
				{
					s_node = dynamic_cast<BTreeNode<T>*>(parent->right);
				}
				//��ǰ�ڵ�Ϊ���ڵ�����������ֵܽڵ���������
				else if(node == parent->right)
				{
					s_node = dynamic_cast<BTreeNode<T>*>(parent->left);
				}
			}
			node->color = BLACK;
		}
		virtual BTreeNode<T>* DeleteNode(BTreeNode<T>* root, const T& var)
		{
			BTreeNode<T>* ret = NULL;
			if (root->value > var)
			{
				ret = DeleteNode(root->left, var);
			}
			else if (root->value < var)
			{
				ret = DeleteNode(root->right, var);
			}
			else if (root != NULL)
			{
				ret = root;
				if (root->right)
				{
					BTreeNode<T>* target = MinElement(root->right);
					DeleteNode(root->right, target->value);
					replace(root, target);

				}
				//���ں������������ǵ�ֻ��ֻ�����ӽڵ����ֻ�����ӽڵ㣬��ô�ӽڵ�һ���Ǻ�ɫ����ʱֻ��Ҫ���ֽڵĴ��浱ǰ�ڵ㣬�����ֽڵ���Ϊ��ɫ����
				else if (root->left) {
					
					RBTreeNode<T>* child = dynamic_cast<RBTreeNode<T>*>(root->left);
					replace(root, root->left);
					root->left = NULL;
					child->color = BLACK;
				}
				//����������ֽڵĵģ���Ϊ��ɫ�ڵ����ֱ��ɾ������Ϊ��ɫ����Ҫ�������˴�ȫ������RBTree_Delete_FixUp�������е���
				else
				{
					replace(root, NULL);
					RBTree_Delete_FixUp(dynamic_cast<RBTreeNode<T>*>(root));
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
			RBTreeNode<T>* cur = dynamic_cast<RBTreeNode<T>*>(n);
			ret = BSTree<T>::insert(cur, np);
			RBTreeNode<T>* parent = dynamic_cast<RBTreeNode<T>*>(cur->parent);
			RBTreeNode<T>* pparent = NULL;
			RBTreeNode<T>* uncle = NULL;
			while (parent !=NULL&&parent->color==RED)
			{
				pparent = dynamic_cast<RBTreeNode<T>*>(parent->parent);
				if (parent == pparent->left)
				{
					uncle = dynamic_cast<RBTreeNode<T>*>(pparent->right);
					if (uncle != NULL&&uncle->color == RED)
					{
						parent->color = BLACK;
						uncle->color = BLACK;
						pparent->color = RED;
						cur = pparent;
						parent = dynamic_cast<RBTreeNode<T>*>(cur->parent);
					}
					else
					{
						if (cur == parent->left)
						{
							RotateR(pparent);
							pparent->color = RED;
							parent->color = BLACK;
							cur->color = RED;
							
						}
						else
						{
							RotateLR(pparent);
							cur->color = BLACK;
							parent->color = RED;
							pparent->color = RED;
						}
						break;
					}
				}
				else
				{
					uncle = dynamic_cast<RBTreeNode<T>*>(pparent->left);
					if (uncle!=NULL&&uncle->color == RED)
					{
						parent->color = BLACK;
						uncle->color = BLACK;
						pparent->color = RED;
						cur = pparent;
						parent = dynamic_cast<RBTreeNode<T>*>(cur->parent);
					}
					else
					{
						if (cur == parent->left)
						{
							RotateRL(pparent);
							cur->color = BLACK;
							parent->color = RED;
							pparent->color = RED;
						}
						else
						{
							RotateL(pparent);
							pparent->color = RED;
							parent->color = BLACK;
							cur->color = RED;
						}
						break;
					}
				}
				
			}
			RBTreeNode<T>* root = dynamic_cast<RBTreeNode<T>*>(this->m_root);
			root->color = BLACK;
			return ret;
		}
	public:
		RBTree()
		{

		}
		~RBTree()
		{

		}
		virtual RBTreeNode<T>* root() const
		{
			return dynamic_cast<RBTreeNode<T>*> (this->m_root);
		}

		virtual bool insert(BTreeNode<T>* node)
		{
			bool ret = false;
			if (node != NULL)
			{
				if (this->m_root == NULL)
				{
					node->parent = NULL;
					this->m_root = node;
					RBTreeNode<T>* root = dynamic_cast<RBTreeNode<T>*>(this->m_root);
					root->color = BLACK;
					ret = true;
				}
				else
				{
					ret = insert(node, root());
				}
			}
			else
			{
				THROW_EXCEPTION(InvalidParameterException, "Parameter node can not be NULL");
			}
			return ret;
		}

		virtual bool insert(const T& value)
		{
			bool ret = false;
			RBTreeNode<T>* node = RBTreeNode<T>::NewNode();
			if (node == NULL)
			{
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to cretae new node ...");
			}
			else
			{
				node->value = value;
				ret = insert(node);
				if (!ret)
				{
					delete node;
				}
			}
			return ret;
		}

	};

}
