#include "vote_controller.hpp"

template <class Serialize>
boost::property_tree::ptree VoteController<Serialize>::get_queryset() {
    return serialize(worker->vote(vote));
};