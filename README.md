# Estrutura de dados Avançada - Árvore Rubro-Negra com Persistência Parcial

## Linguagem 

C++

## Como Rodar

### Pelo arquivo makefile

        make build
        make run ARGS="<arquivo>"

### Pela linha de comando 

        g++ -Wall -g main.cpp -o main -Wfatal-errors
        ./main.exe <arquivo>


Substituindo <arquivo> pelo caminho do arquivo de testes.

### Explicação do Código 

A explicação que segue é de Classes, Estruturas e Métodos presentes no arquivo redBlackTree.h

### Classes
#### RedBlackTree

RedBlackTree é a classe principal que engloba toda a lógica do programa.

- **Propriedades**
    - Node *root: Ponto de partida da raíz e atributo auxiliar na busca.
    - vector<pair<Node *, int>> roots: Histórico de versões da Raíz.
    - int current_version: Variável auxiliar da versão atual.

 - **Métodos**
    - create_root: Cria um novo par para a raíz e inclui na última posição do histórico
    - get_root: Cria a variável auxiliar root para controle. Confere se o tamanho do histórico da raíz é maior do que um. Se sim, percorre o histórico até encontrar a raíz e atribuí-la à variável root. Se não for maior do que um, atribui o valor da raíz do nó à variável root. No fim, retorna a variável root.

    - left_rotate: Recebe um nó e a versão. Realiza a rotação à esquerda utilizando o método modify para atualizar o filho direito do nó e o filho esquerdo do pivô (aux). Se o nó original era a raiz, registra o pivô como a nova raiz da versão via create_root; caso contrário, atualiza o pai do nó para apontar para o pivô.

    - right_rotate: Executa o inverso da rotação à esquerda. O filho esquerdo do nó torna-se o novo pivô. A função utiliza o modify para redefinir as conexões de parentesco e descendência, garantindo que a rotação seja registrada no histórico da versão atual sem destruir os estados anteriores.

    - insert_fix: Função recursiva que corrige violações rubro-negras após uma inserção. Analisa a cor do "tio" do nó atual através de get_uncle. Dependendo do caso (recoloração ou rotações), dispara o método modify para alterar cores e as funções de rotação para reestruturar a árvore na versão atual.

    - remove_fix: Restaura o equilíbrio da árvore após a remoção de um nó preto. Percorre a estrutura corrigindo o déficit de cor preta através de recolorações e rotações nos nós irmãos (right_child ou left_child), registrando cada ajuste de cor e ponteiro no vetor de modificações (mods) dos nós envolvidos.

    - transplant: Auxilia a substituição de uma subárvore por outra dentro de uma versão. Atualiza o pai do nó removido para apontar para o substituto e ajusta o ponteiro de pai do substituto via modify. Se o nó removido for a raiz, registra o substituto como a nova raiz da versão.

    - insert: Incrementa a versão atual e cria um novo nó vermelho. Realiza a busca binária para encontrar o local de inserção. Ao encontrar, utiliza o modify no nó pai para conectar o novo filho e, por fim, chama o insert_fix para validar as propriedades da árvore.

    - remove: Inicia incrementando a versão e buscando o nó alvo via search. Se o nó tiver dois filhos, localiza o sucessor para substituição. Utiliza a função transplant para reorganizar a estrutura e, caso a cor original do nó movido seja preta, executa o remove_fix.

    - search: Interface pública que obtém a raiz da versão desejada através de get_root e inicia a busca chamando o search_helper.

    - search_helper: Função recursiva de busca binária. Navega pelos nós comparando valores, utilizando get_left e get_right com o parâmetro de versão para garantir que a navegação respeite os ponteiros válidos naquele tempo específico.

    - search_successor: Localiza o nó com o menor valor que seja maior que o valor de referência na versão informada. Percorre a árvore até encontrar o valor e então aplica as regras de sucessor (mínimo da subárvore direita ou ancestral à esquerda).

    - get_successor: Função de conveniência que retorna o valor inteiro do nó encontrado por search_successor. Se o sucessor não existir na versão informada, retorna a constante INFINITY.

    - print_to_file: Realiza um percurso em ordem (in-order) na árvore de uma versão específica. Percorre os nós do menor para o maior, calculando a profundidade e identificando a cor (R ou B) através de get_color. Os dados (valor, profundidade e cor) são formatados e enviados simultaneamente para o console e para um arquivo externo.
    

