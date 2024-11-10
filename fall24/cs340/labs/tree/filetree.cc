#include "filetree.h"
#include <fstream>
#include <string>
#include <istream>
#include <sstream>
#include <vector>
#include <algorithm>

using std::istream;
using std::string;

struct node;

enum type {
    directory = 0,
    file = 1
};

auto parse_command(std::stringstream &&ss, node * root) -> std::pair<node *, bool>;
auto find_node(node * root, std::string directory_name) -> node *;
auto get_type(const std::string &file) -> type;
auto insert_child(node * current_node, const int &file_size, const std::string &file_name) -> void; 
auto size_of_tree(node * root) -> size_t;
auto computeSize(node * root, string ext = "")-> int;
auto readInput(std::istream &) -> node *;
auto get_closest_in_size(node * root, int target_size, std::string ext) -> std::vector<std::pair<node *, int>>;
auto get_absolute_path(node * p)-> std::string;
auto get_file_extension(const std::string &name) -> std::string ;
auto print_tree(node * root) -> void;
auto print_deleted(node *, std::string ext) -> void;
auto get_min_sized_node(node * root, int target_size, std::string ext) ->node *;
auto single_ext_type_tree(node * node, std::string extension) -> bool;


struct node {
    int size;
    std::string name; 
    type t;
    node * parent;
    node * left_child;
    node * right_sibling;

    node(int size, std::string name, type t, node * parent = nullptr, node * left_child = nullptr, node * right_sibling = nullptr)
        : size(size), name(name), t(t), parent(parent), left_child(left_child), right_sibling(right_sibling)
        { }
    
};
/* For each functon, make sure you call your readInput function to
    load the data */
void printNode(node * node, int lvl=0) {
    if (node == nullptr) {
        return;
    }
    int i;
    for (i = 0; i < lvl; i++)
        std::cout << "| ";
    std::cout << std::endl;
    for (i = 0; i < lvl-1; i++)
        std::cout << "| ";
    if (lvl > 0)
        std::cout << "+-";
    std::cout << "(" << ((node->t == directory) ? node->name.substr(0, node->name.length()-1) : node->name) << ")" << std::endl;
    // Loop through all the children of the current node
        // print_tree(node);
        printNode(node->left_child, lvl+1);
        printNode(node->right_sibling, lvl);

}
void printTree(istream & is) {
    node * root = readInput(is);
    printNode(root);
}

int computeSize(istream & is, string path)
{
    size_t last = path.find_last_of('/');
    size_t first = path.substr(0, last).find_last_of('/');
    std::string target_path = path = "/" ? path.substr(first + 1, last - first) : "/";
    
    node * root = readInput(is);
    node * path_root = find_node(root, target_path);
    return computeSize(path_root->left_child) + path_root->size;

}

string smallestDir(istream & is, int targetSize, string ext) {
    node * root = readInput(is);

    node * minimized_node = get_min_sized_node(root, targetSize, ext);

    if (minimized_node != nullptr)
        return get_absolute_path(minimized_node);
    else 
        return "";


}

void listDeleted(istream & is, int targetSize, string ext)
{
    node * root = readInput(is);
    node * minimized_node = get_min_sized_node(root, targetSize, ext);
    if (minimized_node == nullptr) { return; }

    print_deleted(minimized_node->left_child,ext);

    if (ext.empty()) {
        std::cout << minimized_node->name;
    }
    else {
        if (single_ext_type_tree(minimized_node->left_child, ext)) {
            std::cout << minimized_node->name;
        }
    }
    
}
auto readInput(std::istream &is) -> node * {
    std::string line;
    std::string token;

    node * root = nullptr;
    node * current_node = nullptr; 

    while (std::getline(is, line)) {
        std::stringstream ss(line);
        ss >> token;

        if (token == "$"){
            auto dir_node = parse_command(std::move(ss), current_node);

            if (dir_node.first != nullptr) {
                if (dir_node.second == false) {
                    if (!size_of_tree(root)) {
                        root = dir_node.first; 
                        current_node = root;
                    } else { 
                        current_node->left_child = dir_node.first;
                    }
                }
                else {
                    current_node = dir_node.first;
                }
            } 
        }
        else {
            std::string file_size = token;
            std::string file_name; ss >> file_name;

            insert_child(current_node, std::stoi(file_size),file_name);
        }
    }
    return root;
}

auto insert_child(node * current_node, const int &file_size, const std::string &name) -> void {
    node * traversal_node = current_node;

    type t = get_type(name);

    if (traversal_node->left_child == nullptr) {
        traversal_node->left_child = new node(file_size, name, t, current_node);
    }
    else {
        traversal_node = traversal_node->left_child;
        while (traversal_node->right_sibling != nullptr) {
            traversal_node = traversal_node->right_sibling;
        }
        traversal_node->right_sibling = new node(file_size, name, t, current_node);
    }
}

auto parse_command(std::stringstream &&ss, node * root) -> std::pair<node *, bool> {
    std::string token;
    ss >> token;

    if (token == "cd") {

        std::string directory_name;
        ss >> directory_name;
        if (directory_name == "..") {

            if (root->parent != nullptr)
                return std::make_pair(root->parent, true);
            else
                return std::make_pair(root, true);
        }
        else {
            if (directory_name != "/") {
                directory_name += '/';
            }
            node * directory_node = find_node(root, directory_name);
            if (directory_node == nullptr) {
                directory_node = new node(0,directory_name, directory, root);
                return std::make_pair(directory_node, false);
            }

            return std::make_pair(directory_node, true);

        }
    }
    
    return std::make_pair(nullptr, false); 
}

