#include "link_maker_handler.hpp"

LinkMakerHandler::LinkMakerHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      pg_cluster_{context.FindComponent<userver::components::Postgres>("postgres-db-1").GetCluster()}
{}

std::string LinkMakerHandler::HandleRequest(
    userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const
{
    std::string longlink = request.GetArg("longlink");
    std::string shortlink = request.GetArg("shortlink");
    pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                 "INSERT INTO mydb.urls VALUES ($1, $2)", shortlink, longlink);
    request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
    request.GetHttpResponse().SetContentType(userver::http::content_type::kTextPlain);
    return "done 4";
}