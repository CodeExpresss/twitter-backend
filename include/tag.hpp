#ifndef TAG_HPP
#define TAG_HPP

#include <string>

class Tag {
public:
    Tag();
    ~Tag();

    std::string get_title() const;
private:
    int tag_id;
    std::string title;
};

#endif
