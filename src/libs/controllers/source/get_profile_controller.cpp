#include "get_profile_controller.hpp"

boost::property_tree::ptree GetProfileController::get_queryset() {
    _profile = worker->get_profile();
    return _serialize(_profile);
}