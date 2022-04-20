#include <Queue/LinkQueue.h>
#include <Array/DynamicArray.h>
#include <Stack/LinkStack.h>
#include <iostream>
using namespace FinlayLib;
using namespace std;


int MinStack(LinkStack<int> pStack[], int len)  // O(k)
{
    int min = 0xFFFF;
    int ret = -1;

    for (int i = 0; (i < len) && pStack; i++)
    {
        if (pStack[i].size() && (pStack[i].top() < min))
        {
            min = pStack[i].top();
            ret = i;
        }
    }

    return ret;
}

int EnterStack(LinkStack<int> pStack[], int len, int total, int index) // O(k)
{
    int ret = -1;
    int min = 0xFFFF;

    for (int i = 0; pStack && (i < len); i++)
    {
        if (pStack[i].size())
        {
            if ((index < pStack[i].top()) && (pStack[i].top() < min))
            {
                min = pStack[i].top();
                ret = i;
            }
        }
        else if (ret == -1)
        {
            ret = i;
        }
    }

    if ((ret == -1) && (len < total))
    {
        ret = len;
    }

    if (ret != -1)
    {
        cout << index << " enter into stack[" << ret << "]." << endl;
        pStack[ret].push(index);
    }

    return ret;
}

void StackToExit(LinkStack<int> pStack[], int len, Queue<int>& result) // O(k*k)
{
    int min = 0xFFFF;
    int msi = 0;

    while ((msi != -1) && pStack)
    {
        min = 0xFFFF;
        msi = -1;

        for (int i = 0; i < len; i++)
        {
            if (pStack[i].size() && (pStack[i].top() < min))
            {
                min = pStack[i].top();
                msi = i;
            }
        }

        if (msi != -1)
        {
            int index = pStack[msi].top();

            cout << index << " from stack[" << msi << "] to exit." << endl;

            result.add(index);

            pStack[msi].pop();
        }
    }
}

bool Rearrange(Array<int>& num, Queue<int>& result)  // O(n*k)
{
    LinkStack<int>* pStack = new LinkStack<int>[num.length()];  // O(n)
    int current = 1;
    int minTop = 0xFFFF;
    int minStack = num.length();
    int slen = 0;

    for (int i = 0; pStack && (i < num.length()); i++)
    {
        if (num[i] == current)
        {
            cout << num[i] << " from entry to exit." << endl;

            result.add(current++);

            while (minTop == current)
            {
                cout << minTop << " from stack[" << minStack << "] to exit." << endl;

                result.add(current++);

                pStack[minStack].pop();

                minStack = MinStack(pStack, slen);

                if (minStack != -1)
                {
                    minTop = pStack[minStack].top();
                }
            }
        }
        else
        {
            int obj = EnterStack(pStack, slen, num.length(), num[i]);

            slen = (obj < slen) ? slen : (obj + 1);

            if (minTop > pStack[obj].top())
            {
                minTop = pStack[obj].top();
                minStack = obj;
            }
        }
    }

    StackToExit(pStack, slen, result);

    delete[] pStack;

    return pStack;
}

bool Rearrange(Queue<int>& queue)
{
    bool ret = true;
    DynamicArray<int> num(queue.length());

    for (int i = 0; i < num.length(); i++)
    {
        num[i] = queue.front();

        queue.remove();
    }

    Rearrange(num, queue);

    return ret;
}

void Rearrange()
{
    int a[] = { 3, 6, 9, 2, 4, 7, 1, 8, 5 };
    int len = sizeof(a) / sizeof(*a);
    LinkQueue<int> queue;

    for (int i = 0; i < len; i++)
    {
        queue.add(a[i]);
    }

    if (Rearrange(queue))
    {
        cout << "finish rearrangement: " << endl;

        while (queue.length())
        {
            cout << queue.front() << " ";
            queue.remove();
        }

        cout << endl;
    }

}