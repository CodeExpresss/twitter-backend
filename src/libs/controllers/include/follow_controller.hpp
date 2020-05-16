#ifndef FOLLOW_CONTROLLER_HPP
#define FOLLOW_CONTROLLER_HPP

#include "controller_header.hpp"

template <class Serialize>
class FollowController {
public:
    explicit FollowController(std::shared_ptr<UnitOfWork> _worker, int inviter_id, int invitee_id)
    : worker(_worker), subscriptions(inviter_id, invitee_id) {};
    ~FollowController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;

    Subscription subscriptions;
    Serialize serialize;
};

#include "templates/template_follow_controllers.hpp"

#endif