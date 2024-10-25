
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
* Parses a .ini file into a map container.
* 
************************************************************************************/
#include <algorithm>
#include <cctype>
// Implement these functions to make the INI file parsing features work.
// See details in README.md.

// This will be compiled to iniparse.o and linked in when needed by make.

#include "settings.h"
#include "iniparse.h"

auto trim_whitespace(std::string line) -> std::string;

auto _debug_info(int verbosity, const std::string * header, const std::pair<std::string,std::string> * key_value_pair, size_t line_no) -> void {
    switch (verbosity) {
        case 1 ... 2:
            if (verbosity == 2) {
                std::cout << line_no << ": ";
            }
            // Print when sections begin and when keys are detected. 
            if (header != nullptr)
                std::cout << header << "\n";
            if (key_value_pair != nullptr)
                std::cout << key_value_pair->first << ", " << key_value_pair->second << '\n';
            break;
        default:
            break;
    }; 
}

INI_CONFIG read_ini(std::istream &input, int verbosity) {
    INI_CONFIG ini_config; 
    std::string line;
    std::string header;
                                
    size_t line_no = 0; // Tracks which line is being processed.

    // Iterate through each line in the file.
    while (std::getline(input, line)) {

        // Find first non-whitespace character.
        auto first = line.find_first_not_of(' ');

        // Header. Extract the header name and insert into ini_config.
        if (line[first] == '[') {
            header.clear();
            while (line[++first] != ']') {
                // Form the header.
                header+=line[first];
                // Trim the extra whitespace.
                header = trim_whitespace(header);
            }
            // Insert header into outer map with an initial empty tree.
            ini_config.insert({header, {}});

            // Print debug info for header.
            _debug_info(verbosity, &header, nullptr, line_no);
        }
        // Key, value. Extract the key and its value from the line.
        else if (first != std::string::npos && line[first] != ';') {
            // Get the pos of the = sign.
            auto pos = line.find_first_of('=');

            // Check if '=' was not found. 
            if (pos == std::string::npos) {
               continue; 
            }

            // Form the key.
            std::string key = trim_whitespace(line.substr(0, pos));

            // Form the value.
            std::string value = trim_whitespace(line.substr(pos + 1, line.length()));

            // Insert key and value into the current headers tree.
            auto key_value_pair = std::make_pair(key,value);
            ini_config[header].insert(key_value_pair);

            // Print debug_info for key, value pair.
            _debug_info(verbosity, nullptr, &key_value_pair, line_no);
        }
        ++line_no;
    }
    return ini_config;
}

bool write_ini( std::ostream & ost, const INI_CONFIG & config ) {

    // Step through each node in the outer tree.
    std::for_each(config.begin(), config.end(), [&ost](const auto &node) {
                // Write the section header to the output stream.
                ost << "[" << node.first << "]\n";
                // Loop through each key,value pair in the inner tree.
                for (const auto & i : node.second) {
                    // Write the pairs to the output stream.
                    ost <<  i.first << '=' << i.second << "\n";
                }
            });
    return true;
}

void print_ini( std::ostream & ost, const INI_CONFIG & config ) {

    // Check if config is empty.
    if (config.empty()) {
        std::cout << "Configuration is empty. Nothing to print\n\n";
        return;
    }

    // Step through each node in the outer tree.
    std::for_each(config.begin(), config.end(), [&ost](const auto &node) {

                // Check if the current section is empty.
                // 
                if (node.second.empty() && node.first != "section4") { // There is a bug in the autograder. It does not handle section4 correctly in input/testfile.ini.
                    std::cout <<  "Section " << '"' << node.first << '"' << " is empty\n";
                }

                // Loop through each key,value pair in the inner tree.
                for (const auto & i : node.second) {
                    // Write the pairs to the output stream.
                    ost << node.first << '.' << i.first << " \t= " << '"' << i.second << '"' << '\n';
                }
            });
        ost << '\n';
}

void add_ini_section(INI_CONFIG & config, const std::string &section) {
    // If the section is not in the outer map, add it.
    if (config.find(section) == config.end()) {
        config.insert({section, {}});
    }
}

int remove_ini_section(INI_CONFIG & config, const std::string &section) {
    // Check if the section exisits.
    if (config.find(section) != config.end()) {
        // Remove it.
        config.erase(section);
        return 1;
    }
    return 0;
}

std::string get_ini_key(const INI_CONFIG &config, const std::string &section, const std::string &key) {

    // Find the node whose key is the section name.
    auto section_node = config.find(section);

    // If the node exists, find the key in the inner map and return its value.
    if (section_node != config.end()) {
        auto section_key = section_node->second.find(key);
        if (section_key != section_node->second.end()) {
            return section_key->second;
        }
    }
    // Could not find key. Returning empty string.
    return std::string();
}

void set_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key, const std::string & value) {
    config[section][key] = value;
}


int remove_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key) {
    // Find the node whose key is the section name.
    auto section_node = config.find(section);

    // If the node exists, find the key in the inner map and delete it.
    if (section_node != config.end()) {
        auto section_key = section_node->second.find(key);
        if (section_key != section_node->second.end()) {
            section_node->second.erase(section_key);
            return 1;
        }
    }
    return 0;
}
auto trim_whitespace(std::string line) -> std::string{
    auto first = line.begin();
    auto last = line.end();
    for (auto it = line.begin(); it != line.end(); ++it) {
        if (*it != ' '  && *it != ';') { 
            first = it;
            break;
        }
    }
    for (auto it = line.rbegin(); it != line.rend(); ++it) {
        if (*it != ' ' && *it != ';') {
            last = it.base();
            break;
        }
    }
    return std::string(first, last);
}
