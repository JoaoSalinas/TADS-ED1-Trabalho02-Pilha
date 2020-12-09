# Definição do trabalho:

## Com base nos conceitos abordados em aula, referente a estrutura de Dados Pilha, implemente um jogo cartas (Burro) usando estrutura de dados PILHA e Lista Simplesmente Encadeada.

### Implementar um jogo simples de cartas(BURRO) com as funções:
  * Cria Naipe com 13 cartas
  * Cria Baralho com 4 Naipes. O baralho será uma estrutura de dados do tipo Pilha;
  * Embaralha as cartas (a função deve realizar o embaralhamento de modo aleatório, retirando cartas do baralho e colocando em  outros baralhos para simular a troca nas posições das cartas. Ao final do processo o baralho principal ficará alterado).
  * O jogo (main) deve ter no mínimo dois jogadores, cada jogador poderá ter uma lista de carta em sua mão (Lista Simplesmente Encadeada);
  * A cada rodada um jogador pode:
    * compra uma carta do baralho (pop) ou jogar um carta da sua lista de carta (Mão de cartas);
  * O adversário deve:
    * jogar uma carta do mesmo naipe (Primeiro jogador), caso não tenha esta carta, deve comprar (pop) do baralho, até encontrar a carta de mesmo Naipe;
  * O jogador que jogar a carta com maior valor vence a rodada e se tornará o primeiro jogador da próxima rodada;
  * O jogador que ficar sem cartas na mão primeiro vence o jogo;
