#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

#include "types.hpp"
#include "tag.hpp"

class TagRepository {
public:
    TagRepository() = default;
    ~TagRepository() = default;


    std::vector<Tag> get_all();
    Tag get_by_id(int id);
    void create(Tag item);
    void update(Tag item);
    void erase(int id);

private:
};

#endif // REPOSITORY_HPP
