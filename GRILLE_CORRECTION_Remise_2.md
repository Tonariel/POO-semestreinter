# Grille de correction : exercice de synthèse du cours 3

**Cycle de vie, copie et gestion manuelle de la mémoire : la classe Library**
Pondération : 15 % de la note finale du cours.

### Description de la tâche
Cet exercice prolonge le projet du cours 2. Vous repartez de vos classes `Book` et `Student` et vous ajoutez une classe `Library`. Vous pouvez utiliser le PDF du cours 3 afin de vous aider.

**Attention** : certaines diapositives ne comprennent pas les éléments évalués. Leur utilisation telle quelle, sans modification, sera pénalisée dans la note finale.

`L'usage des pointeurs intelligents (std::unique_ptr, std::shared_ptr, std::make_unique) est interdit dans cet exercice. L'objectif est précisément d'écrire la gestion manuelle à la main : new, delete, et un destructeur qui fait son travail.`

**Le compteur.** Ajoutez à `Book` un membre `static` qui compte les livres actuellement vivants. Il est incrémenté à chaque construction et décrémenté à chaque destruction. Affichez sa valeur dans le constructeur et dans le destructeur.

**La bibliothèque.** Créez `Library.h` et `Library.cpp`. La bibliothèque contient un **vecteur de livres alloués sur le tas** et elle en est la seule propriétaire : c'est son destructeur qui doit libérer chacun d'eux. Une méthode permet d'ajouter un livre au catalogue.

**La copie.** Lorsqu'un étudiant emprunte un livre, il doit en obtenir sa **propre copie** allouée sur le tas. Cette exigence vous force à vous poser la question du constructeur par copie : la version générée par le compilateur ne touche pas au compteur, ce qui le déséquilibre. À vous d'écrire la vôtre.

`Le critère de réussite est unique et vérifiable : à la toute fin du programme, le compteur doit valoir 0. Autant de destructions que de constructions, sans exception.`

Rappelez-vous que dès qu'une classe possède de la mémoire brute, la **Règle des Cinq** s'applique : un destructeur seul ne suffit pas, la copie doit être écrite ou explicitement.

Finalement, dans le `main.cpp`, remplissez la bibliothèque d'au moins 6 livres, créez 2 étudiants et effectuez l'intégralité des tests demandés dans la [section d'évaluation C](#c-programme-de-démonstration-maincpp-25-points). Affichez la valeur du compteur aux étapes clés et vérifiez explicitement l'équilibre final.

### Résultat de l'exécution du .exe
L'ordre exact des lignes dépendra de vos choix de conception. Ce qui est évalué, c'est la présence de chaque étape et la valeur finale du compteur.

`=== Compteur au demarrage ===`\
`[compteur] avant toute creation : 0 livre(s) vivant(s)`\
\
`=== Remplissage de la bibliotheque ===`\
`+ Construct Dune (count=1)`\
`+ Construct Fondation (count=2)`\
`(... quatre autres constructions ...)`\
`[compteur] apres 6 ajouts : 6 livre(s) vivant(s)`\
\
`=== Livres de la bibliotheque ===`\
`Dune par Frank Herbert : disponible`\
`Fondation par Isaac Asimov : disponible`\
\
`=== Emprunt et copie ===`\
`Dune avant emprunt : disponible`\
`+ Copy      Dune (count=7)`\
`Marie emprunte Dune : True`\
`Dune apres emprunt : emprunte`\
`Hugo emprunte Dune (deja emprunte) : False`\
\
`=== Cas limite : le sixieme emprunt ===`\
`Emprunt 2 (Fondation) : True`\
`Emprunt 3 (Le Petit Prince) : True`\
`Emprunt 4 (1984) : True`\
`Emprunt 5 (Les Miserables) : True`\
`Emprunt 6 (L'Etranger) : False`\
`CanBorrow() apres 5 emprunts : False`\
`La liste contient toujours 5 titres.`\
\
`=== Retours ===`\
`- Destruct  Dune (count=10)`\
`Retour de Dune : True`\
`Dune apres retour : disponible`\
`Retour d'un titre non emprunte : False`\
`Nouvel emprunt apres liberation d'une place : True`\
\
`=== Etat final ===`\
`Etudiant 20240001 (Marie Tremblay) : 5 / 5 livre(s)`\
`Etudiant 20240002 (Hugo Lambert) : 0 / 5 livre(s)`\
\
`=== Sortie de portee ===`\
`(... destruction des copies personnelles ...)`\
`[Library] destruction du catalogue (6 livre(s))`\
`(... destruction des livres du catalogue ...)`\
\
`=== Verification de l'equilibre ===`\
`[compteur] apres destruction de tout : 0 livre(s) vivant(s)`\
`EQUILIBRE : autant de destructions que de constructions.`

### Structure du dossier de remise
Il sera important de fournir un exécutable (.exe). Aucun autre format ne sera accepté et toutes les sections nécessitant l'exécution du programme se verront attribuer la note de 0.
Vous pouvez utiliser CMake afin de produire un build .exe depuis un système d'exploitation autre que Windows.
```text
Project
├── build.exe
├── Public
│   ├── Book.h
│   ├── Student.h
│   └── Library.h
└── Private
│   ├── Book.cpp
│   ├── Student.cpp
│   ├── Library.cpp
└── main.cpp
└── CMakelist.txt
```
---

## A. Structure et organisation du code (20 points)

| Critère | Points |
|---|---|
| Séparation `.h` / `.cpp` | 6 |
| Inclusions correctes | 6 |
| CMake valide | 3 |
| Compilation propre | 3 |
| L'intégralité des fichiers demandés est présente dans la [structure décrite](#structure-du-dossier-de-remise) | 2 |

---

## B. Le compteur statique et le cycle de vie de Book (21 points)

| Critère | Points |
|---|---|
| Membre `static` déclaré dans le `.h` et défini une seule fois dans le `.cpp` | 2 |
| Incrémentation au constructeur, décrémentation au destructeur | 4 |
| Constructeur par copie écrit à la main et incrémentant le compteur | 8 |
| Affichage lisible des constructions et des destructions | 4 |
| Accès au compteur sans instance (méthode `static`) | 2 |
| Aucun pointeur intelligent utilisé | 1 |

---

## C. La classe Library et la gestion manuelle du tas (18 points)

| Critère | Points |
|---|---|
| `Library` contient un vecteur de livres alloués sur le tas | 2 |
| Allocation par `new` lors de l'ajout d'un livre | 2 |
| Le destructeur appelle `delete` sur chaque livre du catalogue | 8 |
| La copie de `Library` est gérée | 6 |


---

## D. Programme de démonstration main.cpp (20 points)

| Critère | Points |
|---|---|
| Le programme exécute l'intégralité des tests demandés sans erreurs de logique | 6 |
| **Le compteur vaut 0 à la fin du programme** | 6 |
| Affichage du compteur aux étapes clés (départ, après ajouts, après emprunts, fin) | 3 |
| L'étudiant obtient bien une copie du livre, et non un partage d'adresse | 4 |
| Chaque test retourne `True` ou `False` | 1 |

---

## Pénalités

| Motif | Pénalité |
|---|---|
| Programme qui plante à l'exécution (double `delete`, pointeur pendouillant) | Les sections nécessitant l'exécution sont notées 0 |

---
