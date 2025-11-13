Funcionalidades a serem implementadas

Relação de pacientes:
    pacientes devem estar numa lista
    funcs:
    - inserir paciente
    - apagar paciente
    - buscar paciente
    - listar todos os pacientes

Triagem dos pacientes:
    Quem chega primeiro é atendido primeiro (FIFO) -> fila
    Nesse caso a fila tem tamanho máximo, que eu mesmo defino
    funcs:
    Fila vazia
    Fila cheia

Histórico do paciente:
    O ultimo histórico é o primeiro a ser descartado (LIFO) -> pilha
    cada paciente tem no máximo 10 históricos
    cada histórico tem até 100 caracteres

    funcs:
    inserir
    retirar
    consultar
    historico cheio/vazio

Interface:
1. Registrar paciente -> mensagem de aviso para que não haja ID repetido
2. Registrar óbito de paciente -> um paciente só morre se já tiver sido chamado para atendimento
3. Adicionar procedimento ao histórico médico -> busca o paciente pelo ID e adiciona ou remove o item, reportar caso não haja procedimento a remover ou se o paciente não for encontrado
4. Desfazer procedimento do histórico médico
5. Chamar paciente para atendimento -> tira paciente da fila
6. Mostrar fila de espera
7. Mostrar histórico do paciente
8. Sair

Persistencia de dados:
Por simplicidade, sugerimos o seguinte
comportamento: ao sair do sistema, armazene tudo de uma única vez (a lista de paciente,
a fila de pacientes e os históricos de atendimento). Ao entrar no sistema, recarregue tudo
Nota: Isso pode, e deve, ser feito com um TAD! Sugestão de nome: IO (Input/Output).
Outra opção é vc estender os TADs já existentes e implementar funções utilitárias do
tipo save() e load(). Cada um de seus TAds pilha, fila e lista teriam um par de métodos
que escreveriam para o disco e leriam do disco.


Testes
