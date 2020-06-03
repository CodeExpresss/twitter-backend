#ifndef VIEW_PROFILE_CONTROLLER_HPP
#define VIEW_PROFILE_CONTROLLER_HPP

#include "controller_header.hpp"

template <typename Serialize>
class ViewProfileController {
public:
    explicit ViewProfileController(std::shared_ptr<UnitOfWork>& _worker, int inviter_id, int invitee_id):
        worker(_worker),
        subscription(inviter_id, invitee_id) {};

    ~ViewProfileController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;

    Profile profile;
    Subscription subscription;
    Serialize serialize;
};

#include "templates/template_view_controller.hpp"

#endif
