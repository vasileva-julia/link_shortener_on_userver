#ifndef LINKMAKERHANDLER_H
#define LINKMAKERHANDLER_H

#include <userver/components/component.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/http/content_type.hpp>

#include <string_view>

class LinkMakerHandler final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-link-maker";

    LinkMakerHandler(const userver::components::ComponentConfig& config,
                     const userver::components::ComponentContext& context);
    std::string HandleRequest(userver::server::http::HttpRequest& request,
                              userver::server::request::RequestContext&) const override;

private:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};

#endif // LINKMAKERHANDLER_H
