#pragma once
#include <stdint.h>
#include <Object/Object.h>
using namespace FinlayLib;

struct Node : public Object
{
    int value;
    Node* next;
    Node* prev;

    Node(int v = 0)
    {
        value = v;
        next = NULL;
        prev = NULL;
    }
};

Node* SelectToStack(Node* prev)
{
    Node head;
    head.prev = prev;
    prev->next = &head;
    Node* ret = NULL;
    
    while (head.prev)
    {
        Node* slider = head.prev;
        Node* max = slider;
        while (slider)
        {
            if (max->value < slider->value)
            {
                max = slider;
            }
            slider = slider->prev;
        }
        Node* prev = max->prev;
        Node* next = max->next;
        if (prev) prev->next = next;
        if (next) next->prev = prev;
        max->prev = ret;
        if (ret)
        {
            ret->next = max;
        }
        ret = max;
    }
    return ret;
}
/*
*   将链表拆分为左子链表和右子链表
*/
void ListSplit(Node* list, Node*& left, Node*& right)
{
    if (list)
    {
        Node* p1 = list;
        Node* p2 = list;
        while (p2)
        {
            p2 = p2->next;
            p2 = p2 ? (p1 = p1->next, p2->next) : NULL;
        }
        left = list;
        right = p1;
        p1 = p1->prev;
        if (p1) p1->next = NULL;
        if (right) right->prev = NULL;
    }
}
void MergeStep(Node*& slider, Node*& node)
{
    slider->next = node;
    node->prev = slider;
    slider = slider->next;
    node = node->next;
}

Node* ListMerge(Node* left, Node* right)
{
    Node head;
    Node* ret = &head;
    Node* slider = ret;
    while (left && right)
    {
        if (left->value > right->value)
        {
            MergeStep(slider, left);
        }
        else
        {
            MergeStep(slider, right);
        }
    }
    while (left)
    {
        MergeStep(slider, left);
    }
    while (right)
    {
        MergeStep(slider, right);
    }
    ret = ret->next;
    if (ret) ret->prev = NULL;
    return ret;
}

Node* ListMergeSort(Node* list)
{
    Node* ret = NULL;
    Node* left = NULL;
    Node* right = NULL;
   
    if (list)
    {
        if (list->next == NULL)
        {
            ret = list;
        }
        else
        {
            ListSplit(list, left, right);
            left = ListMergeSort(left);
            right = ListMergeSort(right);
            ret = ListMerge(left, right);
        }
    }
    return ret;
}