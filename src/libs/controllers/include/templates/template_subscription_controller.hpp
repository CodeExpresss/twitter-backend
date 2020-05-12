#include "subscription_controller.hpp"

template<class Serialize>
boost::property_tree::ptree SubscriptionController<Serialize>::get_queryset(int profile_id) {
    subscriptions = worker->get_subscriptions(profile_id);
    if(subscriptions.size() == 0) {
        return static_cast<boost::property_tree::ptree>(nullptr);
    } else {
        return serialize(subscriptions);
    }
}