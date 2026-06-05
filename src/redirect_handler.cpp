#include "redirect_handler.hpp"

RedirectHandler::RedirectHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& component_context)
    : HttpHandlerBase(config, component_context),
      links_cache_{component_context.FindComponent<shortener::components::LinksCache>()},
      pg_cluster_(component_context.FindComponent<userver::components::Postgres>("postgres-db-1").GetCluster())
{}

std::string RedirectHandler::HandleRequest(userver::server::http::HttpRequest& request, userver::server::request::RequestContext&) const
{
    const auto& id = request.GetPathArg("id");
    const auto links_index = links_cache_.Get();
    const auto& all_links = links_index->all_links;

    if (all_links.find(id) != all_links.end())
    {
        request.SetResponseStatus(userver::server::http::HttpStatus::kMovedPermanently);
        std::string link = all_links.at(id);
        link = "http://" + link;
        std::string header = "Location";
        request.GetHttpResponse().SetHeader(header, link);
        return {};
    }
    else
    {
        // TODO: search in db
        request.SetResponseStatus(userver::server::http::HttpStatus::kNotFound);
        request.GetHttpResponse().SetContentType({"text/html"});
        return "not found";
    }
}