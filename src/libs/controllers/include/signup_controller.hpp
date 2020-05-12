#ifndef SIGHUP_CONTROLLER_HPP
#define SIGHUP_CONTROLLER_HPP

#include "controller_header.hpp"

template<class Serialize>
class SignUpController {
public:
    explicit SignUpController(std::shared_ptr<UnitOfWork> _worker,
        std::string username,
        std::string email,
        std::string password,
        std::string avatar,
        std::string birthday):
            worker(_worker),
            system_user(0, std::move(email), std::move(password)),
            profile(0, 0, std::move(username), std::move(birthday), std::move(avatar)) {};

    ~SignUpController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;

    User system_user;
    Profile profile;
    Serialize serialize;
};

#include "templates/template_signup_controller.hpp"

#endif