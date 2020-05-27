#include "login_controller.hpp"

template <class Serialize>
std::string LoginController<Serialize>::get_queryset() {
    int id;
    std::string session;
    std::tie(id, session) = worker->login(user);
    return session;
};