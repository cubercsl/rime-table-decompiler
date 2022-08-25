FROM alpine:latest AS builder
LABEL maintainer="cubercsl"
COPY src /root/src
WORKDIR /root/src
RUN apk add --no-cache --virtual .build-dependencies \
    build-base \
    cmake \
    boost-dev \ 
    && mkdir -p build \
    && cd build \
    && cmake .. \ 
    && make -j \
    && ldd rime_table_bin_decompiler \
    && apk del .build-dependencies

FROM alpine:latest
RUN apk add --no-cache libstdc++ libgcc boost-filesystem
COPY --from=builder /root/src/build/rime_table_bin_decompiler rime_table_bin_decompiler
VOLUME [ "/data" ]
ENTRYPOINT ["./rime_table_bin_decompiler"]
