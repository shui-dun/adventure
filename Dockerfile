# 使用ubuntu20.04作为基础镜像
FROM ubuntu:focal as builder

# 安装必要的软件包和库
RUN apt update && \
    apt install -y cmake g++ libncursesw5-dev

WORKDIR /app
COPY . .

# 构建项目
RUN mkdir build && cd build && \
    cmake -DUSE_UNICODE=on .. && \
    cmake --build .

# 使用2阶段构建，减少镜像大小
FROM ubuntu:focal

# 安装运行时依赖
# locales用于设置字符集，防止乱码
# apt clean && rm -rf /var/lib/apt/lists/* 用于清理apt缓存
RUN apt update && \
    apt install -y libncursesw5 locales && \
    apt clean && \
    rm -rf /var/lib/apt/lists/*

# 从构建阶段复制必要的文件
WORKDIR /app
COPY --from=builder /app/build/main ./main

# 设置字符集，防止乱码
RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8

# 设置默认的启动命令
CMD ["./main"]

