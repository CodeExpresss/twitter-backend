#include "follow_controller.hpp"

template <class Serialize>
boost::property_tree::ptree FollowController<Serialize>::get_queryset() {
    return serialize(worker->following(subscriptions));
}
