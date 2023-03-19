Sistema MapSearch - Coordenadas Geográficas

Algorítmo desenvolvido em C++, com a principal função de buscar automaticamente no Google
Maps as coordenadas inseridas pelo usuário e também a função de armazenar as localizações
em um bloco de notas "locations.txt".

Caso não esteja funcionando, aqui vai um exemplo de coordenada correta para o programa: 
"-25.4255773,-49.2681186" (Localização: Passeio Público, em Curitiba).

Onde "-25.4255773" é a latitude (Relativa aos paralelos horizontais (Linha do Equador)).
e o "-" significa que está no Hemisfério Sul (Abaixo da linha do Equador). Caso esta latitude
fosse localizada no Hemisfério Norte, seria "25.4255773".

E "-49.2681186" é a longitude (Relativa aos paralelos verticais (Meridiano de Greenwich)).
Onde o "-" significa que está no Hemisfério Ocidental (A Oeste do Meridiano de Greenwich).
Caso esta longitude fosse localizada no Hemisfério Oriental, seria "49.2681186".

É necessário que tanto a latidude quanto a longitude possuam 7 casas decimais, pois o Google 
Maps é bastante preciso quanto a localizações.

Caso a coordenada inserida esteja incorreta, o Google Maps irá abrir o mapa com base na sua 
própria localização puxada através do seu IP.