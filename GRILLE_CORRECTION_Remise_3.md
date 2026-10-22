# Grille de correction : exercice de synthèse du cours 4

**Héritage, polymorphisme et généricité : la bibliothèque devient hétérogène**
Pondération : 15 % de la note finale du cours.

### Description de la tâche
Cet exercice prolonge le projet déjà entamé. Vous repartez de vos classes `Book`, `Member` et `Library`, et vous les transformez pour accueillir plusieurs types de livres et différents membres. Vous pouvez utiliser le PDF du cours 4 afin de vous aider.

**Attention** : certaines diapositives ne comprennent pas les éléments évalués. Leur utilisation telle quelle, sans modification, sera pénalisée dans la note finale.

`Les acquis du cours 3 restent exigés : le compteur statique de livres doit toujours revenir à 0 à la fin du programme. La gestion manuelle de la mémoire se complique avec l'héritage : vous pouvez donc adapter le programme pour utiliser les pointeurs intelligents, ou apporter les modifications nécessaires à la bonne gestion manuelle de la mémoire`

**La classe de base** `Book` devient **abstraite** : elle ne peut plus être instanciée. Elle déclare au moins une méthode purement virtuelle (`= 0`) que chaque enfant devra implémenter, et conserve les comportements communs à tous les livres en méthodes concrètes.

**Au moins trois enfants.** Créez au minimum trois classes dérivées de `Book`, chacune avec ses attributs propres et son propre affichage. Chaque constructeur enfant doit appeler le constructeur de `Book` dans sa liste d'initialisation.

**Ce qui peut être spécialisé doit être virtuel.** Tout comportement que les enfants sont susceptibles de spécialiser doit être déclaré `virtual` dans la base et marqué `override` dans l'enfant.

**Chacun des trois types de livre doit avoir sa propre règle d'emprunt et de retour.** Trois comportements réellement différents, pas seulement trois affichages : par exemple un exemplaire unique pour le papier, une licence illimitée pour le numérique, et un nombre d'écoutes simultanées plafonné pour l'audio. Le retour doit être refusé quand il ne correspond à aucun emprunt en cours.

**Au moins deux types de membres.** Créez au minimum deux classes dérivées de `Member`. **Elles doivent avoir des limites d'emprunt différentes et basses** (par exemple 2 et 3), afin que chaque limite puisse être atteinte et testée sans gonfler le catalogue.

**Une interface obligatoire.** Créez au moins une interface : une classe sans aucune donnée membre, qui ne contient que des méthodes purement virtuelles et un destructeur virtuel. Elle doit être implémentée par au moins deux classes qui n'appartiennent pas à la même hiérarchie (par exemple une interface d'affichage implémentée à la fois par `Book` et par `Member`), et au moins une fonction du programme doit manipuler ces objets uniquement à travers l'interface. Voir les diapositives 22 et 23 du cours.

**Le template.** `Library` doit stocker ses livres **et** ses membres au moyen d'un **conteneur générique de votre conception** (par exemple `Catalog<T>`). Un seul template, deux instanciations distinctes. Le conteneur est propriétaire de ses éléments : c'est lui qui les libère. Sa copie doit être soit correctement gérée, soit explicitement interdite.

**L'affichage.** Le programme doit afficher tous les types présents dans la bibliothèque. `Library` ne doit contenir **ni `switch` sur le type, ni chaîne de `dynamic_cast`** : c'est la table virtuelle qui choisit la bonne méthode.

**Points bonus.** Une fonction ou méthode générique qui traite un catalogue sans connaître le type concret de ses éléments, ou un utilitaire d'affichage réutilisé par plusieurs enfants plutôt que recopié dans chacun. La dernière section de la sortie ci-dessous (« Etat final ») illustre la première option.

**La qualité du code.** La qualité générale de votre C++ est évaluée dans son ensemble.

`Piège à anticiper : dès que Book est abstraite, l'expression "new Book()" ne compile plus. Or un membre doit conserver sa propre copie d'un livre emprunté sans connaître son type réel. Il vous faudra une méthode virtuelle de duplication.`

