FROM debian:bullseye-slim
RUN apt-get update && apt-get install -y g++ make
WORKDIR /app
COPY . /app
EXPOSE 8081
CMD ["./HTTPserver"]