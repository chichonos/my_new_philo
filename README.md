# philosophers

Le problème du « dîner des philosophes » est un cas d'école classique, sur le partage de ressources en informatique système.
Il concerne l'ordonnancement des processus et l'allocation des ressources à ces derniers et a été énoncé par Edsger Dijkstra.

A travers ce cas pratique j'ai pu comprendre comment utiliser des mutex afin que les différents processus ne collectent pas
et/ou ne modifient pas une ressource en même temps.

La situation est la suivante :

![image](https://user-images.githubusercontent.com/86956442/177822547-d616cabb-e7f2-4494-a16e-b09986498628.png)

Des philosophes se trouvent autour d'une table.
Chacun des philosophes a devant lui un plat.
A gauche de chaque assiette se trouve une fourchette.
Un philosophe n'a que trois états possibles :

- Penser pendant un temps indéterminé
- Etre affamé pendant un temps déterminé et fini.
- Manger pendant un temps déterminé et fini.
- Dormir pendant un temps déterminé et fini.

Des contraintes extérieures s'imposent à cette situation :

Lorsqu'un philosophe a faim, il va se mettre dans l'état « affamé » et attendre que les fourchettes soient libres ;
Pour manger, un philosophe a besoin de deux fourchettes : celle qui se trouve à gauche de sa propre assiette,
et celle qui se trouve à droite (c'est-à-dire les deux fourchettes qui entourent sa propre assiette) ;
si un philosophe n'arrive pas à s'emparer d'une fourchette, il reste affamé pendant un temps déterminé, en attendant de renouveler sa tentative.
Le problème consiste à trouver un ordonnancement des philosophes tel qu'ils puissent tous manger, chacun à leur tour.
Si un philosophe n'a pas ses deux fourchettes à temps pour manger alors il meurt et le programme prend fin.
