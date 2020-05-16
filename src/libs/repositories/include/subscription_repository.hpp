#ifndef SUBSCRIPTION_REPOSITORY_HPP
#define SUBSCRIPTION_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "subscription.hpp"

class SubscriptionRepository {
public:
    SubscriptionRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {};
    ~SubscriptionRepository() = default;


    std::vector<Subscription> get_where() {}
    bool check_subscription(Subscription& item, err_code& rc);
    std::vector<int> get_by_invitee_id(int id, err_code &rc);
    std::vector<int> get_by_inviter_id(int id, err_code &rc);
    void create(Subscription &item, err_code &rc);
    void update(Subscription &item, err_code &rc);
    void erase(int id, err_code &rc);

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif // SUBSCRIPTION_REPOSITORY_HPP
