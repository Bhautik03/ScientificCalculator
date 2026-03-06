pipeline {
    agent any

    environment {
        IMAGE_NAME = "bhautik03/scientific-calculator"
        IMAGE_TAG  = "${BUILD_NUMBER}"
        FAILED_STAGE = ""
    }

    stages {

        stage('Checkout SCM') {
            steps {
                script { env.FAILED_STAGE = "Checkout SCM" }
                checkout scm
            }
        }

        stage('Tool Check') {
            steps {
                script { env.FAILED_STAGE = "Tool Check" }
                sh '''
                    echo "Checking installed tools..."
                    cmake --version
                    docker --version
                    ansible --version
                '''
            }
        }

        stage('Checkout') { 
            steps { 
                script { env.FAILED_STAGE = "Checkout" } 
                checkout scm 
            } 
        }

        stage('Build (CMake)') {
            steps {
                script { env.FAILED_STAGE = "Build (CMake)" }
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
                script { env.FAILED_STAGE = "Test" }
                sh '''
                    cd build
                    ctest --output-on-failure
                '''
            }
        }

        stage('Build Image') {
            steps {
                script { env.FAILED_STAGE = "Docker Build Image" }
                sh '''
                    docker build -t ${IMAGE_NAME}:${IMAGE_TAG} .
                '''
            }
        }

        stage('Push Image') {
            steps {
                script { env.FAILED_STAGE = "Push Image" }
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
                script { env.FAILED_STAGE = "Deploy with Ansible" }
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
                body: "Build and Deployment Successful!",
                to: "bhautikv03@gmail.com"
            )
        }

        failure {
            emailext(
                subject: "FAILURE: ${env.JOB_NAME} #${env.BUILD_NUMBER}",
                body: "Build or Deployment FAILED!",
                to: "bhautikv03@gmail.com"
            )
        }
    }
}