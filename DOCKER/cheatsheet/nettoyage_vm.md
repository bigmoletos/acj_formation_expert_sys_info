# Si la vm est pleine on peut supprimer des fichiers, kernel, image...</>

```bash
sudo apt autoremove
sudo apt clean
sudo find /var/log -type f -name "*.log" -exec sudo truncate -s 0 {} \;
sudo rm -rf /tmp/*
sudo rm -rf /var/tmp/*
dpkg --list | grep linux-image
docker container prune -f
docker image prune -a -f
uname -r
sudo apt remove --purge linux-image-6.1.0-25-amd64
sudo apt autoremove
#  test
df -h
```