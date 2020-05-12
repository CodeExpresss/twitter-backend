#ifndef VOTE_CONTROLLER_HPP
#define VOTE_CONTROLLER_HPP

#include "controller_header.hpp"

template <class Serialize>
class VoteController {
public:
    explicit VoteController(std::shared_ptr<UnitOfWork> _worker, int profile_id, int tweet_id):
        worker(_worker),
        vote(profile_id, tweet_id) {};
    ~VoteController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;

    Vote vote;

    Serialize serialize;
};

#include "templates/template_vote_controller.hpp"

#endif