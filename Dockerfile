FROM debian:bullseye-slim
RUN apt-get update && apt-get install -y g++ make
WORKDIR /app
COPY . /app
RUN apk add libstdc++
RUN apk add libc6-compat
EXPOSE 8081
CMD ["./HTTPserver"]
