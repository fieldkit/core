@Library('conservify') _

conservifyProperties()

timestamps {
    node () {
        conservifyBuild(name: 'core', archive: "build/firmware/core/*.bin, build/firmware/test/*.bin")
        distributeFirmware(directory: "build/firmware/core")
    }

    refreshDistribution()
}
