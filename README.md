# Criptografia RSA concorrente
A criptografia RSA precisa de duas chaves, uma pública e uma privada. A pública pode ser usada por qualquer pessoa que queira enviar uma mensagem encriptada para um destinatário. Mas essa mensagem só poderá ser decriptada com a chave privada, conhecida apenas pelo destinatário.  

Essas chaves são geradas a partir de dois números primos grandes, $p$ e $q$ (estes são testados probabilisticamente para a primalidade). Com eles, conseguimos calcular:
* O módulo $n = p \cdot q$
* A função totiente de Euler em $n$: $\phi(n) = (p-1) \cdot (q-1)$
* Um expoente $e$ tal que $1 < e < \phi(n)$ e $e$ e $\phi(n)$ sejam primos entre si
* Um expoente $d$ tal que $d \cdot e \equiv 1 \pmod{\phi(n)}$, i.e., $d$ é o inverso multiplicativo de $e$ em $\pmod{\phi(n)}$

Por fim, a chave pública é o par $(n, e)$ e a chave privada é $d$ (também poderíamos armazenar $p$ e $q$ para acelerar a decriptação).  

## Encriptação
Para encriptar uma mensagem $m$, basta calcular $c \equiv m^e \pmod{n}$, onde $c$ é a mensagem encriptada.

## Decriptação
Para recuperar a mensagem $m$ a partir de $c$, é necessário calcular $m \equiv c^d \pmod{n}$.

## Segurança
A segurança desse tipo de criptografia é baseada na dificuldade de fatoração de números tão grandes. Se conseguirmos fatorar $n$, então conseguimos calcular $p$ e $q$, e com isso, a chave privada $d$. Portanto, utilizamos a biblioteca GMP (GNU Multiple Precision Arithmetic Library) para realizar operações com números grandes e não comprometer a segurança do RSA.

## Como Executar o programa
Para a compilação dos dois programas, é necessária a instalação das bibliotecas pthread e gmp, além da math.h.  
A compilação pode ser dada pelo comando:

~~~bash
gcc decriptar.c -o dec -lgmp -lm -lpthread
gcc decriptarSequencial.c -o decSeq -lgmp -lm
~~~
Para a execução, temos: 
~~~bash
./dec <nomeDoArquivo.txt> <nThreads>
./decSeq <nomeDoArquivo.txt>
~~~

## To do 
- [x] Resolver a falha de segmentação (com arquivos grandes) em descriptar.c
- [x] Atualizar dicionário número->letra e letra->número, removendo caracteres que não aparecem no prompt
- [x] Gerar txt (em python) do texto original sem acentos
- [x] Gerar txt (em c) do texto descriptado (sem acentos)
- [x] Nos testes, comparar o txt descriptado com o txt original
- [ ] Paralelizar a leitura dos arquivos