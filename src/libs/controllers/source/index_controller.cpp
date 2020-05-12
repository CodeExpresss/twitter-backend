#include "index_controller.hpp"

template <class Serialize>
boost::property_tree::ptree IndexController<Serialize>::get_queryset(int profile_id) {
    wall = worker->get_index_tweet(profile_id);
    int wall_size = std::tuple_size<decltype(wall)>::value;
    if(wall_size > 0)
        return serialize(wall);
    else {
        return static_cast<boost::property_tree::ptree>(nullptr);
    }
};