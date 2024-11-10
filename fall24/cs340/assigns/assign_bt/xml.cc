/************************************************************************************
* NIU CSCI 340 Section 3
* Assignment # 5
* Matt Warner - z2004200
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
*  Implements a simple parser for XML that uses a tilted binary tree for storage.
* 
************************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <numeric>

#include "nodes.h" // supplied node declarations
#include "bintree.h"
#include "xml.h"

template <typename UnaryPred1, typename UnaryPred2>
auto make_substring(const std::string &str, UnaryPred1 op1 = [](const std::string &str){return str.begin();}, UnaryPred2 op2 = [](const std::string &str){return str.end() - 1;}) -> std::string;
auto validate_tag(const std::string &tag) -> bool;
auto process_attribute(const std::string &str) -> std::pair<std::string,std::string>;
auto find_next_char(const std::string &input) -> std::string::const_iterator;
auto print_tree(XMLNODE * root, std::ostream &ost) -> void;


std::string to_string(const xml_element &element, bool opening) {

    std::string xml_element;
    // Open tag. Build the full tag.
    if (element.type == tag && opening == true) {

        // Add the opening bracket and the tags name.
        xml_element += '<' + element.name;

        // Add the attributes.
        if (!element.attrs.empty()) {
            std::ranges::for_each( element.attrs, 
            [&xml_element](const auto &attr) mutable 
            { xml_element +=  ' ' + attr.first  + '=' +  '"' + attr.second + '"' ;});
        }
        xml_element += '>';
    }
    // Closing tag. Build the closing tag, ignoring attributes.
    else if (element.type == tag && opening == false) {
        xml_element += "</" + element.name + '>';
    }
    // Plain text. All information needed is contained in data member 'fulltext'.
    else {
        xml_element = element.fulltext;
    }

    return xml_element;
}

std::vector <XMLNODE *> xml_find_by_name(XMLNODE * root, const std::string &name) {
    std::vector<XMLNODE *> nodes;

    if (root == nullptr) {
        return {};
    }

    // Add the node to the vector if its name is a match.
    if (root->data.name == name) {
        nodes.push_back(root);
    }

    // Get the nodes from left subtree of root.
    auto below_left_nodes = xml_find_by_name(root->left,name);
    // Get the nodes from right subtree of root.
    auto below_right_nodes = xml_find_by_name(root->right,name);

    // Merge the nodes from left, right subtrees into current vector.
    nodes.insert(nodes.end(), below_left_nodes.begin(), below_left_nodes.end());
    nodes.insert(nodes.end(), below_right_nodes.begin(), below_right_nodes.end());

    return nodes;
}

std::vector <XMLNODE *> xml_find_with_attr(XMLNODE * root, const std::string &attrname) {
    std::vector<XMLNODE *> nodes;

    if (root == nullptr) {
        return {};
    }
    // If the number of attributes in the attribute tree that have an attribute named attrname is non zero,
    // It gets added to the nodes vector.
    if (std::ranges::count_if(root->data.attrs, [&attrname](const auto &pair) { return pair.first == attrname; }) > 0) {
        nodes.push_back(root);
    }

    // Get the nodes from left subtree of root.
    auto below_left_nodes = xml_find_with_attr(root->left,attrname);
    // Get the nodes from right subtree of root.
    auto below_right_nodes = xml_find_with_attr(root->right,attrname);
    
    // Merge the nodes from left, right subtrees into current vector.
    nodes.insert(nodes.end(), below_left_nodes.begin(), below_left_nodes.end());
    nodes.insert(nodes.end(), below_right_nodes.begin(), below_right_nodes.end());
    return nodes;
}

int xml_add_node(const xml_element &element, xml_tree_state & state, bool verbose) {
    // Tree is empty, insert at root.
    if (state.root == nullptr) {
        state.root = new XMLNODE(element);
        state.cur = state.root;
        return 0;
    }
    // Current node in the tree is null.
    if (state.cur == nullptr) {
        std::cerr << "Cannot insert if current node is NIL.\n";
            return 1;
    }

    XMLNODE * new_xml_node = new XMLNODE(element);
    new_xml_node->parent = state.cur;
    // Current node is plain text or closed. Insert as sibling.
    if (state.cur->data.type == plain || state.cur->data.closed) {
        // Find the node with an empty right child.
        while (state.cur->right != nullptr) {
            state.cur = state.cur->right;
        }
        // Insert the new element into the tree.
        state.cur->right = new_xml_node;

        // Adjust positon of current node to the node
        // that was just inserted into the tree.
        state.cur = state.cur->right;
    }
    // Current node is an open tag. Inserts into tree as child.
    else if (state.cur->data.type == tag && state.cur->data.closed == false) { 
        // Find the node with an empty left child.
        while (state.cur->left != nullptr) {
            state.cur = state.cur->left;
        }
        // Insert the new element into the tree
        state.cur->left = new_xml_node;     
        // Adjust current position to inserted node.
        state.cur = state.cur->left;
    }
    return 0;
}

int xml_close_tag(const std::string name, xml_tree_state & state, bool verbose) {

    // Check if the tag was immediately closed after opening
    // Which indicates that the current node in state is the node we are interested in.
    if (state.cur->data.name == name) {
        state.cur->data.closed = true;
        return 0;
    }

    else {
        // Find the parent node in the tilted tree.
        XMLNODE * parent = tilted_find_parent(state.cur);

        // If the tag with the right name is found, it needs to be marked as closed
        // and the current location in the tree needs to be updated to the parent.
        if (parent != nullptr && parent->data.name == name) {
            parent->data.closed = true; 
            state.cur = parent;
            return 0;
        }
    }  

    // If we are still here, there is something wrong with the tree
    // Printing an error message and returning 1.
    std::cerr << "Faulty logic somewhere. Possibly when adding nodes to tree.\n";

    return 1;
}

int xml_handle_plaintext(std::string &plaintext, xml_tree_state & state, bool verbose) {
    // Construct plaintext element.
    xml_element new_element(plain, "", plaintext, {});
    // Adding it to the tree, returning the error code of xml_add_node.
    return xml_add_node(new_element, state, verbose);
}

int xml_handle_attributes(const std::string &input, std::map<std::string, std::string> &attrs, bool verbose) {
    auto first = input.begin();
    // Finds each instance of a key,value pair.
    while (first != input.end() && *first != '>') {
        // Find the end of the attribute
        bool found_opening_quote = false, found_equals = false;
        // Gets the position of the end of attribute range.
        auto last = std::find_if(first, input.end(), [&found_opening_quote, &found_equals](const char &ch) {
                    if (ch == '=') found_equals = true;
                    if (ch == '"') {
                        if (found_opening_quote) return true;
                        else found_opening_quote = true;
                    } return false; });


        // Checks if last is located at the end of the string
        // in which case there needs to be some error checking.
        if (last == input.end()) {
            // Opening quote was located, but no end quote was found from the above search.
            if (found_opening_quote) {
                std::cerr << "  ERROR: xml_handle_attributes tag ended before value's quotation ended.\n";
            }
            // tag string is missing an equal sign.
            if (found_equals == false) {
                std::cerr << "  ERROR: xml_handle_attributes done. Invalid string remaining "  << '"' << std::string(first, last) << '"' << '\n';
            }
            break;
       }

        std::string attribute(first,last + 1);
        // Invalid string, missing '='.
        if (found_equals == false) {
            std::cerr << "  ERROR: xml_handle_attributes done. Invalid string remaining "  << '"' << attribute << '"' << '\n';
        }
        // Split into key, value pair.
        else {
            auto key_value_pair = process_attribute(attribute);
            attrs.insert(key_value_pair);
        }
        // Get the start of the new range.
        first = std::find_if(last, input.end(), [](const char &ch){ return std::isalpha(ch); });
    }
    // Returns the number of attributes parsed from the tag string.
    return attrs.size();
}

int xml_handle_tag(std::string &tagstring, xml_tree_state & state, bool verbose) {

    // Check if tag is valid before continuing.
    if (validate_tag(tagstring) == false) {
        std::cerr << tagstring << " is a invalid tag.\n";
        return 1;
    }

    // Parses tagstring to retrieve the tags name.
    std::string tag_name = make_substring ( 
            tagstring,
            [](const std::string &str) { return std::ranges::find_if(str, [](const char &ch) { return std::isalpha(ch); });},
            [](const std::string &str) { return std::ranges::find_if(str, [](const char &ch) { return ch == ' ' || ch == '>';}); }
    );
  
    // Closing tag, handle closing.
    if (*(std::ranges::find(tagstring, '<') + 1) == '/') {
        xml_close_tag(tag_name,state);
    }
    // Opening tag, handle attributes.
    else {
        // Strips the name from the tag.
        std::string remaining_tag = tagstring.substr(tag_name.length() + 1);

        // Map to hold the tags attributes. 
        std::map<std::string,std::string> tag_attributes;
        // Process the tags attribues.
        xml_handle_attributes(remaining_tag, tag_attributes, verbose);

        // Construct a new xml element and add it to the tree.
        xml_element new_xml_element(tag, tag_name, tagstring, tag_attributes);
        return xml_add_node(new_xml_element, state, verbose);
    }
    
    return 0;
}

void xml_print_subtree(XMLNODE *root, std::ostream & ost) {
    // Located at the root of the tree
    // Should print the entire tree.
    if (root->parent == nullptr) {
        print_tree(root, ost);
    }
    // Located at some subtree
    // Should avoid the siblings of root.
    else {
        ost << to_string(root->data, true);
        print_tree(root->left, ost);
        if (root->data.type == tag) ost << to_string(root->data, false);
    }

}
auto validate_tag(const std::string &tag) -> bool {

    // Tag is empty.
    if (tag.empty()) return false;
    // Tag is too short.
    if (find_next_char(tag) == tag.end()) return false;
    // Missing angle brackets.
    if (*tag.begin() != '<' || *tag.rbegin() != '>') return false;

    return true;
}

/**
 * Builds a substring from two iterators.
 * Takes two unary functions that are used to build range [first, last).
 */
