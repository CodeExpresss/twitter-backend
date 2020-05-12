#include "tags_controller.hpp"

template<class Serialize>
boost::property_tree::ptree TagsController<Serialize>::get_queryset() {
    tag_list = worker->get_tag_list();

    if(tag_list.size() == 0) {
        return static_cast<boost::property_tree::ptree>(nullptr);
    } else {
        return serialize(tag_list);
    }
}