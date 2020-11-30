#include "header.h"

/**
 * 二叉树遍历：
 *    二叉树遍历方法，前序(递归与非递归)、中序(递归与非递归)、后序(递归与非递归) 和 层次遍历
*/


void printV(int &n)
{
    cout << n << endl;
}

//================================================前序================================================//
/*
 * 前序(DLR)递归遍历
*/
void preOrderRecur(TreeNode *head)
{
    if (nullptr == head)
        return;

    printV(head->val); // do something
    preOrderRecur(head->left);
    preOrderRecur(head->right);
}

/**
 * 前序(DLR)非递归
 * 借助于栈(stack)
*/
void preOrderUnRecur(TreeNode *head)
{
    if (nullptr == head)
        return;

    stack<TreeNode *> st;
    TreeNode *cur = head;
    st.push(cur);
    while (!st.empty())
    {
        cur = st.top();
        st.pop();
        printV(cur->val);

        if (cur->right)
        {
            st.push(cur->right);
        }

        if (cur->left)
        {
            st.push(cur->left);
        }
    }
}

//================================================中序================================================//
/**
 * 中序(LDR)递归遍历
*/
void inOrderRecur(TreeNode *head)
{
    if (nullptr == head)
        return;

    inOrderRecur(head->left); // go left  if node has left child
    printV(head->val);        // do something
    inOrderRecur(head->right);
}

/**
 * 中序(LDR)非递归遍历
 * 思路：
 *    从根结点一直往左走直到没有左孩子为止，然后输出该节点，转向其右孩子
*/
void inOrderUnRecur(TreeNode *head)
{
    if (nullptr == head)
        return;

    stack<TreeNode *> st;
    TreeNode *cur = head;
    while (!st.empty() || cur != nullptr)
    {
        if (cur != nullptr)
        {
            st.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = st.top();
            st.pop();
            printV(cur->val); // do something
            cur = cur->right;
        }
    }
}

//================================================后序================================================//
/**
 * 后序(LRD)递归遍历
*/
void postOrderRecur(TreeNode *head)
{
    if (nullptr == head)
        return;

    postOrderRecur(head->left);
    postOrderRecur(head->right);
    printV(head->val);
}

/**
 * 后序(LRD)非递归遍历
 *  借助于两个栈
*/
void postOrderUnRecur_1(TreeNode *head)
{
    if (head == nullptr)
        return;

    stack<TreeNode *> st1;
    stack<TreeNode *> st2;

    TreeNode *cur = head;
    st1.push(cur);
    while (!st1.empty())
    {
        cur = st1.top();
        st1.pop();
        st2.push(cur);

        if (cur->left)
            st1.push(cur->left);

        if (cur->right)
            st1.push(cur->right);
    }
    while (!st2.empty())
    {
        cur = st2.top();
        st2.pop();
        printV(cur->val);
    }
}

/**
 * 后序(LRD)非递归遍历
 *  借助于1个栈
*/
void postOrderUnRecur_2(TreeNode *head)
{
    if(nullptr == head)
        return ;
    
    TreeNode* visited = nullptr;
    TreeNode* cur = head;
    stack<TreeNode*> st;

    while(!st.empty() || nullptr != nullptr)
    {
        while (cur)
        {
            st.push(cur);
            cur = cur->left;
        }

        cur = st.top();
        
        if (nullptr == cur->right || visited == cur->right)
        {
            st.pop();
            printV(cur->val);
            visited = cur;
            cur = nullptr;
        }
        else 
        {
            cur = cur->right;
        }
    }
}