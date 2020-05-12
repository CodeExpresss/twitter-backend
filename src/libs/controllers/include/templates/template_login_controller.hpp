#include "login_controller.hpp"

template <class Serialize>
boost::property_tree::ptree LoginController<Serialize>::get_queryset() {
    return(serialize(worker->login(user)));
};