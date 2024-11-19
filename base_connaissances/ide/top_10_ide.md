# Top 10 pour utiliser son IDE Vs code ou Cursor

## Trouver remplacer par regex

Utilisez cette regex dans le champ de recherche. Ici on veut rajouter un sudo devant les commandes rm, mv, mkdir :
en mode recherche regex

```shell
(?<!sudo\s)(^|\s)(mkdir|mv|rm)(?=\s)
# Utilisez  dans le champ de remplacement:
sudo $&
```

