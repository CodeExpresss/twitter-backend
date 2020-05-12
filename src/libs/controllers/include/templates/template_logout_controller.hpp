#include "logout_controller.hpp"

template <class Serialize>
boost::property_tree::ptree LogoutController<Serialize>::get_queryset() {
    return(serialize(worker->logout(user)));
};