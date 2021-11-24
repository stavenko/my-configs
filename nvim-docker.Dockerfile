from ubuntu as builder

RUN apt-get update && \
    apt-get install -y wget curl unzip jq

run curl -s https://api.github.com/repos/clangd/clangd/releases/latest | jq -r '.assets[] | select(.name|test("clangd-linux")) | .name' > /zip-file-name
run curl -s https://api.github.com/repos/clangd/clangd/releases/latest | jq -r '.assets[] | select(.name|test("clangd-linux")) | .browser_download_url' | wget -qi - 
run unzip `cat /zip-file-name` -d /clangd && \
    cd /clangd && \
    cd `ls` && \
    mkdir /clangd-bins && \
    mv ./* /clangd-bins
    

from ubuntu

copy --from=builder /clangd-bins/bin/* /bin/
copy --from=builder /clangd-bins/lib/* /lib/

RUN apt-get update && \
    apt-get install -y \
        locales && \
    rm -r /var/lib/apt/lists/*

ENV TZ=America/Los_Angeles
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN sed -i -e 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen && \
    sed -i -e 's/# de_DE.UTF-8 UTF-8/de_DE.UTF-8 UTF-8/' /etc/locale.gen && \
   dpkg-reconfigure --frontend=noninteractive locales


run apt-get update && apt-get install -y software-properties-common curl git
run curl https://deb.nodesource.com/setup_16.x -o sources.sh && \
    bash ./sources.sh && \
    apt-get install -y nodejs gcc unzip zip g++ make cmake;

run add-apt-repository ppa:neovim-ppa/unstable && \ 
    apt-get update && \
    apt-get install -y neovim;


ENV XDG_CONFIG_HOME=/root/.config
ENV XDG_DATA_HOME=/root/.local/share
ENV HOME=/root
run curl -fLo "${XDG_DATA_HOME:-$HOME/.local/share}"/nvim/site/autoload/plug.vim --create-dirs \
       https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
copy ./init.vim /root/.config/nvim/init.vim

run nvim +PlugInstall +qall
run nvim +CocInstall coc-clangd +qall



