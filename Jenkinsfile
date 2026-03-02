pipeline {
    agent any

    options {
        skipDefaultCheckout(true)   // ✅ prevents automatic checkout
    }

    environment {
        IMAGE_NAME = "bhautik03/scientific-calculator"
        IMAGE_TAG  = "${BUILD_NUMBER}"
    }

    stages {

        stage('Checkout SCM') {
            steps {
                checkout scm
            }
        }

        stage('Tool Check') {
            steps {
                sh '''
                    docker --version
                    ansible --version
                '''
            }
        }

        stage('Docker Build') {
            steps {
                sh '''
                    docker build -t ${IMAGE_NAME}:${IMAGE_TAG} .
                '''
            }
        }

        stage('Run Tests in Container') {
            steps {
                sh '''
                    docker run --rm ${IMAGE_NAME}:${IMAGE_TAG} ctest --test-dir build
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
                        echo "$DOCKER_PASS" | docker login -u "$DOCKER_USER" --password-stdin
                        docker push ${IMAGE_NAME}:${IMAGE_TAG}
                        docker tag ${IMAGE_NAME}:${IMAGE_TAG} ${IMAGE_NAME}:latest
                        docker push ${IMAGE_NAME}:latest
                        docker logout
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
            emailext(
                subject: "SUCCESS: ${env.JOB_NAME} #${env.BUILD_NUMBER}",
                body: "Build SUCCESS.",
                to: "bhautikv03@gmail.com"
            )
        }

        failure {
            emailext(
                subject: "FAILURE: ${env.JOB_NAME} #${env.BUILD_NUMBER}",
                body: "Build FAILED.",
                to: "bhautikv03@gmail.com"
            )
        }
    }
}