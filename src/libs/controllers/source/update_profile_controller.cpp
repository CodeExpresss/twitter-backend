#include "update_profile_controller.hpp"

template <class Serialize>
boost::property_tree::ptree UpdateProfileController<Serialize>::get_queryset() {
    return serialize(worker->profile_update(profile));
};