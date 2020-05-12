#ifndef TAG_CONTROLLER_HPP
#define TAG_CONTROLLER_HPP

#include "controller_header.hpp"

template <class Serialize>
class TagsController {
public:
    explicit TagsController(std::shared_ptr<UnitOfWork> _worker): worker(std::move(_worker)) {};
    ~TagsController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;

    vector<Tag> tag_list;
    Serialize serialize;
};

#include "templates/template_tags_controller.hpp"

#endif