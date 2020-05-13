#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include "controller_header.hpp"

template<class Serialize>
class GetAuthUserController {
public:
    explicit GetAuthUserController(std::shared_ptr<UnitOfWork> _worker, int id, std::string email, std::string password):
        worker(_worker),
        user(id, std::move(email), std::move(password)) {};
    ~GetAuthUserController() = default;

    boost::property_tree::ptree get_queryset() {};

private:
    std::shared_ptr<UnitOfWork> worker;

    User user;
    Profile profile;

    Serialize serialize;
};

#include "templates/template_get_auth_user_controller.hpp"

#endif