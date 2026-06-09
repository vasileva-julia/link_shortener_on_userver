from http import HTTPStatus


# async def test_redirect_existing_link(service_client, pgsql):
#     response = await service_client.post('/v1/create', params = {'longlink': 'http://www.wikipedia.org/',
#                                                                 'shortlink' : 'wiki'})
#     assert response.status == HTTPStatus.CREATED
#     response = await service_client.get('/v1/link/wiki')
#     assert response.status == HTTPStatus.FOUND
#     assert response.headers.get('Location') == 'http://www.wikipedia.org/'

async def test_redirect_new_link(service_client):
    response = await service_client.get('/v1/link/wiki')
    assert response.status == HTTPStatus.NOT_FOUND