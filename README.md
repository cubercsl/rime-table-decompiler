# rime-table-decompiler

反编译 Rime 的 ``xxx.table.bin`` 二进制词典文件。

## 简介

本项目 Fork 自 [whjiang/rime_table_bin_decompiler]。

相对于原项目，本项目有以下的更改。

+ 修复了在 Linux 系统上的编译错误
+ 更易读的 README
+ 从 Docker 运行

本项目用于简单的反编译 Rime 的 ``xxx.table.bin`` 二进制词典文件，以生成 ``xxx.dict.yaml`` 源纯文本词典文件。

需要注意的是，由于 ``xxx.table.bin`` 二进制词库文件没有元数据信息，所以生成的 ``xxx.dict.yaml`` 源纯文本词典文件的文件头中的元数据信息是根据常见的元数据信息填补进去的，所以可能是错误的，需自行修正。

[whjiang/rime_table_bin_decompiler]: https://github.com/whjiang/rime_table_bin_decompiler

## 从源代码编译

### 工具链

+ GNU toolchain
+ Boost
+ Marisa
+ CMake

**Debian/Ubuntu** 需要安装 `build-essential`, `cmake`, `libboost-filesystem-dev`, `libmarisa-dev`

**Arch** 需要安装 `base-devel`, `boost`, `cmake`, `marisa`

### 步骤

```bash
cd rime-table-decomplier
mkdir build && cd build
cmake ..
make -j
# make install
```

### 运行

反编译二进制词库并标准输出。

```Bash
rime_table_bin_decompiler xxx.table.bin
```

反编译二进制词库并输出到纯文本词库文件中。

```Bash
rime_table_bin_decompiler xxx.table.bin > xxx.dict.yaml
```
