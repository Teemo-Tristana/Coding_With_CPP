#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>


using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};