wget -nc https://github.com/llvm/llvm-project/archive/refs/heads/main.zip

docker build . -t nvim-docker -f ./nvim-docker.Dockerfile
