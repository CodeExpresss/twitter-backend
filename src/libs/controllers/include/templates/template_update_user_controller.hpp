#include "update_user_controller.hpp"

template <class Serialize>
boost::property_tree::ptree UpdateUserController<Serialize>::get_queryset() {
    return serialize(worker->user_update(user));
};