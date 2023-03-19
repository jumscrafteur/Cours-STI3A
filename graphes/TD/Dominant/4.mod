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

var y{(i,j) in E},   binary ;                        


/* But général : */
maximize size: sum{(i,j) in E} y[i, j];


/*  Modélisation des contraintes */ 
s.t.

Node{i in V}:
   sum{(i,j) in E} y[i,j] <= 1;
Symetry{(i,j) in E: i<j}:
   y[i,j] = y[j,i];

/*  Résolution */
solve;

/* On peut afficher le résultat avec une forme qui ressemble à du C */
printf{1..56} "="; printf "\n";

printf "Taille d'un Couplage maximum %g\n\n", size;

printf "Sommet        Choisi \n";
printf "-------------  --------\n";
printf{(i,j) in E: y[i,j] != 0}: "(%s,%s)      %12g  \n", i,j,     y[i,j];

printf{1..56} "="; printf "\n";

end;
