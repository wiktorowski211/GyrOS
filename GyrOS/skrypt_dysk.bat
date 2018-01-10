echo 1. Zapisuje do pliku plik1.txt slowa 'Hello World'
echo Hello World>plik1.txt
echo 2. Wyswietlam plik 'plik1.txt'
type plik1.txt
echo 3. Dopisuje do pliku slowa ' ITS ME!'
echo  ITS ME!>>plik1.txt
echo 4. Wyswietlam plik 'plik1.txt'
type plik1.txt
echo 5. Dodaje alias 'hello.txt' do 'plik1.txt'
mklink hello.txt plik1.txt
echo 6. Wyswietlam plik 'hello.txt'
type hello.txt
echo 7. Usuwam plik 'plik1.txt'
del plik1.txt
echo 8. Wyswietlam plik 'hello.txt'
type hello.txt
echo 9. Nadpisuje plik 'hello.txt' slowami 'Good Bye'
echo Good Bye!>hello.txt
echo 10. Zmieniam nazwe 'hello.txt' na 'bye.txt'
rename hello.txt bye.txt
echo 11. Wyswietlam plik 'bye.txt'
type bye.txt
echo 12. Usuwam plik 'plik1.txt'
del bye.txt