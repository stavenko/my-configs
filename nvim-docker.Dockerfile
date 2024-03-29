from ubuntu as builder

RUN apt-get update && \
    apt-get install -y wget curl xz-utils jq
run curl -s https://api.github.com/repos/llvm/llvm-project/releases/latest | jq -r ".assets[] | select(.name|test(\"llvm.*`uname -m`.*tar.xz$\")) | .browser_download_url" | wget -q -O llvm.tar.xz -i -

run mkdir -p /llvm-bins && \
    tar -xf llvm.tar.xz --directory /llvm-bins && \
    cd /llvm-bins && \
    cd `ls` && \
    mkdir /llvm && \
    mv ./* /llvm

from ubuntu

copy --from=builder /llvm/bin/* /bin/
copy --from=builder /llvm/lib/* /lib/

RUN apt-get update && \
    apt-get install -y \
        locales && \
    rm -r /var/lib/apt/lists/*

ENV TZ=America/Los_Angeles
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN sed -i -e 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen && \
    sed -i -e 's/# de_DE.UTF-8 UTF-8/de_DE.UTF-8 UTF-8/' /etc/locale.gen && \
   dpkg-reconfigure --frontend=noninteractive locales


run apt-get update && \
    apt-get install -y software-properties-common curl git openssh-server sudo libncurses5 ripgrep
run curl https://deb.nodesource.com/setup_16.x -o sources.sh && \
    bash ./sources.sh && \
    apt-get install -y nodejs;

run add-apt-repository ppa:neovim-ppa/unstable && \ 
    apt-get update && \
    apt-get install -y neovim;


run useradd -rm -d /home/nvim -s /bin/bash -g root -G sudo -u 1000 nvim 
run  echo 'nvim:nvim' | chpasswd
RUN service ssh start
user nvim


ENV XDG_CONFIG_HOME=/home/nvim/.config
ENV XDG_DATA_HOME=/home/nvim/.local/share
ENV HOME=/home/nvim
run mkdir $XDG_CONFIG_HOME
run curl -fLo "${XDG_DATA_HOME:-$HOME/.local/share}"/nvim/site/autoload/plug.vim --create-dirs \
       https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
run chown -R nvim $XDG_CONFIG_HOME
copy ./init.vim $XDG_CONFIG_HOME/nvim/init.vim

run nvim +PlugInstall +qall 
run nvim "+CocInstall -sync coc-clangd" +qall

user root
entrypoint ["/usr/sbin/sshd", "-D", "-p22"]




