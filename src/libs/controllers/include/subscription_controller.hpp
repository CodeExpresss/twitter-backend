#ifndef SUBSCRIPTION_CONTROLLER_HPP
#define SUBSCRIPTION_CONTROLLER_HPP

#include "controller_header.hpp"

template <class Serialize>
class SubscriptionController {
public:
    explicit SubscriptionController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~SubscriptionController() = default;

    boost::property_tree::ptree get_queryset(int profile_id);

private:
    std::shared_ptr<UnitOfWork> worker;

    std::vector<Profile> subscriptions;
    Serialize serialize;
};

#include "templates/template_subscription_controller.hpp"

#endif