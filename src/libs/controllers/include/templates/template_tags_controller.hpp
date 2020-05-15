#include "tags_controller.hpp"

template<class Serialize>
boost::property_tree::ptree TagsController<Serialize>::get_queryset() {
    boost::property_tree::ptree default_tree;
    default_tree.put("status", "error");
    tag_list = worker->get_tag_list();

    if(tag_list.size() == 0) {
        return default_tree;
    } else {
        return serialize(tag_list);
    }
}