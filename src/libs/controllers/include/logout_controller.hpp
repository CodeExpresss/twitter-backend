#ifndef LOGOUT_CONTROLLER_HPP
#define LOGOUT_CONTROLLER_HPP

#include "controller_header.hpp"

template<class Serialize>
class LogoutController {
public:
    explicit LogoutController(std::shared_ptr<UnitOfWork> _worker, std::string id):
    worker(_worker), session(id) {};

    ~LogoutController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
    std::string session;

    Serialize serialize;
};

#include "templates/template_logout_controller.hpp"

#endif