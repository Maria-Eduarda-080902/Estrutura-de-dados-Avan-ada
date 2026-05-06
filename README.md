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
    - left_rotate
    - right_rotate
    - remove_fix
    - insert_fix
    - transplant
    - insert
    - search
    - search_helper
    - search_successor
    - get_successor
    - remove
    - print_to_file
    

#### Operator

Operator é uma subclasse da classe RedBlackTree, que serve como wrapper para a complexidade da classe. Permite que os dados sejam acessados com segurança.
 - **Métodos**
    - value: retorna o valor numérico do nó.
    - successor: 


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




