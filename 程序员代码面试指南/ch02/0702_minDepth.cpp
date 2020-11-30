#include "header.h"

/**
 * 给定一颗二叉树，求这颗二叉树的最小深度
*/

// 方法1
int process(TreeNode* cur, int level)
{
    if (cur->right == nullptr && cur->left == nullptr)
        return level;
    
    int ans = INT_MAX;
    if (cur->left)
        ans = min(process(cur->left, level+1), ans);
    
    if (cur->right)
        ans = min(process(cur->right, level+1), ans);

    return ans;
}

int minDepthofBinaryTree_1(TreeNode* head)
{
    if (head == nullptr)
        return 0;
    return process(head, 1);
}

// 方法2
int minDepthofBinaryTree_2(TreeNode* head)
{
    if (head == nullptr)
        return 0;
    return 1 + min(minDepthofBinaryTree_2(head->left), minDepthofBinaryTree_2(head->right));
}