#include "signup_controller.hpp"

template<class Serialize>
boost::property_tree::ptree SignUpController<Serialize>::get_queryset() {
    boost::property_tree::ptree mock;

    return serialize(worker->sing_up(system_user, profile));
}