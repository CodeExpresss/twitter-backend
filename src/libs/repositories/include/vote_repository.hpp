#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

#include "vote.hpp"
#include "types.hpp"

class VoteRepository {
public:
    VoteRepository() = default;
    ~VoteRepository() = default;


    std::vector<Vote> get_all();
    Vote get_by_id(int id);
    void create(Vote item);
    void update(Vote item);
    void erase(int id);

private:
};

#endif // REPOSITORY_HPP
