#!/bin/bash
set -uo pipefail
GOSRCDIR=$HOME

function install_go() {
    if [[ "$#" != 1 ]]; then
        echo "usage: download_go destdir"
        exit -1
    fi

    cd $1
    wget https://dl.google.com/go/go1.10.darwin-amd64.tar.gz
    sudo tar -C /usr/local -xzf go1.10.darwin-amd64.tar.gz
    mkdir -p $HOME/go1.10/bin
    mkdir -p $HOME/go1.10/src
    mkdir -p $HOME/go1.10/pkg

    cat >> $HOME/.zshrc <<-'EOF'
    export GOROOT=/usr/local/bin
    export PATH=$PATH:$(go env GOPATH)/bin:$GOROOT/bin
EOF

    source $HOME/.zshrc
}



install_go "$GOSRCDIR"

