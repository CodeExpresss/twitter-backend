#ifndef SUBSCRIPTION_REPOSITORY_HPP
#define SUBSCRIPTION_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "subscription.hpp"

class SubscriptionRepository {
public:
    SubscriptionRepository() = default;
    ~SubscriptionRepository() = default;


    std::vector<Subscription> get_where();
    Subscription get_by_id(int id);
    void create(Subscription item);
    void update(Subscription item);
    void erase(int id);

private:
    std::shared_ptr<DBController> db_controller;
};

#endif // SUBSCRIPTION_REPOSITORY_HPP
