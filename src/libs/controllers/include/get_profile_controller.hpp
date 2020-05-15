#ifndef GET_PROFILE_CONTROLLER_HPP
#define GET_PROFILE_CONTROLLER_HPP

#include "controller_header.hpp"

template <typename Serialize>
class GetProfileController {
public:
    explicit GetProfileController(std::shared_ptr<UnitOfWork>& _worker): worker(_worker) {};

    ~GetProfileController() = default;

    boost::property_tree::ptree get_queryset(int profile_id);

private:
    std::shared_ptr<UnitOfWork> worker;

    Profile profile;
    Serialize serialize;
};

#include "templates/template_get_profile_controller.hpp"

#endif