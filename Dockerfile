FROM gcc:13

WORKDIR /app

COPY build/calculator /app/calculator

CMD ["./calculator"]