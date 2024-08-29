# корневой image образ для сборки - чистый ubuntu
FROM ubuntu

# обновляем apt пакеты и устанавливаем по очереди нужные зависимости
RUN apt-get update && apt-get install -y \
    gcc \
    make \
    valgrind \
    vim \
    check \
    clang \
    llvm \
    lcov \
    clang-format \
    libpcre3 \
    libpcre3-dev

COPY . /code

# Устанавливаем 
WORKDIR /code

CMD /bin/bash