#### Operator

Operator é uma subclasse da classe RedBlackTree, que serve como wrapper para a complexidade da classe. Permite que os dados sejam acessados com segurança.
 - **Métodos**
    - value: retorna o valor numérico do nó.
    - successor: Recebe um ponteiro de nó e a versão desejada. O método identifica o sucessor do nó atual na hierarquia da árvore rubro-negra para aquela versão específica. Se o nó possuir uma subárvore direita, ele busca o valor mínimo dessa árvore; caso contrário, ele sobe na hierarquia para encontrar o primeiro ancestral à direita, retornando o próximo nó em ordem crescente ou nullptr se o nó for o maior da árvore.


### Structs

#### Node
- **Propriedades**
    - int value: Valor Numérico do Nó
    - COLOR color: Valor dentro do ENUM COLOR
    - Node *left: Ponteiro para o Filho Esquerdo
    - Node *right: Ponteiro para o Filho Direito
    - Node *parent: Ponteiro para o nó Pai
    - Node *return_left: Ponteiro auxiliar para avisar ao filho esquerdo que o nó foi atualizado sem precisar percorrer o vetor de modificações.
    - Node *return_right: Ponteiro auxiliar para avisar ao filho direito que o nó foi atualizado sem precisar percorrer o vetor de modificações
    - Node *return_parent: Ponteiro auxiliar para avisar ao nó pai direito que o nó foi atualizado sem precisar percorrer o vetor de modificações
    - Node *next: Ponteiro para a próxima cópia do Nó.
    - vector<Mod> mods: Vetor de Modificações do Nó. Possui o limite de tamanho de 6.

