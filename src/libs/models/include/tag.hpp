#ifndef TAG_HPP
#define TAG_HPP

#include "models_header.hpp"

class Tag {
public:
    Tag(int tag_id, std::string &title) : tag_id(tag_id), title(std::move(title)) {}
    Tag(int tag_id) : tag_id(tag_id), title("dd") {}
    ~Tag() = default;

    int get_tag_id() {return tag_id;}
    std::string& get_title() {return title;}

    void set_tag_id(int id) {tag_id = id;}
    void set_title(std::string& _title) {title = _title;}

private:
    int tag_id;
    std::string title;
};

#endif
