#Trabalho Candy Crush
<h4>Trabalho de Lógica e Algorítimos #3 <h4>
<h5>Descrição: </h5>
	
<h6> O seguinte algorítimo tem por finalidade ler, utilizar da API "Canvas 2D - Versão C" de autoria de Cesar Tadeu Pozzer na implementação de funções básicas de desenho 2D na tela para utilização em casos mais complexos. Nesse trabalho, o programa implementado foi uma versão do jogo Candy Crush porém reformulado nas capacidades da linguagem C/C++. </h6>
	
<h5>Objetivos e apresentação:</h5>

<h6>	O jogo se baseia na apresentação de um tabuleiro de dimensões 9x9 como uma figura dentro de cada "casa" deste tabuleiro (81 peças) divididas entre sete figuras geométricas com cores e/ou figuras diferentes entre si, sendo seis delas capazes de se obter a qualquer momento a partir da renderização natural do jogo. Todo o jogo é manipulado a partir da solicitação do jogador e controlado utilizando somente as funções de movimentar e pressionar o botão esquerdo do mouse.</h6>

<h6>O objetivo do jogo é alterar as posições das peças com o mouse para formar combinações de peças iguas na horizontal, vertival ou ambos (casos de combinações cruzadas) com três ou mais doces iguais. A troca dessas peças e feita a partir de dois cliques do mouse, sendo um deles para a primeira posição e o segundo para a peça adjacente no qual se deseja realizar a troca. Será possível identificar as peças escolhidas uma vez que a mesma estará destacada após a seleção. Como regra fundamental, uma troca de peças só é válida quando após acontecer a alteração, uma ou mais combinações de peças forem possíveis se fazer. Caso a troca se mostrar irrelevante para o andamento do jogo, nenhum doce mudará de lugar Baseado no número de doces combinados em uma mesma troca, uma pontuação será apresentada no canto superior direito do tabuleiro, juntamente com uma mensagem de parabenização no canto superior esquerdo da tela. É importante salientar que para as seis peças padrões do jogo, nenhum fator além do número de peças combinadas influencia na contagem de pontos, ou seja, suas cores não são relevante nesse quesito.</h6>

<h6>Após a troca ter sido válidada, a primeira peça selecionada toma o lugar da segunda e vice versa, assim, todas as peças da mesma cor dentro da combinação formada serão "explodidas" exibindo uma pequena animação de explosão e logo serão substituídas por espaços em branco, onde as peças das fileiras de cima irão por si só	caírem conforme o tempo passa e subituindo os locais vazios. No topo onde restará sobrando espaço vazio, novas peças serão sorteadas de maneira aleatória. Enquanto o programa estiver ou quebrando peças ou realizando o ShiftDown (queda das peças superiores) nenhum clique ou seleção de doces será habilitado para evitar bugs.</h6>

<h5>Peças Especiais:</h5>

<h6>Como dito anteriormente, além das seis peças padrão do jogo há a implementação de uma peça especial onde carinhosamente foi chamada de "biscoitão". O biscoitão é obtido ao juntar-se cinco ou mais peças iguais, a partir daí, uma peça diferente das demais aparecerá na fileira destruída com as habilidades do biscoitão. Esse doce em especial tem a capacidade de destruir qualquer peça que por ele seja trocada, ou seja, se o biscoitão for trocado de posição com uma peça circular azul, todos círculos azuis no tabuleiro serão apagados e seus pontos serão registrados. Caso haja a troca de um biscoitão por outro, então todas as peças do tabuleiro serão "explodidas" e sorteadas novamente com seus pontos contabilizados.</h6>
  
<h5>Contagem de Pontos:</h5>
	
<h6>Tricas:                                   		  	     	+40 </h6>
<h6>Quadras ou Mais:                                                 	+80 (por peças além da trinca)</h6>
<h6>Cruz Comum:                                                      	+30</h6>
<h6>Cruzamento Vertical de Trica(em uma linha horizontal):           	+60</h6>
<h6>Cruzamento Vertical de Quadras ou mais(em uma linha horizontal): 	+80 (por peças além da trinca)</h6>
<h6>Biscoitão:                                                       	+15 (por peça explodida) </h6>

