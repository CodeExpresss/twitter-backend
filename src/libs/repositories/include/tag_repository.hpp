#ifndef TAG_REPOSITORY_HPP
#define TAG_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "tag.hpp"

class TagRepository {
public:
    TagRepository() = default;
    ~TagRepository() = default;


    std::vector<Tag> get_where();
    Tag get_by_id(int id);
    void create(Tag item);
    void update(Tag item);
    void erase(int id);

private:
    std::shared_ptr<DBController> db_controller;
};

#endif // TAG_REPOSITORY_HPP
