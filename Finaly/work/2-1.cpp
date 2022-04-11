#include <Stack/LinkStack.h>
#include <iostream>
#include <Sort/ListSort.h>
using namespace FinlayLib;
using namespace std;

void MergeToStack(Stack<int>& stack, Node* prev)
{
    Node* slider = prev;

    while (slider->prev)
    {
        slider = slider->prev;
    }

    slider = ListMergeSort(slider);

    while (slider->next)
    {
        slider = slider->next;
    }

    while (slider)
    {
        stack.push(slider->value);
        slider = slider->prev;
    }
}

void StackSort2(Stack<int>& stack, Node* prev)
{
    if (stack.size())
    {
        Node node(stack.top());

        node.prev = prev;

        if (prev)
        {
            prev->next = &node;
        }

        stack.pop();

        StackSort2(stack, &node);
    }
    else if (prev)
    {
        // select max to push to stack
        /*
        Node* node =SelectToStack(prev);
        ListMergeSort(prev);
        while (node)
        {
            stack.push(node->value);
            node = node->prev;
        }
        */
        MergeToStack(stack, prev);
    }
}

void StackSort()
{
    int a[] = { 8, 3, 2, 1, 5, 6, 7, 0, 4, 9 };
    int len = sizeof(a) / sizeof(*a);
    LinkStack<int> stack;

    for (int i = 0; i < len; i++)
    {
        stack.push(a[i]);
    }

    // StackSort1(stack);
    StackSort2(stack, NULL);

    while (stack.size())
    {
        cout << stack.top() << " ";
        stack.pop();
    }

    cout << endl;
}