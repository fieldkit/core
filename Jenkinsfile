@Library('conservify') _

timestamps {
    node () {
        conservifyBuild(name: 'core', repository: 'https://github.com/fieldkit/core.git')

        build job: "distribution", parameters: []
    }
}
