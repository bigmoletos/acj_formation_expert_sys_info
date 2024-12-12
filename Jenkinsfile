pipeline {
    agent any

    environment {
        DOCKER_HUB_CREDS = credentials('docker-hub-credentials')
        DOCKER_IMAGE = 'virtus/franckgroupe2dec24'
        DOCKER_TAG = 'v1'
    }

    stages {
        stage('Setup Python') {
            steps {
                script {
                    try {
                        def pythonVersion = sh(
                            script: 'python3 --version',
                            returnStdout: true
                        ).trim()
                        echo "Python version: ${pythonVersion}"
                    } catch (Exception e) {
                        error "Python3 n'est pas installé ou n'est pas accessible. Erreur: ${e.message}"
                    }
                }
            }
        }

        stage('Load Configuration') {
            steps {
                script {
                    // Charger la configuration si nécessaire
                    echo "Configuration chargée"
                }
            }
        }

        stage('Login to Docker Hub') {
            steps {
                script {
                    withCredentials([usernamePassword(
                        credentialsId: 'docker-hub-credentials',
                        usernameVariable: 'DOCKER_HUB_USER',
                        passwordVariable: 'DOCKER_HUB_PASS'
                    )]) {
                        sh """
                            echo \$DOCKER_HUB_PASS | docker login -u \$DOCKER_HUB_USER --password-stdin
                        """
                    }
                }
            }
        }

        stage('Build Docker Image') {
            steps {
                script {
                    sh """
                        docker build -t ${DOCKER_IMAGE}:${DOCKER_TAG} .
                    """
                }
            }
        }

        stage('Push to Registry') {
            steps {
                script {
                    sh """
                        docker push ${DOCKER_IMAGE}:${DOCKER_TAG}
                    """
                }
            }
        }

        stage('Deploy') {
            steps {
                script {
                    // Déploiement avec Ansible
                    sh """
                        ansible-playbook -i ansible/inventories/vm_jenkins.inv playbook_ansible_deploy.yml
                    """
                }
            }
        }
    }

    post {
        always {
            sh """
                echo "=== Nettoyage ==="
                docker logout
                docker system prune -f
            """
            cleanWs()
        }
        success {
            echo "Le pipeline s'est terminé avec succès!"
        }
        failure {
            echo "Le pipeline a échoué. Vérifiez les logs ci-dessus pour plus de détails."
        }
    }
}