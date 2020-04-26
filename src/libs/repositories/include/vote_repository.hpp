#ifndef VOTE_REPOSITORY_HPP
#define VOTE_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "vote.hpp"

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

#endif // VOTE_REPOSITORY_HPP
