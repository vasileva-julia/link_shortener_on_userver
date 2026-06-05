async def test_redirect_existing_link(service_client, pgsql):
    cursor = pgsql['db_1'].cursor()
    cursor.execute('INSERT INTO mydb.urls VALUES (\'wiki\', \'www.wikipedia.org/\');')
    response = await service_client.get('/v1/link/wiki')
    assert response.status == 308
    assert response.headers.get('Location') == 'www.wikipedia.org/'


async def test_redirect_new_link(service_client):
    response = await service_client.get('/v1/link/wiki')
    assert response.status == 404