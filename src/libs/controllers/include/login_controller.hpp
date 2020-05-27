#ifndef LOGIN_CONTROLLER_HPP
#define LOGIN_CONTROLLER_HPP

#include "controller_header.hpp"
#include <utility>

template<class Serialize>
class LoginController {
public:
    explicit LoginController(std::shared_ptr<UnitOfWork> _worker, std::string email, std::string password):
    worker(_worker),
    user(0, std::move(email), std::move(password)) {};

    ~LoginController() = default;

    std::string get_queryset();
private:
    std::shared_ptr<UnitOfWork> worker;

    User user;
    Serialize serialize;
};

#include "templates/template_login_controller.hpp"

#endif