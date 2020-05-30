#ifndef TAG_HPP
#define TAG_HPP

#include "models_header.hpp"

class Tag {
public:
    Tag(int tag_id, std::string &title);
    Tag(int tag_id);
    ~Tag() = default;

    int get_tag_id();
    std::string& get_title();

    void set_tag_id(int id);
    void set_title(std::string& _title);

private:
    int tag_id;
    std::string title;
};

#endif
