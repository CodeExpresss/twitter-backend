#ifndef UPDATE_PROFILE_CONTROLLER_HPP
#define UPDATE_PROFILE_CONTROLLER_HPP

#include <controller_header.hpp>

template <class Serialize>
class UpdateProfileController {
public:
    explicit UpdateProfileController(std::shared_ptr<UnitOfWork> _worker,
            int profile_id, int user_id,
            std::string username,
            std::string birthday,
            std::string avatar ):
                worker(std::move(_worker)),
                profile(profile_id, user_id, std::move(username), std::move(birthday), std::move(avatar)) {};

    ~UpdateProfileController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;

    Profile profile;
    Serialize serialize;
};

#endif