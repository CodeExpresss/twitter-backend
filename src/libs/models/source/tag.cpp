#include "tag.hpp"

Tag::Tag(int tag_id, std::string &title)
    : tag_id(tag_id), title(std::move(title)) {}

Tag::Tag(int tag_id) : tag_id(tag_id), title("dd") {}

int Tag::get_tag_id() {
    return tag_id;
}
std::string& Tag::get_title() {
    return title;
}

void Tag::set_tag_id(int id) {
    tag_id = id;
}
void Tag::set_title(std::string& _title) {
    title = _title;
}

