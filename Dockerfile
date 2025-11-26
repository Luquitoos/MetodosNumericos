FROM gcc:latest

WORKDIR /usr/src/app

COPY . .

RUN make

CMD ["./bin/sismico_solver"]