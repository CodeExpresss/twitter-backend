#ifndef TAG_SEARCH_CONTROLLER_HPP
#define TAG_SEARCH_CONTROLLER_HPP

#include "controller_header.hpp"

template<class Serialize>
class TagSearchController {
public:
    explicit TagSearchController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~TagSearchController() = default;

    boost::property_tree::ptree get_queryset(const std::string& tag);

private:
    std::shared_ptr<UnitOfWork> worker;
    Serialize serialize;
};

#include "templates/template_tag_search_controller.hpp"

#endif