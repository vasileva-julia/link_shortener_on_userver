#ifndef HANDLER_H
#define HANDLER_H

#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>

#include <string_view>

#include "links_cache.hpp"

class RedirectHandler final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-redirect-to-long";

    RedirectHandler(const userver::components::ComponentConfig& config,
                    const userver::components::ComponentContext& context);

    std::string HandleRequest(userver::server::http::HttpRequest& request,
                              userver::server::request::RequestContext&) const override;

private:
    shortener::components::LinksCache& links_cache_;
    userver::storages::postgres::ClusterPtr pg_cluster_;
};

#endif // HANDLER_H