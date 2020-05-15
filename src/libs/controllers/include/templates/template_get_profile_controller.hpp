#include "get_profile_controller.hpp"

template <class Serialize>
boost::property_tree::ptree GetProfileController<Serialize>::get_queryset(int profile_id) {
    err_code rc;
    profile = worker->get_profile(profile_id, rc);
    return serialize(profile);
};
