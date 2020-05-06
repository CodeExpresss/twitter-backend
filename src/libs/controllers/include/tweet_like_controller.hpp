#include <controller_header.hpp>

class TweetLikeController {
public:
    explicit TweetLikeController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~TweetLikeController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};