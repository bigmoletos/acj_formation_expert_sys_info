# Installation d'une nouvelle VM ubuntu


## ajout droit sudo au user

```bash
su -
usermod -aG sudo master
visudo
# ajouter
master ALL=(ALL:ALL) ALL
exit
```

## obtenir l'IP de la vm

```shell

ip route get 1.1.1.1 | awk '{print $7}'

```

## obtenir l'IP du gateway  de la vm

```shell

ip route | grep default | awk '{print $3}'


```

## mise à jour et installation des apt

```shell

sudo apt update && sudo apt upgrade -y

sudo apt-get install ca-certificates curl
sudo apt install net-tools build-essential libncursesw5-dev libncurses-dev autoconf autoconf-archive automake make  m4 build-essential gdb lcov pkg-config   libbz2-dev libffi-dev libgdbm-dev libgdbm-compat-dev liblzma-dev   libncurses5-dev libreadline6-dev libsqlite3-dev libssl-dev  lzma lzma-dev tk-dev uuid-dev zlib1g-dev unzip  ssh ufw htop dos2unix sshpass  ansible apt-transport-https base-passwd ca-certificates conntrack curl dash diffutils ethtool findutils  gnupg grep grub2-common  gzip hostname htop hyphen-en-us init ipvsadm language-pack-fr language-pack-en-base language-pack-gnome-fr language-pack-gnome-fr-base libdebconfclient0 libfprint-2-tod1 libfwupdplugin1 libllvm9  libxmlb1 linux-generic-hwe-20.04 mythes-en-us ncurses-base ncurses-bin  os-prober software-properties-common ssh terminator  ubuntu-desktop-minimal ubuntu-minimal  -y

sudo apt update && sudo apt upgrade -y


```