- **Métodos**

    - get_color(Versão, Cor): Serve para retornar a a cor da versão selecionada. Confere se o nó é nulo. Se sim, retorna a cor do parâmetro. Se não for, [nusei]. Então confere se o vetor de modificações está vazio. Se sim, retorna cor. Se não, segue e percorre o vetor de modificações até encontrar a última modificação que tenha como type_field o valor 0 e que seja menor ou igual à versão do parâmetro, alocando este valor na variável Cor. Depois, confere se a versão pedida é maior do que a última versão. Se sim, retorna a última cor modificada. Se Não, checa se o nó tem uma próxima cópia. Se sim, chama o método de forma recursiva para a cópia e retorna o resultado. No fim, , caso nenhuma das condições tenha sido atendida, retorna a variável cor, que deve ter sido alterada durante a checagem do vetor de modificações.

    - get_left(Versão, left): Serve para retornar o ponteiro para o filho esquerdo da versão selecionada. Confere se o nó é nulo. Se sim, retorna o nó. Se não for, [nusei]. Então confere se o vetor de modificações está vazio. Se sim, retorna left. Se não, segue e percorre o vetor de modificações até encontrar a última modificação que tenha como type_field o valor 1 e que seja menor ou igual à versão do parâmetro, alocando este valor na variável left. Depois, confere se a versão pedida é maior do que a última versão. Se sim, retorna a variável left alterada (a última versão). Se Não, checa se o nó tem uma próxima cópia. Se sim, chama o método de forma recursiva para a cópia e retorna o resultado. No fim, caso nenhuma das condições tenha sido atendida, retorna a variável left, que deve ter sido alterada durante a checagem do vetor de modificações.

    - get_right(Versão, right): Serve para retornar o ponteiro para o filho esquerdo da versão selecionada. Confere se o nó é nulo. Se sim, retorna o nó. Se não for, [nusei]. Então confere se o vetor de modificações está vazio. Se sim, retorna left. Se não, segue e percorre o vetor de modificações até encontrar a última modificação que tenha como type_field o valor 2 e que seja menor ou igual à versão do parâmetro, alocando este valor na variável right. Depois, confere se a versão pedida é maior do que a última versão. Se sim, retorna a variável right alterada (a última versão). Se Não, checa se o nó tem uma próxima cópia. Se sim, chama o método de forma recursiva para a cópia e retorna o resultado. No fim, caso nenhuma das condições tenha sido atendida, retorna a variável right, que deve ter sido alterada durante a checagem do vetor de modificações.

    - get_parent(versão, parent): Serve para retornar o ponteiro para o pai da versão selecionada. Confere se o nó é nulo. Se sim, retorna o nó. Se não for, usa um operador ternário para contar com o fato de que o Parent pode ser um Nullpointer, significando que o nó é uma raíz. Então confere se o vetor de modificações está vazio. Se sim, retorna parent. Se não, segue e percorre o vetor de modificações até encontrar a última modificação que tenha como type_field o valor 3 e que seja menor ou igual à versão do parâmetro, alocando este valor na variável parent. Depois, confere se a versão pedida é maior do que a última versão. Se sim, retorna a variável parent alterada (a última versão). Se Não, checa se o nó tem uma próxima cópia. Se sim, chama o método de forma recursiva para a cópia e retorna o resultado. No fim, caso nenhuma das condições tenha sido atendida, retorna a variável parent, que deve ter sido alterada durante a checagem do vetor de modificações. Retornar nullpointer significa que o nó é uma raíz.

    - get_grandparents: Serve para retornar o pai do pai do nó na versão selecionada. Primeiro, confere se o pai do nó na versão selecionada é um Nullpointer chamando o método get_parent. Se sim, significa que o nó é uma Raíz. Se não for, o método get_parent é chamado para o Parent do nó. Se o Parent do Parent for um nullpointer, significa que o pai do nó é uma raíz.

    - get_uncle: Serve para retornar o irmão do pai do nó na versão selecionada. Testa se o avô do nó é um nullpointer utilizando o método get_grandparent. Se não for, confere se o pai do nó é um filho esquerdo. Se sim, retorna o filho direito do avô do nó. Se não, retorna o filho esquerdo do avô do nó.

    - is_left_child / is_right_child: Métodos que servem para conferir se o nó é um filho esquerdo ou direito. Em ambos os métodos, confere se o pai do nó é um Nullpointer (se o nó é raíz), e se não for, retorna se o valor do nó é igual ao valor do filho direito ou esquerdo do pai do nó. Separados para fins de legibilidade.

    - create_mod: Cria uma nova modificação utilizando os valores do Nó.. Então, checa o tipo de campo que deve ser alterado e faz a alteração através do parâmetro Cor (caso o campo seja 0) ou pelo parâmetro Pointer se a atualização for relacionada aos relacionamentos do Nó.

    - modify: Método de persistência do nó. Testa se o nó é nulo e, se não for, cria uma variável auxiliar copiando o nó. Percorre a cadeia de cópias do nó para que possa copiar a última, e então confere se o vetor de modificações da última cópia válida chegou ao tamanho máximo (6). Se sim, faz uma nova cópia chamando o método make_copy, e aloca na variável auxiliar. Então, cria uma nova modificação com os valores passados nos parâmetros, na versão correta e na última cópia válida.

    - make_copy: Cria uma nova cópia do nó passado por parâmetro. Primeiro, copia todos os valores do nó "original" (nó do parâmetro) em um novo nó. Percorre o vetor de modificações do nó original para garantir que os valores da cópia estão de acordo com a última versão registrada. Por fim, configura o nó cópia como próxima cópia do nó original. Então, o método tem uma sequência de Ifs para conferir os relacionamentos do nó original (Filho direito, filho esquerdo e pai), checando se não são nullpointers, e se o relacionamento deles com o nó original está correto, e então modificando os ponteiros para apontar para a cópia.

#### Mod 
- **Propriedades**

    - Node *left: Ponteiro para o Filho Esquerdo
    - Node *right: Ponteiro para o Filho Direito
    - Node *parent: Ponteiro para o nó Pai
    - COLOR color: Valor dentro do ENUM COLOR
    - int version: Identificador de versão do nó.
    - int type_field: identificador do tipo de campo sendo alterado. 0 para Cor, 1 para alterar o ponteiro Left, 2 para alterar o ponteiro Right, 3 para alterar o ponteiro Parent.




