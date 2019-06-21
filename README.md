## Pokretanje

1) Docker
	- neophodno je imati instaliran docker
	- git clone https://github.com/salesh/klee.git
	- cd klee
	- docker build -t klee/klee .
	- docker run --rm -ti --ulimit='stack=-1:-1' klee/klee
	- cd klee_src/test/search-target-test
	- clang -I ../../include -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone test-1.c
	- klee --search=target-searcher --target-function=better_with_dfs test-1.bc 


2) Instaliranje u okviru host masine na linuxu, upustvo na linku http://klee.github.io/build-llvm60/<br/>
Napomena: U osmom koraku (Get KLEE source) treba klonirati ovaj repozitorijum

## Način upotrebe nove pretrage

```klee --exit-on-error --search=target-searcher --target-function=ime_funkcije ime_fajla.bc```<br/>  
Dakle, potrebno je navesti naziv pretrage **target-searcher**, zatim naziv funkcije u kojoj će biti primenjena DFS pretraga i ime odgovarajućeg .bc fajla. 

## Rezultati

U folderu target-searcher-stats nalazi se statistika upotrebe bfs, dfs i target-search pretraga pozivom klee alata sa parametrom --exit-on-error.
1) **BFS**
	- ```klee --exit-on-error --search=bfs test-1.bc```
	![alt text](./target-searcher-stats/bfs-test-1.png)
	- ```klee --exit-on-error --search=bfs test-2.bc```
	![alt text](/target-searcher-stats/bfs-test-2.png)
2) **DFS**
	- ```klee --exit-on-error --search=dfs test-1.bc```
	![alt text](/target-searcher-stats/dfs-test-1.png)
	- ```klee --exit-on-error --search=dfs test-2.bc```
	![alt text](/target-searcher-stats/dfs-test-2.png)
3) **TARGET SEARCHER**
	- ```klee --exit-on-error --search=target-searcher --target-function=better_with_dfs test-1.bc```
	![alt text](/target-searcher-stats/ts-test-1.png)
	- ```klee --exit-on-error --search=target-searcher --target-function=better_with_dfs test-2.bc```
	![alt text](/target-searcher-stats/ts-test-2.png)
  
Ova statistika pokazuje da ako označimo odgovarajuću funkciju (u kojoj će se izvršiti DFS pretraga) prilikom poziva target-searcher-a možemo dobiti bolje rezultate nego primenom samo BFS ili samo DFS pretrage. Najvažniji deo jeste izbor funkcija u kojima će se izvršiti DFS pretraga, tj. unaped treba odrediti takve funkcije.

## Izbor funkcija kod kojih će se koristiti DFS pretraga
Obe strategije, obilaska čvorova u dubinu (DFS) i širinu (BFS), funkcionišu tako što posećuju prvu narednu neposećenu granu i nove ulazne vrednosti se računaju na osnovu uslova dolaska u tu granu. Ipak, način na koji biraju narednu neposećenu granu se razlikuje kod obilaska u dubinu i širinu. Ukoliko bi program analizirao čitavo stablo, obe strategije će posetiti sve moguće putanje. Međutim, nekada zbog složenosti samog stabla to nije moguće (usled vremenskih i memorijskih ograničenja) i u takvim situacijama izbor jedne od ove dve strategije može uticati na krajnji rezultat analize.

Prednost DFS strategije je u sitacijama kada se analiza koda vrši korišćenjem jedne programske niti. U svakom trenutku, DFS obilazi jedno podstablo i onog trenutka kada je to 
podstablo pretraženo, može se ukloniti iz memorije, dok se kod BFS strategije celo stablo mora držati u memoriji sve vreme. Drugim rečima, DFS strategija je memorijski efikasnija. Sa druge strane, činjenica da se DFS zadržava u podstablu sve dok ga celo ne pretraži može biti i mana DFS-a ukoliko u podstablu ima jako puno mogućih putanja, što je slučaj na primer ukoliko se tu nalazi neka petlja, pa će veći deo vremena program provesti u malom delu stabla i time potencijalno preskočiti mnoge, "važnije" putanje. BFS ravnomerno prolazi celo stablo, pa ne može zapasti opisani problem.

Još jedna mana strategije obilaska u dubinu jeste da najpre bira čvorove koji su duboko u stablu, a na taj način su i uslovi dolaska u te čvorove kompleksniji za računanje (za rešavač), za razliku od BFS strategije koja najpre bira čvorove bliže korenu za koje je lakše izračunati uslove dolaska. 





## Primeri

Test fajlovi na kojima se može istestirati rad algoritma mogu se naći u folderu /test/search-target-test<br/>
Poziv za test-1.bc: ```klee --exit-on-error --search=target-searcher --target-function=better_with_dfs test-1.bc``` 
