pipeline {
    agent any

    environment {
        IMAGE_NAME = "bhautik03/scientific-calculator"
        IMAGE_TAG  = "latest"
    }

    stages {

        stage('Checkout SCM') {
            steps {
                checkout scm
            }
        }

        stage('Tool Install') {
            steps {
                sh 'cmake --version'
                sh 'docker --version'
                sh 'ansible --version'
            }
        }

        stage('Build') {
            steps {
                sh '''
                rm -rf build
                mkdir build
                cd build
                cmake ..
                make
                '''
            }
        }

        stage('Test') {
            steps {
                sh '''
                cd build
                ctest --output-on-failure
                '''
            }
        }

        stage('Docker Build') {
            steps {
                sh '''
                docker build -t $IMAGE_NAME:$IMAGE_TAG .
                '''
            }
        }

        stage('Push Image') {
            steps {
                withCredentials([usernamePassword(
                    credentialsId: 'dockerhub-creds',
                    usernameVariable: 'DOCKER_USER',
                    passwordVariable: 'DOCKER_PASS'
                )]) {
                    sh '''
                    echo $DOCKER_PASS | docker login -u $DOCKER_USER --password-stdin
                    docker push $IMAGE_NAME:$IMAGE_TAG
                    '''
                }
            }
        }

        stage('Deploy with Ansible') {
            steps {
                sh '''
                ansible-playbook -i inventory deploy.yml
                '''
            }
        }
    }

    post {
        always {
            cleanWs()
        }
        success {
            echo "Pipeline executed successfully!"
        }
        failure {
            echo "Pipeline failed!"
        }
    }
}