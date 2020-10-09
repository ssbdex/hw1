import os

text = '''{
    "package": {
        "name": "helloworld",
        "repo": "otus-cpp",
        "subject": "ampermetr123",
        "desc": "I was pushed completely automatically",
        "website_url": "www.jfrog.com",
        "issue_tracker_url": "https://github.com/Ampermetr123/otus-cpp/issues",
        "vcs_url": "https://github.com/Ampermetr123/otus-cpp.git",
        "licenses": ["GPL-2.0"]
    },

    "version": {
        "name": "0.0.$TRAVIS_BUILD_NUMBER",
        "desc": "This is a version"
    },

    "files":
        [{"includePattern": "build/_CPack_Packages/Linux/DEB/(.*\.deb)", "uploadPattern": "pool/main/h/helloworld/$1",
            "matrixParams": {
            "deb_distribution": "bionic",
            "deb_component": "main",
            "deb_architecture": "amd64"}
        }
    ]

}'''

with open("./deploy.txt","w") as f:
    f.write( text.replace('$TRAVIS_BUILD_NUMBER', os.getenv('TRAVIS_BUILD_NUMBER',0) ))


