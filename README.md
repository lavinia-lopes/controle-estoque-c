# 📚 Sistema de Controle de Estoque de Livros (Linguagem C)

Este projeto foi desenvolvido como parte do meu aprendizado prático em lógica de programação na **FATEC Rubens Lara (3º ciclo)**. O objetivo foi criar um sistema funcional para gerenciar um estoque de livros diretamente pelo terminal, focando em organização de dados e persistência em arquivos.

## 🛠️ O que eu utilizei (Detalhes Técnicos)

Para que o sistema fosse eficiente e os dados não fossem perdidos ao fechar o programa, apliquei conceitos fundamentais de C:

- **Structs e Vetores:** Usei para organizar as informações de cada livro (nome, autor, preço e quantidade) de forma estruturada.
- **Arquivos Binários (`.dat`):** Em vez de arquivos de texto comuns, usei arquivos binários com as funções `fwrite` e `fread`. Isso torna o armazenamento mais profissional e seguro.
- **Manipulação com `fseek`:** Este foi um dos pontos mais detalhados do projeto. Usei o `fseek` para navegar pelo arquivo e alterar apenas um dado específico (como um preço ou quantidade) sem precisar sobrescrever todo o estoque.
- **Exclusão Lógica:** Implementei a técnica de marcar registros com um asterisco (`*`). Isso permite "apagar" o livro para o usuário, mas manter o dado no arquivo para integridade do sistema.
- **Tratamento de Buffer:** Criei uma função específica para limpar o lixo do teclado (`limpa_buffer`), evitando erros comuns de leitura com `scanf`.

## 🚀 Funcionalidades do Sistema

O sistema conta com um menu interativo que permite:
1.  **Cadastrar** novos livros.
2.  **Listar** todo o estoque ativo.
3.  **Pesquisar** por nome, inicial do autor ou faixa de preço.
4.  **Alterar** dados (preço, quantidade ou o registro completo).
5.  **Excluir** livros de forma segura (exclusão lógica).

## 💻 Como testar
1. Compile o código com um compilador C (como o GCC).
2. Execute o arquivo gerado. O programa criará automaticamente o arquivo `livros.dat` para salvar suas informações.

---
*Este projeto reflete minha base em Engenharia de Software e minha capacidade de resolver problemas lógicos com código estruturado.*
