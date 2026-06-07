#include "redirect_handler.hpp"
#include "shortener/sql_queries.hpp"

RedirectHandler::RedirectHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& component_context)
    : HttpHandlerBase(config, component_context),
      links_cache_{component_context.FindComponent<shortener::components::LinksCache>()},
      pg_cluster_(component_context.FindComponent<userver::components::Postgres>("postgres-db-1").GetCluster())
{}

std::string RedirectHandler::HandleRequest(userver::server::http::HttpRequest& request,
                                           userver::server::request::RequestContext&) const
{
    if (request.GetMethod() != userver::server::http::HttpMethod::kGet)
    {
        throw userver::server::handlers::ClientError(userver::server::handlers::ExternalBody
            {fmt::format("Unsupported method {}", request.GetMethod())});
    }

    const auto& id = request.GetPathArg("id");
    const auto links_index = links_cache_.Get();
    const auto& all_links = links_index->all_links;

    auto link_it = all_links.find(id);
    std::string link;
    if (link_it == all_links.end())
    {
        auto result = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave,
                                           shortener::sql::kSelectLonglinkByShortlink,
                                           id);
        if (result.IsEmpty())
        {
            request.SetResponseStatus(userver::server::http::HttpStatus::kNotFound);
            request.GetHttpResponse().SetContentType(userver::http::content_type::kTextPlain);
            return {};
        }
        else
            link = result.AsSingleRow<std::string>();
    }
    else
        link = link_it->second;

    std::string_view header = "Location";
    request.SetResponseStatus(userver::server::http::HttpStatus::kMovedPermanently);
    request.GetHttpResponse().SetHeader(header, link);
    return {};
}