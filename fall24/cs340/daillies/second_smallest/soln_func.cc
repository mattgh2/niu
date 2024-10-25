#include <vector>
#include <algorithm>
#include <iostream>
class TreeNode {
public:
    TreeNode * left, * right;
    int value;
};
auto r(TreeNode * root) -> std::vector<int> {
    std::vector<int> v;
    if (root == nullptr) {
        return {};
    }
    v.push_back(root->value);
    std::vector<int> elements_from_left_subtree = r(root->left);
    std::vector<int> elements_from_right_subtree = r(root->right);
    
    if (!elements_from_left_subtree.empty()) {
        v.insert(v.end(), elements_from_left_subtree.begin(), elements_from_left_subtree.end());
    }
    if (!elements_from_right_subtree.empty()) {
        v.insert(v.end(), elements_from_right_subtree.begin(), elements_from_right_subtree.end());
    }
    return v;


}
auto secondsmallest(TreeNode * root, int &val) -> bool {
    if (!root->left && !root->right) { return false; }
    auto values = r(root);
    std::make_heap(values.begin(),values.end(), std::greater<>{});
    std::pop_heap(values.begin(), values.end(), std::greater<>{});
    val = values[0];
    return true;

}

// int main(int argc, char **argv){
//
//     TreeNode * root = new TreeNode;
//     root->value = 20;
//     root->left = new TreeNode;
//     root->left->value = 15;
//     root->right = new TreeNode;
//     root->right->value = 10;
//     root->left->left = new TreeNode;
//     root->left->left->value = 30;
//     root->left->right = new TreeNode;
//     root->left->right->value = 25;
//     root->right->left = new TreeNode;
//     root->right->left->value = 40;
//     root->right->right = new TreeNode;
//     root->right->right->value = 35;
//
//     std::vector<int> values = r(root);
//
//     std::make_heap(values.begin(),values.end(), std::greater<>{});
//     std::pop_heap(values.begin(), values.end(), std::greater<>{});
//     for (auto i : values) { std::cout << i << ' '; }
//     // std::cout << values[0];
//     return 0;
// }
