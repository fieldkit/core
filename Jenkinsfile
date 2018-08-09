@Library('conservify') _

conservifyProperties()

timestamps {
    node () {
        conservifyBuild(name: 'core')

        build job: "distribution", wait: false
    }
}
