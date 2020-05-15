#include "index_controller.hpp"

template <class Serialize>
boost::property_tree::ptree IndexController<Serialize>::get_queryset(int profile_id) {
    boost::property_tree::ptree default_tree;
    default_tree.put("status", "error");

    wall = worker->get_index_tweet(profile_id);
    if(wall.size() > 0)
        return serialize(wall);
    else {
        return default_tree;
    }
};