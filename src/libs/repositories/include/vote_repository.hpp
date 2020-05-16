#ifndef VOTE_REPOSITORY_HPP
#define VOTE_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "vote.hpp"

class VoteRepository {
public:
    VoteRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {};
    ~VoteRepository() = default;


    std::vector<Vote> get_where() {}
    bool get_by_id(int p_id, int t_id, err_code &rc);
    void create(Vote &item, err_code &rc);
    void update(Vote &item, err_code &rc);
    void erase(int p_id, int t_id, err_code &rc);

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif // VOTE_REPOSITORY_HPP