<h5>Implementação do Programa:</h5>

<h6>Para a manipulação do código do jogo, como já dito, foi utilizado das funções disponíveis na API Canvas 2D e das funções padrões do C, como math.h e string.h. Todo o programa no caso, é repetido sem interrupções na função "render" debtro da API que tem a capacidade de desenhar qualquer desenho na tela do computador a partir de cada alteração feita pelo usuário, no caso, dentro da função render há uma função chamada Iniciar que manda e retorna uma valor para uma mesma variável que por si só controlará o início do jogo para evitar a aleatoriedade do programa antes do necessário. </h6>

<h6>Para o desenho do tabuleiro do jogo foram denessário dos laços de repetição, um para linhas horizontais e outro para linhas verticais que no caso, a partir de um valor inicial (margem e piso) das coordenadas do tabuleiro esenham somando a si mesmo um valor em X ou Y no plano cartesiano para desenhar linhas de um tabuleiro quadriculado e representar setores onde entrarão cada figura do jogo. Na primeira jogada, todas peças do tabuleiro são sorteadas aleatoriamente a partir da biblioteca time.h e posteriormente serão mantidas para serem alterada somente pelo usuário. Para representar cada peça, há outros dois laços de repetição que percorrerão da mesma maneira que o desenho do tabuleiro, todo a matriz em branco para desenhar cada peça no exato centro das "casas" da malha e ter seus limites da figura alterados manualmente pelo programador em cada tipo de figura. Foram representado círculos, triângulos, hexágonos e quadrados pelas funções 'circle', 'rect' e 'polygon'.</h6>

<h6>Para o contador de pontos, a pontuação é configurada a medida das combinações do jogador e guardados em uma variável global. Tendo em vista que o programa só exibe textos estáticos, o valor da pontuação é converitido para um vetor que guardará cada ordem das unidades cimples (unidade, dezena, centena, etc.) e imprimirá cada uma na tela formando um valor só e exibindo a pontuação real do usuário.</h6>

<h6>Para a seleção de peças do jogador, o programa chama uma função sempre que as coordenadas do mouse estiverem dentro	do tabuleiro e o botão esquerdo for pressionado. A partir daí, o programa percorrerá todo a matriz do jogo comparando cada posição do mouse com sua coordenada reespecitiva do tabuleiro para assim, quando encontrar a posição correspondente, guardar essa informação em um ponteiro que receberá o endereço da matriz na posição específica para comparar posteriormente. Se durante a função de desenahr as peças, for encontrada a posíção onde o ponteiro possuir o mesmo endereço do doce, um quadrado dourado será desenhado em volta para demontrar que ali a peça foi selecionada. Para segunda seleção o funcionamento é exatamente igual, contudo, caso a segunda seleção seja a mesma posição que a primeira, a seleção será desfeita. Caso a segunda escolha esteja muito longe (qualquer posição que não seja adjacente a primeira seleção de maneira horizontal ou vertical) então a primeira seleção tomará o lugar segunda e a antiga seleção será desfeita.</h6>
	
<h6>Para a procura de combinações, dois laçoes de repeptição percorrerão toda a matriz do jogo procurando primeiramente por linahs horizontais que tenham o mesmo valor consecutivo de três ou mais peças iguais, para posteriormente, buscar combinações verticais. Caso seja encontrada uma combinação horizontal, outro laço percorrerá essa linha correspondente buscando por combinações verticais, formando assim, as combinações diferenciadas (cruzadas, forma de L ou T). Quando uma combinação é formada, todas as peças desta são substituídas por uma figuras vermelha e laranja para representar uma explosão das peças. Posteriormente, o programa procurará por essas figuras de explosão e automaticamente as substituirá por espaçoes em branco para realizar o ShiftDown. Como já dito, no topo novas peças serão sorteadas. Caso o jogador selecione duas peças que após sua troca não será possível realizar combinações, então a troca não será efetuada a as seleções do jogador serão desfeitas.</h6>

<h6>Durante o ShiftDown, cada peça válida será tranferida para baixo de cada vez, realizando um efeito visual de movimento dando a entender que as peças estão literalmente caindo nos espaços livres.	</h6>


	  
