pipeline {
    agent any

    stages {

        stage('Clone') {
            steps {
                git 'https://github.com/Bhautik03/ScientificCalculator.git'
            }
        }

        stage('Build') {
            steps {
                sh '''
                mkdir -p build
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
    }
}
