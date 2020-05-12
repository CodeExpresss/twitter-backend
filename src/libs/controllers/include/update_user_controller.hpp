#ifndef UPDATE_USER_CONTROLLER_HPP
#define UPDATE_USER_CONTROLLER_HPP

#include <controller_header.hpp>

template <class Serialize>
class UpdateUserController {
public:
    explicit UpdateUserController(std::shared_ptr<UnitOfWork> _worker, int id, std::string email, std::string password):
        worker(std::move(_worker)),
        user(id, std::move(email), std::move(password)) {};

    ~UpdateUserController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;

    User user;
    Serialize serialize;
};

#include "templates/template_update_user_controller.hpp"

#endif