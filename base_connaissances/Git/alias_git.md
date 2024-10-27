## créer un alias git à mettre de maniére globale dans le fichier .gitconfig

git config --global alias.ckt checkout
git config --global alias.ts status
git config --global alias.br branch
git config --global alias.mg merge
git config --global alias.pl pull
git config --global alias.ps push
git config --global alias.gtm !f() { git commit -a -m "$1"; }; f
git config --global alias.pr !f() { gh pr create --title "$1" --body "$2"; }; f




## pour avoir la liste des alias
git config --get-regexp ^alias
git config --global --get-regexp ^alias


## modifier un alias Git
git config --global alias.co votre_nouvelle_commande

## supprimer un alias, vous pouvez utiliser la commande suivante :
git config --global --unset alias.votre_alias