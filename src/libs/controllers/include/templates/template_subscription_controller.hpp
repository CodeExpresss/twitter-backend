#include "subscription_controller.hpp"

template<class Serialize>
boost::property_tree::ptree SubscriptionController<Serialize>::get_queryset(int profile_id) {
    err_code rc;
    boost::property_tree::ptree default_tree;
    default_tree.put("status", "error");

    subscriptions = worker->get_subscriptions(profile_id, rc);
    if(subscriptions.size() == 0) {
        return default_tree;
    } else {
        return serialize(subscriptions);
    }
}