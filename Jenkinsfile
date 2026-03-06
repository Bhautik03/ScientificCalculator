pipeline {
agent any

```
environment {
    IMAGE_NAME = "bhautik03/scientific-calculator"
    IMAGE_TAG  = "${BUILD_NUMBER}"
    FAILED_STAGE = ""
}

stages {

    stage('Tool Install') {
        steps {
            script { env.FAILED_STAGE = "Tool Setup" }
            sh '''
                echo "Checking and installing required tools..."

                #Install CMake if not installed
                if ! command -v cmake >/dev/null 2>&1; then
                    echo "CMake not found. Installing..."
                    sudo apt update
                    sudo apt install -y cmake
                else
                    echo "CMake already installed"
                fi

                # Install Google Test if missing
                if [ ! -d "/usr/src/gtest" ]; then
                    echo "Installing Google Test..."
                    sudo apt install -y libgtest-dev
                    cd /usr/src/gtest
                    sudo cmake .
                    sudo make
                    sudo cp lib/*.a /usr/lib
                else
                    echo "Google Test already installed"
                fi

                # Verify Docker and Ansible
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

    stage('Build Docker Image') {
        steps {
            script { env.FAILED_STAGE = "Docker Build Image" }
            sh '''
                docker build -t ${IMAGE_NAME}:${IMAGE_TAG} .
            '''
        }
    }

    stage('Push Docker Image') {
        steps {
            script { env.FAILED_STAGE = "Push Docker Image" }
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
```

}
