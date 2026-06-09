# link_shortener_on_userver

Сервис для сокращения ссылок, написанный с использованием userver.

## Запуск:
Запустить:
```bash
docker compose -f ./docker-compose.yaml up
```
Завершить:
```bash
docker compose down
```

## API

* HTTP POST по пути "/v1/create" с параметрами запроса "shortlink" и "longlink" запоминает пару переданных короткой и длинной ссылки
* HTTP GET по пути "/v1/link/{id}" перенаправляет на длинную ссылку, с короткой ссылки {id}

Пример:
```bash
$ curl -X POST 'localhost:8083/v1/create?shortlink=wiki&longlink=http://www.wikipedia.org' -i
HTTP/1.1 201 Created
Date: Tue, 09 Jun 2026 23:07:27 UTC
Server: userver/2.16-rc (20260329065830; rv:c97c635)
traceparent: 00-204437e3885246d033879b80b16977cb-3eac2e4ef204e18f-01
X-YaRequestId: 5075e43fc9261e48a5b53e1867d348c0
X-YaTraceId: 204437e3885246d033879b80b16977cb
X-YaSpanId: 3eac2e4ef204e18f
Accept-Encoding: gzip, zstd, identity
Content-Type: text/plain; charset=utf-8
Connection: keep-alive
Content-Length: 4

wiki
$ curl GET 'localhost:8083/v1/link/wiki' -i
HTTP/1.1 302 Found
Date: Tue, 09 Jun 2026 23:07:43 UTC
Content-Type: application/octet-stream
Server: userver/2.16-rc (20260329065830; rv:c97c635)
traceparent: 00-aca4d55fc5f36a9750202f576062624d-769a91de311f7c67-01
X-YaRequestId: cdf8af6ba3fbe79284d9f71ef06910d8
X-YaTraceId: aca4d55fc5f36a9750202f576062624d
X-YaSpanId: 769a91de311f7c67
Accept-Encoding: gzip, zstd, identity
Location: http://www.wikipedia.org
Connection: keep-alive
Content-Length: 0


```