template <typename UnaryPred1, typename UnaryPred2>
auto make_substring(const std::string &str, UnaryPred1 op1, UnaryPred2 op2) -> std::string {
    auto first = op1(str);
    auto last = op2(str);
    return std::string(first,last);
}

/**
 * Helper function for xml_handle_attributes.
 * Builds a key, value pair for an attribute.
 */
auto process_attribute(const std::string &str) -> std::pair<std::string,std::string> {
    std::string key = make_substring (
            str,
            [](const std::string &str) { return find_next_char(str); },
            [](const std::string &str) { return std::find_if(str.begin(), str.end(), [](const char &ch) { return  ch == '='; });}
            );
    std::string value = make_substring (
            str,
            [&key](const std::string &str) { return std::find(str.begin() + key.length(), str.end(), '"')+1;},
 
            [&key](const std::string &str) { return (std::find(str.crbegin(), str.crend(),'"')+1).base();}
            );

    return std::pair(key,value);
}
auto find_next_char(const std::string &input) -> std::string::const_iterator {
    return std::ranges::find_if(input, [](const char &ch){ return std::isalpha(ch); });
}
/**
 * Helper function for xml_print_subtree.
 */
auto print_tree(XMLNODE * root, std::ostream &ost) -> void {
    if (root == nullptr)
        return;

    ost << to_string(root->data);

    print_tree(root->left, ost);
    if (root->data.type == tag)
        ost << to_string(root->data, false);
    print_tree(root->right, ost);
}
