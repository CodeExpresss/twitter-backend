#include "index_controller.hpp"

template <class Serialize>
boost::property_tree::ptree IndexController<Serialize>::get_queryset(int profile_id) {
    return serialize(worker->get_index_tweet(profile_id));
};