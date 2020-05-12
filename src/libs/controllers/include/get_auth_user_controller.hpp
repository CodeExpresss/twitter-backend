#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include <controller_header.hpp>

template<class Serialize>
class GetUserController {
public:
    explicit GetUserController(std::shared_ptr<UnitOfWork> _worker):
        worker(_worker),
        user(id, std::move(email), std::move(password)),{};
    ~GetUserController() = default;

    boost::property_tree::ptree get_queryset() {};

private:
    std::shared_ptr<UnitOfWork> worker;

    User user;
    Profile profile;

    Serialize serialize;
};

#endif