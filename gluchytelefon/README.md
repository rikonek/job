# Głuchy telefon

Napisać serię programów komunikujących się ze sobą za pomocą różnych protokołów IPC. Każdy z programów ma za zadanie przed przekazaniem wiadomości przekształcić ją w odpowiedni sposób.

Wszystkie programy powinny być budowane za pomocą makefile'ow (np. autotools, cmake bądź gnu make). Przynajmniej jeden z programów powinien być napisany w python'ie. Kod pod kontrolą lokalnego git-a. Sposób uruchamiania dowolny ale zintegrowany (przy użyciu jednej komendy). W przypadku gdy wynik którejś z modyfikacji przekroczy zakres u32, powinna pojawić się o tym informacja na wyjściu. Wejściowa aplikacja "Konsola" przyjmuje liczby do momentu gdy użytkownik wciśnie ctrl+c, wówczas wszystkie programy powinny zostać pozamykane.

- **Wiadomość**: liczba unsigned 32 bity
- **Środowisko**: dowolny linux (natywny, bądź zwirtualizowany w virtualbox'ie)

1. "Konsola":
    - Wejście: stdin
    - Modyfikacja/wyjście: x:=x+1
2. "Argument"
    - Wejście: argument do programu parsowany za pomocą getopt
    - Modyfikacja/wyjście: x:= lustrzane odbicie bitów, np. dla 6(110):= 3(011)
3. "Pipe"
    - Wejście: Nazwany pipe
    - Modyfikacja/wyjście: Następna liczba pierwsza
4. "Jajko"
    - Wejście: interfejs znakowy (linux kernel module over chrdev)
    - Modyfikacja/wyjście: Liczba ciągu Fibonacciego odpowiadająca otrzymanemu numerowi
5. "Netlink"
    - Wejście: Generic netlink
    - Modyfikacja/wyjście:
        - jeżeli liczba jest parzysta -> x=x/2
        - jeżeli nie -> przekształcenie bitowe według schematu ABCD -> BDAC, gdzie A,B,C i D to 8-bitowe cząstki liczby wejściowej
6. "Sieć"
    - Wejście: Stream tcp
    - Wyjście: stdout na osobnej konsoli -> zmodyfikowana liczba lub info o przekroczeniu zakresu