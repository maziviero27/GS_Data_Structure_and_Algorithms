# GS_Data_Structure_and_Algorithms
Sistema desenvolvido em linguagem C para monitoramento de uma missão espacial experimental.

## Funcionalidades

- Inserção de dados da missão
- Visualização do status atual
- Análise automática de riscos
- Histórico de leituras
- Encerramento do sistema

## Fluxograma

```text
Início
  |
  v
Menu Principal
  |
  +--> Inserir Dados
  |
  +--> Visualizar Status
  |
  +--> Analisar Sistema
  |
  +--> Exibir Histórico
  |
  +--> Encerrar
           |
           v
          Fim
```

## Lógica Utilizada

O sistema armazena informações da missão em uma estrutura (`struct`) contendo:

- Temperatura da nave
- Nível de energia
- Status da comunicação
- Status operacional

Cada leitura é salva em um vetor de histórico, permitindo consultar os dados posteriormente.

Durante a análise automática, o sistema verifica:

- Temperatura acima de 80°C → Alerta de superaquecimento
- Energia abaixo de 20% → Modo de economia de energia
- Comunicação offline → Falha de comunicação
- Status crítico, falha ou risco → Risco operacional

Caso nenhuma condição crítica seja encontrada, a missão é considerada estável.

## Conceitos Aplicados

- Structs
- Vetores
- Funções
- Condicionais (`if`)
- Repetições (`for` e `do while`)
- Menu com `switch`
- Manipulação de strings
- Validação de entradas

## Autores

Arthur Maziviero Faria, 573928;
Tommaso C. Nagliatti,  572147.
