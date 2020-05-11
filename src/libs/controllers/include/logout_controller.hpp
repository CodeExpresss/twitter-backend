#ifndef LOGOUT_CONTROLLER_HPP
#define LOGOUT_CONTROLLER_HPP

#include <controller_header.hpp>

template<class Serialize>
class LogoutController {
public:
    explicit LogoutController(std::shared_ptr<UnitOfWork> _worker, int id, std::string email, std::string password):
    worker(std::move(_worker)),
    user(id, std::move(email), std::move(password)) {};

    ~LogoutController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;

    User user;
    Serialize serialize;
};

#endif