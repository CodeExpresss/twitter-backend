#ifndef INDEX_CONTROLLER_HPP
#define INDEX_CONTROLLER_HPP

#include <controller_header.hpp>

template<class Serialize>
class IndexController {
public:
    explicit IndexController(std::shared_ptr<UnitOfWork> _worker): worker(std::move(_worker)) {};
    ~IndexController() = default;

    boost::property_tree::ptree get_queryset(int profile_id);

private:
    std::shared_ptr<UnitOfWork> worker;

    std::vector<std::tuple<Tweet, Profile>> wall;
    Serialize serialize;
};

#include "templates/template_index_controller.hpp"

#endif