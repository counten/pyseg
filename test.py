import pyseg

if __name__ == '__main__':
    # s = pyseg.init_seg()

    # customer config and lexicon.
    s = pyseg.init_seg_with_conf("lexicon/config.ini")

    if s == 0:
        print(pyseg.seg("我想听周杰伦的歌"))
        str_in = input(">>")
        while str_in != "quit":
            res = pyseg.seg(str_in)
            print(res)
            str_in = input(">>")
