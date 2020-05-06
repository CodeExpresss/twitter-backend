#include <controller_header.hpp>

class VoteController {
public:
    explicit VoteController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~VoteController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};