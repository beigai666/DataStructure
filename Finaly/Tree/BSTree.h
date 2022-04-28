#pragma once
#include "Tree.h"
#include <Queue/LinkQueue.h>
#include <Array/DynamicArray.h>
#include "BTreeNode.h"
namespace FinlayLib
{
	enum BTTraversal
	{
		PreOrder,
		InOrder,
		PostOrder,
		LevelOrder
	};
	template<typename T>
	class BSTree
	{
	protected:
		BTreeNode<T>* m_root;
		virtual BTreeNode<T>* find(BTreeNode<T>* node, const T& value)const
		{
			
			BTreeNode<T>* ret = NULL;
			if (node != NULL)
			{
				if (node->value == value)
				{
					ret = node;
				}
				else
				{
					if (ret == NULL && node->value > value)
					{
						ret = find(node->left, value);
					}
					else if(ret == NULL && node->value < value)
					{
						ret = find(node->right, value);
					}
				}
			}
			return ret;
		}

		virtual BTreeNode<T>* find(BTreeNode<T>* node, const TreeNode<T>* obj)const
		{
			BTreeNode<T>* ret = NULL;
			if (node != NULL)
			{
				if (node == obj)
				{
					ret = node;
				}
				else
				{
					if (ret == NULL && node->value > obj->value)
					{
						ret = find(node->left, obj);
					}
					else if (ret == NULL && node->value < obj->value)
					{
						ret = find(node->right, obj);
					}
				}
			}
			return ret;
		}
		/*Ñ°ÕÒ×îÐ¡ÔªËØ*/
		BTreeNode<T>* MinElement(BTreeNode<T>* node)
		{
			if (node->left)
				return MinElement(node->left);
			else
				return node;
		}
		void replace(BTreeNode<T>* node, BTreeNode<T>* target)
		{
			BTreeNode<T>* node_parent = dynamic_cast<BTreeNode<T>*>(node->parent);
			if (node_parent != NULL) {
				if (node_parent->left == node)
				{
					node_parent->left = target;
				}
				else if (node_parent->right == node)
				{
					node_parent->right = target;
				}
			}
			else
			{
				this->m_root = target;
			}
			if (target) {
				target->parent = node_parent;
				target->left = node->left;
				target->right = node->right;
			}
			node->left = NULL;
			node->right = NULL;
			node->parent = NULL;
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
					BTreeNode<T>* target =MinElement(root->right);
					DeleteNode(root->right, target->value);
					replace(root, target);

				}
				else if (root->left)
				{
					replace(root, root->left);
					root->left = NULL;
				}
				else
				{
					replace(root, NULL);
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
			if (n != NULL && np != NULL)
			{
				if (np->value > n->value)
				{
					if (np->left != NULL)
					{
						ret = BSTree<T>::insert(n, np->left);
					}
					else
					{
						np->left = n;
						n->parent = np;
						ret = true;
					}
				}
				else
				{
					if (np->right != NULL)
					{
						ret = BSTree<T>::insert(n, np->right);
					}
					else
					{
						np->right = n;
						n->parent = np;
						ret = true;
					}
				}
			}
			return ret;
		}
		virtual void free(BTreeNode<T>* node)
		{
			if (node != NULL)
			{
				free(node->left);
				free(node->right);
				if (node->flag())
				{
					delete node;
				}
			}
		}
		virtual int degree(BTreeNode<T>* node)const {
			int ret = 0;

			if (node != NULL)
			{
				BTreeNode<T>* child[] = { node->left, node->right };

				ret = (!!node->left + !!node->right);

				for (int i = 0; (i < 2) && (ret < 2); i++)
				{
					int d = degree(child[i]);

					if (ret < d)
					{
						ret = d;
					}
				}
			}
			return ret;
		}
		virtual int count(BTreeNode<T>* node)const {
			return (node != NULL) ? (count(node->left) + count(node->right) + 1) : 0;
		}
		virtual int height(BTreeNode<T>* node) const {
			int ret = 0;

			if (node != NULL)
			{
				int lh = height(node->left);
				int rh = height(node->right);

				ret = ((lh > rh) ? lh : rh) + 1;
			}

			return ret;
		}

		void preOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
		{
			if (node != NULL)
			{
				queue.add(node);
				preOrderTraversal(node->left, queue);
				preOrderTraversal(node->right, queue);
			}
		}

		void inOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
		{
			if (node != NULL)
			{
				inOrderTraversal(node->left, queue);
				queue.add(node);
				inOrderTraversal(node->right, queue);
			}
		}

		void postOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
		{
			if (node != NULL)
			{
				postOrderTraversal(node->left, queue);
				postOrderTraversal(node->right, queue);
				queue.add(node);
			}
		}

		void levelOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
		{
			if (node != NULL)
			{
				LinkQueue<BTreeNode<T>*> tmp;

				tmp.add(node);

				while (tmp.length() > 0)
				{
					BTreeNode<T>* n = tmp.front();

					if (n->left != NULL)
					{
						tmp.add(n->left);
					}

					if (n->right != NULL)
					{
						tmp.add(n->right);
					}

					tmp.remove();
					queue.add(n);
				}
			}
		}

		void traversal(BTTraversal order, LinkQueue<BTreeNode<T>*>& queue)
		{
			switch (order)
			{
			case PreOrder:
				preOrderTraversal(root(), queue);
				break;
			case InOrder:
				inOrderTraversal(root(), queue);
				break;
			case PostOrder:
				postOrderTraversal(root(), queue);
				break;
			case LevelOrder:
				levelOrderTraversal(root(), queue);
				break;
			default:
				THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");
				break;
			}
		}

		public:

			BSTree()
			{
				m_root = NULL;
			}

			~BSTree()
			{
				clear();
			}

			virtual bool insert(const T& value)
			{
				bool ret = false;
				BTreeNode<T>* node = BTreeNode<T>::NewNode();
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
			virtual bool remove(const T& value)
			{
				bool ret = false;
				BTreeNode<T>* node = DeleteNode(root(), value);
				if (node)
				{
					ret = true;
					this->free(node);
				}
				return ret;
			}
			virtual BTreeNode<T>* root() const
			{
				return this->m_root;
			}
			virtual int degree()const
			{
				BTreeNode<T>* node = root();
				return degree(node);
			}
			virtual int count()const
			{
				BTreeNode<T>* node = root();
				return count(node);
			}
			virtual int height() const
			{
				BTreeNode<T>* node = root();
				return height(node);
			}
			virtual void clear()
			{
				free(root());
				this->m_root = NULL;
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
			virtual BTreeNode<T>* find(const T& value)const
			{
				return find(root(), value);
			}
			

			virtual BTreeNode<T>* find(BTreeNode<T>* node) const
			{
				return find(root(), node);
			}

			SharedPointer< Array<T> > traversal(BTTraversal order)
			{
				DynamicArray<T>* ret = NULL;
				LinkQueue<BTreeNode<T>*> queue;

				traversal(order, queue);

				ret = new DynamicArray<T>(queue.length());

				if (ret != NULL)
				{
					for (int i = 0; i < ret->length(); i++, queue.remove())
					{
						ret->set(i, queue.front()->value);
					}
				}
				else
				{
					THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create return array ...");
				}

				return ret;
			}
	};

}