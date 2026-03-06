FROM ubuntu:22.04

WORKDIR /app

COPY build/calculator /app/calculator

CMD ["./calculator"]