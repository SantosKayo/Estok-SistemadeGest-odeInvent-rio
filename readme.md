# PRÁTICA PROFISSIONAL FERRAMENTAS E TÉCNICAS DE PROGRAMAÇÃO

### Estok+ Sistema de Gestão de Inventário (Grupo 10)

# Integrantes:
    Ruan de Moura Trindade – RA 202413887
    Luís Felipe Costa Azevedo de Souza – RA 202430014
    Welinton Fernandes de Almeida – RA 202415966
    Cristian Alves de Sousa – RA 202412817
    José Iago Nascimento Silva – RA 202437674
    Kayo Pereira Santos – RA 202413584

# Professor Responsável:
    Pedro Fascina Casarin
# Atenção!

Projeto desenvolvido para fins educacionais! 

# Linguagem escolhida para desenvolvimento: C
- 📚 [Documentação da Linguagem C](https://learn.microsoft.com/pt-br/cpp/c-language/?view=msvc-170)

---

## Tutorial de Execução do Projeto Estok+

### Requisitos
Para compilar e executar o código em linguagem C, você precisará:
1. Compilador C (gcc ou similar)
2. Terminal para executar os comandos

### Instalando o GCC
Caso o GCC ainda não esteja instalado:
- **Windows**: Recomendado instalar via [MinGW](http://www.mingw.org/).
- **macOS**: O GCC pode ser instalado via `Xcode Command Line Tools`.
- **Linux**: A maioria das distribuições já inclui o GCC, mas pode ser instalado com os pacotes `build-essential`.

---

## Compilando e Executando o Projeto

### Passo 1: Compilar o Código
Navegue até a pasta onde o código está localizado e execute o seguinte comando no terminal:

```bash
gcc nome_do_arquivo.c -o nome_do_executavel
```

Substitua `nome_do_arquivo.c` pelo nome do arquivo de código principal (por exemplo, `estok.c`) e `nome_do_executavel` pelo nome que deseja dar ao executável.

### Passo 2: Executar o Código Compilado

#### **macOS/Linux**
Para executar o arquivo, utilize o seguinte comando:

```bash
./nome_do_executavel
```

#### **Windows**
Para executar o arquivo no Windows, utilize o seguinte comando no terminal:

```cmd
nome_do_executavel.exe
```

---

## Instruções Detalhadas por Sistema Operacional

### macOS
1. **Instale o GCC**: Execute o comando abaixo para instalar as ferramentas de linha de comando do Xcode:
   ```bash
   xcode-select --install
   ```
2. **Compile o Código**: Navegue até a pasta do projeto e compile:
   ```bash
   gcc nome_do_arquivo.c -o nome_do_executavel
   ```
3. **Execute o Programa**:
   ```bash
   ./nome_do_executavel
   ```

### Linux
1. **Instale o GCC** (se ainda não estiver instalado):
   ```bash
   sudo apt update
   sudo apt install build-essential
   ```
2. **Compile o Código**:
   ```bash
   gcc nome_do_arquivo.c -o nome_do_executavel
   ```
3. **Execute o Programa**:
   ```bash
   ./nome_do_executavel
   ```

### Windows
1. **Instale o GCC** via MinGW:
   - Baixe e instale o MinGW no site [mingw.org](http://www.mingw.org/).
   - No instalador, selecione a opção `gcc` para instalação.
   - Adicione o caminho do `bin` do MinGW ao `PATH` do sistema.
2. **Compile o Código**:
   - Abra o Prompt de Comando e navegue até a pasta do projeto.
   ```cmd
   gcc nome_do_arquivo.c -o nome_do_executavel.exe
   ```
3. **Execute o Programa**:
   ```cmd
   nome_do_executavel.exe
   ```

---

## Modelagem de Dados

### Estrutura da Entidade `Item`

Para o sistema de inventário, a principal entidade será `Item`, representando os produtos cadastrados no estoque. Cada item terá as seguintes propriedades:

| Campo               | Tipo           | Descrição                                          |
|---------------------|----------------|----------------------------------------------------|
| `id`                | `int`          | Identificador único do item, gerado automaticamente. |
| `nome`              | `char[50]`     | Nome do item.                                     |
| `descricao`         | `char[100]`    | Descrição detalhada do item.                       |
| `preco`             | `float`        | Preço do item, em reais.                           |
| `quantidade`        | `int`          | Quantidade disponível no estoque.                  |
| `data_criacao`      | `char[20]`     | Data e hora de criação do item, formato `dd/mm/aaaa hh:mm`. |
| `data_atualizacao`  | `char[20]`     | Data e hora da última atualização do item, formato `dd/mm/aaaa hh:mm`. |

#### Exemplo de Registro de Item
Um registro de item pode ser estruturado da seguinte forma em um arquivo ou banco de dados:

```plaintext
ID: 1
Nome: Parafuso
Descrição: Parafuso de aço, 3cm de comprimento
Preço: R$ 0,50
Quantidade: 1000
Data de Criação: 01/11/2024 10:30
Data de Última Atualização: 01/11/2024 10:30
```

---

## Operações Principais

### 1. **Adicionar Item**
   - Insere um novo item no inventário, gerando automaticamente o `id` e registrando a `data_criacao`.

### 2. **Listar Itens**
   - Exibe uma lista de todos os itens cadastrados no inventário, incluindo detalhes como `id`, `nome`, `descricao`, `preco`, `quantidade`, `data_criacao`, e `data_atualizacao`.

### 3. **Buscar Item por ID**
   - Permite localizar um item específico no inventário usando o `id` como chave de pesquisa.

### 4. **Editar Item**
   - Modifica as informações de um item existente, como `nome`, `descricao`, `preco`, e `quantidade`. Atualiza o campo `data_atualizacao` com a data e hora da modificação.

### 5. **Remover Item**
   - Remove um item do inventário usando o `id` como identificador. Realoca o array para atualizar o número total de itens.

---

## Observações

- **ID Auto-incremental**: O campo `id` é gerado automaticamente para cada novo item, garantindo unicidade dentro do inventário.
- **Data e Hora**: A `data_criacao` é definida na adição do item, enquanto `data_atualizacao` é alterada apenas ao editar o item.
- **Controle de Estoque**: `quantidade` representa a quantidade disponível no estoque e pode ser ajustada conforme as operações de entrada e saída de estoque.

---

Esse projeto foi desenvolvido para fins educacionais e tem como objetivo fornecer uma solução prática de controle de inventário em C. Caso tenha dúvidas, consulte a [Documentação da Linguagem C](https://learn.microsoft.com/pt-br/cpp/c-language/?view=msvc-170) para mais informações.