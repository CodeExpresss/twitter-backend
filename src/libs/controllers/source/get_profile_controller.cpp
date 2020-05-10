#include "get_profile_controller.hpp"

template <class Serialize>
boost::property_tree::ptree GetProfileController<Serialize>::get_queryset() {
    profile = worker->get_profile();
    return serialize(profile);
};