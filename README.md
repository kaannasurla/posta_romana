# Sistem gestionare corespondență Poșta Română
### NASURLA_KAAN_315CC
### Timp de implementare: 30 ore
### Scurt rezumat pe taskuri:
## ====== TASK 1 =========
### acesta functie este responsabila cu citirea de la tastatura 
### ps: trebuie mare atentie la alocarea memoriei, altfel ai o gramada de segfaulturi
## ====== TASK 2 =========
### se initializeaza toate campurile cu 0, pentru inceput. aplic operatii pe biti (mutand la stanga)
## ====== TASK 3 =========
### fac atribuiri postasului in baza idului
## ====== TASK 4 =========
### este o sortare in functie de 2 factori. rioritate si greutate. apoi daca astea sunt egale le returnezi in ordinea in care sunt primite.
### ps:avand in vedere ca e un numar mic de colete care necesita sa fie sortate, am decis sa folosesc bubblesort (compara doua colete si le interschimba in functie de situatie).
## ====== TASK 5 =========
### regex, dar conceptual e acelasi lucru, elimini semnele de punctuatie si numeri cate cuvinte ai, apoi convertesti in vector si folosesti inversia unui vector pentru a “codifica” mesajul. din moment ce literele din interiorul cuvantului raman in aceeasi ordine, e si mai simplu. fac doar astfel incat a[x] = b[a.lungime] si apoi crescator il iterez pe x pana ajunge la marimea lui a.
## ====== TASK 6 =========
### functia modelare_cod aplica o criptare asupra unui cod initial, utilizand factorizarea numerelor.
functia operatie_cod parcurge un set de pachete si, in functie de ID-ul postasului, aplica functia de criptare pe pachetele care contin o anumita cifra corespunzatoare ID-ului postasului.
## ====== TASK 7 =========
### punctajul final reprezinta numarul de pachete care au avut un cod corect în raport cu numarul total de pachete. fiecare pachet corect adauga la punctaj 1.0 / nrPachete. Astfel, punctajul total va fi un numar între 0 și 1, unde:
#### 0 înseamna ca niciun pachet nu a avut codul corect.
#### 1 înseamna că toate pachetele au avut codurile corecte.
