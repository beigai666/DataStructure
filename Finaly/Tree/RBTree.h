#pragma once
#include "BSTree.h"
#include "RBTreeNode.h"
namespace FinlayLib {
	template <typename T>
	class RBTree : public BSTree<T>
	{
		//右单旋                                                                                                
		void RotateR(BTreeNode<T>* node)
		{
			BTreeNode<T>* nodeP = dynamic_cast<BTreeNode<T>*>(node->parent);
			BTreeNode<T>* nodeL = dynamic_cast<BTreeNode<T>*>(node->left);
			BTreeNode<T>* nodeLR = dynamic_cast<BTreeNode<T>*>(nodeL->right);

			//1 :先将祖父节点与nodeL连接
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
			//2：构建nodeL子树，将node与nodeL连接
			nodeL->right = node;
			node->parent = nodeL;
			//3：构建node的左子树，将nodeLR与node连接
			node->left = nodeLR;
			if (nodeLR) {
				nodeLR->parent = node;
			}
		}
		//左单旋
		void RotateL(BTreeNode<T>* node)
		{
			BTreeNode<T>* nodeP = dynamic_cast<BTreeNode<T>*>(node->parent);
			BTreeNode<T>* nodeR = dynamic_cast<BTreeNode<T>*>(node->right);
			BTreeNode<T>* nodeRL = dynamic_cast<BTreeNode<T>*>(nodeR->left);
			//1 :先将祖父节点与nodeR连接
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
			//2：构建nodeR子树，将node与nodeR连接
			nodeR->left = node;
			node->parent = nodeR;
			//3：构建node的右子树，将nodeRL与node连接
			node->right = nodeRL;
			if (nodeRL) {
				nodeRL->parent = node;
			}
		}
		//左右双旋
		void RotateLR(BTreeNode<T>* node)
		{
			BTreeNode<T>* pNode = node;
			BTreeNode<T>* nodeL = dynamic_cast<BTreeNode<T>*>(node->left);
			BTreeNode<T>* nodeLR = dynamic_cast<BTreeNode<T>*>(nodeL->right);
			RotateL(dynamic_cast<BTreeNode<T>*>(node->left));
			RotateR(node);
		}
		//右左双旋
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
			RBTreeNode<T>* s_l = NULL;
			RBTreeNode<T>* s_r = NULL;
			//进入循环的一定是叶子节点为黑色的这种情况
			while (node !=this->m_root&& node->color==BLACK)
			{
				parent = dynamic_cast<RBTreeNode<T>*>(node->parent);
				
				//当前节点为父节点的左子树，兄弟节点在右子树
				if (node == parent->left)
				{
					s_node = dynamic_cast<RBTreeNode<T>*>(parent->right);
					//第一种情况：兄节点为红色
					if (s_node->color == RED)
					{
						s_node->color = BLACK;
						parent->color = RED;
						RotateL(parent);
						parent = dynamic_cast<RBTreeNode<T>*>(node->parent);
						s_node = dynamic_cast<RBTreeNode<T>*>(parent->right);
					}
					s_l = dynamic_cast<RBTreeNode<T>*>(s_node->left);
					s_r = dynamic_cast<RBTreeNode<T>*>(s_node->right);
					/*
					// 第二种情况：兄黑，子全黑
					// 处理方式，兄涂红色，node指向父结点，下次while循环，如果父为红色，结束循环，
					// 循环跳出后会设置父结点为黑。如果父为黑色，此时就需要
					// 递归向上处理，以parent为n，再找其兄弟结点，通过局部平衡达到全局平衡。
					// s->color == BLACK判断并没有多大意义，因为第一种情况被处理后兄结点为黑，其他情况兄结点一定为黑，所以说判断可加可不加

					*/

					if (s_node->color == BLACK &&(((s_l == NULL) || s_l->color == BLACK) && (s_r==NULL|| s_r->color == BLACK)))
					{
						s_node->color = RED;
						node = dynamic_cast<RBTreeNode<T>*>(node->parent);
						parent = dynamic_cast<RBTreeNode<T>*>(node->parent);
					}
					/*
					*
					第三种情况:兄黑，兄在右子树，兄的左孩子红色
					*/
					if ((s_r == NULL || s_r->color == BLACK) &&(s_l!=NULL&& s_l->color == RED))
					{
						s_node->color = RED;
						s_l->color = BLACK;
						RotateR(s_node);
						parent = dynamic_cast<RBTreeNode<T>*>(node->parent);
						s_node = dynamic_cast<RBTreeNode<T>*>(parent->right);
						s_l = dynamic_cast<RBTreeNode<T>*>(s_node->left);
						s_r = dynamic_cast<RBTreeNode<T>*>(s_node->right);
						//一环接一环，处理后s变为情况4
						//转为情况4处理
					}
					//第四种情况:兄黑，兄弟节点在右子树，右孩子为红色
					if (s_r!=NULL && s_r->color==RED)
					{
						s_node->color = parent->color;
						parent->color = BLACK;
						s_r->color = BLACK;
						RotateL(parent);
						node = dynamic_cast<RBTreeNode<T>*>(this->m_root);
					}
				}
				//当前节点为父节点的右子树，兄弟节点在左子树
				else if(node == parent->right)
				{
					s_node = dynamic_cast<RBTreeNode<T>*>(parent->left);
					//第一种情况：兄节点为红色
					if (s_node->color == RED)
					{
						s_node->color = BLACK;
						parent->color = RED;
						RotateR(parent);
						parent = dynamic_cast<RBTreeNode<T>*>(node->parent);
						s_node = dynamic_cast<RBTreeNode<T>*>(parent->left);
					}
					s_l = dynamic_cast<RBTreeNode<T>*>(s_node->left);
					s_r = dynamic_cast<RBTreeNode<T>*>(s_node->right);
					/*
					// 第二种情况：兄黑，子全黑
					// 处理方式，兄涂红色，node指向父结点，下次while循环，如果父为红色，结束循环，
					// 循环跳出后会设置父结点为黑。如果父为黑色，此时就需要
					// 递归向上处理，以parent为n，再找其兄弟结点，通过局部平衡达到全局平衡。
					// s->color == BLACK判断并没有多大意义，因为第一种情况被处理后兄结点为黑，其他情况兄结点一定为黑，所以说判断可加可不加

					*/

					if (s_node->color == BLACK && ((s_l == NULL) || s_l->color == BLACK) && (s_r == NULL || s_r->color == BLACK))
					{
						s_node->color = RED;
						node = dynamic_cast<RBTreeNode<T>*>(node->parent);
						parent = dynamic_cast<RBTreeNode<T>*>(node->parent);
					}
					/*
					*
					第三种情况:兄黑，兄在左子树，兄的右孩子红色
					*/
					if (((s_l == NULL) || s_l->color == BLACK) &&(s_r!=NULL &&s_r->color == RED))
					{
						s_node->color = RED;
						s_r->color = BLACK;
						RotateL(s_node);
						parent = dynamic_cast<RBTreeNode<T>*>(node->parent);
						s_node = dynamic_cast<RBTreeNode<T>*>(parent->right);
						s_l = dynamic_cast<RBTreeNode<T>*>(s_node->left);
						s_r = dynamic_cast<RBTreeNode<T>*>(s_node->right);
						//一环接一环，处理后s变为情况4
						//转为情况4处理
					}
					//第四种情况:兄黑，兄弟节点在右子树，右孩子为红色
					if (s_l != NULL && s_l->color == RED)
					{
						s_node->color = parent->color;
						parent->color = BLACK;
						s_l->color = BLACK;
						RotateR(parent);
						node = dynamic_cast<RBTreeNode<T>*>(this->m_root);
					}
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
					BTreeNode<T>* target = BSTree<T>::MinElement(root->right);
					DeleteNode(root->right, target->value);
					BSTree<T>::replace(root, target);

				}
				//对于红黑树，如果有是单只，只有左子节点或者只有右子节点，那么子节点一定是红色，此时只需要将字节的代替当前节点，并将字节的设为黑色即可
				else if (root->left) {
					
					RBTreeNode<T>* child = dynamic_cast<RBTreeNode<T>*>(root->left);
					BSTree<T>::replace(root, root->left);
					root->left = NULL;
					child->color = BLACK;
				}
				//对于无如何字节的的，若为红色节点可以直接删除，若为黑色则需要调整，此处全部调用RBTree_Delete_FixUp函数进行调整
				else
				{
					RBTree_Delete_FixUp(dynamic_cast<RBTreeNode<T>*>(root));
					BSTree<T>::replace(root, NULL);
					
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
