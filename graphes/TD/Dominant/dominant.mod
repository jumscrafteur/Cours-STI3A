/**********************************************************************/
/*                                                                    */
/*                 Dominant dans un graphe                            */
/*                                                                    */
/*  Auteur : P. Berthomé                                              */
/*  Date   : 18/03/2020                                               */
/*  Version: 1.0                                                      */
/*                                                                    */
/**********************************************************************/

/* Description des entrées : le graphe avec ses sommets et ses arêtes */
/* Nombre de sommets */
param n, integer, >=2;

/* Ensemble de sommets */
set V, default {1 .. n};

/* Ensemble d'arêtes comme sous-ensemble du produit cartésien */
set E, within V cross V;

/* Variables du problème */

/* Version exacte */
/* var x{i in V},   binary ; */
/* Version relachée  pour le dominant fractionnaire */
var x{i in V},    >=0;                           


/* But général : trouver le dominant de taille minimale   */
minimize size: sum{i in V} x[i];


/*  Modélisation des contraintes */ 
s.t.

Node{i in V}:
   x[i] + sum{(i,j) in E} x[j] >= 1;

/*  Résolution */
solve;

/* On peut afficher le résultat avec une forme qui ressemble à du C */
printf{1..56} "="; printf "\n";

printf "Taille d'un dominant minimum %g\n\n", size;

printf "Sommet        Choisi \n";
printf "-------------  --------\n";
printf{i in V: x[i] != 0}: "%13s     %12g  \n", i,     x[i];

printf{1..56} "="; printf "\n";

end;
