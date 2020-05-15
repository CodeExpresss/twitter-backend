#ifndef TAG_REPOSITORY_HPP
#define TAG_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "tag.hpp"

class TagRepository {
public:
    TagRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {};
    ~TagRepository() = default;

    std::vector<Tag> get_where() {}
    Tag get_by_id(int id, err_code& rc);
    void create(Tag& item, err_code& rc);
    void update(Tag& item, err_code& rc);
    //void erase(int id, err_code& rc);

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif // TAG_REPOSITORY_HPP
