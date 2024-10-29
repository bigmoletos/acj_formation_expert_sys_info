
# Download the binary for your system
sudo curl -L --output /usr/local/bin/gitlab-runner https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-linux-amd64

# Give it permission to execute
sudo chmod +x /usr/local/bin/gitlab-runner

# Create a GitLab Runner user
sudo useradd --comment 'GitLab Runner' --create-home gitlab-runner --shell /bin/bash

# Install and run as a service
sudo gitlab-runner install --user=gitlab-runner --working-directory=/home/gitlab-runner
sudo gitlab-runner start
# Commande pour enregistrer le runner
sudo gitlab-runner register --url http://192.168.1.97:8088/ --registration-token GR1348941B-iJkCzTU7-mZyXhf1XF

# redemarrage
sudo systemctl restart gitlab-runner

# status du runner
sudo gitlab-runner status

# commit
sudo systemctl stop  gitlab-runner && sudo systemctl start  gitlab-runner && gitlab-runner status && git commit -a -m "modif gitlab " && gps