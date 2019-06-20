/*输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，
则重建二叉树并返回。*/

#include <iostream>
#include <vector>
using namespace std;


struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):left(NULL),right(NULL) { val = x; }
};

class Solution 
{
public:

    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> mid) 
    {

        if (pre.size()==0 || pre.size()!=mid.size())
        {
            return NULL;
        }
        else
        {
            TreeNode* temp = new TreeNode(pre[0]);

            int i = 0;
            while(mid[i] != pre[0]) ++i;

            vector<int> p1(pre.begin()+1, pre.begin()+i+1);
            vector<int> m1(mid.begin(), mid.begin()+i);
            temp->left = reConstructBinaryTree(p1,m1);

            vector<int> p2(pre.begin()+i+1, pre.end());
            vector<int> m2(mid.begin()+i+1, mid.end());
            temp->right = reConstructBinaryTree(p2,m2);

            return temp;
        }
    }


    void printTree(TreeNode* tree) 
    {
        cout<<"——";
        if(tree != NULL)
        {
            printTree(tree->left);
            cout<<tree->val<<endl;
            printTree(tree->right);
        }
        else
        {
            cout<<endl;
        }
    }
};

int main(int argc, char const *argv[])
{
    vector<int> pre={1,2,4,7,3,5,6,8};
    vector<int> mid={4,7,2,1,5,3,8,6};
    Solution s;
    TreeNode* tree=s.reConstructBinaryTree(pre,mid);
    s.printTree(tree);
    return 0;
}