# APS1-Embarcados
**Descrição:**

Sistema embarcado que produz músicas monofônicas.

Link para o [vídeo](https://drive.google.com/file/d/1hq7CcMX19Wzr3KQtEtQPS3rvf2VTzqGl/view?usp=sharing).

**Passo a Passo de como usar o projeto**
1. Ligar os componentes de acordo com o diagrama abaixo.
2. Conectar a placa no computador. 
3. Abrir e rodar o código.
- Botão1: selecionar a música
- Botão2: tocar a música
- Botão3: ```play/pause```

![](desenho_APS1.png)

**Estrutura do projeto**
- ```function.c```: Neste arquivo estão as funções que controlam a música. Essas funções colocam a música para tocar e também fazem o ```play/pause```.

- ```functions.h```: Neste arquivo definimos nosso buzzer, botões e leds de acordo com seus PIOs.
Além disso, definimos nosso struct de música na qual contém as frequências e o tempo de cada nota.

- ```musicas.h```: guarda as frequências e o tempo de cada música selecionada para tocar.

- ```main.c```: no main chamamos functions.h e musicas.h. Neste criamos flags/ interrupções possibilitando 
que nossos botões tenham funcionalidades. Além disso, há a inicialização do uC e dos componentes definidos em ```functions.h```. Por fim, no ```main()``` está a função que integra todas as outras partes do código. Faz com que o programa rode e os leds pisquem, a música toque e outras funcionalidades dos botões.

**As funções são:**

- ```main()```: o main faz com que o LED1 piscam de acordo com a música que está sendo selecionada.
 Além disso, o LED2 pisca no ritmo da música que está tocando. Por fim, o main possiblita
que toque a música que foi selecionada.

- ```pause()```: possibilita parar a música e botar play quando quiser.

- ```sing(int freq[], int tempo[], int size)```: toca a música. Os argumentos passados para essa função são os vetores de frequência e tempo de cada nota musical e o tamanho desses vetores (que deve ser o mesmo).

**Rubricas:**
- C:
  - [x] Repositório com read.me, conexões elétricas, passos de como usar o projeto e link do vídeo;

  - [x] funcionalidade play/pause;

  - [x] Seleção musical;

  - [x] produz duas músicas;

  - [x] led piscando de acordo com a música;

  - [x] indicação de música selecionada.
  
- B:
  - [x] README.md explica o que é o projeto e como o software foi estruturado;
  - [x] Músicas separadas em ```.h```;
  - [x] Utiliza ```struct``` para organizar as músicas;
  - [x] Código organizado em funções e que recebem ```struct``` contendo música;
  - [x] Utiliza ```#define``` sempre que necessário;
  - [ ] Fecha todos os issues que forem abertos no repositório pelo professor (nenhum até o momento);
- B+:
  - [x] Toca uma terceira música. 

- A (1 item Embarcado + 1 item C):
  - Embarcado:
    - [ ] Utiliza dois falantes (para fazer uma música mais complexa);
    - [x] Utiliza interrupção nos botões.
  - C: 
    - [ ] Músicas organizadas em vetores de structs (ponteiros);
    - [x] Cria um arquivo ```.c``` ```.h``` com as funções de reprodução musical.
