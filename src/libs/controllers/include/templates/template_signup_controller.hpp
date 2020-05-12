#include "signup_controller.hpp"

template<class Serialize>
boost::property_tree::ptree SignUpController<Serialize>::get_queryset() {
    return serialize(worker->sing_up(system_user, profile));
}