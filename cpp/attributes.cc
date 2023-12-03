#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

struct Tag {
    std::map<std::string, std::string> attrs;
    std::map<std::string, Tag*>* children;
    std::map<std::string, Tag*>* siblings;
    struct Tag* parent;

    void insert(std::string name, Tag *tag) {
        children->insert(std::make_pair(name, tag));
    }
    void insert(std::string name, std::string value) {
        attrs.insert(std::make_pair(name, value));
    }
};

void strip(std::string &str) {
    while (str.at(0) == ' ' || str.at(0) == '<' || str.at(0) == '\"')
        str = str.substr(1, str.size()-1);
    while (str.at(str.size() -1) == ' ' || str.at(str.size() -1) == '\"')
        str = str.substr(0, str.size()-1);
}

int main() {
    int N,Q;
    std::string line;
    std::getline(std::cin, line);
    sscanf(line.data(), "%d %d", &N, &Q);

    std::map<std::string, Tag*> root;
    std::map<std::string, Tag*>* children = &root;

    Tag* open_tag = NULL;

    while (N--) {
        std::string line;
        std::getline(std::cin, line);
        strip(line);
        if (open_tag && line.at(0) == '/') { // close tag
            if (open_tag->parent == NULL) { // Then new tag belongs to root
                children = open_tag->siblings;
                if (N > 0) // don't allocate new if we're done
                    open_tag = new Tag;
                open_tag = NULL; // The root tag is NULL
            } else {
                children = open_tag->siblings; // The parents children is the current tag's children
                open_tag = open_tag->parent;
            }
            continue;
        }

        auto new_tag = new Tag;
        new_tag->parent = open_tag;
        if (new_tag->parent) {
            new_tag->siblings = children;
        } else
            new_tag->siblings = &root;

        open_tag = new_tag;
        open_tag->children = new std::map<std::string, Tag*>;

        std::string tag_name;
        if (line.find(" ") == line.npos) { // empty tag
            tag_name = line.substr(0, line.size() -1);
            goto insert_tag;
        }

        tag_name = line.substr(0, line.find(" "));
        line = line.substr(line.find(" "), line.npos);

        // now find all attributes
        for(;;) {
            std::string key = line.substr(0, line.find("="));
            strip(key);

            line = line.substr(line.find("=")+1, line.size());
            strip(line);

            std::string val;
            if (line.find(" ") < line.find(">")) { // More than one attribute
                val = line.substr(0, line.find(" "));
                strip(val);
                line = line.substr(line.find(" "), line.size());
                strip(line);
                open_tag->insert(key, val);
                continue;
            }

            val = line.substr(0, line.find(">"));
            strip(val);
            open_tag->insert(key, val);
            break;
        }

    insert_tag:
        children->insert(std::make_pair(tag_name, open_tag));
        children = open_tag->children;
    }

    while (Q--) {
        std::string line;
        std::getline(std::cin, line);
        children = &root;
        Tag *open_tag = NULL;
        for (;;) {
            if (line.find(".") < line.find("~")) { // nested tags
                std::string tag_name = line.substr(0, line.find("."));
                line = line.substr(line.find(".")+1, line.size());

                auto tag = children->find(tag_name);
                if (tag == children->end()) {
                    std::cout << "Not Found!" << std::endl;
                    break;
                }
                open_tag = tag->second;
                children = tag->second->children;
                continue;
            }
            std::string tag_name = line.substr(0, line.find("~"));
            auto tag = children->find(tag_name);
            if (tag == children->end()) {
                std::cout << "Not Found!" << std::endl;
                break;
            }
            open_tag = tag->second;

            std::string key = line.substr(line.find("~")+1, line.size());
            auto val = open_tag->attrs.find(key);
            if (val == open_tag->attrs.end()) {
                std::cout << "Not Found!" << std::endl;
            } else {
                std::cout << val->second << std::endl;
            }
            break;
        }
    }

    return 0;
}
