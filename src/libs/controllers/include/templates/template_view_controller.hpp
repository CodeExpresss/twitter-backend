#include "view_profile_controller.hpp"

template <class Serialize>
boost::property_tree::ptree ViewProfileController<Serialize>::get_queryset() {
    err_code rc;
    profile = worker->get_profile(subscription.get_inviter_id(), rc);
    bool is_follow = worker->check_subscriptions(subscription, rc);
    return serialize(std::make_pair(profile, is_follow));
};