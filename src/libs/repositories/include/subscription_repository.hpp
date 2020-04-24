#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

#include "types.hpp"
#include "subscription.hpp"

class SubscriptionRepository {
public:
    SubscriptionRepository() = default;
    ~SubscriptionRepository() = default;


    std::vector<Subscription> get_all();
    Subscription get_by_id(int id);
    void create(Subscription item);
    void update(Subscription item);
    void erase(int id);

private:
};

#endif // REPOSITORY_HPP
