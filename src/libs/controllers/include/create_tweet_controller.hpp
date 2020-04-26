#include <controller_header.hpp>

class AddTweetController {
public:
    explicit AddTweetController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~AddTweetController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};