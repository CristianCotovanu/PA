
1.  Temele buclucase    
      Algoritmul a fost conceput conform programarii dinamice.  
      Dinamica se desfasoara pe doua dimensiuni si anume:  
      - prima corespunde temei pana la care s-au folosit pentru scorul curent  
      - a doua corespunde numarului de saptamani necesare pentru a completa temele   
      
      Matricea hwsDone ne va ajuta sa verificam ce teme au fost rezolvate in  
      configuratia curenta astfel: hwsDone[h][w] este 0 daca tema "h" nu se afla in  
      configuratie, altfel hwsDone[h][w] este 1, tema figurand in configuratie.
        
      Algoritm:  
      - am sortat temele crescator dupa deadline
      - recurenta folosita este:
              w + hws[h + 1].timp < hws[h + 1].dline este verificarea indexului in limite  
              dp[h][w] + hws[h + 1].score > dp[h + 1][w + hws[h + 1].timp]  
              In limbaj natural, daca tema h + 1 m-ar ajuta la maximizarea scorului  
              o voi lua in considerare, altfel nu.  
      - rezultatul se va afla pe ultima linie a matricei  
      (unde se iau in considerare toate temele pentru calculul scorului)

2.  Numarul Magic  
Algoritmul a fost conceput conform divide et impera, respectiv algoritmul  
gasirii distantei minime intre doua puncte (closest pair of points).  
Am abordat problema adaptand algoritmul de la problema distantei dintre doua puncte  
pentru a satisface cerintele temei, anume am atribuit fiecarui numar doua dimensiuni:  
indexul in vectorul initial si suma elementelor cu indecsi mai mici (sume partiale).
  
    Algoritm:  
    - sortam vectorul dupa primul criteriu.
    - stabilim mijlocul vectorului.
    - gasim minimul pe cele doua subintervale (stang, respectiv drept)
    - consideram ca fiind distanta minima minimul dintre dist_stg si dist_drpt
    - apoi luam in considerare faptul ca s-ar putea ca distanta minima sa se gaseasca  
    exact unde am impartit vectorul initial, asadar vom verifica si cazul acesta.  
    Daca distanta gasita este mai mica, modificam valoarea acesteia.
    - distanta minima a fost gasita acum.  
    
3.  Ratustele  
    Algoritmul a fost conceput conform tehnicii greedy.  
    Ideea principala este: in timpul unei coliziuni daca ratele nu ar avea identificatori,  
    se poate considera ca acestea se intersecteaza dar nu isi modifica directiile, ci trec una pe langa alta.  
    Asadar am calculat niste timpi de cadere evitand orice fel de coliziune   
    (ca si cum rata ar merge exact catre capat fara nicio ciocnire)
      
    Algoritm:  
    -   sortez ratele crescator in functie de timpul de cadere, respectiv
      dupa id.
    - retin timpul la care ar trebui sa cada a K-a rata.
    - sortez ratele crescator in functie de coordonatele x si y din "matrice",
      respectiv dupa id.
    - retin indecsii initiali ratelor intr-o structura auxiliara.
    - ratele se vor efectua un numar de mutari egal cu timpul necesar celei de-a K rata sa cada.
    - ratele sunt sortate apoi crescator in functie de coordonatele x si y din "matrice",
      respectiv dupa id.
    - indecsii initiali vor fi restaurati.
    - ratele cazute in acelasi moment cu rata K, vor adaugate intr-o  
      structura auxiliara si vor fi sortate in functie de id.

4.  Jocul numerelor impare  
    Algoritmul a fost conceput avand in minte programarea dinamica.  
    Dinamica se desfasoara pe 3 dimensiuni si anume:  
    Fie "i" indexul de la iteratia curenta  
    - prima dimensiune constituie pentru 0 cea mai buna solutie tinand cont de numerele de la 1 la i - 2  
    iar 1 reprezinta cea mai buna solutie tinand cont de numerele de la 1 la i - 1 (avandu-l in secventa)  
    - a doua constituie numarul de subsecvente  
    - a treia lungimea totala a secventei (suma lungimilor subsecventelor)  
    - structura auxiliara creata Parity stocheaza cele 2 paritati.  
    
    Algoritm:  
    - dp[0] o sa ia valoare maxima dintre dp[0] si dp[1]  
    - dp[1][k][l].parity o sa ia valoarea maximului dintre  
    dp[0][k - 1][l - 1].parity si dp[1][k][l - 1].parity + numarul de la iteratia curenta(nums[i])  
    avand in vedere paritatea acestuia  