Finalement, dans le `main.cpp`, remplissez la bibliothèque d'au moins 6 livres couvrant les trois types, créez au moins 2 membres couvrant les deux types, et effectuez l'intégralité des tests demandés dans la [section d'évaluation E](#e-programme-de-démonstration-maincpp-16-points).

### Résultat de l'exécution du .exe
Voici la sortie complète d'une solution de référence. Le format d'affichage et l'ordre des lignes dépendront de vos choix de conception : ce qui est évalué, c'est que chaque type s'affiche différemment, que chaque règle d'emprunt et de retour se distingue des autres, que chaque limite de membre soit atteinte, et que le compteur finisse à 0.

`=== Compteur au demarrage ===`\
`[compteur] avant toute creation : 0 livre(s) vivant(s)`\
\
`=== Remplissage de la bibliotheque ===`\
`+ Construct Dune (count=1)`\
`+ Construct Les Miserables (count=2)`\
`+ Construct Fondation (count=3)`\
`+ Construct 1984 (count=4)`\
`+ Construct Le Petit Prince (count=5)`\
`+ Construct L'Etranger (count=6)`\
`[compteur] apres 6 ajouts : 6 livre(s) vivant(s)`\
\
`=== Affichage polymorphe du catalogue ===`\
`-- Catalogue (6 livre(s)) --`\
`[Papier]    Dune par Frank Herbert | rayon SF-12 | disponible`\
`[Papier]    Les Miserables par Victor Hugo | rayon CL-03 | endommage`\
`[Numerique] Fondation par Isaac Asimov | 4 Mo | https://biblio.uqac.ca/fondation | 0 pret(s) | disponible`\
`[Numerique] 1984 par George Orwell | 2 Mo | https://biblio.uqac.ca/1984 | 0 pret(s) | disponible`\
`[Audio]     Le Petit Prince par Antoine de Saint-Exupery | lu par Bernard Giraudeau | 96 min (francais) | 0/2 ecoute(s) | disponible`\
`[Audio]     L'Etranger par Albert Camus | lu par Michael Lonsdale | 210 min (francais) | 0/1 ecoute(s) | disponible`\
\
`=== Affichage polymorphe des membres ===`\
`-- Membres (3) --`\
`[Etudiant]  20240001 (Marie Tremblay, informatique) : 0 / 2 livre(s) [aucun emprunt]`\
`[Etudiant]  20240002 (Hugo Lambert, mathematiques) : 0 / 2 livre(s) [aucun emprunt]`\
`[Enseignant] 10001 (Valere Dubois, informatique) : 0 / 3 livre(s) [aucun emprunt]`\
\
`=== Test 1 - livre PAPIER : exemplaire unique ===`\
`Dune avant emprunt : disponible`\
`+ Copy      Dune (count=7)`\
`Marie emprunte Dune : True`\
`Dune apres emprunt : emprunte`\
`Hugo emprunte Dune (deja sorti) : False`\
`- Destruct  Dune (count=6)`\
`Marie rend Dune : True`\
`Dune apres retour : disponible`\
`Retour d'un exemplaire non sorti : False`\
\
`=== Test 2 - livre PAPIER endommage : jamais empruntable ===`\
`Les Miserables : endommage`\
`Marie emprunte Les Miserables : False`\
\
`=== Test 3 - livre NUMERIQUE : licence illimitee ===`\
`+ Copy      Fondation (count=7)`\
`Marie emprunte Fondation : True`\
`+ Copy      Fondation (count=8)`\
`Hugo emprunte Fondation (meme titre) : True`\
`+ Copy      Fondation (count=9)`\
`Valere emprunte Fondation (3e simultane) : True`\
`Fondation reste : disponible`\
`- Destruct  Fondation (count=8)`\
`Marie rend Fondation : True`\
`- Destruct  Fondation (count=7)`\
`Hugo rend Fondation : True`\
`- Destruct  Fondation (count=6)`\
`Valere rend Fondation : True`\
`Retour numerique sans pret en cours : False`\
\
`=== Test 4 - livre AUDIO : licences simultanees limitees ===`\
`Le Petit Prince accepte 2 ecoutes simultanees.`\
`+ Copy      Le Petit Prince (count=7)`\
`Marie ecoute Le Petit Prince : True`\
`+ Copy      Le Petit Prince (count=8)`\
`Hugo ecoute Le Petit Prince : True`\
`Statut apres 2 ecoutes : emprunte`\
`Valere ecoute Le Petit Prince (3e) : False`\
`- Destruct  Le Petit Prince (count=7)`\
`Marie arrete son ecoute : True`\
`+ Copy      Le Petit Prince (count=8)`\
`Valere reessaie apres liberation : True`\
`- Destruct  Le Petit Prince (count=7)`\
`Hugo arrete son ecoute : True`\
`- Destruct  Le Petit Prince (count=6)`\
`Valere arrete son ecoute : True`\
`Retour audio sans ecoute en cours : False`\
\
`=== Test 5 - limite d'un ETUDIANT (2 livres) ===`\
`Limite de Marie (Etudiant) : 2`\
`+ Copy      Dune (count=7)`\
`Emprunt 1 (Dune) : True`\
`+ Copy      1984 (count=8)`\
`Emprunt 2 (1984) : True`\
`CanBorrow() apres 2 emprunts : False`\
`Emprunt 3 (L'Etranger) : False`\
`Marie possede toujours 2 livre(s) : etat coherent.`\
`- Destruct  Dune (count=7)`\
`Marie rend Dune : True`\
`+ Copy      L'Etranger (count=8)`\
`Emprunt apres liberation d'une place : True`\
\
`=== Test 6 - limite d'un ENSEIGNANT (3 livres) ===`\
`Limite de Valere (Enseignant) : 3`\
`+ Copy      Dune (count=9)`\
`Emprunt 1 (Dune) : True`\
`+ Copy      Fondation (count=10)`\
`Emprunt 2 (Fondation) : True`\
`+ Copy      Le Petit Prince (count=11)`\
`Emprunt 3 (Le Petit Prince) : True`\
`CanBorrow() apres 3 emprunts : False`\
`Emprunt 4 (1984) : False`\
`Valere possede toujours 3 livre(s) : etat coherent.`\
`La meme limite, deux types de membres : 2 contre 3.`\
`[compteur] apres tous les tests : 11 livre(s) vivant(s)`\
\
`=== Etat final (fonction template generique) ===`\
`Livres : 6 element(s)`\
`[Papier]    Dune par Frank Herbert | rayon SF-12 | emprunte`\
`[Papier]    Les Miserables par Victor Hugo | rayon CL-03 | endommage`\
`[Numerique] Fondation par Isaac Asimov | 4 Mo | https://biblio.uqac.ca/fondation | 1 pret(s) | disponible`\
`[Numerique] 1984 par George Orwell | 2 Mo | https://biblio.uqac.ca/1984 | 1 pret(s) | disponible`\
`[Audio]     Le Petit Prince par Antoine de Saint-Exupery | lu par Bernard Giraudeau | 96 min (francais) | 1/2 ecoute(s) | disponible`\
`[Audio]     L'Etranger par Albert Camus | lu par Michael Lonsdale | 210 min (francais) | 1/1 ecoute(s) | emprunte`\
\
`Membres : 3 element(s)`\
`[Etudiant]  20240001 (Marie Tremblay, informatique) : 2 / 2 livre(s) [1984 (Numerique), L'Etranger (Audio)]`\
`[Etudiant]  20240002 (Hugo Lambert, mathematiques) : 0 / 2 livre(s) [aucun emprunt]`\
`[Enseignant] 10001 (Valere Dubois, informatique) : 3 / 3 livre(s) [Dune (Papier), Fondation (Numerique), Le Petit Prince (Audio)]`\
\
`=== Sortie de portee ===`\
`- Destruct  1984 (count=10)`\
`- Destruct  L'Etranger (count=9)`\
`- Destruct  Dune (count=8)`\
`- Destruct  Fondation (count=7)`\
`- Destruct  Le Petit Prince (count=6)`\
`- Destruct  Dune (count=5)`\
`- Destruct  Les Miserables (count=4)`\
`- Destruct  Fondation (count=3)`\
`- Destruct  1984 (count=2)`\
`- Destruct  Le Petit Prince (count=1)`\
`- Destruct  L'Etranger (count=0)`\
\
`=== Verification de l'equilibre ===`\
`[compteur] apres destruction de tout : 0 livre(s) vivant(s)`\
`Membres vivants : 0`\
`EQUILIBRE : autant de destructions que de constructions.`

### Structure du dossier de remise
Il sera important de fournir un exécutable (.exe). Aucun autre format ne sera accepté et toutes les sections nécessitant l'exécution du programme se verront attribuer la note de 0.
Vous pouvez utiliser CMake afin de produire un build .exe depuis un système d'exploitation autre que Windows.
```text
Project
├── build.exe
├── Public
│   ├── Books
│   │   ├── Book.h
│   │   └── (vos 3 enfants de Book).h
│   ├── Members
│   │   ├── Member.h
│   │   └── (vos 2 membres avec des restrictions différentes).h
│   ├── Interfaces
│   │   └── (votre interface).h
│   ├── Catalog.h
│   └── Library.h
├── Private
│   ├── Books
│   │   ├── Book.cpp
│   │   └── (vos 3 enfants de Book).cpp
│   ├── Members
│   │   ├── Member.cpp
│   │   └── (vos 2 membres avec des restrictions différentes).cpp
│   └── Library.cpp
└── main.cpp
```
Un template s'écrit entièrement dans le `.h` : c'est normal qu'il n'y ait pas de `Catalog.cpp`, et vous devez pouvoir l'expliquer. Une interface n'a pas non plus de `.cpp` : elle ne contient aucune implémentation.

---

## A. Structure et organisation du code (10 points)

| Critère | Points |
|---|---|
| Séparation `.h` / `.cpp`, un fichier par classe (le template et l'interface n'ont pas de `.cpp`) | 3 |
| Inclusions correctes, déclaration anticipée là où elle suffit | 2 |
| CMake valide | 2 |
| Compilation propre, sans avertissement | 2 |
| L'intégralité des fichiers demandés est présente dans la [structure décrite](#structure-du-dossier-de-remise) | 1 |

---

## B. La hiérarchie, l'abstraction et l'interface (22 points)

| Critère | Points |
|---|---|
| `Book` est abstraite | 3 |
| **Destructeur `virtual` dans la classe de base** | 4 |
| Au moins 3 classes dérivées de `Book` et 2 de `Member`, chacune avec ses attributs propres | 4 |
| Chaque constructeur enfant appelle celui du parent dans sa liste d'initialisation | 3 |
| Chaque enfant implémente le contrat et marque ses méthodes `override` | 2 |
| Choix pertinent entre `private` et `protected` dans la base | 2 |
| **Une interface sans données, implémentée par deux classes de hiérarchies différentes et utilisée à travers un pointeur ou une référence vers l'interface** | 4 |

---

## C. Le polymorphisme en action (15 points)

| Critère | Points |
|---|---|
| Les comportements communs spécialisables sont déclarés `virtual` | 2 |
| **Les trois types de livre ont chacun une règle d'emprunt et de retour distincte** | 3 |
| Aucun `switch` sur le type ni chaîne de `dynamic_cast` dans `Library` | 4 |
| La duplication d'un livre passe par une méthode virtuelle (le problème de `new Book`) | 4 |
| Ajouter un quatrième type ne demanderait aucune modification de `Library` | 2 |

---

## D. Généricité et gestion de la mémoire (22 points)

| Critère | Points |
|---|---|
| Un conteneur template écrit par l'étudiant, instancié pour les livres **et** les membres | 6 |
| Le conteneur est propriétaire : il libère ses éléments (destructeur explicite ou pointeurs intelligents) | 4 |
| Sa copie est gérée ou explicitement interdite (Règle des Cinq) | 4 |
| **Le compteur de livres vaut 0 à la fin du programme** | 5 |
| Aucune fuite ni double libération, quelle que soit l'approche retenue | 3 |

---

## E. Programme de démonstration main.cpp (16 points)

| Critère | Points |
|---|---|
| Au moins 6 livres couvrant les trois types, et au moins 2 membres couvrant les deux types | 2 |
| Tous les types sont affichés, chacun avec son format propre | 3 |
| **Chacun des trois types de livre est testé à l'emprunt ET au retour**, y compris son cas de refus | 5 |
| **La limite de chacun des deux types de membre est atteinte et testée séparément** | 4 |
| Statuts affichés avant et après, et état de l'objet resté cohérent après un refus | 1 |
| Vérification explicite de l'équilibre final du compteur | 1 |

---

## F. Qualité du code C++ (15 points)

| Critère | Points |
|---|---|
| Qualité générale du code C++, appréciée dans son ensemble | 15 |

À titre indicatif seulement : absence de copier-coller, traitements groupés plutôt que répétés, soin et rigueur, démarche réfléchie.

---

## Bonus (jusqu'à 5 points)

| Critère | Points |
|---|---|
| Fonction ou méthode générique traitant un catalogue sans connaître le type concret, **ou** utilitaire d'affichage partagé par plusieurs enfants | 5 |

---

## Pénalités

| Motif | Pénalité |
|---|---|
| Programme qui plante à l'exécution | Les sections nécessitant l'exécution sont notées 0 |

---