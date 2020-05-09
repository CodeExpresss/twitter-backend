#ifndef GET_PROFILE_CONTROLLER_HPP
#define GET_PROFILE_CONTROLLER_HPP

#include "controller_header.hpp"

template <typename Serialize>
class GetProfileController: public AbstractController {
public:
    explicit GetProfileController(const AbstractController& _worker): AbstractController(_worker) {};

    ~GetProfileController() = default;

    boost::property_tree::ptree get_queryset() override;

private:
    Profile profile;
    Serialize serialize;
};

#endif