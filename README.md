# ECOM042-monitoria

## Atividade 03 — Entradas e saídas com GPIO emulado

Todo firmware conversa com o mundo externo por pinos digitais ou analógico: uma saída
acende um LED, uma entrada lê um botão. Em código, isso é configurar cada
pino na direção certa e depois escrever ou ler seu nível lógico, sempre
pela API de GPIO do driver, nunca mexendo direto no hardware.

Sem placa física, o `native_sim` traz um controlador **GPIO emulado**. 

Ele responde à mesma API de um controlador real e ainda permite
simular o mundo externo, como "apertar" um botão, direto do código.

Só que o hardware não fica hardcoded no código: quem descreve *quais pinos
existem e pra que servem* é o **devicetree**. 

Sua tarefa é escrever um módulo de entradas/saídas com esse LED (saída) e
com um botão no pino 1 de `gpio0` (entrada, alias `sw0`), ambos ativos em
nível alto, e usá-lo em `main()`: para cada valor da sequência `0, 1, 0, 1`,
simule o botão, leia seu estado, copie-o para o LED e imprima:

```
Button: 0 -> LED: 0
Button: 1 -> LED: 1
Button: 0 -> LED: 0
Button: 1 -> LED: 1
```

A interface do módulo já está em `src/board_io.h` (`io_init`, `led_set`,
`button_read`). Cabe a você
criar o overlay (`app.overlay`), implementar o módulo, completar o
`main()` e habilitar o suporte a GPIO e ao emulador no `prj.conf`. Enquanto
o alias `sw0` não existir, o build não passa. O CI (`clang-format`, build e
testes) roda no seu PR e valida se a solução está correta.

Como entregar

 Faça um **fork** deste repositório.

No seu fork, crie/trabalhe numa branch com o **mesmo nome da
atividade** (ex.: `Atividade-03`) — o CI identifica qual atividade
corrigir pelo nome da branch do PR.

Implemente sua solução nessa branch e dê push pro seu fork.

Abra um **Pull Request** do seu fork pra este repositório, usando essa
branch como origem.

O CI roda automaticamente no PR (clang-format, build e testes). Se algo
falhar, corrija e dê push de novo na mesma branch — o PR atualiza
sozinho, sem precisar abrir um novo.
