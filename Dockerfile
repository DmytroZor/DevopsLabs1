FROM alpine:latest AS build
RUN apk add --no-cache build-base automake autoconf
WORKDIR /app
COPY . .
RUN autoreconf --install
RUN ./configure
RUN make


FROM alpine:latest
COPY --from=build /app/HTTPserver /usr/local/bin/HTTPserver
ENTRYPOINT ["/usr/local/bin/HTTPserver"]
