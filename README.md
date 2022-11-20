# What?

![](https://raw.githubusercontent.com/jaseg/lolcat/master/LOLCat-Rainbow.jpg)

## Screenshot

![](https://raw.githubusercontent.com/jaseg/lolcat/master/screenshot.png)

![](./sl.gif)


## I'm Doin' What the fuck I please and making this a phat cat.
## Woo, I figure this base c project is a good place to start.
More to come on the topic of directions... forward.

### THings
- lolcat -> raimbo text
- cowsay -> text bubbles from a cow
- censor -> replace chars with censored versions
- fortune -> get a quote

noscat -> A server 

## Installation

```sh

apk add git make alpine-sdk
apt install build-essentials git make
git clone https://github.com/syonfox/lolcat.git
cd lolcat
make clean ; # remove old bins and clean any shit up
# if nproc isint available was on alpine 3.16
#NUMCORES=`grep ^cpu\\scores /proc/cpuinfo | uniq |  awk '{print $4}'`
make all -j`nproc`; # use all the cores #https://stackoverflow.com/a/17089001/4530300

sudo make install ; # install into system bin folder

cowsay "$(cat README.md)" | lolcat ;


```

## Original c-lolcat Install
### Archlinux

There's an [AUR package](https://aur.archlinux.org/packages/c-lolcat):

```bash
$ git clone https://aur.archlinux.org/packages/c-lolcat
$ cd c-lolcat
$ makepkg -csi
```

### Fedora ###

```bash
$ dnf install lolcat
```

### Ubuntu (Snap)

See [this awesome blog post by a kind person from the internet](https://blog.simos.info/how-to-make-a-snap-package-for-lolcat-with-snapcraft-on-ubuntu/):

```bash
$ snap install lolcat-c
```

### Mac

Build loclcat with:
```
$ make lolcat
```
...and put the resulting binary at a place of your choice.

### Others

```bash
$ make && sudo make install
```

## Why?

This `lolcat` clone is an attempt to reduce the world's carbon dioxide emissions by optimizing inefficient code. It's >10x as fast and <0.1% as large as the original one.

```bash
newton~/d/lolcat <3 dmesg>foo
newton~/d/lolcat <3 time upstream/bin/lolcat foo
13.51user 1.34system 0:15.99elapsed 92%CPU (0avgtext+0avgdata 10864maxresident)k
0inputs+0outputs (0major+1716minor)pagefaults 0swaps
newton~/d/lolcat <3 time ./lolcat foo
0.02user 0.00system 0:00.09elapsed 34%CPU (0avgtext+0avgdata 1936maxresident)k
0inputs+0outputs (0major+117minor)pagefaults 0swaps
```

Bonus comparison with [python-lolcat](https://github.com/tehmaze/lolcat/):
```bash
newton~/d/lolcat <3 dmesg>foo
$ time python-lolcat foo
12.27user 0.00system 0:12.29elapsed 99%CPU (0avgtext+0avgdata 11484maxresident)k
0inputs+0outputs (0major+1627minor)pagefaults 0swaps
$ time c-lolcat foo
0.29user 0.00system 0:00.30elapsed 98%CPU (0avgtext+0avgdata 468maxresident)k
0inputs+0outputs (0major+21minor)pagefaults 0swaps
```

(Read: ```c-lolcat << python-lolcat << ruby-lolcat```)