auto find_node(node * root, std::string directory_name) -> node * {

    if (root == nullptr) {
        return nullptr;
    }
    if (root->name == directory_name) {
        return root;
    }

    node * l = find_node(root->left_child, directory_name);
    node * r = find_node(root->right_sibling, directory_name);
        
    if (l) { return l; }
    if (r) { return r; }
    else   { return nullptr; }

} 

auto print_tree(node * root) -> void {
    if (root == nullptr) {
        return;
    }
    std::cout << root->name << "\n";

    print_tree(root->left_child);
    print_tree(root->right_sibling);
        
} 
auto size_of_tree(node * root) -> size_t {
    size_t size = 1;
    if (root == nullptr) {
        return 0;
    }
    size_t child_size = size_of_tree(root->left_child);
    size_t sibling_size = size_of_tree(root->right_sibling);
    return size + child_size + sibling_size;

}
auto get_type(const std::string &file) -> type {
    return (*file.rbegin() == '/') ? type::directory : type::file;
}

auto computeSize(node * root, string ext) -> int {
    if (root == nullptr) {
        return 0;
    }
    int size = 0;
    if (ext.empty()) {
        size = root->size;
    }
    else {
        if (root->t == file) {
            if (get_file_extension(root->name) == ext) {
                size = root->size;
            }
        }
    }
    int size_of_children = computeSize(root->left_child, ext);
    int size_of_siblings = computeSize(root->right_sibling, ext);

    return size + size_of_children + size_of_siblings;
}

 auto get_closest_in_size(node * root, int target_size, std::string ext) -> std::vector<std::pair<node*, int>> {
    std::vector<std::pair<node *, int>> v;
    if (root == nullptr) {
        return v;
    }

    int size = 0;
    if (root->t == directory) {
        size = computeSize(root->left_child, ext) + root->size;
    }
    if (size >= target_size){
        v.push_back(std::make_pair(root, size));
    }
    auto child_sizes = get_closest_in_size(root->left_child, target_size, ext);
    auto sibling_sizes = get_closest_in_size(root->right_sibling, target_size, ext);

    v.insert(v.end(), child_sizes.begin(), child_sizes.end());
    v.insert(v.end(), sibling_sizes.begin(), sibling_sizes.end());

    return v;

 }
auto get_absolute_path(node * p) -> std::string {
    std::string full_path; 
    if (p == nullptr) {
        return full_path;
    }

    std::string sub_path = get_absolute_path(p->parent);

    full_path += p->name;

    return sub_path + full_path;
     
}
// Right Now im printing all the nodes in the directories tree. Printing the directory after all of its children are printed. (minus the root).
// If there is a extension specified, i need to print only the nodes that have that extension. If all of the nodes in that directory would be deleted,
// I need to delete that directory.
auto print_deleted(node * root, std::string ext) -> void {

    if (root == nullptr) {
        return;
    }
    std::string path;
    if (ext.empty()) {
        path = get_absolute_path(root);
        if (root->t != directory) {
            std::cout << path << '\n';
        }
    }
    else {
        if (root->t == file && get_file_extension(root->name) == ext) {
            std::cout << path << '\n';
        }
    }
    print_deleted(root->left_child, ext);

    if (root->t == directory && ext.empty()) {
        std::cout << path << '\n';
    }
    else {
        if (root->t == directory && single_ext_type_tree(root->left_child, ext)) {
            std::cout << path << '\n';
        }
    }
    print_deleted(root->right_sibling, ext);
    
}
auto get_file_extension(const std::string &name) -> std::string {
    return name.substr(name.find_first_of('.'));
}
auto single_ext_type_tree(node * node, std::string extension) -> bool {
    
    if (node == nullptr) { return true; }
     
    if (node->t == file) {
        if (get_file_extension(node->name) != extension) {

            return false;
        }
    }
    return  single_ext_type_tree(node->left_child, extension) && single_ext_type_tree(node->right_sibling, extension);
}

auto get_min_sized_node(node * root, int target_size, std::string ext) ->node * {

    auto v = get_closest_in_size(root, target_size, ext);
    for (const auto & [first,second] : v) { std::cout << first->name << ",  " << second << '\n'; }

    if (v.empty()) { return nullptr; }
    else {
        return std::min_element(v.rbegin(), v.rend(), [](const auto &a, const auto &b){
                return a.second < b.second;
                })->first;
    }
}

 int main () {
     std::fstream input_file("input.txt");
       
      // node * root = readInput(input_file);
      // root = root->left_child->left_child->right_sibling->right_sibling;
      // print_tree(root->left_child);
     // std::cout << std::boolalpha << single_ext_type_tree(root->left_child, "");

      // std::string path = "/a/f/";
      // std::cout << computeSize(input_file, "/a/");
      // printTree(input_file);
      // std::string s = smallestDir(input_file, 650000);
      listDeleted(input_file, 650000, ".jpg");
      // std::cout << s;
     return 0;
  }
