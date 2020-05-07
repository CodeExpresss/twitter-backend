#ifndef VOTE_REPOSITORY_HPP
#define VOTE_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "vote.hpp"

class VoteRepository {
public:
    VoteRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {};
    ~VoteRepository() = default;


    std::vector<Vote> get_where() {}
    Vote get_by_id(int id) {}
    void create(Vote item) {}
    void update(Vote item) {}
    void erase(int id) {}

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif // VOTE_REPOSITORY_HPP
