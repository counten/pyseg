# PySeg
Chinese tokenizer implement with C, and package with python.
c 语言开发的一款开源的高性能中文分词器，使用流行的mmseg算法实现。

## Build and test
```shell script
python3 setup.py build_ext --inplace
python3 test.py
```

### Install
```shell script
python3 setup.py install
```

### TODO 
dist to pypi with wheel(can not pack data file till now).

### About
1. contact me wbq813@foxmail.com or www.codeyourlife.cn
1. The core C implement of this project [friso](https://github.com/lionsoul2014/friso).