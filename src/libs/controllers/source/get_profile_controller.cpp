#include "get_profile_controller.hpp"

template <class Serialize>
boost::property_tree::ptree GetProfileController<Serialize>::get_queryset(int profile_id) {
    profile = worker->get_profile(profile_id);
    return serialize(profile);
};