FROM alpine:latest AS builder
LABEL maintainer="cubercsl"
COPY  . /root/src
WORKDIR /root/src
RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.ustc.edu.cn/g' /etc/apk/repositories
RUN apk add --no-cache --virtual .build-dependencies \
    build-base \
    cmake boost-dev libmarisa-dev \ 
    && cmake . -DCMAKE_INSTALL_PREFIX=/usr \ 
    && make -j \
    && make install \
    && ldd /usr/bin/rime_table_bin_decompiler \
    && apk del .build-dependencies

FROM alpine:latest
RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.ustc.edu.cn/g' /etc/apk/repositories
RUN apk add --no-cache libstdc++ libgcc boost-filesystem libmarisa
COPY --from=builder /usr/bin/rime_table_bin_decompiler /usr/bin/rime_table_bin_decompiler
VOLUME [ "/data" ]
ENTRYPOINT ["/usr/bin/rime_table_bin_decompiler"]
