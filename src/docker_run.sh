docker build -t "container" .
docker run -it -v $PWD:/tmp -w /tmp container
