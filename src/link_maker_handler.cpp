#include "link_maker_handler.hpp"

#include "shortener/sql_queries.hpp"

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
    if (request.GetMethod() != userver::server::http::HttpMethod::kPost)
    {
        throw userver::server::handlers::ClientError(userver::server::handlers::ExternalBody
            {fmt::format("Unsupported method {}", request.GetMethod())});
    }
    request.GetHttpResponse().SetContentType(userver::http::content_type::kTextPlain);

    if (!request.HasArg("longlink") || !request.HasArg("shortlink"))
    {
        request.SetResponseStatus(userver::server::http::HttpStatus::kBadRequest);
        if (!request.HasArg("longlink") && !request.HasArg("shortlink"))
            return "need arguments longlink shortlink";
        if (!request.HasArg("longlink"))
            return "need arguments longlink";
        if (!request.HasArg("shortlink"))
            return "need arguments shortlink";
    }
    std::string longlink = request.GetArg("longlink");
    std::string shortlink = request.GetArg("shortlink");

    userver::storages::postgres::Transaction transaction = 
            pg_cluster_->Begin("transaction_link_creation",
                               userver::storages::postgres::ClusterHostType::kMaster,
                               {});

    auto result = transaction.Execute(shortener::sql::kInsertLinksPair, shortlink, longlink);
    if (result.RowsAffected())
    {
        transaction.Commit();
        request.SetResponseStatus(userver::server::http::HttpStatus::kCreated);
    }
    else
    {
        result = transaction.Execute(shortener::sql::kSelectLonglinkByShortlink, shortlink);
        transaction.Rollback();
    
        if (!result.IsEmpty())
            request.SetResponseStatus(userver::server::http::HttpStatus::kConflict);
        else
            request.SetResponseStatus(userver::server::http::HttpStatus::kInternalServerError);
    }

    return shortlink;
}